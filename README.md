# AlgoAsgn6
Algorithms Homework 6

//===================================
// Quicker Emails
//===================================

Description:

There are some computers connected by cables (one cable connects 2 computers).
The cables have a latency that is measured in milliseconds required for an email to be sent.
Your goal is to build a program that calculates the shortest time required to send
an email from a computer, S, to a destination computer, T. (HINT: Dijkstra)

Input:
The first line will be the number of cases, N.

Each case starts with a line containing n (number of computers), m (number of connected cables),
S (starting location computer), and T (destination computer). The next 'm' lines contain 3 integers; 2 different computers that are connected by a cable and
the latency, w, of that cable.

Output:
For each case, output "Case #x:" (where 'x' is the current case number) followed by
the number of milliseconds it takes to send an email from S to T. If there is no route
print "unreachable".

Sample Input:
3
2 1 0 1
0 1 100

3 3 2 0
0 1 100
0 2 200
1 2 50

2 0 0 1

Sample Output:
Case #1: 100
Case #2: 150
Case #3: unreachable



*** NOTE ***
Make sure you output EXACTLY WHAT IS DESCRIBED ABOVE!

As always, your program will be named AlgoAsgn6.cpp (or .java).

I will be attaching more test cases for this problem on moodle.
