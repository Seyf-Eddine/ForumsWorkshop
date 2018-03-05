from flask import render_template
import models
import app


@app.route("/")
@app.route("/index")
def home():
    return render_template("index.html", posts=app.post_store.get_all())
