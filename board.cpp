#include "board.h"
#include "snake.h"
#include "mainwindow.h"

#include <QPainter>
#include <QVector>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDateTime>


Board::Board(QWidget *parent) : QWidget(parent)
{
    connect(timer, &QTimer::timeout, this, Board::timerMethod);
    connect(solverTimer, &QTimer::timeout, this, Board::solverTimerMethod);
    setFocusPolicy(Qt::StrongFocus);
    gameStatus = "Press any key to begin";
    keyPressEventEnabled = true;
}

void Board::keyPressEvent(QKeyEvent *event)
{
    if (keyPressEventEnabled == false)
    {
        return;
    }
    //if the timer is stopped and the reset cool is not activated then start the timer
    if (timer->isActive() == false && resetBool == false)
    {
        timer->start(speed);
        gameStatus = "Game running";
        lastTime = QDateTime::currentDateTime();
    }

    //if the reset bool is true then next keypress will reset the grid and stop the timer
    if (resetBool == true)
    {
        timer->stop();
        resetBool = false;
        update(); //this command updates the widget which calls the paintevent function above
        gameStatus = "Press any key to begin";
    }

    //change the direction based on the keypress. if current direction is opposite to that requested - nothing happens.
    switch (event->key())
    {
    case Qt::Key_Down:
        if (snake.getDirection() == 1)
        {
            break;
        }
        snake.setDirection(0);
        break;
    case Qt::Key_Up:
        if (snake.getDirection() == 0)
        {
            break;
        }
        snake.setDirection(1);
        break;
    case Qt::Key_Left:
        if (snake.getDirection() == 3)
        {
            break;
        }
        snake.setDirection(2);
        break;
    case Qt::Key_Right:
        if (snake.getDirection() == 2)
        {
            break;
        }
        snake.setDirection(3);
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void Board::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    grid.clear();
    QVector<int> gridRow;

    //initialise grid with all zeros
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            gridRow.push_back(0);
        }
        grid.push_back(gridRow);
        gridRow.clear();
    }

    //change the grid to ones where the snake is located
    for (int i = 0; i < snake.getBody().size(); i++)
    {
        int x = snake.getBody()[i][0];
        int y = snake.getBody()[i][1];
        grid[x][y] = 1;
    }

    //change the grid where the food is located to 2
    grid[food[0]][food[1]] = 2;

    int cellWidth = (int)(width()/(float)(gridSize) + 0.5f);
    int cellHeight = (int)(height()/(float)(gridSize) + 0.5f);

    for (int row = 0; row < gridSize; row++)
    {
        for (int col = 0; col < gridSize; col++)
        {
            if (grid[row][col] == 0)
            {
                painter.setBrush(Qt::black);//normal grid
            }
            if (grid[row][col] == 1)
            {
                painter.setBrush(Qt::white);//snake
            }
            if (grid[row][col] == 2)
            {
                painter.setBrush(Qt::red);//food
            }
            int x = col * cellWidth;
            int y = row * cellHeight;
            painter.drawRect(x,y,cellWidth,cellHeight);
        }
    }

    //this adds the blue lines to the grid to help visualisation. can be added back in.
//    painter.setPen(Qt::blue);
//    for (int row = 0; row <gridSize; ++row)
//    {
//        int y = row * cellHeight;
//        painter.drawLine(0,y,cellWidth*gridSize,y);
//    }
//    for (int col = 0; col < gridSize; ++col)
//    {
//        int x = col *cellWidth;
//        painter.drawLine(x,0,x,cellHeight*gridSize);
//    }
}

void Board::timerMethod()
{
    if (snake.wallCheck(gridSize) == true)
    {
        timer->stop();
        gameStatus = "Game over. Press any key to reset.";
        return;
    }
    snake.move();

    if (snake.bodyCheck() == true)
    {
        timer->stop();
        gameStatus = "Game over. Press any key to reset.";
        return;
    }
    update();//this command updates the widget which calls the paintevent function above

    if (snake.getHead() == food)
    {
        foodEaten();
        snake.grow();
        score++;
    }

    //increments the timer counter for every second passed since the game began
    currentTime = QDateTime::currentDateTime();
    if (currentTime > lastTime.addSecs(1))
    {
        gameTime++;
        lastTime = currentTime;
    }
}

void Board::solverTimerMethod()
{
    //normal wall check
    if (snake.wallCheck(gridSize) == true)
    {
        solverTimer->stop();
        gameStatus = "Game over. Press any key to reset.";
        return;
    }

    // do 4 moves up then right and continue
    if (counter < 5)
    {
        snake.move();
        counter++;
    }
    else
    {
        counter = 1;
        if (snake.getDirection() == 1)
        {
            snake.setDirection(2);
        }
        else if (snake.getDirection() == 2)
        {
            snake.setDirection(1);
        }
    }

    //normal body check
    if (snake.bodyCheck() == true)
    {
        solverTimer->stop();
        gameStatus = "Game over. Press any key to reset.";
        return;
    }

    update();//this command updates the widget which calls the paintevent function above

    if (snake.getHead() == food)
    {
        foodEaten();
        snake.grow();
        score++;
    }

    //increments the timer counter for every second passed since the game began
    currentTime = QDateTime::currentDateTime();
    if (currentTime > lastTime.addSecs(1))
    {
        gameTime++;
        lastTime = currentTime;
    }
}

void Board::foodEaten()
{
    //change location of food to somewhere else in the grid that isn't the snake body
    while(true)
    {
        int row = QRandomGenerator::global()->bounded(gridSize);
        int col = QRandomGenerator::global()->bounded(gridSize);
        int match = 0;
        food = {row,col};

        for (int i = 0; i < snake.getBody().size(); i++)
        {
            if (snake.getBody()[i] == food)
            {
                match++;
            }
        }
        if (match ==0)
        {
            return;
        }
    }
}

int Board::getScore()
{
    return score;
}

int Board::getTime()
{
    return gameTime;
}

QString Board::getGameStatus()
{
    return gameStatus;
}

void Board::reset()
{
    resetBool = true;

    //reset all the game variables
    score = 0;
    gameTime = 0;
    food = {5,5};
    snake = Snake();
    gameStatus = "Game over. Press any key to reset.";
}

void Board::setDifficulty(QString diff)
{
    if (diff == "easy")
    {
        speed = 150;
    }
    if (diff == "medium")
    {
        speed = 80;
    }
    if (diff == "hard")
    {
        speed = 25;
    }
}

void Board::setKeyPressEventEnabled(bool val)
{
    keyPressEventEnabled = val;
}

void Board::runSolver()
{
    solverTimer->start(speed);
    gameStatus = "Game running";
}

