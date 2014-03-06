SoftSysDB
=========

Homework 03 -- Experiment with Redis

Setup
-----

Parse imdb compressed files and dump into .jl files
```
python imdb.py
```

Generate intermediate representation and save as .jl files
```
python parse.py && python merge.py
```

Dump final representation into redis
```
python redis_save.py
```

Run a python version of the bidirectional shortest path search algorithm.
The file can be edited to find the path between different actor pairs.
```
python sps.py
```

Compile C file that demonstrates basic C functionality
```
gcc sps.c -o sps -I hiredis -L hiredis -lhiredis -lm
```

Run the demo C file and find actors/actresses 1 edge away from a given actor/actress
```
./sps
```

Implementation
--------------
We (Madison and Ankeet) worked together to write a series of programs that would access a Redis database to show how an actor was connected to any other actor through a series of movies. 

First we located a program written by Allen Downey that would deal with the odd text file dump of actors and actresses and allow us to convert it into Python dictionaries we could work with more easily. 

Then we split our data up into two dictionaries: one which mapped from actors to movies, and one which mapped from movies to actors. Next, we wrote a search program that implemented a bidirectional breadth first search using both actors that compared the two leaves of the path trees we generated and searched for a set intersection. Although the search itself was efficient, simply loading the two large dictionaries into memory was time intensive.

We then stored the two dictionaries on Redis and wrote the interface to access them using the python program. Lastly, we created a demo C interface that would take an actor and list all the actors related to him.

Installation
------------
The redis server we used was free, easy to install and under the three clause BSD license.  Installation was only a matter of a simple `wget`, `tar xzvf`, and `make`.  

Immersion
---------
It was pretty easy to start and fairly easy to find good example code and documentation. 
We were able to start using the database for what we wanted in about half an hour. All in all, the first time user experience was pleasant.  Redis is very basic in the sense that it’s not a relational database, its merely a key value store, and that fact made use quite easy.

Semantics
----------
The system handled all the queries we want it to pretty efficiently. We decided to preprocess all the data into a set that maps all movies to actors and all actors to movies. The database has a set type that allowed us to easily store data in an data structure optimized for our situation.  

Performance
-----------
The python program that we wrote allows us to send a query and get a response in under a second even when there were 6 connections between the two actors/actresses. The current system should be pretty scalable since Redis has synchronous and asynchronous options. For further optimization at the cost of additional space, we could precompute all the paths between actors and dump a hashmap into Redis. We could also exponentiate matrices to easily compute the number of links between two actors and start using a depth search which could possibly be faster but our current algorithm is already pretty fast. 

ACIDity
-------
Redis sacrifices a bit of data integrity in return for blazing speed, although there are configuration options that can adjust this trade-off to produce a more stable data store.  If data consistency is critical, redis can even add redundancy to the data store using a master-slave replication mechanism. Atomicity, consistency, and isolation are guaranteed by default, and durability is guaranteed with the proper append-only file (AOF) settings.




