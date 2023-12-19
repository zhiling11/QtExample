#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CTableModel.h"
#include "DataStructure.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initialize();

private:
    Ui::MainWindow *ui;
    CTableModel * m_tableModel;
    QList<DataStructure> m_dataStructureList;
};

#endif // MAINWINDOW_H
