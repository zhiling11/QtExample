#include "CTableModel.h"


CTableModel::CTableModel(QObject *parent):QAbstractTableModel(parent)
{
    m_headerList<< QString("col0")<< QString("col1")<< QString("col2")<< QString("col3")<< QString("col4")<< QString("col5");
}

QVariant CTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
            return m_headerList.at(section);
    }


    return QVariant();
}

int CTableModel::rowCount(const QModelIndex &parent) const
{
    //判断单元格的父节点是否为非法，非法（NULL是正确的）才会返回行数据
    if(parent.isValid())
        return 0;

    return m_dataStructureList.size();
}

int CTableModel::columnCount(const QModelIndex &parent) const
{
    //判断单元格的父节点是否为非法，非法（NULL是正确的）才会返回列数据
    if(parent.isValid())
        return 0;

    return m_headerList.size();
}

QVariant CTableModel::data(const QModelIndex &index, int role) const
{
    //非法索引，直接返回空值
    if(!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0:
            return m_dataStructureList.at(index.row()).col0;
            break;
        case 1:
            return m_dataStructureList.at(index.row()).col1;
            break;
        case 2:
            return m_dataStructureList.at(index.row()).col2;
            break;
        case 3:
            return m_dataStructureList.at(index.row()).col3;
            break;
        case 4:
            return m_dataStructureList.at(index.row()).col4;
            break;
        case 5:
            return m_dataStructureList.at(index.row()).col5;
            break;
        }
    }

    return QVariant();
}

bool CTableModel::updateTable(QList<DataStructure> dataStructureList)
{
    beginResetModel();
    m_dataStructureList = dataStructureList;
    endResetModel();
    return true;
}
