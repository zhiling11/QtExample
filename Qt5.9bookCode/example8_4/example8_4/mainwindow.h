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

    void iniGraphicsSystem();//创建Graphics View图形

protected:
    void resizeEvent(QResizeEvent * event);//窗口改变大小事件

private slots:
    void on_mouseMovePoint(QPoint point);
    void on_mouseCliked(QPoint point);

};
#endif // MAINWINDOW_H
