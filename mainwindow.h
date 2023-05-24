#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pytania.h"
#include "pytanie.h"
#include "student.h"
#include "studenci.h"

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <algorithm>
#include <Qcolor>
#include <QColorDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void WypiszPytania(double ocena, Typ typ);
    void SET_GUI();
public slots:
    void on_pushButton_SelectStudents_clicked();
    void on_pushButton_SelectQuestions_clicked();
    void on_pushButton_StartExam_clicked();
    void on_pushButton_LosujBlok1_clicked();
    void on_pushButton_EndExam_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_pushButton_Cofnijdostart_clicked();
    double ocenaFromCombo(int index);
private:
    Ui::MainWindow *ui;
    Student m_student;
    Studenci m_studenci;
    Pytania m_pytania;
    Pytanie m_pytanie;
};
#endif // MAINWINDOW_H
