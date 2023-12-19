#include "cstyleditemdelegate.h"

#include <QSpinBox>
#include <QComboBox>

CStyledItemDelegate::CStyledItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *CStyledItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 4)
    {
        QSpinBox *editor = new QSpinBox(parent);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if(index.column() == 5)
    {
        QComboBox *editor = new QComboBox(parent);
        return editor;
    }
//    return QStyledItemDelegate::createEditor(parent, option, index);
}

void CStyledItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column() == 4)
    {
        int value = index.model()->data(index).toInt();
        QSpinBox *spinBox = qobject_cast<QSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if(index.column() == 5)
    {
        QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
        QStringList list;
        list << "111" << "222" << "333";
        comboBox->addItems(list);
        QString value = index.model()->data(index).toString();
        comboBox->setCurrentText(value);//若是初始值不属于comboBox中任何一个item项，则默认选择首项
    }
//    QStyledItemDelegate::setEditorData(editor, index);
}

void CStyledItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.column() == 4)
    {
        QSpinBox *spinBox = qobject_cast<QSpinBox*>(editor);
        spinBox->interpretText();//对输入的值解析，合法值则转换，否则保留初始值
        int value = spinBox->value();
        model->setData(index , value , Qt::EditRole);
    }
    else if(index.column() == 5)
    {
        QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
        model->setData(index , comboBox->currentText() , Qt::EditRole);
    }
    //    QStyledItemDelegate::setModelData(editor, model, index);
}

//void CStyledItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    QStyledItemDelegate::paint(painter , option, index);
//}

//bool CStyledItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
//{
//    return QStyledItemDelegate::editorEvent(event , model , option , index);
//}
