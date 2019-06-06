from flask import Flask, render_template, make_response, request
from flask_socketio import SocketIO
from flask_sockets import Sockets
import websockets
import threading
import json
import socket


app = Flask(__name__)
socketio = SocketIO(app)
sockets = Sockets(app)
application = app

@app.route('/')
def sessions():
    return render_template('session.html') #Возврат страницы чата при переходе на сайт 

@sockets.route('/') #Сокет для Qt приложения
def echo_socket(ws):  #Получение сокета
    print(ws)
    while not ws.closed: #Пока есть соединение
        message = ws.receive() #Считываем сообщение от QT
        ws.send('streamer:' + message) #Отправляем их обратно на QT
        print(message)
        data = {'id': 'streamer','message': message} #Записываем в Json
        socketio.emit('my response', data) #Пересылаем сообщение от QT в браузер
        streamer = ws #Записываем сокет в глобальную переменную для отправки с браузера
        if message == "Disconnect":
            ws.close() #Qt стример отключился


@socketio.on('my event') #socketio на event'ах
def handle_my_custom_event(json): #Получаем Json
    print(json)
    if json['message'].encode().decode('utf8','replace').replace('<', '&lt') != "": #Если в Json есть собщение, то
        data = {'id': json['id'].encode().decode('utf8','replace'), #Исправляем кодировку
                'message': json['message'].encode().decode('utf8','replace').replace('<', '&lt')} #Заменяем знак '<' на спецсимвол для защиты от html разметки 
        print(json['message'].encode().decode('utf8','replace').replace('<', '&lt'))
        socketio.emit('my response', data) #Отправляем сообщение в браузер
    if streamer != "": #Если есть QT стример, то
        streamer.send(json['message'].encode().decode('utf8','replace').replace('<', '&lt')) #Отправляем QT стримеру сообщение

if __name__ == "__main__":
    global streamer #Глобальная переменная стримера
    streamer = ""
    from gevent import pywsgi
    from geventwebsocket.handler import WebSocketHandler
    server = pywsgi.WSGIServer(('0.0.0.0', 5000), app, handler_class=WebSocketHandler) #Настройка сервера
    server.serve_forever() #Запуск сервера
