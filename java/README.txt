Bombai Java Random Client
-------------------------
This is a basic implementation of a BombAI client in Java that plays the game but doesn't do it very well.

Every round it will figure out which actions are possible based on its location and number of placed bombs. 
It will then randomly (with equal distribution) select one of these actions and execute it.

This client contains infrastructure to communicate with the BombAI game server. It will read the game state 
at the beginning of every round and write your actions at the end of each round.

Getting started
---------------
To improve the existing client you need to provide your own, improved, implementation of the Engine interface.

You can use the RandomEngine as starting point for improvements. To make the client use your gaming engine instead
of RandomEngine change the implementation in method Client.createEngine().

Compilation and execution
-------------------------
To compile the client:
cd <source folder>
javac *.java

To run the client:
java Client

The client will wait for input on stdin formatted according to the BombAI protocol and will print its actions to stdout.

You cannot add packages and subpackages, that will break the build on the server and your client will not be
able to compete.

System requirements/limitations
-------------------------------
- The client will be compiled an run using java version 1.7
- No disk IO allowed
- No network access allowed