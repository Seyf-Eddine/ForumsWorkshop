import models
import stores

memberStore = stores.MemberStore()
postStore = stores.PostStore()


def create_members():
    member1 = models.Member("Seif Eddine", 26)
    member2 = models.Member("Mez", 22)
    member3 = models.Member("testmember", 20)
    print(member1)
    print(member2)
    print(member3)
    print("=" * 30)

    return member1, member2, member3


def store_should_add_models(members_instances, member_store):
    for member in members_instances:
        member_store.add(member)


def stores_should_be_similar():
    member_store1 = stores.MemberStore()
    member_store2 = stores.MemberStore()
    if member_store1.get_all() is member_store2.get_all():
        print("Same stores elements !")


def print_all_members(member_store):
    print("=" * 30)

    for member in member_store.get_all():
        print(member)

    print("=" * 30)


def get_by_id_should_retrieve_same_object(member_store, member2):
    member2_retrieved = member_store.get_by_id(member2.id)

    if member2 is member2_retrieved:
        print("member2 and member2_retrieved are matching !")


def update_should_modify_object(member_store, member3):
    member3_copy = models.Member(member3.name, member3.age)
    member3_copy.id = 3

    if member3_copy is not member3:
        print("member3 and member3_copy are not the same !")

    print(member3_copy)
    member3_copy.name = "john"
    member_store.update(member3_copy)
    print(member_store.get_by_id(member3.id))


def catch_exception_when_deleting():
    try:
        member_store.delete(5)
    except ValueError:
        print("It should be an existence entity before deleting !")


################################################################################

def create_posts():
    post1 = models.Post("Post_1","Post_1 Content")
    post2 = models.Post("Post_2","Post_2 Content")
    post3 = models.Post("Post_3","Post_3 Content")
    print(post1)
    print(post2)
    print(post3)
    print("=" * 30)

    return post1, post2, post3


def post_store_should_add_models(posts_instances, post_store):
    for post in posts_instances:
        post_store.add(post)


def post_stores_should_be_similar():
    post_store1 = stores.PostStore()
    post_store2 = stores.PostStore()
    if post_store1.get_all() is post_store2.get_all():
        print("Same stores elements !")


def print_all_posts(post_store):
    print("=" * 30)

    for post in post_store.get_all():
        print(post)

    print("=" * 30)


def post_get_by_id_should_retrieve_same_object(post_store, post2):
    post2_retrieved = post_store.get_by_id(post2.id)

    if post2 is post2_retrieved:
        print("post2 and post2_retrieved are matching !")


def post_update_should_modify_object(post_store, post3):
    post3_copy = models.Post(post3.title, post3.content)
    post3_copy.id = 3

    if post3_copy is not post3:
        print("post3 and post3_copy are not the same !")

    print(post3_copy)
    post3_copy.title = "post_3 New title"
    post_store.update(post3_copy)
    print(post_store.get_by_id(post3.id))


def post_catch_exception_when_deleting():
    try:
        post_store.delete(5)
    except ValueError:
        print("It should be an existence entity before deleting !")


################################################################################

members_instances = create_members()
member1, member2, member3 = members_instances

member_store = stores.MemberStore()

store_should_add_models(members_instances, member_store)

stores_should_be_similar()

print_all_members(member_store)

get_by_id_should_retrieve_same_object(member_store, member2)

update_should_modify_object(member_store, member3)

catch_exception_when_deleting()

print_all_members(member_store)


################################################################################


posts_instances = create_posts()
post1, post2, post3 = posts_instances

post_store = stores.PostStore()

post_store_should_add_models(posts_instances, post_store)

post_stores_should_be_similar()

print_all_posts(post_store)

post_get_by_id_should_retrieve_same_object(post_store, post2)

post_update_should_modify_object(post_store, post3)

post_catch_exception_when_deleting()

print_all_posts(post_store)
