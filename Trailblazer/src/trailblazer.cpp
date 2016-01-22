#include "trailblazer.h"
// TODO: include any other headers you need; remove this comment

using namespace std;
/*struct Cluster {
    Set<Vertex*> isExist;
    Set<Vertex*> tree;
    Cluster(Set<Vertex*> t) : tree(t) {}
};*/
class Cluster {
public:
    Cluster() {mysize = 0;}
    ~Cluster();
    int size();
    void merge(Edge* edge);
    void add(Set<Vertex*> vertset);
    bool isDiffCluster(Edge* edge);

private:
    Vector<Set<Vertex*> > tree;
    Map<Vertex*, int> lookup;
    int mysize;
};

int Cluster::size() {
    return mysize;
}

Cluster::~Cluster() {

}

void Cluster::add(Set<Vertex*> vertset) {
    mysize++; // same size with vector index
    tree.add(vertset);
    for (Vertex* v : vertset) {
        lookup.add(v,mysize-1);
    }
}

bool Cluster::isDiffCluster(Edge* edge) {
    return (lookup.get(edge->start) != lookup.get(edge->end));
}

void Cluster::merge(Edge* edge) {
    mysize--;
    Vertex* start = edge->start;
    Vertex* end = edge->end;
    int startIndex;
    int endIndex;
    if (tree[lookup[start]].size() >= tree[lookup[end]].size()) {
        startIndex = lookup[start];
        endIndex = lookup[end];

    } else {
        endIndex = lookup[start];
        startIndex = lookup[end];
    }
    for (Vertex* v : tree[endIndex]) {
        tree[startIndex].add(v);
        lookup[v] = startIndex;
    }
}

Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vector<Vertex*> path;
    bool pathFound = false;
    depthFirstSearchHelper(path, graph, start, end, pathFound);
    return path;
}

Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vector<Vertex*> path;
    Queue<Vertex*> q;
    q.enqueue(start);
    start->visited = true;

    while (!q.isEmpty()) {
        Vertex* currVertex = q.dequeue();
        currVertex->setColor(GREEN);
        if (currVertex == end) {
            constructPath(path, currVertex);
            return path;
        }
        for (Vertex* vert: graph.getNeighbors(currVertex)) {
            if (!vert->visited) {
                vert->visited = true;
                vert->setColor(YELLOW);
                q.enqueue(vert);
                vert->previous = currVertex;
            }
        }
    }
    return path;
}

Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    return djikstraAstarHelper(graph, start, end, true);
}

Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    return djikstraAstarHelper(graph, start, end, false);
}

Set<Edge*> kruskal(BasicGraph& graph) {
    graph.resetData();
    Set<Edge*> mst;
    Set<Edge*> allEdges = graph.getEdgeSet();
    PriorityQueue<Edge*> edgeQueue;
    Cluster clusters;
    for (Edge* edge: allEdges) {
        edgeQueue.enqueue(edge, edge->weight);

    }
    Set<Vertex*> vertices = graph.getVertexSet();
    for (Vertex* v : vertices) {
        Set<Vertex*> vertset;
        vertset.add(v);
        clusters.add(vertset);
    }
    while (clusters.size() > 1) {
        Edge* edge = edgeQueue.dequeue();
        if (clusters.isDiffCluster(edge)) {
            clusters.merge(edge);
            mst.add(edge);
        }
    }
   /* while (!edgeQueue.isEmpty()) {
        Edge* edge = edgeQueue.dequeue();
        bool isStart= visited.contains(edge->start);
        bool isEnd = visited.contains(edge->end);
        if (!isStart || !isEnd) {
            mst.add(edge);
        }

        if (!isStart) {
            visited.add(edge->start);
        }
        if (!isEnd) {
            visited.add(edge->end);
        }

    }*/
    return mst;
}

void depthFirstSearchHelper(Vector<Vertex*>& path, const BasicGraph& graph, Vertex* start, Vertex* end, bool& pathFound) {
    start->visited = true;
    start->setColor(GREEN);
    path.add(start);

    if (start == end) {
        pathFound = true;
        return;
    }

    for (Vertex* vert : graph.getNeighbors(start)) {
        if (!vert->visited) {
            depthFirstSearchHelper(path, graph, vert, end, pathFound);
            if (pathFound) {
                return;
            } else {
                path.remove(path.size()-1);
                vert->setColor(GRAY);
            }
        }
    }
}

void constructPath(Vector<Vertex*>& path, Vertex* currVertex) {
    while (currVertex) {
        path.insert(0,currVertex);
        currVertex = currVertex->previous;
    }
}

Vector<Vertex*> djikstraAstarHelper(BasicGraph& graph, Vertex* start, Vertex* end, bool isdjikstra) {
    graph.resetData();
    PriorityQueue<Vertex*> pq;
    Set<Vertex*> vertexSet = graph.getVertexSet();
    Set<Vertex*> inQueue;
    Vector<Vertex*> path;

    for (Vertex* v: vertexSet) {
        if (!v->visited) {
            v->cost = POSITIVE_INFINITY;
        }
    }
    start->cost = 0;
    double priority = currPriority(start->cost, start, end, isdjikstra);
    pq.enqueue(start, priority);
    inQueue.add(start);

    while (!pq.isEmpty()) {
        Vertex* currVertex = pq.dequeue();
        currVertex->visited = true;
        currVertex->setColor(GREEN);
        if (currVertex == end) {
            constructPath(path, currVertex);
            return path;
        }

        for (Vertex* vert: graph.getNeighbors(currVertex)) {
            if (!vert->visited) {
                addCost(graph, currVertex, vert, end, pq, inQueue, isdjikstra);
            }

        }
    }
    return path;
}

void addCost(BasicGraph& graph, Vertex* currVertex, Vertex* vert, Vertex* end, PriorityQueue<Vertex*>& pq, Set<Vertex*>& inQueue, bool& isDjikstra) {
    double cost = currVertex->cost + graph.getEdge(currVertex,vert)->weight;
    if (cost < vert->cost) {
        vert->cost = cost;
        vert->previous = currVertex;
        vert->setColor(YELLOW);
        double priority = currPriority(cost,vert, end, isDjikstra);
        if (inQueue.contains(vert)) {
            pq.changePriority(vert, priority);
        } else {
            inQueue.add(vert);
            pq.enqueue(vert, priority);
        }
    }
}

double currPriority(double cost, Vertex* currVertex, Vertex* end, bool& isDjikstra) {
    if (!isDjikstra) {
        cost += heuristicFunction(currVertex,end);
    }
    return cost;
}
