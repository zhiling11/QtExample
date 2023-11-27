﻿#ifndef CTABLEMODEL_H
#define CTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "DataStructure.h"
class CTableModel : public QAbstractTableModel
{
public:
    CTableModel(QObject * parent);
    /************************一、数据显示*****************************/
    ///1、显示表头数据
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    ///2、使用QAbstractTableModel必须继承函数
    //行数
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    //列数
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    //显示单元格内数据,包括显示、编辑、颜色等数据
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /************************二、更新数据*****************************/
    ///3、更新数据
    bool updateTable(QList<DataStructure> dataStructureList);

    /************************三、数据编辑*****************************/
    /***
     * 1、设置数据可编辑
     * *************************************************************/
    ///4、设置可编辑数据标志
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    /// 5、保存编辑后的数据
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);


private:
    QList<DataStructure> m_dataStructureList;
    QList<QString> m_headerList;
};

#endif // CTABLEMODEL_H
