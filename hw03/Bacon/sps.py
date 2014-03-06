from collections import defaultdict
from sklearn.externals import joblib
import redis

def sps(start, goal, successors):
    """
    Generic bidirectional shortest path search
    """

    frontiers = [[[start]], [[goal]]]
    exploreds = [set(), set()]

    while all(frontiers):
        # generic bidirectional breadth first search
        for i, frontier in enumerate(frontiers):    
            path = frontier.pop(0)
            s = path[-1]
            for action, state in successors(s):
                if state not in exploreds[i]:
                    exploreds[i].add(state)
                    new_path = path + [action, state]
                    if state in exploreds[abs(i-1)]:
                        for other_path in frontiers[abs(i-1)]:
                            if other_path[-1] == state:
                                return new_path + other_path[:-1][::-1]
                    else:
                        frontier.append(new_path)
    return False

r = redis.StrictRedis(host='localhost', port=6379, db=0)

def successors(person):
    """
    Generate edges connected to person
    """
    states = []
    visited_people = set()
    for movie in r.smembers(person):
        for new_person in r.smembers(movie):
            if new_person not in visited_people:
                visited_people.add(new_person)
                states.append((movie, new_person))
    return states

    
if __name__ == "__main__":
    print sps('Watson, Emma (II)', 'Khan, Amir (I)', successors)
