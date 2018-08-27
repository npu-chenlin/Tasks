#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

#include "player.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static const int SIZE = 15;
    const int WIDTH = 30;
    const int x_offset = 20, y_offset = 20;

protected:
    void mouseReleaseEvent(QMouseEvent *event);

private slots:

private:
    void paintEvent(QPaintEvent *);//绘图函数声明
    QPainter paint;

private:
    int m[SIZE - 1][SIZE - 1];
    Player computer((int*)m,SIZE);
    int steps = 0;
};

#endif // MAINWINDOW_H
