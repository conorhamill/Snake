#ifndef SNAKE_H
#define SNAKE_H

#include <QVector>

class Snake
{
public:
    Snake();
    QVector<int> getHead();
    QVector<int> getTail();
    QVector<QVector<int>> getBody();
    int getDirection();
    void setDirection(int aDirection);
    void move();
    void grow();
    bool wallCheck(int gridSize);
    bool bodyCheck();

private:
    QVector<int> mHead;
    QVector<int> mTail;
    QVector<QVector<int>> mBody;
    int mDirection;
};

#endif // SNAKE_H
