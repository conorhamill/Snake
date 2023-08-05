#include "snake.h"
#include <QDebug>
#include "board.h"

#include <QVector>
#include <QRandomGenerator>

Snake::Snake()
{
    mHead = {12,12};
    mBody = {{12,12},{13,12},{14,12}};
    mTail = {14,12};
    mDirection = 1;
}

QVector<int> Snake::getHead()
{
    return mHead;
}

QVector<int> Snake::getTail()
{
    return mTail;
}

QVector<QVector<int> > Snake::getBody()
{
    return mBody;
}

int Snake::getDirection()
{
    return mDirection;
}

void Snake::setDirection(int aDirection)
{
    mDirection = aDirection;
}

void Snake::move()
{
    //create an empty array the same size as body to hold the next position of the snake
    QVector<QVector<int>> nextPosition;
    for (int i = 0; i < mBody.size(); i++)
    {
        nextPosition.push_back({0,0});
    }
    mHead = mBody[0];

    if (mDirection == 0)//down
    {
        mHead[0]++;
    }
    if (mDirection == 1)//up
    {
        mHead[0]--;
    }
    if (mDirection == 2)//left
    {
        mHead[1]--;
    }
    if (mDirection == 3)//right
    {
        mHead[1]++;
    }
    nextPosition[0] = mHead;

    for (int i = 1; i < mBody.size(); i++)
    {
        nextPosition[i] = mBody[i-1];
    }
    mBody = nextPosition;
    mTail = mBody[mBody.size()-1];
    qDebug() << mTail;
}

void Snake::grow()
{
    QVector<int> end = mBody[mBody.size()-1];
    mBody.push_back(end);
}

bool Snake::wallCheck(int gridSize)
{
    //check if the mHead has hit the wall
    //bottom wall and mDirection is down
    if (mHead[0] == gridSize-1 && mDirection == 0)
    {
        return true;
    }
    //top wall and mDirection is up
    if (mHead[0] == 0 && mDirection == 1)
    {
        return true;
    }
    //left wall and mDirection is left
    if (mHead[1] == 0 && mDirection == 2)
    {
        return true;
    }
    //right wall and mDirection is right
    if (mHead[1] == gridSize-1 && mDirection == 3)
    {
        return true;
    }
    return false;
}

bool Snake::bodyCheck()
{
    //check if the mHead has hit the mBody
    for (int i = 1; i< mBody.size(); i++)
    {
        if (mHead == mBody[i])
        {
            return true;
        }
    }
    return false;
}

