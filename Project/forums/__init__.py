from flask import Flask
from forums.stores import MemberStore, PostStore
from forums.dummy_data import seed_stores

member_store = MemberStore()
post_store = PostStore()

app = Flask(__name__)

from forums.views import *

if __name__ == "__main__":
    seed_stores(member_store, post_store)
    app.run()
