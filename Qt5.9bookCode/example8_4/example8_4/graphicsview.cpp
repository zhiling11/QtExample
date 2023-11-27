#include "graphicsview.h"

#include <QPoint>
#include <QMouseEvent>
GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{

}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    emit mouseMovePoint(point);
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() ==  Qt::LeftButton)
    {
        QPoint point = event->pos();
        emit mouseCliked(point);
    }
    QGraphicsView::mousePressEvent(event);
}
