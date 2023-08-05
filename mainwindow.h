#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "board.h"
#include <QLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer* mainTimer = new QTimer(this);
    void timerMethod();


private slots:

    void on_solver_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Board* board;
    QHBoxLayout* layout;
};
#endif // MAINWINDOW_H
