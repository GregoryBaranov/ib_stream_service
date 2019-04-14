from flask import Flask, request, render_template
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

application = app

a = ""

temp = []


@app.route('/')
def default():
    return render_template("index.html")


@app.route('/sendMessage')
def sendMessage():
    token = request.args.get('token', '')
    ms_text = request.args.get('text', '')
    hash = request.args.get('hash', '')
    global a
    a = request.args.get('text', '')
    temp.append(a)
    return (a)


@app.route('/ismessage')
def ismessage():
    return (a)


if __name__ == '__main__':
    app.Debug = True
    app.run('0.0.0.0', 5007)
