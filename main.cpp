#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QRegExp>
#include <QString>
#include <QRegularExpression>

#include <iostream>
#include <windows.h>

#include "graph.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString targetPath = QCoreApplication::applicationDirPath();

    QFile fileInput(targetPath + "/input.txt");
    QFile fileResult(targetPath + "/result.txt");

    if(!fileInput.open(QIODevice::ReadOnly)){
        std::cout << "File input.txt don't open";
        return a.exec();
    }
    if(!fileResult.open(QIODevice::ReadOnly)){
        std::cout << "File result.txt don't open";
        return a.exec();
    }

    Graph graph1;

    LARGE_INTEGER l1,l2;
    QueryPerformanceFrequency(&l1);
    double freq = double(l1.QuadPart)/1000.0;

    QRegExp reg("^\\w+(,\\s*\\w+)*$"); //проверка первой строки
    QRegExp sReg(",\\s*"); //разделитель между вершинами/расстоянием
    QRegExp reg2("^((\\w+,\\s*){2})(\\d+(.\\d+)?)$"); //проверка вершин и расстояния

    float dist;
    QStringList slist;
    std::cout<< "Beginning of reading file input.txt" << std::endl;
    QueryPerformanceCounter(&l1);

    while(!fileInput.atEnd()){
        QString str = fileInput.readLine();
        str.remove("\n");
        str.remove("\r");

        if(!reg.exactMatch(str))
        {
            std::cout << "First string of file result.txt isn't correct: " << str.toStdString();
            return a.exec();
        }

        slist = str.split(sReg, QString::SkipEmptyParts);
        foreach (QString el, slist) {
            graph1.addVertex(el);
        }

        //проверяем оставшиеся строки
        if(fileInput.atEnd()){
            std::cout << "Don't find edges in file input.txt";
            return a.exec();
        }

        //int p1e, p2s, p2e, p3s;
        while(!fileInput.atEnd()){
            str = fileInput.readLine();
            str.remove("\n");
            str.remove("\r");

            if(!reg2.exactMatch(str)){
                std::cout << "String in file result.txt isn't correct: " << str.toStdString();
                return a.exec();
            }

           /* p1e = str.indexOf(',');
            p2s = p1e + 1;
            while(str[p2s] == ' ') ++p2s;
            p2e = str.indexOf(',',p2s);
            p3s = p2e + 1;
            while(str[p3s] == ' ') ++p3s;

            dist = str.mid(p3s).toFloat();
            if(!graph1.addEdge(str.mid(0,p1e),str.mid(p2s,(p2e-p2s)),dist)){
                std::cout << "Don't add edge from file input.txt in graph: " << str.toStdString();
                return a.exec();
            }*/

            slist = str.split(sReg, QString::SkipEmptyParts);
            dist = ((QString)slist[2]).toFloat();

            if(!graph1.addEdge(slist[0],slist[1],dist)){
                std::cout << "Don't add edge from file input.txt in graph: " << str.toStdString();
                return a.exec();
            }
        }
    }
    QueryPerformanceCounter(&l2);
    std::cout << "time: " << (l2.QuadPart - l1.QuadPart)/freq << " ms" << std::endl;

    std::cout<< "Beginning of checking connectivity of the graph" << std::endl;
    QueryPerformanceCounter(&l1);
    if(!graph1.checkConnectivity()){
        std::cout << "Graph from file input.txt isn't connectivity";
        return a.exec();
    }
    QueryPerformanceCounter(&l2);
    std::cout << "time: " << (l2.QuadPart - l1.QuadPart)/freq << " ms" << std::endl;

    std::cout<< "Beginning of extraction of a tree from the graph" << std::endl;

    QueryPerformanceCounter(&l1);
    Graph graph2 = graph1.getTree();
    QueryPerformanceCounter(&l2);

    std::cout << "time: " << (l2.QuadPart - l1.QuadPart)/freq << " ms" << std::endl;

    if(fileResult.atEnd()){
        std::cout << "File result.txt is empty";
        return a.exec();
    }

    QRegExp reg3("^(\\w+,\\s*\\w+)$");
    QVector<GraphEdge *> indexVector;

    std::cout<< "Beginning of reading file result.txt" << std::endl;

    QueryPerformanceCounter(&l1);

    while(!fileResult.atEnd()){
        QString str = fileResult.readLine();
        str.remove("\n");
        str.remove("\r");

        if(!reg3.exactMatch(str)){
            std::cout << "Wrong edge-line in result.txt (regExp error): " << str.toStdString();
            return a.exec();
        }

        slist = str.split(sReg, QString::SkipEmptyParts);

        GraphEdge *ge = graph2.getEdge(slist[0],slist[1]);
        if(ge == nullptr){
            std::cout << "Wrong edge in result.txt (Correct graph-tree doesn't contain this edge): " << str.toStdString();
            return a.exec();
        }

        if(indexVector.contains(ge)){
            std::cout << "Edge from result.txt is repeated: " << str.toStdString();
            return a.exec();
        }
        indexVector.append(ge);
    }
    if(indexVector.length() != graph2.getNumberEdge()){
        std::cout << "Result graph-tree from file result.txt is wrong!";
        return a.exec();
    }

    QueryPerformanceCounter(&l2);
    std::cout << "time: " << (l2.QuadPart - l1.QuadPart)/freq << " ms" << std::endl;

    std::cout << "OK" << std::endl;
    std::cout << "END PROGRAM";
    return a.exec();
}
