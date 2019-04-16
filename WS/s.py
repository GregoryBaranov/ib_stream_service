from flask import Flask, render_template
from flask_socketio import SocketIO
from flask_sockets import Sockets
import websockets
import threading
import json

app = Flask(__name__)
app.config['SECRET_KEY'] = 'vnkdjnfjknfl1232#'
socketio = SocketIO(app)
sockets = Sockets(app)
application = app

data = "hello world"

@app.route('/')
def sessions():
    return render_template('session.html')

def messageReceived(methods=['GET', 'POST']):
    print('message was received!!!')
	
@sockets.route('/')
def echo_socket(ws):
    while not ws.closed:
        print(ws)
        message = ws.receive()
        ws.send(data)
        prin(data)
        ws.send(message)
        print(message)
        data = {'id': 'streamer','message': message}
        socketio.emit('my response', data)
		
@socketio.on('my event')
def handle_my_custom_event(json, methods=['GET', 'POST']):
    print(json)
    data = {'id': json['id'].encode().decode('utf8','replace'),'message': json['message'].encode().decode('utf8','replace').replace('<', '&lt')}
    socketio.emit('my response', data, callback=messageReceived)
	
@app.route('/echo_test', methods=['GET'])
def echo_test():
    return render_template('echo_test.html')

		

if __name__ == "__main__":
    from gevent import pywsgi
    from geventwebsocket.handler import WebSocketHandler
    server = pywsgi.WSGIServer(('0.0.0.0', 5007), app, handler_class=WebSocketHandler)
    server.serve_forever()