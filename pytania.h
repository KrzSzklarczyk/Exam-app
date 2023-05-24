#ifndef PYTANIA_H
#define PYTANIA_H

#include "pytanie.h"

#include <QFile>
#include <QTextStream>
#include <QString>
#include <random>
#include <QStringList>
#include <QList>
#include <algorithm>
#include <list>
#include <qDebug>

class Pytania
{
public:
    Pytania();
    void Set_Pytania(QString FileName);
    void set_All(QString dane);
    const QString &getAll() const;
    QList<Pytanie> get_Blok1();
    QString m_All;
    QString losuj();
    QList<Pytanie> losuj(int x, Typ typ);
private:
    QList<Pytanie> m_blok1;
    QList<Pytanie> m_blok2;
    QList<Pytanie> m_blok3;
    QList<Pytanie> m_blok4;
};

#endif // PYTANIA_H

