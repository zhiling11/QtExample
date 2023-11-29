#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QLabel *labViewCord;
    QLabel *labSceneCord;
    QLabel *labItemCord;
    QLabel  *labItemInfo;

    static const int ItemId = 1;   //绘图项自定义数据的key
    static const int ItemDesciption = 2;   //绘图项自定义数据的key

    int seqNum=0;//图形编号
    int backZ=0;//用于bring to front
    int frontZ=0;//用于bring to back

private slots:
    void    on_mouseMovePoint(QPoint point); //鼠标移动

    void    on_mouseCliked(QPoint point); //鼠标单击

    void    on_mouseDoubleClick(QPoint point); //鼠标双击

    void    on_keyPress(QKeyEvent *event); //按键

    void on_actItem_Rect_triggered();

    void on_actItem_Ellipse_triggered();

    void on_actItem_Polygon_triggered();

    void on_actEdit_Delete_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actRestore_triggered();

    void on_actRotateLeft_triggered();

    void on_actRotateRight_triggered();

    void on_actEdit_Front_triggered();

    void on_actEdit_Back_triggered();

    void on_actItem_Line_triggered();

    void on_actItem_Text_triggered();

    void on_actGroup_triggered();

    void on_actGroupBreak_triggered();

    void on_actItem_Circle_triggered();

    void on_actItem_Triangle_triggered();

};
#endif // MAINWINDOW_H
