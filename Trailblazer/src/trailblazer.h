/*
 * CS 106X Trailblazer
 * This file declares the functions you will write in this assignment.
 * 
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 *
 * !!!IF YOU MODIFY THIS FILE, YOU *WILL* LOSE POINTS ON YOUR GRADE!!!
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Marty Stepp, based on past code by Keith Schwarz
 * @version 2015/11/11 by Cynthia Lee for CS106X
 */

#ifndef _trailblazer_h
#define _trailblazer_h

#include "basicgraph.h"
#include "set.h"
#include "vector.h"
#include "Color.h"
#include "queue.h"
#include "pqueue.h"
#include "map.h"

/*
 * The path-searching algorithms you must implement.
 */

Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end);
Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end);
Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end);
Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end);
void depthFirstSearchHelper(Vector<Vertex*>& path, const BasicGraph& graph, Vertex* start, Vertex* end, bool& pathFound);
void constructPath(Vector<Vertex*>& path, Vertex* currVertex);
void addCost(BasicGraph& graph, Vertex* currVertex, Vertex* vert, Vertex* end, PriorityQueue<Vertex*>& pq, Set<Vertex*>& inQueue, bool& isDjikstra);
double currPriority(double cost, Vertex* currVertex, Vertex* end, bool& isDjikstra);
Vector<Vertex*> djikstraAstarHelper(BasicGraph& graph, Vertex* start, Vertex* end, bool isdjikstra);
/*
 * The minimum spanning tree / maze generation algorithm you must implement.
 */
Set<Edge*> kruskal(BasicGraph& graph);

/*
 * Returns a 'heuristic' value, or rough estimation, of the distance between
 * this vertex and the given other vertex.
 * The heuristic function is guaranteed to be an 'admissible heuristic',
 * meaning that it is never an overestimation of the distance.
 * (The word 'extern' means this function is defined elsewhere.
 *  You do not need to worry about it.)
 */
extern double heuristicFunction(Vertex* from, Vertex* to);

#endif

/*
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 * !!! DO NOT MODIFY THIS FILE !!!
 */

