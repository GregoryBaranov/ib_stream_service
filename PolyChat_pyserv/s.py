from flask import Flask, render_template, make_response, request
from flask_socketio import SocketIO
from flask_sockets import Sockets
import websockets
import threading
import json
import socket


app = Flask(__name__)
app.config['SECRET_KEY'] = 'vnkdjnfjknfl1232#'
socketio = SocketIO(app)
sockets = Sockets(app)
application = app

def transform(text_file_contents):
    return text_file_contents.replace("=", ",")
@app.route('/transform', methods=["POST"])
def transform_view():
    file = request.files['data_file']
    if not file:
        return "No file"

    file_contents = file.stream.read().decode("utf-8","ignore")

    result = transform(file_contents)

    response = make_response(result)
    response.headers["Content-Disposition"] = "attachment; filename=result.csv"
    return response
	
@app.route('/')
def sessions():
    return render_template('session.html')

def messageReceived(methods=['GET', 'POST']):
    print('message was received!!!')
	
@sockets.route('/')
def echo_socket(ws):
    print(ws)
    list.append(ws)
    while not ws.closed:
        message = ws.receive()
        ws.send(message)
        print(message)
        data = {'id': 'streamer','message': message}
        socketio.emit('my response', data)

        if message == "Disconnect":
            print("=====================================")
            print(list.remove(ws))
            print(list)
            print("=====================================")
            ws.close()
    if ws.closed:
        print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")

		
@socketio.on('my event')
def handle_my_custom_event(json, methods=['GET', 'POST']):
    print(json)
    data = {'id': json['id'].encode().decode('utf8','replace'),'message': json['message'].encode().decode('utf8','replace').replace('<', '&lt')}
    print(json['message'].encode().decode('utf8','replace').replace('<', '&lt'))
    socketio.emit('my response', data, callback=messageReceived)
    print(list)
    print(len(list))
    i = 0
    while i < len(list):
        ws = list[i]
        ws.send(json['message'].encode().decode('utf8','replace').replace('<', '&lt'))
        i = i + 1

if __name__ == "__main__":
    global list
    list = []
    from gevent import pywsgi
    from geventwebsocket.handler import WebSocketHandler
    server = pywsgi.WSGIServer(('0.0.0.0', 5000), app, handler_class=WebSocketHandler)
    server.serve_forever()
