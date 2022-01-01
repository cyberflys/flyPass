#include "mainwindow.h"
#include <unistd.h>
#include <QApplication>

int main(int argc, char *argv[])
{

    chdir("passwords/");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
