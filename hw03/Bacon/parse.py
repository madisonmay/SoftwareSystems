from sklearn.externals import joblib
from collections import defaultdict

def invert(string):
    d = joblib.load(string + '.jl')
    print "Loaded"

    inverted = defaultdict(set)
    for k, v in d.items():
        for n in v:
            inverted[n].add(k)

    print "Inverted"
    joblib.dump(inverted, string + "_inverted.jl")

if __name__ == "__main__":
    invert('actors')
    invert('actresses')