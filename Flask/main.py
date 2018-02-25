from flask import Flask

app = Flask(__name__)


@app.route("/")
@app.route("/index")
def home():
    return "Hi there"


@app.route("/SayHello/<person>")
def say_hello(person):
    return "Hello %s" % person


app.run()
