#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




public slots:

    //void Box(std::string data,int posx,int posy,std::string status);
    void logincheck();
    void deletefilez();
    void createkey();
    void openpop(std::string comb);
    void supp();
    void deletetask();
    void passwordz();
    void savepass();
    void aboutpage();
    void backed();
    void chkeyz();
    void chgkey();
    void showallpass();
    void homescr();
    //class Box;



private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
