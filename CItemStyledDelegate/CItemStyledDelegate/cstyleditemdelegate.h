#ifndef CSTYLEDITEMDELEGATE_H
#define CSTYLEDITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class CStyledItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CStyledItemDelegate(QObject *parent = nullptr);
    /// 1、给控件添加spinbox、combobox
    //创建编辑器
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    //提供编辑数据
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    //保存编辑的数据到模型中
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

//    ///2、单元个添加按钮、设置复习选框
//    //绘制按钮，文本，复选框
//    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
//    //获取点击事件
//    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) Q_DECL_OVERRIDE;

signals:

};

#endif // CSTYLEDITEMDELEGATE_H
