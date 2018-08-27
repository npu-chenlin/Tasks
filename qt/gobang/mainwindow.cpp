#include <cmath>
#include <vector>
#include <QDebug>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{

  ui->setupUi(this);

}
MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    // FIXME: do not mix the algorithm into the GUI code
    // you can create a board class, and pass the board object into the main window, and then decide how to draw the board

    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing, true);
    paint.setPen(QPen(Qt::darkGray, 2, Qt::SolidLine)); //钢笔工具：颜色，线号，实线 (FIXME: using English comments)
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
    // FIXME: get the user input location, and then pass the data to algorithm class

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
                if (computer.isWin(i, j))
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
                Point p = computer.dropChessman(false);

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
