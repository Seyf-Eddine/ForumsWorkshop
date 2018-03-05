import dummy_data
import stores

member_store = stores.MemberStore()
post_store = stores.PostStore()

from views import *

if __name__ == "__main__":
    dummy_data.seed_stores(member_store, post_store)
    app.run()
