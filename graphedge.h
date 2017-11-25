#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H


class GraphEdge
{
public:
    GraphEdge();

    float distance;
    int vertexA;
    int vertexB;

    /*bool operator ==(const GraphEdge &b){
        return (vertexA == b.vertexA && vertexB == b.vertexB) || (vertexA == b.vertexB && vertexB == b.vertexA);
    }*/

    friend bool operator ==(const GraphEdge &a,const GraphEdge &b){
        return (a.vertexA == b.vertexA && a.vertexB == b.vertexB) || (a.vertexA == b.vertexB && a.vertexB == b.vertexA);
    }

    bool operator ==(const GraphEdge &b){
        return (vertexA == b.vertexA && vertexB == b.vertexB) || (vertexA == b.vertexB && vertexB == b.vertexA);
    }


};

#endif // GRAPHEDGE_H
