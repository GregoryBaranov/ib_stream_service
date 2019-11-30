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
            print(Dict)
            try:
                if Dict[ses_id]:
                    cookie = str(random.randint(1,999999))
                    bd[ses_id].append({Username:cookie})
                    resp = make_response(redirect(ses_id))
                    resp.set_cookie('Cookie', cookie, max_age=60*60)
                    return resp
            except:
                pass
    return render_template('index.html')

@app.route('/<int:id_ses>')
def qwe(id_ses):
    try:
        if Dict[str(id_ses)]:
            return render_template('page2.html')
    except:
        return redirect('/')

@sockets.route('/<int:id_ses>') #Сокет для Qt приложения
def echo_socket(ws,id_ses):  #Получение сокета
    id_ses = str(id_ses)
    bd.update({id_ses:[]})
    print(bd)
    print(ws) #Проверка сокета
    Dict.update({id_ses: ws})
    print(Dict)
    while not ws.closed: #Пока есть соединение
        message = ws.receive() #Считываем сообщение от QT
        ws.send('Streamer: ' + message) #Отправляем их обратно на QT
        print(message)
        data = {'id': 'streamer','message': message} #Записываем в Json
        socketio.emit(id_ses, data) #Пересылаем сообщение от QT в браузер
        if message == "Disconnect":
            print(Dict) #Проверка пустоты
            Dict.pop(str(id_ses))
            ws.close() #Qt стример отключился


@socketio.on('my event') #socketio на event'ах
def handle_my_custom_event(json): #Получаем Json
    print(json)
    flag = True
    for i in bd[json['session_id']]:
        for key,value in i.items():
            if value == request.cookies.get('Cookie'):
                if ignor:
                    for i in ignor:
                        if 'Алексей' == i:
                            flag = False
                else:
                    flag = True
            else:
                flag = False
            

    if json['message'].encode().decode('utf8','replace').replace('<', '&lt') != "" and flag == True: #Если в Json есть собщение, то
        data = {'id': json['id'].encode().decode('utf8','replace'), #Исправляем кодировку
                'message': json['message'].encode().decode('utf8','replace').replace('<', '&lt')} #Заменяем знак '<' на спецсимвол для защиты от html разметки 
        print(json['id'].encode().decode('utf8','replace') + json['message'].encode().decode('utf8','replace').replace('<', '&lt'))
        socketio.emit(json['session_id'], data) #Отправляем сообщение в браузер
        print(json['session_id'])
    if Dict[json['session_id']] and flag == True:   
        Dict[json['session_id']].send(json['id'].encode().decode('utf8','replace') + json['message'].encode().decode('utf8','replace').replace('<', '&lt')) #Отправляем QT стримеру сообщение
    if json['message'].encode().decode('utf8','replace').replace('<', '&lt') == "test":
        print(bd)
        # for i in range(len(bd[json['session_id']])):
        #     for l in bd[json['session_id']]:
        #         for key,value in l.items():
        #             if key == 'Username':
        #                 bd[json['session_id']].pop(i)
        for i in bd[json['session_id']]:
            for key,value in i.items():
                if key == 'Алексей':
                    ignor.append(key)    

if __name__ == "__main__":
    global Dict
    Dict = {}
    global ignor
    ignor = []
    global bd
    bd = {}

    from gevent import pywsgi
    from geventwebsocket.handler import WebSocketHandler
    server = pywsgi.WSGIServer(('0.0.0.0', 5000), app, handler_class=WebSocketHandler) #Настройка сервера
    server.serve_forever() #Запуск сервера