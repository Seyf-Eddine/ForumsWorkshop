class MemberStore():
    members = []
    last_id = 1

    def add(self, member):
        member.id = MemberStore.last_id
        MemberStore.members.append(member)
        MemberStore.last_id += 1

    def get_all(self):
        return MemberStore.members

    def get_by_id(self, id):
        all_members = self.get_all()
        for member in all_members:
            if id == member.id:
                return member

    def entity_exists(self, member):
        result = True
        if self.get_by_id(member.id) is None:
            result = False
        return result

    def delete(self, id):
        member = self.get_by_id(id)
        if member is not None:
            MemberStore.members.remove(member)


class PostStore():
    posts = []
    last_id = 1

    def add(self, post):
        post.id = PostStore.last_id
        PostStore.posts.append(post)
        PostStore.last_id += 1

    def get_all(self):
        return PostStore.posts

    def get_by_id(self, id):
        all_posts = self.get_all()
        for post in all_posts:
            if id == post.id:
                return post

    def delete(self, id):
        post = self.get_by_id(id)
        if post is not None:
            PostStore.posts.remove(post)
