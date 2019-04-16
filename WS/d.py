from flask import Flask, render_template
from flask_socketio import SocketIO

app = Flask(__name__)
app.config['SECRET_KEY'] = 'vnkdjnfjknfl1232#'
socketio = SocketIO(app)


@app.route('/')
def sessions():
    return render_template('session.html')


def messageReceived(methods=['GET', 'POST']):
    print('message was received!!!')


@socketio.on('my event')
def handle_my_custom_event(json, methods=['GET', 'POST']):
#    data = {'message': json['message'].encode('latin1').decode('utf8','replace')}
#    socketio.emit('my response', data, callback=messageReceived)
    
    
    a = str(json.setdefault('message')).encode('latin1','ignore').decode('utf8','replace')
    print(a)
    if a == "None":
        b = dict.fromkeys(['message'], 'Welcome')
    else:
        b = {}
        b = dict.fromkeys(['message'], a)
        print(b)
        socketio.emit('my response', b,  callback=messageReceived)
    
#    a = str(json.keys()).encode('latin1').decode('unicode-escape').encode('latin1').decode('utf8','replace')
#    print(json)
##    b = dict.fromkeys(['data'])
#    b = dict.fromkeys([a])
#    print("это a - " , a)
#    print("это json - " , json)
#    print("это Б - " , b)
    


if __name__ == '__main__':
    socketio.run(app, '0.0.0.0', 5000)