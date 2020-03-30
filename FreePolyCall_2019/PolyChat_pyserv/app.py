from flask import Flask, request, session, g, url_for, abort, render_template, make_response, redirect, app, flash
from flask_socketio import SocketIO
from flask_sockets import Sockets
import websockets
import threading
import json
import socket
import random
import math, re, sys
from link_preview import link_preview
#from werkzeug.contrib.cache import MemcachedCache      
#from __init__ import buf
#import uuid
#from flask_caching import Cache
app = Flask(__name__)
app.debug = 1
socketio = SocketIO(app)
sockets = Sockets(app)
application = app
app.secret_key = "super secret key"


@app.route('/', methods=['GET','POST'])
def home():
    if request.method == 'POST':
        ses_id = str(request.form.get('ses_id', ''))
        Email = request.form.get('Email', '')
        Username = request.form.get('name_usr', '')
        if ses_id and Email and Username:
            result = re.search(r'^[a-zA-Zа-яА-Я0-9]{2,20}$', Username)
            if result:
                try:
                    for i in bd[ses_id]:
                        for key,value in i.items():
                            if value == request.cookies.get('Cookie', ''):
                                return redirect(ses_id)
                            elif key == Username:
                                flash("Данный никнейм занят другим пользователем")
                                return render_template('index.html')
                except:
                    pass
                print(Stream)
                try:
                    if Stream[ses_id]:
                        cookie = str(random.randint(1,999999))
                        bd[ses_id].append({Username:cookie})
                        Stream[ses_id].send("%%%" + Username + "$$$") #Отправляем QT стримеру сообщение
                        resp = make_response(redirect(ses_id))
                        resp.set_cookie('Cookie', cookie, max_age=60*60)
                        return resp
                except:
                    pass
            else:
                return render_template('index.html')
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
    print(id_ses)
    return id_ses
    
@app.route('/<int:id_ses>')
def qwe(id_ses):
    temp = None
    id_ses = str(id_ses)
    Cookie = request.cookies.get('Cookie', '')
    try:
        if Stream[id_ses] and Cookie:
            for i in bd[id_ses]:
                for key,value in i.items():
                    if value == Cookie:
                        temp = sn[id_ses]
                        print(sn[id_ses])
                        return render_template('page2.html',temp = temp)
                    else:
                        print("---------------------------------------------------")
                        pass
        else:
            return redirect('/')
        return redirect('/')
    except:
        return redirect('/')

@sockets.route('/<int:id_ses>') #Сокет для Qt приложения
def echo_socket(ws,id_ses):  #Получение сокета
    try:
        ws.send('Pong')
        id_ses = str(id_ses)

        print(bd)
        print(ws) #Проверка сокета
        print(Stream)

        bd.update({id_ses:[]})
        ignor.update({id_ses:[]})
        print(bd)
        print(ws) #Проверка сокета
        Stream.update({id_ses: ws})
        print(Stream)
        while not ws.closed: #Пока есть соединение
            message = ws.receive() #Считываем сообщение от QT
            result = re.search(r'[%]{3}([a-zA-ZА-Яа-я]+)[&]{2}([\S ]+)[$]{3}', message)
            if result:
                users = result.group(2).split('&&')
                if result.group(1) == "MUTE":
                    for user in users:
                        for i in bd[id_ses]:
                            for key,value in i.items():
                                if key == user:
                                    ignor[id_ses].append(key)
                if result.group(1) == "UNMUTE":
                    for user in users:
                        ignor[id_ses].remove(user)
                if result.group(1) == "NAME":
                    sn.update({id_ses:result.group(2)})
            else:
                result = re.findall(r'[^\s]+', message)
                if result:
                    message = " ".join(result)

                    ws.send('Streamer: ' + message) #Отправляем их обратно на QT
                    print('Сообщение - ' + message)
                    dict_elem = link(message)
                    data = {'id': 'streamer','message': message,'title':dict_elem['title'],'website': dict_elem['website'], 'image': dict_elem['image']} #Записываем в Json
                    socketio.emit(id_ses, data) #Пересылаем сообщение от QT в браузер
                    if message == "Disconnect":
                        print("Сокеты стримера")
                        print(Stream) #Проверка пустоты
                        Stream.pop(id_ses)
                        bd.pop(id_ses)
                        sn.pop(id_ses)
                        ws.close() #Qt стример отключился

    except TypeError:
        Stream.pop(id_ses)
        bd.pop(id_ses)
        sn.pop(id_ses)

@socketio.on('my event') #socketio на event'ах
def handle_my_custom_event(json): #Получаем Json
    print(json)
    flag = True
    for i in bd[json['session_id']]:
        for key,value in i.items():
            if value == json['id']:
                test = key
                if ignor[json['session_id']]:
                    for i in ignor[json['session_id']]:
                        if test == i:
                            flag = False
                            
    message = json['message'].encode().decode('utf8','replace').replace('<', '&lt')
    result = re.findall(r'[^\s]+', message)
    if result:
        message = " ".join(result)
        if  flag == True: #Если в Json есть собщение, то

            dict_elem = link(message)

            data = {'id': test,'message': message,'title':dict_elem['title'],'website': dict_elem['website'], 'image': dict_elem['image']} #Заменяем знак '<' на спецсимвол для защиты от html разметки 
            print(json['id'].encode().decode('utf8','replace') + message)
            socketio.emit(json['session_id'], data) #Отправляем сообщение в браузер

            print(json['session_id'])
            print(bd)
            print(ignor)
        if Stream[json['session_id']] and flag == True:   
            Stream[json['session_id']].send(test + ": " + message) #Отправляем QT стримеру сообщение


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
    global Stream,ignor,bd,sn
    Stream = {}
    ignor = {} 
    bd = {}
    sn = {}

    from gevent import pywsgi
    from geventwebsocket.handler import WebSocketHandler
    server = pywsgi.WSGIServer(('0.0.0.0', 5000), app, handler_class=WebSocketHandler) #Настройка сервера
    server.serve_forever() #Запуск сервера