#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <algorithm>
#include <QDialog>

static int ile_ocen;
static double m_ocenakoncowa;
static int current_index_blok1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SET_GUI();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SET_GUI()
{
    this->setStyleSheet("background-color: #262626");
    ui->pushButton_SelectStudents->setStyleSheet("background-color: #505050");
    ui->pushButton_SelectQuestions->setStyleSheet("background-color: #505050");
    ui->pushButton_StartExam->setStyleSheet("background-color: #458438");
    ui->lineEdit_ocena1->setStyleSheet("background-color: black");
    ui->lineEdit_ocena2->setStyleSheet("background-color: black");
    ui->lineEdit_ocena3->setStyleSheet("background-color: black");
    ui->lineEdit_ocena4->setStyleSheet("background-color: black");
    ui->comboBox->setStyleSheet("background-color: #505050");
    ui->label_5->setStyleSheet("background-color: #505050");
    ui->label_6->setStyleSheet("background-color: #505050");
    ui->label_7->setStyleSheet("background-color: #505050");
    ui->label_8->setStyleSheet("background-color: #505050");
    ui->pushButton_LosujBlok1->setStyleSheet("background-color: #505050");
    ui->pushButton_Cofnijdostart->setStyleSheet("background-color: #505050");
    ui->pushButton_EndExam->setStyleSheet("background-color: #505050");
    ui->checkBox_Blok1->setChecked(1);
    ui->checkBox_Blok2->setChecked(1);
    ui->checkBox_Blok3->setChecked(1);
    ui->checkBox_Blok4->setChecked(1);
    ui->pushButton_LosujBlok1->setEnabled(0);
    ui->lineEdit_ocena1->setAlignment(Qt::AlignCenter);
    ui->lineEdit_ocena2->setAlignment(Qt::AlignCenter);
    ui->lineEdit_ocena3->setAlignment(Qt::AlignCenter);
    ui->lineEdit_ocena4->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_pushButton_SelectStudents_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            "Wskaż plik",
                                            "",
                                            "Plik tekstowy (*.txt)");
    bool noEmpty = !fileName.isEmpty();
    // sprawdzenie sciezki
    auto iterator = fileName.end();
    QString path;
    iterator--;
    while(true)
    {
        if(*iterator != '/')
        {
            path.push_front(*iterator);
            iterator--;
        }
        else
            break;
    }
    if(path == "PPKStudenci.txt")
    {
        ui->lineEdit_ocena3->setEnabled(0);
        ui->lineEdit_ocena4->setEnabled(0);
        ui->comboBox_Ocena3->setEnabled(0);
        ui->comboBox_Ocena4->setEnabled(0);
    }
    if(path != "PPKStudenci.txt" && path!= "StudenciPK.txt")
    {
        QMessageBox mesBox;
        mesBox.setText(ui->comboBox->currentText() + "Wybrano niepoprawny plik!!!");
        mesBox.exec();
    }
    else
    {
        if(noEmpty)
        {
            ui->statusbar->showMessage("Plik ustawiony");
            m_studenci.set_studenci(fileName);
            QList<Student> ListaStudentow = m_studenci.get_Studenci();
            ui->pushButton_SelectStudents->setEnabled(0);
            for(int i=0; i<ListaStudentow.size(); i++)
            {
                ui->comboBox->addItem(ListaStudentow[i].get_dane());
            }
        }
        else
            ui->statusbar->showMessage("Brak pliku");
    }
/*
    QFileInfo path(fileName);
    std::string sciezka = path.baseName().toStdString();
    QString siema;
    siema.fromStdString(sciezka);
    qDebug() << siema;
    if(sciezka == "PPKStudenci.txt")
    {
        qDebug() << "fileName";
    }
*/

}

void MainWindow::on_pushButton_SelectQuestions_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            "Wskaż plik",
                                            "",
                                            "Plik tekstowy (*.txt)");
    // sprawdzenie sciezki
    auto iterator = fileName.end();
    QString path;
    iterator--;
    while(true)
    {
        if(*iterator != '/')
        {
            path.push_front(*iterator);
            iterator--;
        }
        else
            break;
    }
    if(path != "PPKPytania.txt" && path!= "PytaniaPK.txt")
    {
        QMessageBox mesBox;
        mesBox.setText(ui->comboBox->currentText() + "Wybrano niepoprawny plik!!!");
        mesBox.exec();
    }
    else
    {
        bool noEmpty = !fileName.isEmpty();

        if(noEmpty)
        {
            ui->statusbar->showMessage("Plik ustawiony");
            m_pytania.Set_Pytania(fileName);
            ui->pushButton_SelectQuestions->setEnabled(0);
        }
        else
        {
            ui->statusbar->showMessage("Brak pliku");
        }
    }
}

void MainWindow::on_pushButton_StartExam_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->EgzaminPK);
   QList<Student> ListaStudentow = m_studenci.get_Studenci();

    ui->textEdit->clear();

   if(ui->pushButton_SelectStudents->isEnabled() == 0 && ui->pushButton_SelectQuestions->isEnabled() == 0)
       ui->pushButton_LosujBlok1->setEnabled(1);
}

void MainWindow::WypiszPytania(double ocena, Typ typ)
{
    if(ocena <= 3.5)
    {
        QList<Pytanie> wylosowane_pytanie = m_pytania.losuj(1, typ);
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[0].get_Zawartosc());
        ui->textEdit->insertPlainText("\n");
        ui->textEdit->setTextColor( QColor( "red" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[0].get_czerowne());
        ui->textEdit->setTextColor( QColor( "green" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[0].get_zielone());
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->insertPlainText("\n");
    }
    else if(ocena > 3.5 && ocena < 4.5)
    {
        QList<Pytanie> wylosowane_pytanie = m_pytania.losuj(2, typ);
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[0].get_Zawartosc());
        ui->textEdit->insertPlainText("\n");
        ui->textEdit->setTextColor( QColor( "red" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[0].get_czerowne());
        ui->textEdit->setTextColor( QColor( "green" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[0].get_zielone());
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->insertPlainText("\n");
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[1].get_Zawartosc());
        ui->textEdit->insertPlainText("\n");
        ui->textEdit->setTextColor( QColor( "red" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[1].get_czerowne());
        ui->textEdit->setTextColor( QColor( "green" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[1].get_zielone());
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->insertPlainText("\n");

    }
    else if(ocena >= 4.5)
    {
        QList<Pytanie> wylosowane_pytanie = m_pytania.losuj(3, typ);
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[0].get_Zawartosc());
        ui->textEdit->insertPlainText("\n");
        ui->textEdit->setTextColor( QColor( "red" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[0].get_czerowne());
        ui->textEdit->setTextColor( QColor( "green" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[0].get_zielone());
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->insertPlainText("\n");
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[1].get_Zawartosc());
        ui->textEdit->insertPlainText("\n");
        ui->textEdit->setTextColor( QColor( "red" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[1].get_czerowne());
        ui->textEdit->setTextColor( QColor( "green" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[1].get_zielone());
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->insertPlainText("\n");
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[2].get_Zawartosc());
        ui->textEdit->insertPlainText("\n");
        ui->textEdit->setTextColor( QColor( "red" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[2].get_czerowne());
        ui->textEdit->setTextColor( QColor( "green" ) );
        ui->textEdit->insertPlainText(wylosowane_pytanie[2].get_zielone());
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->insertPlainText("\n");

    }
}

void MainWindow::on_pushButton_LosujBlok1_clicked()
{

    QString daneStudenta = ui->comboBox->currentText();
    QList<Student> ListaStudentow = m_studenci.get_Studenci();
    for(int i=0; i<ListaStudentow.size(); i++)
    {
        if(ListaStudentow[i].get_dane() == daneStudenta)
        {
            if(ListaStudentow[i].get_ocenaBlok3() == 0)
            {
                ui->textEdit->clear();
                if(ui->checkBox_Blok1->isChecked())
                {
                    ui->textEdit->setTextColor( QColor( "white" ) );
                ui->textEdit->setFontWeight(1000);
                ui->textEdit->insertPlainText("BLOK1");
                ui->textEdit->insertPlainText("\n");
                ui->textEdit->setFontWeight(1000);
                WypiszPytania(ListaStudentow[i].get_ocenaBlok1(), Typ::blok1);
                }
                if(ui->checkBox_Blok2->isChecked())
                {
                    ui->textEdit->setTextColor( QColor( "white" ) );
                ui->textEdit->setFontWeight(1000);
                ui->textEdit->insertPlainText("BLOK2");
                ui->textEdit->insertPlainText("\n");
                ui->textEdit->setFontWeight(1000);
                WypiszPytania(ListaStudentow[i].get_ocenaBlok2(), Typ::blok2);
                }
            }
            else
            {
            ui->textEdit->clear();
            if(ui->checkBox_Blok1->isChecked())
            {
            ui->textEdit->setTextColor( QColor( "white" ) );
            ui->textEdit->setFontWeight(1000);
            ui->textEdit->insertPlainText("BLOK1");
            ui->textEdit->insertPlainText("\n");
            ui->textEdit->setFontWeight(1000);
            WypiszPytania(ListaStudentow[i].get_ocenaBlok1(), Typ::blok1);
            }
            if(ui->checkBox_Blok2->isChecked())
            {
                ui->textEdit->setTextColor( QColor( "white" ) );
            ui->textEdit->setFontWeight(1000);
            ui->textEdit->insertPlainText("BLOK2");
            ui->textEdit->insertPlainText("\n");
            ui->textEdit->setFontWeight(1000);
            WypiszPytania(ListaStudentow[i].get_ocenaBlok2(), Typ::blok2);
            }
            if(ui->checkBox_Blok3->isChecked())
            {
                ui->textEdit->setTextColor( QColor( "white" ) );
            ui->textEdit->setFontWeight(1000);
            ui->textEdit->insertPlainText("BLOK3");
            ui->textEdit->insertPlainText("\n");
            ui->textEdit->setFontWeight(1000);
            WypiszPytania(ListaStudentow[i].get_ocenaBlok3(), Typ::blok3);
            }
            if(ui->checkBox_Blok4->isChecked())
            {
                ui->textEdit->setTextColor( QColor( "white" ) );
            ui->textEdit->setFontWeight(1000);
            ui->textEdit->insertPlainText("BLOK4");
            ui->textEdit->insertPlainText("\n");
            ui->textEdit->setFontWeight(1000);
            WypiszPytania(ListaStudentow[i].get_ocenaBlok3(), Typ::blok4);
            }
            }
        }
    }
}

double MainWindow::ocenaFromCombo(int index)
{
    switch(index)
    {
    case 0:
        return 2.0;
        break;
    case 1:
        return 3.0;
        break;
    case 2:
        return 3.5;
        break;
    case 3:
        return 4.0;
        break;
    case 4:
        return 4.5;
        break;
    case 5:
        return 5.0;
        break;
    }

}

void MainWindow::on_pushButton_EndExam_clicked()
{
    double ocena1 = ocenaFromCombo(ui->comboBox_Ocena1->currentIndex());
    double ocena2 = ocenaFromCombo(ui->comboBox_Ocena2->currentIndex());
    double ocena3 = ocenaFromCombo(ui->comboBox_Ocena3->currentIndex());
    double ocena4 = ocenaFromCombo(ui->comboBox_Ocena4->currentIndex());
    double srednia;
    if(ui->comboBox_Ocena3->isEnabled() == 1)
    {
        srednia = (ocena1 + ocena2 + ocena3 + ocena4) / 4;
    }
    else
    {
        srednia = (ocena1 + ocena2) / 2;
    }
    QMessageBox mesBox;
    mesBox.setText(ui->comboBox->currentText() + " Twoja Ocena Koncowa to: ");
    mesBox.setInformativeText(QString::number(srednia));
    mesBox.exec();
    m_studenci.wpisz_ocene_koncowa(ui->comboBox->currentText(), srednia);

}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    QList<Student> ListaStudentow = m_studenci.get_Studenci();

    for(int i=0; i<ListaStudentow.size(); i++)
    {
        if(ListaStudentow[i].get_dane() == arg1)
        {
            if(ListaStudentow[i].get_ocenaBlok3() == 0)
            {
                ui->lineEdit_ocena1->setText(QString::number(ListaStudentow[i].get_ocenaBlok1()));
                ui->lineEdit_ocena2->setText(QString::number(ListaStudentow[i].get_ocenaBlok2()));
                ui->lineEdit_ocena3->setDisabled(1);
                ui->lineEdit_ocena4->setDisabled(1);
            }
            else
            {
                ui->lineEdit_ocena1->setText(QString::number(ListaStudentow[i].get_ocenaBlok1()));
                ui->lineEdit_ocena2->setText(QString::number(ListaStudentow[i].get_ocenaBlok2()));
                ui->lineEdit_ocena3->setText(QString::number(ListaStudentow[i].get_ocenaBlok3()));
                ui->lineEdit_ocena4->setText(QString::number(ListaStudentow[i].get_ocenaBlok4()));
            }
        }
    }
}

void MainWindow::on_pushButton_Cofnijdostart_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Start);
}
