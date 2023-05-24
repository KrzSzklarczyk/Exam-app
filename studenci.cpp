#include "studenci.h"

Studenci::Studenci()
{

}

void Studenci::set_studenci(QString dane)
{

    m_MyFileStudents.setFileName(dane);
    if(m_MyFileStudents.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream inStream(&m_MyFileStudents);
        while(!inStream.atEnd())
        {
            QString line = inStream.readLine();
            auto split = line.split(";");
            Student student(split[0], split[1].toDouble(), split[2].toDouble(), split[3].toDouble(), split[4].toDouble());
            m_DaneStudentow.push_back(student);    
        }
        m_MyFileStudents.close();
    }
}

void Studenci::wpisz_studentow(QString dane)
{
    m_MyFileStudents.setFileName(dane);
    if(m_MyFileStudents.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream outStream(&m_MyFileStudents);
        Student student;
        for(Student &student : m_DaneStudentow)
        {
            outStream << student.get_dane();
            outStream << ';';
            outStream << "\n";
        }
    }
    m_MyFileStudents.close();
}

QList<Student> Studenci::get_Studenci()
{
    return m_DaneStudentow;
}

void Studenci::wpisz_ocene_koncowa(QString dane, double ocena)
{
    QString in_fileName = "OcenyKoncowe.txt";
    static QString fileName = "";
    if(!in_fileName.isEmpty())
        fileName = in_fileName;
    bool noEmpty = !fileName.isEmpty();
    if(noEmpty)
    {
        m_MyFileOceny.setFileName(fileName);
    }
    else
    {

    }

    m_SrednieStudentow.clear();
    if(m_MyFileOceny.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream inStream(&m_MyFileOceny);
        while(!inStream.atEnd())
        {
            QString line = inStream.readLine();
            if(!line.contains(";"))
            {
                continue;
            }
            QList<QString> split = line.split(';');
            Student text(split[0], split[1].toDouble());
            m_SrednieStudentow.push_back(text);
        }
        //ui->statusBar->showMessage("Odczytano tekst");
        m_MyFileOceny.close();
    }

    Student st(dane, ocena);
    m_SrednieStudentow.push_back(st);

    if(m_MyFileOceny.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream outStream(&m_MyFileOceny);
        for(Student &st : m_SrednieStudentow)
        {
        outStream << st.get_dane();
        outStream << ";";
        outStream << st.get_srednia();
        outStream << "\n";
        }
        m_MyFileOceny.close();
    }
}
