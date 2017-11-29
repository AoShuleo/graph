#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QString>
#include <QHash>
#include <QSet>

#include <graphedge.h>
class Graph
{

private:
    QHash<QString, int> hashVertex;
    QSet<GraphEdge*> setEdges;

    int countVertex;

    void addEdgeByEdge(GraphEdge *eg);
public:
    Graph();
    bool addVertex(QString sVertex); //добавление вершины в граф
    bool addEdge(QString vertA, QString vertB, float dist); //добавление ребра в граф
    QList<GraphEdge *> sortEdges(); //сортировка ребер по их весу/длине
    Graph getTree(); //извлечь минимальное остовное дерево

    QString getVertex(int iVertex){
        return hashVertex.key(iVertex);
    }
    ;
    int getIndexVertex(QString sVertex){
        return hashVertex.value(sVertex, -1);
    }

    GraphEdge* getEdge(QString sVertexA, QString sVertexB);//индекс ребра в массиве ребер

    int getNumberEdge() //количество ребер в графе
    {
        return setEdges.size();
    }

    bool checkConnectivity();

    int inRec;
};

#endif // GRAPH_H
