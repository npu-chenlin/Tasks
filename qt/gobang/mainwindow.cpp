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
                    update();
                    break;
                }
                Point p = dropChessman(false);

                m[p.x][p.y] = -1;
                update();
                if (isWin(p.x, p.y))
                {
                    if (m[p.x][p.y] == 1)
                    {
                        QMessageBox::information(NULL, tr("Game Over"), tr("Black Win!"));
                    }
                    else
                        QMessageBox::information(NULL, tr("Game Over"), tr("White Win!"));
                    memset(m, 0, sizeof(m));
                    update();
                    break;
                }
                break;
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
    Point p1,p2;
    int attackScore = 0;
    int defenceScore = 0;
    for (int i = 0; i < SIZE - 1; ++i)
    {
        for (int j = 0; j < SIZE - 1; ++j)
        {
            if (m[i][j]) continue;
            p = evaluater(i , j , player);
            if (p.score > attackScore)
            {
                attackScore = p.score;
                p1 = p;
            }
        }
    }
    for (int i = 0; i < SIZE - 1; ++i)
    {
        for (int j = 0; j < SIZE - 1; ++j)
        {
            if (m[i][j]) continue;
            p = evaluater(i , j , !player);
            if (p.score > defenceScore)
            {
                defenceScore = p.score;
                p2 = p;
            }
        }
    }
    attackScore+=2;
    if (attackScore > defenceScore) return p1;
    else return p2;
}

void calculateScore(Point& p)
{
    p.score = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (p.dir[i].Num+p.dir[i+4].Num >= 4)p.score +=100000;
        else if (p.dir[i].Num+p.dir[i+4].Num == 3 && p.dir[i].isEmpty == true && p.dir[i+4].isEmpty == true) p.score +=6000;
        else if (p.dir[i].Num+p.dir[i+4].Num == 3 && p.dir[i].isEmpty != p.dir[i+4].isEmpty) p.score +=2000;
        else if (p.dir[i].Num+p.dir[i+4].Num == 2 && p.dir[i].isEmpty == true && p.dir[i+4].isEmpty == true) p.score +=2500;
        else if (p.dir[i].Num+p.dir[i+4].Num == 2 && p.dir[i].isEmpty != p.dir[i+4].isEmpty) p.score +=1500;
        else if (p.dir[i].Num+p.dir[i+4].Num == 1 && p.dir[i].isEmpty == true && p.dir[i+4].isEmpty == true) p.score +=1500;
        else if (p.dir[i].Num+p.dir[i+4].Num == 1 && p.dir[i].isEmpty != p.dir[i+4].isEmpty) p.score +=500;
        else if (p.dir[i].Num+p.dir[i+4].Num == 0 && p.dir[i].isEmpty == true && p.dir[i+4].isEmpty == true) p.score +=200;
        else if (p.dir[i].Num+p.dir[i+4].Num == 0 && p.dir[i].isEmpty != p.dir[i+4].isEmpty) p.score +=20;
    }
}

int getChessmanColor(bool player)
{
    if(player) return 1;
    else return -1;
}

Point MainWindow::evaluater(int x0, int y0 , bool player)
{
    int forword = 0;
    int post = 0;
    Point p;

    m[x0][y0] = getChessmanColor(player);
    p.x = x0;
    p.y = y0;
    while (1)
    {
        if (x0 - (++post) < 0)
        {
            p.dir[4].isEmpty = false;
            break;
        }
        if(m[x0 - post][y0] == getChessmanColor(!player))
        {
            p.dir[4].isEmpty = false;
            break;
        }
        if(m[x0 - post][y0] == 0)
        {
            p.dir[4].isEmpty = true;
            break;
        }
    }
    while (1)
    {
        if (x0 + (++forword) > SIZE - 2)
        {
            p.dir[0].isEmpty = false;
            break;
        }
        if(m[x0 + forword][y0] == getChessmanColor(!player))
        {
            p.dir[0].isEmpty = false;
            break;
        }
        if(m[x0 + forword][y0] == 0)
        {
            p.dir[0].isEmpty = true;
            break;
        }
    }
    p.dir[4].Num = post - 1;
    p.dir[0].Num = forword -1;

    forword = post = 0;
    while (1)
    {
        if (y0 - (++post) < 0)
        {
            p.dir[6].isEmpty = false;
            break;
        }
        if(m[x0][y0 - post] == getChessmanColor(!player))
        {
            p.dir[6].isEmpty = false;
            break;
        }
        if(m[x0][y0 - post] == 0)
        {
            p.dir[6].isEmpty = true;
            break;
        }
    }
    while (1)
    {
        if (y0 + (++forword) > SIZE - 2)
        {
            p.dir[2].isEmpty = false;
            break;
        }
        if(m[x0][y0 + forword] == getChessmanColor(!player))
        {
            p.dir[2].isEmpty = false;
            break;
        }
        if(m[x0][y0 + forword] == 0)
        {
            p.dir[2].isEmpty = true;
            break;
        }
    }
    p.dir[6].Num = post - 1;
    p.dir[2].Num = forword -1;

    forword = post = 0;
    while (1)
    {
        if ((y0 - (++post) < 0) || (x0 - post < 0))
        {
            p.dir[5].isEmpty = false;
            break;
        }
        if(m[x0 - post][y0 - post] == getChessmanColor(!player))
        {
            p.dir[5].isEmpty = false;
            break;
        }
        if(m[x0 - post][y0 - post] == 0)
        {
            p.dir[5].isEmpty = true;
            break;
        }
    }
    while (1)
    {
        if ((x0 + (++forword) > SIZE - 2) || ((y0 + forword) > SIZE - 2))
        {
            p.dir[1].isEmpty = false;
            break;
        }
        if(m[x0 + forword][y0 + forword] == getChessmanColor(!player))
        {
            p.dir[1].isEmpty = false;
            break;
        }
        if(m[x0 + forword][y0 + forword] == 0)
        {
            p.dir[1].isEmpty = true;
            break;
        }
    }
    p.dir[5].Num = post - 1;
    p.dir[1].Num = forword -1;

    forword = post = 0;
    while (1)
    {
        if ((x0 - (++post) < 0) || (y0 + post > SIZE - 2))
        {
            p.dir[3].isEmpty = false;
            break;
        }
        if(m[x0 - post][y0 + post] == getChessmanColor(!player))
        {
            p.dir[3].isEmpty = false;
            break;
        }
        if(m[x0 - post][y0 + post] == 0)
        {
            p.dir[3].isEmpty = true;
            break;
        }
    }
    while (1)
    {
        if ((x0 + (++forword) > SIZE - 2) || ((y0 - forword) < 0))
        {
            p.dir[7].isEmpty = false;
            break;
        }
        if(m[x0 + forword][y0 - forword] == getChessmanColor(!player))
        {
            p.dir[7].isEmpty = false;
            break;
        }
        if(m[x0 + forword][y0 - forword] == 0)
        {
            p.dir[7].isEmpty = true;
            break;
        }
    }
    p.dir[3].Num = post - 1;
    p.dir[7].Num = forword -1;

    calculateScore(p);
    m[x0][y0] = 0;
    return p;
}
