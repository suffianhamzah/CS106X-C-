/**
 * File: graphtypes.h
 * ------------------
 * This file defines low-level data structures that represent graphs.
 * You are free to modify this header file to help accomodate the needs to
 * your Stanford 1-2-3 application.
 */

#ifndef _graphtypes_
#define _graphtypes_

#include <string>
#include "gtypes.h"
#include "map.h"
#include "set.h"

struct Node;     /* Forward references to these two types so  */
struct Arc;      /* that the C++ compiler can recognize them. */

/**
 * Type: SimpleGraph
 * -----------------
 * This type represents a graph and consistsyout of a set of nodes, a set of
 * arcs, and a map that creates an association between names and nodes.
 */

struct SimpleGraph {
   Set<Node *> nodes;
   Set<Arc *> arcs;
   Map<std::string, Node *> nodeMap;
};

/**
 * Type: Node
 * ----------
 * This type represents an individual node and consists of the
 * name of the node and the set of arcs from this node.
 */

struct Node {
   std::string name;
   Set<Arc *> arcs;
   Node(std::string n) : name(n) {}
};

/**
 * Type: Arc
 * ---------
 * This type represents an individual arc and consists of pointers
 * to the endpoints, along with the cost of traversing the arc.
 */

struct Arc {
   Node *start;
   Node *finish;
   Arc(Node *s, Node *f) : start(s), finish(f) {}
};

#endif
