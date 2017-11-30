#include "graph.h"

#include <QDebug>
#include <QStack>

#include <dsf.h>


Graph::Graph()
{
    inRec = 0;
    countVertex = 0;
}

bool Graph::addVertex(QString sVertex)
{
    if(!hashVertex.contains(sVertex)){
        hashVertex.insert(sVertex,countVertex);
        ++countVertex;
        return true;
    }
    return false;
}

bool Graph::addEdge(QString vertA, QString vertB, float dist)
{
    GraphEdge *edge = new GraphEdge();
    edge->vertexA = hashVertex.value(vertA);
    edge->vertexB = hashVertex.value(vertB);

    if(!setEdges.contains(edge))
    {
        edge->distance = dist;
        setEdges.insert(edge);
        return true;
    }
    else{
        delete edge;
        return false;
    }
}

QList<GraphEdge *> Graph::sortEdges()
{
    QList<GraphEdge *> listEdges = setEdges.toList();
    std::sort(listEdges.begin(),listEdges.end(),[](GraphEdge *a, GraphEdge *b) -> bool
    {
        return a->distance < b->distance;
    });
    return listEdges;
}

Graph Graph::getTree()
{
    Graph newGraph;

    DSF dsf(countVertex+1);

    int countInter = 3;
    foreach (GraphEdge *ge, this->sortEdges())
    {
        if(dsf.unionM(ge->vertexA,ge->vertexB))
        {

            if(newGraph.getIndexVertex(getVertex(ge->vertexA)) < 0 &&
                    newGraph.getIndexVertex(getVertex(ge->vertexB)) < 0)
            {
                countInter = 0;
            }
            else if(newGraph.getIndexVertex(getVertex(ge->vertexA)) < 0)
            {
                countInter = 1;
            }
            else if(newGraph.getIndexVertex(getVertex(ge->vertexB)) < 0)
            {
                countInter = 2;
            }

            if(countInter == 1 || countInter == 0)
                newGraph.addVertex(hashVertex.key(ge->vertexA));
            if(countInter == 2 || countInter == 0)
                newGraph.addVertex(hashVertex.key(ge->vertexB));

            newGraph.addEdge(getVertex(ge->vertexA),getVertex(ge->vertexB),ge->distance);

            countInter = 3;
        }
    }
    return newGraph;
}

GraphEdge *Graph::getEdge(QString sVertexA, QString sVertexB)
{
    int iA = getIndexVertex(sVertexA);
    int iB = getIndexVertex(sVertexB);
    if(iA < 0 || iB < 0)
        return nullptr;
    foreach (GraphEdge *eg, setEdges) {
        if((eg->vertexA == iA && eg->vertexB == iB) ||
               (eg->vertexB == iA && eg->vertexA == iB) ){
            return eg;
        }
    }
    return nullptr;
}

bool Graph::checkConnectivity()
{
    /*QStack<int> stackVertex;
    QSet<int> connVertex;
    int currentVertex = 0, nextVertex = 0;

    stackVertex.push(currentVertex);

    connVertex.reserve(countVertex+1);
    connVertex.insert(currentVertex);

    QList<GraphEdge *> listEdges = setEdges.toList();
    while(stackVertex.length() > 0){
        currentVertex = stackVertex.pop();
        foreach (GraphEdge *el, listEdges)
        {
            if(el->vertexA == currentVertex){
                nextVertex = el->vertexB;
            }
            else if(el->vertexB == currentVertex){
                nextVertex = el->vertexA;
            }

            if(nextVertex != currentVertex)
            {
                if(!connVertex.contains(nextVertex)){
                    //currentVertex = nextVertex;
                    stackVertex.push(nextVertex);
                    connVertex.insert(nextVertex);
                }
                else
                {
                    nextVertex = currentVertex;
                }
            }
        }
    }
    return connVertex.size() == countVertex;*/



}
