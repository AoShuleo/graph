#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QList>
#include <QVector>
#include <QString>
#include <graphedge.h>
class Graph
{

private:
    QList<GraphEdge*> listEdges;
    QVector<QString> setVertexes;

    void addEdgeByEdge(GraphEdge *eg);
    bool checkCycle(QString vertA, QString vertB);
    bool recCheckVertex(int vertex, int prevVertex, int baseVertex);
    void recCheckConnectivity(GraphEdge *ge, int prevVertex, QVector<GraphEdge*>*vectorE);
public:
    Graph();
    bool addVertex(QString sVertex); //добавление вершины в граф
    bool addEdge(QString vertA, QString vertB, float dist); //добавление ребра в граф
    bool sortEdges(); //сортировка ребер по их весу/длине
    Graph getTree(); //извлечь минимальное остовное дерево

    QString getVertex(int iVertex){
        return setVertexes.at(iVertex);
    }
    int getIndexVertex(QString sVertex){
        return setVertexes.indexOf(sVertex);
    }

    int indexEdge(QString sVertexA, QString sVertexB);//индекс ребра в массиве ребер

    int getNumberEdge() //количество ребер в графе
    {
        return listEdges.length();
    }

    bool checkConnectivity();

    int inRec;
};

#endif // GRAPH_H
