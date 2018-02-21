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
        result = None
        for member in all_members:
            if id == member.id:
                result = member
                break
        return result

    def get_by_name(self, name):
        all_members = self.get_all()
        result = []
        for member in all_members:
            if name == member.name:
                result.append(member)
        return result

    def entity_exists(self, member):
        result = True
        if self.get_by_id(member.id) is None:
            result = False
        return result

    def delete(self, id):
        MemberStore.members.remove(self.get_by_id(id))

    def update(self, member):
        all_members = self.get_all()
        for index, member_to_update in enumerate(all_members):
            if member.id == member_to_update.id:
                self.members[index] = member
                break


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
        result = None
        for post in all_posts:
            if id == post.id:
                result = post
                break
        return result

    def entity_exists(self, post):
        result = True
        if self.get_by_id(post.id) is None:
            result = False
        return result

    def delete(self, id):
        PostStore.posts.remove(self.get_by_id(id))

    def update(self, post):
        all_posts = self.get_all()

        for index, post_to_update in enumerate(all_posts):
            if post.id == post_to_update.id:
                self.posts[index] = post
                break
