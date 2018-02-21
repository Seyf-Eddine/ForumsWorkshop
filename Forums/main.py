import models
import stores

memberStore = stores.MemberStore()
postStore = stores.PostStore()

member1 = models.Member(0, "Seif Eddine", 26)
member2 = models.Member(0, "Mez", 22)
member3 = models.Member(0, "testmember", 20)

post1 = models.Post(0, "post1_title","here is post1 content this is a simple text")
post2 = models.Post(0, "post2_title","here is post2 content this is a simple text")
post3 = models.Post(0, "post3_title","here is post2 content this is a simple text")

memberStore.add(member1)
memberStore.add(member2)

postStore.add(post1)
postStore.add(post2)
postStore.add(post3)

print memberStore.get_by_id(2)

print memberStore.entity_exists(member3)

try:
    memberStore.delete(2)
    memberStore.delete(3)
    postStore.delete(1)
except ValueError:
    print "Can't delete"

for member in memberStore.get_all():
    print member.name + " " + str(member.age)

for post in postStore.get_all():
    print post.title + " " + post.content
