#include "student.h"

Student::Student(QString dane, double oc1, double oc2, double oc3, double oc4)
{
    m_dane = dane;
    m_ocenaBlok1 = oc1;
    m_ocenaBlok2 = oc2;
    m_ocenaBlok3 = oc3;
    m_ocenaBlok4 = oc4;
}

Student::Student(QString dane, double oc1, double oc2)
{
    m_dane = dane;
    m_ocenaBlok1 = oc1;
    m_ocenaBlok2 = oc2;
}

Student::Student(QString dane, double oc1)
{
    m_dane = dane;
    m_srednia = oc1;
}


Student::Student()
{

}

Student::~Student()
{

}


void Student::set_ocenaBlok1(double oc)
{
    m_ocenaBlok1 = oc;
}
void Student::set_ocenaBlok2(double oc)
{
    m_ocenaBlok2 = oc;
}
void Student::set_ocenaBlok3(double oc)
{
    m_ocenaBlok3 = oc;
}
void Student::set_ocenaBlok4(double oc)
{
    m_ocenaBlok4 = oc;
}

double Student::get_ocenaBlok1()
{
    return m_ocenaBlok1;
}
double Student::get_ocenaBlok2()
{
    return m_ocenaBlok2;
}
double Student::get_ocenaBlok3()
{
    return m_ocenaBlok3;
}
double Student::get_ocenaBlok4()
{
    return m_ocenaBlok4;
}
double Student::get_srednia()
{
    return m_srednia;
}

const QString &Student::get_dane() const
{
    return m_dane;
}
