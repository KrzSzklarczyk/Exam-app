#ifndef STUDENCI_H
#define STUDENCI_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>
#include <algorithm>
#include <list>
#include <qDebug>
#include "student.h"


class Studenci
{
public:
    Studenci();
    void set_studenci(QString dane);
    void wpisz_studentow(QString dane);
    void wpisz_ocene_koncowa(QString dane, double ocena);
    QList<Student> get_Studenci();
private:
    QList<Student> m_DaneStudentow;
    QList<Student> m_SrednieStudentow;
    QFile m_MyFileStudents;
    QFile m_MyFileOceny;
};

#endif // STUDENCI_H
