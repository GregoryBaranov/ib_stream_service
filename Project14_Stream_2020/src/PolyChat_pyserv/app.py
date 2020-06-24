from flask import Flask, request, session, g, url_for, abort, render_template, make_response, redirect, app, flash
from flask_socketio import SocketIO
from flask_sockets import Sockets
import websockets
import threading
import json
import socket
import random
import math, re, sys
import sqlite3
from sqlite3 import Error
from link_preview import link_preview
app = Flask(__name__)
app.debug = 1
socketio = SocketIO(app)
sockets = Sockets(app)
application = app
app.secret_key = "super secret key"

def create_table(conn, create_table_sql):
    try:
        c = conn.cursor()
        c.execute(create_table_sql)
    except Error as e:
        print(e)

def create_connection():
    global conn
    conn = None
    try: 
        conn = sqlite3.connect(':memory:')
        print("Версия sqlite - " + sqlite3.version)
        if conn is not None:
            sql_create_session_table = """ CREATE TABLE IF NOT EXISTS Session (
                                        id integer PRIMARY KEY,
                                        name_stream text,
                                        socket text,
                                        session integer
                                    ); """
            sql_create_users_table = """CREATE TABLE IF NOT EXISTS Users (
                                    id integer PRIMARY KEY,
                                    username text NOT NULL,
                                    cookie integer NOT NULL,
                                    status_ban bool NOT NULL,
                                    status_activity bool NOT NULL,
                                    id_session integer NOT NULL,
                                    FOREIGN KEY (id_session) REFERENCES Session (session) 
                                    ON DELETE cascade
                                );"""
            create_table(conn, sql_create_session_table)
            create_table(conn, sql_create_users_table)
        else:
            print("Error! cannot create the database connection.")
    except Error as e:
        print(e)
    print("Сервер успешно запущен!")

@app.route('/', methods=['GET','POST'])
def home():
    if request.method == 'POST':
        ses_id = str(request.form.get('ses_id', ''))
        Email = request.form.get('Email', '')
        Username = request.form.get('name_usr', '')
        if ses_id and Email and Username:
            result = re.search(r'^[a-zA-Zа-яА-Я0-9]{2,20}$', Username)
            if result:
                cookie = request.cookies.get('Cookie', '')
                if cookie:
                    sql = ''' SELECT cookie, username  FROM Users WHERE cookie = ? and username = ? and id_session = ?''' 
                    task = (int(cookie),Username,int(ses_id))
                    cur = conn.cursor()
                    cu = cur.execute(sql,task)
                    if cu:
                        for i in cu:
                            print(i)
                            if i[0]:
                                return redirect(ses_id)

                sql = ''' SELECT username  FROM Users WHERE username = ? and id_session = ?''' 
                task = (Username,int(ses_id))
                cur = conn.cursor()
                cu = cur.execute(sql,task)
                if cu:
                    for i in cu:
                        print(i)
                        if i[0]:
                            flash("Данный никнейм занят другим пользователем")
                            return render_template('index.html',ses_id = ses_id)
                
                if cookie:
                    sql = ''' SELECT username FROM Users WHERE cookie = ? and id_session = ?''' 
                    task = (int(cookie),int(ses_id))
                    cur = conn.cursor()
                    cu = cur.execute(sql,task)
                    if cu:
                        for i in cu:
                            print(i)
                            if i[0]:
                                flash("          Вы уже есть в этой сессии!")
                                flash("          Ваш Username - " + i[0])
                                return render_template('index.html',ses_id = ses_id, Username = i[0])


                sql = '''SELECT socket FROM Session WHERE session = ?'''
                task =(int(ses_id))
                cur = conn.cursor()
                print('='*32)
                for ws in cur.execute(sql,(task,)):
                    if ws[0]:
                        cookie = str(random.randint(1,999999))
                        
                        sql = ''' INSERT INTO Users(username,cookie,status_ban,status_activity,id_session) VALUES(?,?,?,?,?)''' 
                        task = (Username,int(cookie),0,0,ses_id)
                        cur = conn.cursor()
                        cur.execute(sql,task)

                        ###################################
                        sql = '''SELECT * FROM Users'''
                        cur = conn.cursor()
                        print('+'*32)
                        for i in cur.execute(sql):
                            print(i)
                        print('+'*32)

                        #ДОДЕЛАТЬ WS
                        ####################################

                        Stream[ses_id].send("%%%" + Username + "$$$") #Отправляем QT стримеру сообщение

                        resp = make_response(redirect(ses_id))
                        resp.set_cookie('Cookie', cookie, max_age=60*60)
                        return resp
                    else:
                        flash("Данной сессии не существует!")
                        return render_template('index.html',Username = Username)
            else:
                flash("Username не подходит условиям")
                return render_template('index.html',ses_id = ses_id)
    return render_template('index.html')

@app.route('/id_ses') #Выдача сессии
def ransddom():
    while True:
        id_ses = str(random.randint(10000,99999))
        if not Stream:
            break
        else:
            try:
                if Stream[id_ses]:
                    pass
            except:
                break
        if len(Stream.values()) == 90000:
            id_ses = 'සෑම දෙයක්ම තඹ බේසමකින් ආවරණය විය'
            break
    print("Выдан - " + id_ses)
    return id_ses
    
@app.route('/<int:id_ses>')
def qwe(id_ses):
    temp = None
    _id_ses = id_ses
    id_ses = str(id_ses)
    Cookie = request.cookies.get('Cookie', '')
    try:
        if Stream[id_ses] and Cookie:
            sql = ''' SELECT name_stream FROM Session JOIN Users ON Session.session = Users.id_session WHERE cookie = ? and id_session = ?''' 
            task = (Cookie,_id_ses)
            cur = conn.cursor()
            name_stream = cur.execute(sql,task)
            if name_stream:
                for i in name_stream:
                    temp = str(i[0])
                    print(temp)
                return render_template('page2.html',temp = temp)
            else:
                return redirect('/')
        else:
            return redirect('/')
    except:
        return redirect('/')

def delete_session(_id_ses):
    sql = ''' DELETE FROM Session WHERE session = ?''' 
    task = (_id_ses)
    cur = conn.cursor()
    cur.execute(sql,(task,))
    conn.commit()


@sockets.route('/<int:id_ses>') #Сокет для Qt приложения
def echo_socket(ws,id_ses):  #Получение сокета
    try:
        Stream.update({str(id_ses): ws})
        ws.send('Pong')
        sql = ''' INSERT INTO Session(name_stream,socket,session) VALUES(?,?,?)''' 
        task = (None,str(ws),id_ses)
        cur = conn.cursor()
        cur.execute(sql,task)
    
        ####################################
        sql = '''SELECT * FROM Session'''
        cur = conn.cursor()
        print('+'*32)
        for i in cur.execute(sql):
            print(i)
        print('+'*32)
        ####################################

        while not ws.closed: #Пока есть соединение
            message = ws.receive() #Считываем сообщение от QT
            result = re.search(r'[%]{3}([a-zA-ZА-Яа-я]+)[&]{2}([\S ]+)[$]{3}', message)
            if result:
                users = result.group(2).split('&&')
                if result.group(1) == "MUTE":
                    for user in users:
                        sql = ''' Update Users SET status_ban = '1' WHERE username = ? and id_session = ?''' 
                        task = (user,id_ses)
                        cur = conn.cursor()
                        cur.execute(sql,task)
                if result.group(1) == "UNMUTE":
                    for user in users:
                        sql = ''' Update Users SET status_ban = '0' WHERE username = ? and id_session = ?''' 
                        task = (user,id_ses)
                        cur = conn.cursor()
                        cur.execute(sql,task)
                if result.group(1) == "NAME":
                    name_stream = str(result.group(2))
                    sql = ''' Update Session SET name_stream = ? WHERE session = ?''' 
                    task = (name_stream,id_ses)
                    cur = conn.cursor()
                    cur.execute(sql,task)
            else:
                result = re.findall(r'[^\s]+', message)
                if result:
                    message = " ".join(result)
                    ws.send('Streamer: ' + message) #Отправляем их обратно на QT
                    print('Сообщение - ' + message)
                    dict_elem = link(message)
                    data = {'id': 'streamer','message': message,'title':dict_elem['title'],'website': dict_elem['website'], 'image': dict_elem['image']} #Записываем в Json
                    socketio.emit(str(id_ses), data) #Пересылаем сообщение от QT в браузер
                    if message == "Disconnect":
                        delete_session(str(id_ses))
                        Stream.pop(str(id_ses))
                        ws.close() #Qt стример отключился

    except TypeError:
        Stream.pop(str(id_ses))
        delete_session(id_ses)

@socketio.on('my event') #socketio на event'ах
def handle_my_custom_event(json): #Получаем Json
    flag = None
    sql = ''' SELECT username FROM Users WHERE status_ban = ? and id_session = ? and cookie = ?''' 
    task = (0,int(json['session_id']),int(json['id']))
    cur = conn.cursor()
    usn = cur.execute(sql,task)
    for i in usn:
        test = i[0]
        if test:
            flag = True
        else:
            flag = False

    message = json['message'].encode().decode('utf8','replace').replace('<', '&lt')
    result = re.findall(r'[^\s]+', message)
    if result:
        print(json)
        message = " ".join(result)
        if  flag == True: #Если в Json есть собщение, то
            dict_elem = link(message)
            data = {'id': test,'message': message,'title':dict_elem['title'],'website': dict_elem['website'], 'image': dict_elem['image']} #Заменяем знак '<' на спецсимвол для защиты от html разметки
            socketio.emit(json['session_id'], data) #Отправляем сообщение в браузер
        try:
            if Stream[json['session_id']] and flag == True:  
                Stream[json['session_id']].send(test + ": " + message) #Отправляем QT стримеру сообщение
        except:
            pass


def link(msg):
    dict_elem = {'title': '','website': '', 'image': ''}
    try:
        result = re.search(r'(https?:\/\/)?([0-9a-z.-]+\.)([a-z]{2,6})(([\/a-zA-Z0-9_.-]*)*\/?[\S]*)', msg)
        if result:
            if not result.group(1):
                dict_elem = link_preview.generate_dict('http://' + result.group(0)) # this is a dict()
                dict_elem['website'] = result.group(0)
            else:
                dict_elem = link_preview.generate_dict(result.group(0))
                dict_elem['website'] = result.group(2) + result.group(3) + result.group(4)
        return dict_elem
    except:
        return dict_elem

if __name__ == "__main__":
    create_connection()

    global Stream
    Stream = {}

    from gevent import pywsgi
    from geventwebsocket.handler import WebSocketHandler
    server = pywsgi.WSGIServer(('0.0.0.0', 5000), app, handler_class=WebSocketHandler) #Настройка сервера
    server.serve_forever() #Запуск сервера