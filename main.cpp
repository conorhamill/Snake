#include "mainwindow.h"
#include "board.h"
#include "snake.h"

#include <QApplication>
#include <QMainWindow>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(600,600);
    w.show();
    return a.exec();
}
