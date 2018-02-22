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

    def get_by_name(self, member_name):
        return (member for member in self.get_all() if member.name == member_name)

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

    def get_members_with_posts(self, all_posts):
        all_members = self.get_all()
        result = []
        for member in all_members:
            for post in all_posts:
                if member.id == post.member_id:
                    member.posts.append(post)
            result.append(member)
        return result

    def get_top_two(self, all_posts):
        members_with_posts = self.get_members_with_posts(all_posts)
        sorted_members = sorted(members_with_posts, key=lambda x: len(x.posts), reverse=True)
        return sorted_members[:2]


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
