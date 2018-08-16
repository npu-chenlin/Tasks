#include <cmath>
#include <QDebug>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{
    memset(m, 0, sizeof(m));
}

MainWindow::~MainWindow(){}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.setPen(QPen(Qt::darkGray, 2, Qt::SolidLine)); //钢笔工具：颜色，线号，实线
    //画SIZE+1条横线
    for (int i = 0; i < SIZE + 1; i++)
    {
        paint.drawLine(x_offset, y_offset + WIDTH * i, x_offset + WIDTH * (SIZE), y_offset + WIDTH * i); //画线函数：x1,y1,x2,y2:画从(x1,y1)到(x2,y2)的线
    }
    //画SIZE+1条竖线
    for (int i = 0; i < SIZE + 1; i++)
    {
        paint.drawLine(x_offset + WIDTH * i, y_offset, x_offset + WIDTH * i, y_offset + WIDTH * (SIZE));
    }
    //画棋子
    for (int i = 0; i < SIZE - 1; ++i)
    {
        for (int j = 0; j < SIZE - 1; ++j)
        {
            if (m[i][j] == 1)
            {
                paint.setBrush(QBrush(Qt::black, Qt::SolidPattern)); //毛刷：颜色，实图案
                paint.drawEllipse((x_offset + WIDTH * (i + 0.5)), (y_offset + WIDTH * (j + 0.5)), WIDTH, WIDTH); //画椭圆：中心点X,Y,宽度，高度
            }
            if (m[i][j] == -1)
            {
                paint.setBrush(QBrush(Qt::white, Qt::SolidPattern)); //毛刷：颜色，实图案
                paint.drawEllipse((x_offset + WIDTH * (i + 0.5)), (y_offset + WIDTH * (j + 0.5)), WIDTH, WIDTH); //画椭圆：中心点X,Y,宽度，高度
            }
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int x0 = event->x() - x_offset-WIDTH/2;
    int y0 = event->y() - y_offset-WIDTH/2;
    if (!(x0 >= 0 && x0 <= WIDTH * (SIZE - 1) && y0 >= 0 && y0 <= WIDTH * (SIZE - 1))) return;
    int lx = x0 / WIDTH;
    int ly = y0 / WIDTH;
    bool flag = false;
    for (int i = lx; i < lx + 2 && !flag; ++i)
    {
        for (int j = ly; j < ly + 2 && !flag; ++j)
        {
            if (std::sqrt(std::pow((x0 - (WIDTH/2 + i * WIDTH)), 2) + std::pow((y0 - (WIDTH/2 + j * WIDTH)), 2)) < 20)
            {
                if (m[i][j]) return;

                flag = true;
                ++steps;
                m[i][j] = 1;
                if (isWin(i, j))
                {
                    if (m[i][j] == 1)
                    {
                        QMessageBox::information(NULL, tr("Game Over"), tr("Black Win!"));
                    }
                    else
                        QMessageBox::information(NULL, tr("Game Over"), tr("White Win!"));
                    memset(m, 0, sizeof(m));
                    steps = 0;
                }
                update();
                Point p = dropChessman(false);
                m[p.x][p.y] = -1;
                if (isWin(p.x, p.y))
                {
                    if (m[i][j] == 1)
                    {
                        QMessageBox::information(NULL, tr("Game Over"), tr("Black Win!"));
                    }
                    else
                        QMessageBox::information(NULL, tr("Game Over"), tr("White Win!"));
                    memset(m, 0, sizeof(m));
                    steps = 0;
                }
                update();
            }
        }
    }
}

bool MainWindow::isWin(int x0, int y0)
{
    int forword = 0;
    int post = 0;
    while (m[x0 - post][y0] == m[x0][y0])
    {
        if (x0 - (++post) < 0) break;
    }
    while (m[x0 + forword][y0] == m[x0][y0])
    {
        if (x0 + (++forword) > SIZE - 1)break;
    }
    if (post + forword >= 6)return true;

    forword = post = 0;
    while (m[x0][y0 - post] == m[x0][y0])
    {
        if (y0 - (++post) < 0) break;
    }
    while (m[x0][y0 + forword] == m[x0][y0])
    {
        if (y0 + (++forword) > SIZE - 1)break;
    }
    if (post + forword >= 6)return true;

    forword = post = 0;
    while (m[x0 - post][y0 - post] == m[x0][y0])
    {
        if ((y0 - (++post) < 0) && (x0 - post < 0)) break;
    }
    while (m[x0 + forword][y0 + forword] == m[x0][y0])
    {
        if ((x0 + (++forword) > SIZE - 1) && ((y0 + forword) > SIZE - 1))break;

    }
    if (post + forword >= 6)return true;

    forword = post = 0;
    while (m[x0 - post][y0 + post] == m[x0][y0])
    {
        if ((x0 - (++post) < 0) && (y0 + post > SIZE - 1)) break;
    }
    while (m[x0 + forword][y0 - forword] == m[x0][y0])
    {
        if ((x0 + (++forword) > SIZE - 1) && ((y0 - forword) < 0))break;
    }
    if (post + forword >= 6)return true;

    return false;
}
void MainWindow::thinker(bool player)
{
    Point t1 = dropChessman(player);
    if(player)m[t1.x][t1.y] = 1;
    else m[t1.x][t1.y] = -1;
    Point t2 = dropChessman(!player);
    if(player)m[t2.x][t2.y] = 1;
    else m[t2.x][t2.y] = -1;
}

Point MainWindow::dropChessman(bool player)
{
    Point p;
    int attackScore = 0;
    int defenceScore = 0;
    int value = 0;
    int m0 = 0, n0 = 0;
    int m1, n1;
    for (int i = 0; i < SIZE - 1; ++i)
    {
        for (int j = 0; j < SIZE - 1; ++j)
        {
            if (m[i][j]) continue;
            value = evaluater(i , j , player);
            if (value > attackScore)
            {
                attackScore = value;
                m0 = i;
                n0 = j;
            }
        }
    }
    for (int i = 0; i < SIZE - 1; ++i)
    {
        for (int j = 0; j < SIZE - 1; ++j)
        {
            if (m[i][j]) continue;
            value = evaluater(i , j , !player);
            if (value > defenceScore)
            {
                defenceScore = value;
                m1 = i;
                n1 = j;
            }
        }
    }
    attackScore+=3;
    if (attackScore > defenceScore)
    {
        p.x=m0;
        p.y=n0;
        return p;
    }
    else
    {
        p.x=m1;
        p.y=n1;
        return p;
    }

}

void calculateScore(int i,int & value)
{
    if (i >= 6) value+=100;
    else if (i == 5) value+=50;
    else if (i == 4) value+=10;
    else if (i == 3) value+=3;
}

int MainWindow::evaluater(int x0, int y0 , bool player)
{
    int value = 0;
    int forword = 0;
    int post = 0;

    std::vector<int> v;

    if (player) m[x0][y0] = 1;
    else m[x0][y0] = -1;

    while (m[x0 - post][y0] == m[x0][y0])
    {
        if (x0 - (++post) < 0) break;
    }
    while (m[x0 + forword][y0] == m[x0][y0])
    {
        if (x0 + (++forword) > SIZE - 1)break;
    }
    calculateScore(post+forword,value);


    forword = post = 0;
    while (m[x0][y0 - post] == m[x0][y0])
    {
        if (y0 - (++post) < 0) break;
    }
    while (m[x0][y0 + forword] == m[x0][y0])
    {
        if (y0 + (++forword) > SIZE - 1)break;
    }
    calculateScore(post+forword,value);


    forword = post = 0;
    while (m[x0 - post][y0 - post] == m[x0][y0])
    {
        if ((y0 - (++post) < 0) && (x0 - post < 0)) break;
    }
    while (m[x0 + forword][y0 + forword] == m[x0][y0])
    {
        if ((x0 + (++forword) > SIZE - 1) && ((y0 + forword) > SIZE - 1))break;

    }
    calculateScore(post+forword,value);


    forword = post = 0;
    while (m[x0 - post][y0 + post] == m[x0][y0])
    {
        if ((x0 - (++post) < 0) && (y0 + post > SIZE - 1)) break;
    }
    while (m[x0 + forword][y0 - forword] == m[x0][y0])
    {
        if ((x0 + (++forword) > SIZE - 1) && ((y0 - forword) < 0))break;
    }
    calculateScore(post+forword,value);

    m[x0][y0] = 0;
    return value;
}
