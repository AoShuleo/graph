#include "graph.h"

#include <QDebug>
#include <QStack>


bool Graph::checkCycle(QString vertA, QString vertB)
{
    int iVA = getIndexVertex(vertA);
    int iVB = getIndexVertex(vertB);
    return recCheckVertex(iVA, iVB, iVB);
}

bool Graph::recCheckVertex(int vertex, int prevVertex, int baseVertex)
{
    if(vertex == baseVertex)
        return true;
    foreach (GraphEdge *ge, listEdges) {
        if(ge->vertexA == vertex && ge->vertexB != prevVertex){
            if(recCheckVertex(ge->vertexB,vertex,baseVertex))
                return true;
        }
        else if(ge->vertexB == vertex && ge->vertexA != prevVertex){
            if(recCheckVertex(ge->vertexA,vertex,baseVertex))
                return true;
        }
    }
    return false;
}

void Graph::recCheckConnectivity(GraphEdge *ge, int prevVertex, QVector<GraphEdge*> *vectorE)
{
   // qDebug() << inRec++;

    if(vectorE->length() == listEdges.length())
        return;

    if(vectorE->contains(ge))
        return;
    vectorE->append(ge);



    int vert0;
    int vert1;
    vert0 = ge->vertexA == prevVertex ? ge->vertexB : ge->vertexA;
    vert1 = ge->vertexB == prevVertex ? ge->vertexB : ge->vertexA;

    foreach (GraphEdge *el, listEdges) {
        if(vectorE->length() == listEdges.length())
            return;
        if((el->vertexA == vert0 && el->vertexB != vert1) ||
                (el->vertexB == vert0 && el->vertexA != vert1)){
            recCheckConnectivity(el,vert0,vectorE);
        }
    }

}

Graph::Graph()
{
    inRec = 0;
}

bool Graph::addVertex(QString sVertex)
{
    if(setVertexes.contains(sVertex)){
        return false;
    }
    setVertexes.append(sVertex);
    return true;
}

bool Graph::addEdge(QString vertA, QString vertB, float dist)
{
    GraphEdge *edge = new GraphEdge();
    edge->distance = dist;
    edge->vertexA = setVertexes.indexOf(vertA);
    edge->vertexB = setVertexes.indexOf(vertB);

    GraphEdge *invEdge = new GraphEdge();
    invEdge->vertexA = edge->vertexB;
    invEdge->vertexB = edge->vertexA;

    if(edge->vertexA < 0 || edge->vertexB < 0 ||
            listEdges.indexOf(edge)>=0 || listEdges.indexOf(invEdge) >= 0)
    {
        delete edge;
        delete invEdge;
        return false;
    }
    delete invEdge;

    listEdges.append(edge);
    return true;
}

bool Graph::sortEdges()
{
    qSort(listEdges.begin(),listEdges.end(),[](GraphEdge *a, GraphEdge *b) -> bool
    {
        return a->distance < b->distance;
    });
    return true;
}

Graph Graph::getTree()
{
    Graph newGraph;
    this->sortEdges();

    foreach (GraphEdge *ge, listEdges) {
        int countInter;
        bool bf1 = false;

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
        else
        {
            countInter = 3;
        }

        if(countInter > 2){
            bf1 = newGraph.checkCycle(getVertex(ge->vertexA),getVertex(ge->vertexB));
        }
        else{
            if(countInter == 1 || countInter == 0)
                newGraph.addVertex(setVertexes.at(ge->vertexA));
            if(countInter == 2 || countInter == 0)
                newGraph.addVertex(setVertexes.at(ge->vertexB));
        }
        if(bf1 == false){
            newGraph.addEdge(getVertex(ge->vertexA),getVertex(ge->vertexB),ge->distance);
        }

    }
    return newGraph;
}

int Graph::indexEdge(QString sVertexA, QString sVertexB)
{
    int iA = getIndexVertex(sVertexA);
    int iB = getIndexVertex(sVertexB);
    if(iA < 0 || iB < 0)
        return -1;
    foreach (GraphEdge *eg, listEdges) {
        if((eg->vertexA == iA && eg->vertexB == iB) ||
               (eg->vertexB == iA && eg->vertexA == iB) ){
            return listEdges.indexOf(eg);
        }
    }
    return -1;
}

bool Graph::checkConnectivity()
{
    /*QVector<GraphEdge*> *edgesFromGrap = new QVector<GraphEdge*>();
    GraphEdge *eg = listEdges.at(0);
    recCheckConnectivity(eg, eg->vertexB, edgesFromGrap);
    recCheckConnectivity(eg, eg->vertexA, edgesFromGrap);

    if(edgesFromGrap->length() == listEdges.length()){
        return true;
    }
    else
        return false;
    delete edgesFromGrap;*/
    //GraphEdge *eg = listEdges.at(0);
    QStack<int> stackVertex;
    QVector<int> connVertex;
    int currentVertex = 0, nextVertex = 0;

    stackVertex.push(currentVertex);
    connVertex.append(currentVertex);

    while(stackVertex.length() > 0){
        currentVertex = stackVertex.pop();
        foreach (GraphEdge *el, listEdges) {
            if(el->vertexA == currentVertex){
                nextVertex = el->vertexB;
            }
            else if(el->vertexB == currentVertex){
                nextVertex = el->vertexA;
            }
            if(nextVertex != currentVertex)
                if(!connVertex.contains(nextVertex)){
                    //currentVertex = nextVertex;
                    stackVertex.push(nextVertex);
                    connVertex.append(nextVertex);
                }
                else
                {
                    nextVertex = currentVertex;
                }
        }
    }
    return connVertex.length() == setVertexes.length();

}
