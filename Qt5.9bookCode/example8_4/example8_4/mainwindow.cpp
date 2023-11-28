#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labViewCord = new QLabel("View 坐标: ");
    labViewCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labViewCord);

    labSceneCord = new QLabel("Scene 坐标: ");
    labSceneCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labSceneCord);

    labItemCord = new QLabel("Item 坐标: ");
    labItemCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labItemCord);

    ui->graphicsView->setCursor(Qt::CrossCursor);//鼠标形状设置
    ui->graphicsView->setMouseTracking(true);//鼠标移动事件
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);//鼠标拖拽

    connect(ui->graphicsView , &GraphicsView::mouseMovePoint , this , &MainWindow::on_mouseMovePoint);
    connect(ui->graphicsView , &GraphicsView::mouseCliked , this , &MainWindow::on_mouseCliked);

    iniGraphicsSystem();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniGraphicsSystem()
{
    //sccene逻辑坐标定义
    QRectF rect(-200 , -100 , 400 , 200);//左上角坐标，宽高
    scene = new QGraphicsScene(rect);
    ui->graphicsView->setScene(scene);

    //绘制一个矩形，大小等于scene
    QGraphicsRectItem *item = new QGraphicsRectItem(rect);
    item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    scene->addItem(item);

    //绘制一个位于scene中心的椭圆，测试局部坐标
    QGraphicsEllipseItem *item2 = new QGraphicsEllipseItem(-100 , -50 ,200 ,100);
    item2->setPos(0,0);
    item2->setBrush(QBrush(Qt::blue));
    item2->setFlags(QGraphicsItem::ItemIsMovable |QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    scene->addItem(item2);

    //绘制一个元，位于中心边缘
    QGraphicsEllipseItem *item3 = new QGraphicsEllipseItem(-50 , -50 ,100 ,100);
    item3->setPos(rect.right() , rect.bottom());
    item3->setBrush(QBrush(Qt::red));
    item3->setFlags(QGraphicsItem::ItemIsMovable |QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    scene->addItem(item3);

    scene->clearSelection();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->labViewSize->setText(QString::asprintf("Graphics View坐标,左上角总是(0,0),宽度= %d, 高度= %d" , ui->graphicsView->width() , ui->graphicsView->height()));
    QRectF rectF = ui->graphicsView->sceneRect();
    ui->labSceneRect->setText(QString::asprintf("QGraphicsView::sceneRect= (left,Top,Width,Height)=%.0f,%.0f,%.0f,%.0f" , rectF.left() , rectF.top() , rectF.width() , rectF.height()) );

}

void MainWindow::on_mouseMovePoint(QPoint point)
{
    //鼠标移动事件，point是graphicsView得坐标，物理坐标
    labViewCord->setText(QString::asprintf("View 坐标: %d, %d" , point.x() , point.y()));

    //转换为scene的坐标
    QPointF pointScene = ui->graphicsView->mapToScene(point);
    labSceneCord->setText(QString::asprintf("Scene 坐标: %d, %d" , pointScene.x() , pointScene.y()));
}

void MainWindow::on_mouseCliked(QPoint point)
{
    //鼠标单击事件
    QPointF pointScene = ui->graphicsView->mapToScene(point);
    QGraphicsItem *item =  NULL;
    item = scene->itemAt(pointScene , ui->graphicsView->transform());
    if(item != NULL)
    {
        QPointF pointItem = ui->graphicsView->mapFromScene(pointScene);
        labItemCord->setText(QString::asprintf("Item 坐标: %d, %d" , pointItem.x() , pointItem.y()));
    }

}

