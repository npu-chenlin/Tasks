#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int evaluater(int, int, bool);//0 is white , 1 is black
    void dropChessman(bool);
    static const int SIZE = 14;
    const int WIDTH = 40;
    const int x_offset = 20, y_offset = 20;

protected:
    void mouseReleaseEvent(QMouseEvent *event);

private slots:

private:
    void paintEvent(QPaintEvent *);//绘图函数声明
    bool isWin(int , int);
    QPainter *paint;

private:
    friend class ComputerPlayer;
    int m[SIZE - 1][SIZE - 1];
    int steps = 0;
};

#endif // MAINWINDOW_H
