#include "pytania.h"
#include "qdebug.h"


Pytania::Pytania()
{

}

void Pytania::set_All(QString dane)
{
    m_All = dane;
}

const QString &Pytania::getAll()const
{
     return m_All;
}

QList<Pytanie> Pytania::get_Blok1()
{
    return m_blok1;
}

void Pytania::Set_Pytania(QString path)
{
    QFile m_MyFileQuestions(path);
    if(m_MyFileQuestions.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream inStream(&m_MyFileQuestions);
        while(!inStream.atEnd())
         {
            QString line = inStream.readLine();
            QList<QString> split = line.split(';');
            Pytanie pytanie((Typ)split[0].toInt(), split[1], split[2], split[3]);
            if(pytanie.get_typ()==Typ::blok1)
            {
                m_blok1.append(pytanie);
            }
            else if(pytanie.get_typ()==Typ::blok2)
            {
                m_blok2.push_back(pytanie);
            }
            else if(pytanie.get_typ()==Typ::blok3)
            {
                 m_blok3.push_back(pytanie);
            }
            else if(pytanie.get_typ()==Typ::blok4)
            {
                m_blok4.push_back(pytanie);
            }
            else
                qDebug() << "nie dizala zaden blok";
         }
         m_MyFileQuestions.close();
    }
}


QList<Pytanie> Pytania::losuj(int x, Typ typ)
{
    QList<Pytanie> pytania;
    if(typ == Typ::blok1)
        pytania = m_blok1;
    else if(typ == Typ::blok2)
        pytania = m_blok2;
    else if(typ == Typ::blok3)
        pytania = m_blok3;
    else if(typ == Typ::blok4)
        pytania = m_blok4;

    std::random_device srng; std::mt19937 rng;
    rng.seed(srng());
    int zasieg = pytania.size();
    std::uniform_int_distribution<int> uniDistInt(0, zasieg);
    std::shuffle(pytania.begin(),pytania.end(), rng);
    QList<Pytanie> wynik;
    for(int i = 0; i < x; i++)
    {
        wynik.push_back(pytania[i]);
    }
    return wynik;
}
