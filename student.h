#ifndef STUDENT_H
#define STUDENT_H

#include "qobjectdefs.h"
#include <QString>
#include <QVector>
#include <QObject>
class Student
{
public:
    Student(QString dane, double oc1, double oc2, double oc3, double oc4);
    Student(QString dane, double oc1, double oc2);
    Student(QString dane, double oc1);
    Student();
    ~Student();
    void set_ocenaBlok1(double oc);
    void set_ocenaBlok2(double oc);
    void set_ocenaBlok3(double oc);
    void set_ocenaBlok4(double oc);
    double get_ocenaBlok1();
    double get_ocenaBlok2();
    double get_ocenaBlok3();
    double get_ocenaBlok4();
    double get_srednia();
    const QString &get_dane() const;
private:
    QString m_dane;
    double m_srednia;
    double m_ocenaBlok1;
    double m_ocenaBlok2;
    double m_ocenaBlok3;
    double m_ocenaBlok4;

};

#endif // STUDENT_H
