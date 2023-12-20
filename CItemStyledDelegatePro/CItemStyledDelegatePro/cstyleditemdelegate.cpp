#include "cstyleditemdelegate.h"

#include "DataStructure.h"
#include <QSpinBox>
#include <QComboBox>
#include <QApplication>
#include <QMouseEvent>
#include <QRect>
#include <QDebug>

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

void CStyledItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        QRect rect = option.rect;
        QRect rectCheckBox= rect.adjusted(2, 2, -(rect.width() - rect.height())-2 , -2);//复选框
        QRect rectText= rect.adjusted(rect.height() +2 , 2 , -2 , -2);//文本

        QStyleOptionComboBox comboBox;
        comboBox.rect = rectCheckBox;
        comboBox.state |= QStyle::State_Enabled | QStyle::State_Active;
        bool isChecked = index.data(Qt::UserRole+1).value<DataStructure>().isChecked;
        if(isChecked)
        {
            comboBox.state |= QStyle::State_On;
        }
        else
        {
            comboBox.state |= QStyle::State_Off;
        }

        QApplication::style()->drawPrimitive(QStyle::PE_IndicatorCheckBox , &comboBox , painter);
        QApplication::style()->drawItemText(painter, rectText, Qt::AlignLeft|Qt::AlignVCenter , QPalette() , true , index.data(Qt::DisplayRole).toString());
        return;
    }
    else if(index.column() == 2)
    {
        //绘制双按钮
        QRect rect = option.rect;//获取单元格大小
        QRect rect1 = rect.adjusted(2, 2, -rect.width()/2 -2 , -2);
        QRect rect2 = rect.adjusted(rect.width()/2 +2, 2, -2 , -2);

        QStyleOptionButton button1;
        button1.rect = rect1;
        button1.text = QString("A");
        QApplication::style()->drawControl(QStyle::CE_PushButton , &button1  ,painter);

        QStyleOptionButton button2;
        button2.rect = rect2;
        button2.text = QString("B");
        QApplication::style()->drawControl(QStyle::CE_PushButton , &button2  ,painter);
        return;
    }
    QStyledItemDelegate::paint(painter , option, index);
}

bool CStyledItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(index.column() == 0)
        {
            bool isChecked = index.data(Qt::UserRole+1).value<DataStructure>().isChecked;
            if(isChecked)
            {
                model->setData(index , false , Qt::UserRole+1);
            }
            else
            {
                model->setData(index , true , Qt::UserRole+1);
            }
            return true;
        }
        else if(index.column() == 2)
        {
            //获取点击位置
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPoint pos = mouseEvent->pos();

            QRect rect = option.rect;//获取单元格大小
            QRect rect1 = rect.adjusted(2, 2, -rect.width()/2 -2 , -2);
            QRect rect2 = rect.adjusted(rect.width()/2 +2, 2, -2 , -2);

            //判断点击的按钮
            if(rect1.contains(pos))
            {
                qDebug() << QString("点击按钮A");
            }
            else if(rect2.contains(pos))
            {
                qDebug() << QString("点击按钮B");
            }
            return true;
        }
    }
    return QStyledItemDelegate::editorEvent(event , model , option , index);
}
