from sklearn.externals import joblib
from collections import defaultdict

actors = joblib.load('actors.jl')
print "Actors loaded"
inverted_actors = joblib.load('actors_inverted.jl')
print "Actors inverted loaded"
actresses = joblib.load('actresses.jl')
print "Actresses loaded"
inverted_actresses = joblib.load('actresses_inverted.jl')
print "Actresses inverted loaded"
both = dict(actors.items() + actresses.items())
print "Dictionaries combined"
joblib.dump(both, "both.jl")

inverted_both = defaultdict(set)
for movie, actors in inverted_actors.items():
    inverted_both[movie] |= actors
for movie, actresses in inverted_actresses.items():
    inverted_both[movie] |= actresses
print "Inverted dictionaries combined"
joblib.dump(inverted_both, "inverted_both.jl")
