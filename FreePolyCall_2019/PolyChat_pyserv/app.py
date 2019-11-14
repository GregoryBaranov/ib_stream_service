from flask import Flask, request, session, g, url_for, abort, render_template, make_response, redirect, app, flash
from flask_socketio import SocketIO
from flask_sockets import Sockets
import websockets
import threading
import json
import socket

import math, re, sys
#from werkzeug.contrib.cache import MemcachedCache      
#from __init__ import buf
#import redis
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
        ses_id = request.form.get('ses_id', '')
        if ses_id:
            #flash('Пользователь с таким никнеймом уже существует!')
            return redirect('/'+str(ses_id))
    return render_template('index.html')


@app.route('/<int:id_ses>')
def qwe(id_ses):
    return render_template('page2.html')

@sockets.route('/<int:id_ses>') #Сокет для Qt приложения
def echo_socket(ws,id_ses):  #Получение сокета
    print(ws) #Проверка сокета
    Dict.update({str(id_ses): ws})
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
    if json['message'].encode().decode('utf8','replace').replace('<', '&lt') != "": #Если в Json есть собщение, то
        data = {'id': json['id'].encode().decode('utf8','replace'), #Исправляем кодировку
                'message': json['message'].encode().decode('utf8','replace').replace('<', '&lt')} #Заменяем знак '<' на спецсимвол для защиты от html разметки 
        print(json['id'].encode().decode('utf8','replace') + json['message'].encode().decode('utf8','replace').replace('<', '&lt'))
        socketio.emit(json['session_id'], data) #Отправляем сообщение в браузер
        print(json['session_id'])
    if Dict[json['session_id']]:   
        Dict[json['session_id']].send(json['id'].encode().decode('utf8','replace') + json['message'].encode().decode('utf8','replace').replace('<', '&lt')) #Отправляем QT стримеру сообщение

if __name__ == "__main__":
    global Dict
    Dict = {}
    from gevent import pywsgi
    from geventwebsocket.handler import WebSocketHandler
    server = pywsgi.WSGIServer(('0.0.0.0', 5000), app, handler_class=WebSocketHandler) #Настройка сервера
    server.serve_forever() #Запуск сервера