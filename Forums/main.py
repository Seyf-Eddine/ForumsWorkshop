import models
import stores

memberStore = stores.MemberStore()
postStore = stores.PostStore()

member1 = models.Member("Seif Eddine", 26)
member2 = models.Member("Mez", 22)

post1 = models.Post("post1_title","here is post1 content this is a simple text")
post2 = models.Post("post2_title","here is post2 content this is a simple text")
post3 = models.Post("post3_title","here is post2 content this is a simple text")

memberStore.add(member1)
memberStore.add(member2)

postStore.add(post1)
postStore.add(post2)
postStore.add(post3)

for member in memberStore.get_all():
    print member.name + " " + str(member.age)

for post in postStore.get_all():
    print post.title + " " + post.content
