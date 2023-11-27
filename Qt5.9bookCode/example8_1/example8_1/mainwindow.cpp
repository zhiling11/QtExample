#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QRect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//告诉引擎尽量使用反锯齿绘制图形
    painter.setRenderHint(QPainter::TextAntialiasing);//告诉引擎尽量使用反2锯齿绘制文字
    int w = this->width();
    int h= this->height();
    QRect rect(w/4 , h/4 , w/2 , h/2);//x,y,widget,height

    //设置画笔
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);//线端点样式
    pen.setJoinStyle(Qt::BevelJoin);//线段连接方式
    painter.setPen(pen);

    //设置画刷
    QBrush brush;
    brush.setColor(Qt::yellow);//画刷样式
    brush.setStyle(Qt::SolidPattern);//画刷填充样式
    painter.setBrush(brush);

    //绘图
    painter.drawRect(rect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

