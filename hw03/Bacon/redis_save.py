from sklearn.externals import joblib
import redis

r = redis.StrictRedis(host='localhost', port=6379, db=0)

full = joblib.load('both.jl')
print "File loaded."

for person, movies in full.items():
    for movie in movies:
        r.sadd(person, movie)
        r.sadd(movie, person)