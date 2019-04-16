from flask import Flask, render_template
from flask_socketio import SocketIO


app = Flask(__name__)
app.config['SECRET_KEY'] = 'vnkdjnfjknfl1232#'
socketio = SocketIO(app)
application = app


@app.route('/')
def sessions():
    return render_template('session.html')
	
def messageReceived(methods=['GET', 'POST']):
    print('message was received!!!')


@socketio.on('my event')
def handle_my_custom_event(json, methods=['GET', 'POST']):
    print(json)
    data = {'id': json['id'].encode().decode('utf8','replace'),'message': json['message'].encode().decode('utf8','replace').replace('<', '&lt')}
    socketio.emit('my response', data, callback=messageReceived)
	
		
if __name__ == "__main__":
    socketio.run(app,'0.0.0.0',5000)
	
	
	
	if __name__ == "__main__":
    socketio.run(app,'0.0.0.0',5000)
	
    asyncio.get_event_loop().run_until_complete(
        websockets.serve(echo, '0.0.0.0',5000))
    asyncio.get_event_loop().run_forever()