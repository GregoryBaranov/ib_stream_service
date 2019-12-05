from flask import Flask, request, session, g, url_for, abort, render_template, make_response, redirect, app, flash
from flask_socketio import SocketIO
from flask_sockets import Sockets
import websockets
import threading
import json
import socket
import random

import math, re, sys
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


# arr = ""
#     for key in red1.keys():
#         arr += "#{}${}&&".format(key.decode('utf8','replace'), red1.get(key).decode('utf8','replace'))


@app.route('/', methods=['GET','POST'])
def home():
    if request.method == 'POST':
        ses_id = str(request.form.get('ses_id', ''))
        Email = request.form.get('Email', '')
        Username = request.form.get('name_usr', '')
        if ses_id and Email and Username:
            try:
                for i in bd[ses_id]:
                    for key,value in i.items():
                        if key == Username:
                            flash("Ник занят")
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
    return render_template('index.html')

@app.route('/<int:id_ses>')
def qwe(id_ses):
    try:
        if Stream[str(id_ses)]:
            return render_template('page2.html')
    except:
        return redirect('/')

@sockets.route('/<int:id_ses>') #Сокет для Qt приложения
def echo_socket(ws,id_ses):  #Получение сокета
    ws.send('Pong')
    id_ses = str(id_ses)
    # bd.update({id_ses:[]})
    print(bd)
    print(ws) #Проверка сокета
    print(Stream)
    flag = True
    for i in bd:
        if i == id_ses:
            print('++++++++++++++')
            ws.send('Сессия "' + id_ses +'" в данный момент занята!')
            flag = False
    if flag == True:
        print('=============')
        bd.update({id_ses:[]})
        ignor.update({id_ses:[]})
        print(bd)
        print(ws) #Проверка сокета
        Stream.update({id_ses: ws})
        print(Stream)
        while not ws.closed: #Пока есть соединение
            message = ws.receive() #Считываем сообщение от QT
            result = re.search(r'[%]{3}([a-zA-ZА-Яа-я]+)[&]{2}([\S]+)[$]{3}', message)
            if result:
                if result.group(1) == "MUTE":
                    print('-'*32)
                    print(result.group(2))
                    print('-'*32)
                    for i in bd[id_ses]:
                        for key,value in i.items():
                            if key == result.group(2):
                                ignor[id_ses].append(key)
                if result.group(1) == "UNMUTE":
                    ignor[id_ses].remove(result.group(2))
            else:
                ws.send('Streamer: ' + message) #Отправляем их обратно на QT
                print(message)
                data = {'id': 'streamer','message': message} #Записываем в Json
                socketio.emit(id_ses, data) #Пересылаем сообщение от QT в браузер
                if message == "Disconnect":
                    print("Сокеты стримера")
                    print(Stream) #Проверка пустоты
                    Stream.pop(id_ses)
                    bd.pop(id_ses)
                    ws.close() #Qt стример отключился


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

    if json['message'].encode().decode('utf8','replace').replace('<', '&lt') != "" and flag == True: #Если в Json есть собщение, то
        data = {'id': test,'message': json['message'].encode().decode('utf8','replace').replace('<', '&lt')} #Заменяем знак '<' на спецсимвол для защиты от html разметки 
        print(json['id'].encode().decode('utf8','replace') + json['message'].encode().decode('utf8','replace').replace('<', '&lt'))
        socketio.emit(json['session_id'], data) #Отправляем сообщение в браузер
        print(json['session_id'])
        print(bd)
        print(ignor)
    if Stream[json['session_id']] and flag == True:   
        Stream[json['session_id']].send(test + ": " + json['message'].encode().decode('utf8','replace').replace('<', '&lt')) #Отправляем QT стримеру сообщение

if __name__ == "__main__":
    global Stream,ignor,bd
    Stream = {}
    ignor = {}
    bd = {}

    from gevent import pywsgi
    from geventwebsocket.handler import WebSocketHandler
    server = pywsgi.WSGIServer(('0.0.0.0', 5000), app, handler_class=WebSocketHandler) #Настройка сервера
    server.serve_forever() #Запуск сервера