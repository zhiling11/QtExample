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

    if(role == Qt::DisplayRole || role == Qt::EditRole)
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
        {
            int value =  m_dataStructureList.at(index.row()).col3.toInt();
            return value;
            break;
        }
        case 4:
            return m_dataStructureList.at(index.row()).col4;
            break;
        case 5:
            return m_dataStructureList.at(index.row()).col5;
            break;
        }
    }
    if(role == Qt::UserRole+ 1)
    {
        return QVariant::fromValue(m_dataStructureList.at(index.row()));
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

Qt::ItemFlags CTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    return flags;
}

bool CTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;

    if(role == Qt::EditRole)
    {
        QString str = value.toString();
        switch (index.column()) {
        case 0:
            m_dataStructureList[index.row()].col0 = str;
            break;
        case 1:
            m_dataStructureList[index.row()].col1 = str;
            break;
        case 2:
            m_dataStructureList[index.row()].col2 = str;
            break;
        case 3:
        {
            m_dataStructureList[index.row()].col3 = str;
            break;
        }
        case 4:
            m_dataStructureList[index.row()].col4 = str;
            break;
        case 5:
            m_dataStructureList[index.row()].col5 = str;
            break;
        default:
            break;
        }
        emit dataChanged(index,index);
        return true;
    }

    if(role == Qt::UserRole +1)
    {
        if(value.canConvert<bool>())
        {
            bool isChecked = value.toBool();
            m_dataStructureList[index.row()].isChecked = isChecked;
            emit dataChanged(index , index);//通知试图刷新
            return true;
        }
    }
    return false;
}
