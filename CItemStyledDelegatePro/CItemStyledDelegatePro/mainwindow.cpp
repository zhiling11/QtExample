#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cstyleditemdelegate.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    m_tableModel = new CTableModel(this);
    CStyledItemDelegate * cStyledItemDelegate = new CStyledItemDelegate(this);
    ui->tableView->setItemDelegateForColumn(2, cStyledItemDelegate);
    ui->tableView->setItemDelegateForColumn(4, cStyledItemDelegate);
    ui->tableView->setItemDelegateForColumn(5, cStyledItemDelegate);

    for(int i = 0 ; i < 5 ; i++)
    {
        DataStructure dataStructure;
        dataStructure.col0 = QString::number(i) + QString::number(0);
        dataStructure.col1 = QString::number(i) + QString::number(1);
        dataStructure.col2 = QString::number(i) + QString::number(2);
        dataStructure.col3 = QString::number(i) + QString::number(3);
        dataStructure.col4 = QString::number(i) + QString::number(4);
        dataStructure.col5 = QString::number(i) + QString::number(5);

        m_dataStructureList.append(dataStructure);
    }
    m_tableModel->updateTable(m_dataStructureList);
    ui->tableView->setModel(m_tableModel);

}
