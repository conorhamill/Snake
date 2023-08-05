#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include "snake.h"
#include <QTimer>
#include <QString>
#include <QDateTime>

class Board : public QWidget
{
    Q_OBJECT
public:

    explicit Board(QWidget *parent = nullptr);

    QTimer* timer = new QTimer(this);
    QTimer* solverTimer = new QTimer(this);

    QVector<QVector<int>> grid;
    int gridSize = 25;
    int score = 0;
    int gameTime = 0;
    QString gameStatus = "";
    QVector<int> food = {5,5};
    bool resetBool = false;
    int speed = 80;
    bool keyPressEventEnabled;

    //test variables for circular loop
    int counter = 1;

    QDateTime lastTime;
    QDateTime currentTime;

    Snake snake;

    void paintEvent(QPaintEvent *event);
    void timerMethod();
    void solverTimerMethod();
    void keyPressEvent(QKeyEvent *event);
    void foodEaten();
    int getScore();
    int getTime();
    QString getGameStatus();
    void reset();
    void setDifficulty(QString diff);
    void setKeyPressEventEnabled(bool val);

    void runSolver();

};

#endif // BOARD_H
