#include "pytanie.h"

Pytanie::Pytanie()
{

}

Pytanie::Pytanie(Typ typ, const QString &tytul, const QString &czerwone, const QString &zielone)
{
    m_typ = typ;
    m_tytul = tytul;
    m_czerwone = czerwone;
    m_zielone = zielone;
}

Typ Pytanie::get_typ() const
{
    return m_typ;
}


const QString &Pytanie::get_Zawartosc() const
{
    return m_tytul;
}

const QString &Pytanie::get_zielone() const
{
    return m_zielone;
}

const QString &Pytanie::get_czerowne() const
{
    return m_czerwone;
}

void Pytanie::set_Zawartosc(QString dane)
{
    m_tytul = dane;
}
void Pytanie::set_Typ(Typ typ)
{
    m_typ = typ;
}

