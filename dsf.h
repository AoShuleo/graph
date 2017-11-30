#ifndef DSF_H
#define DSF_H

#include <QObject>
#include <QVector>

class DSF
{
    QVector<int> sets; // номер множества
    QVector<int> rnk; // ранг
    int size = 0;
public:

    DSF(int size)
    {
        this->size = size;

        rnk =  QVector<int>(size);
        for (int i = 0; i < size; i++)
            sets.append(i);
    }

    ~DSF(){
        sets.clear();
        rnk.clear();
    }

    // Возвращает множество, которому принадлежит x
    int setM(int x)
    {
        return x == sets[x] ? x : (sets[x] = setM(sets[x]));
    }

    // Если u и v лежат в разных множествах, то сливаем их и возвращаем true
    bool unionM(int u, int v)
    {
        if ((u = setM(u)) == (v = setM(v)))
            return false;
        if (rnk[u] < rnk[v]) {
            sets[u] = v;
        } else {
            sets[v] = u;
            if (rnk[u] == rnk[v])
                rnk[u]++;
        }
        return true;
    }

    bool isComplete() {
           // checks if set is complete (all elements are in one set)
           int primary_set = setM(0);
           for (int i = 1; i < size; ++i) {
               if (setM(i) != primary_set) {
                   return false;
               }
           }
           return true;
       }
};

#endif // DSF_H
