class Member():
    def __init__(self, name, age):
        self.name = name
        self.age = age


class Post():
    def __init__(self, title, content):
        self.title = title
        self.content = content


class MemberStore():
    members = []

    def add(self, member):
        MemberStore.members.append(member)

    def get_all(self):
        for member in MemberStore.members:
            return member


class PostStore():
    posts = []

    def add(self, post):
        PostStore.posts.append(post)

    def get_all(self):
        for post in PostStore.posts:
            return post
