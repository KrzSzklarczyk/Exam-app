#ifndef PYTANIE_H
#define PYTANIE_H

#include <QString>

enum Typ{blok1, blok2, blok3, blok4};

class Pytanie
{
public:
    Pytanie();
    Pytanie(Typ typ, const QString &tytul, const QString &czerwone, const QString &zielone);
    Typ get_typ() const;
    const QString &get_Zawartosc() const;
    const QString &get_czerowne() const;
    const QString &get_zielone() const;
    void set_Zawartosc(QString dane);
    void set_Typ(Typ typ);
private:
    QString m_tytul;
    QString m_czerwone;
    QString m_zielone;
    Typ m_typ;
};
#endif // PYTANIE_H

