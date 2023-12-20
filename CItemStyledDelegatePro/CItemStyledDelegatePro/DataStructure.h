#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QString>
#include <QMetaType>
class DataStructure
{
public:
    DataStructure();

    QString col0;
    QString col1;
    QString col2;
    QString col3;
    QString col4;
    QString col5;

    bool isChecked;
};
Q_DECLARE_METATYPE(DataStructure)

#endif // DATASTRUCTURE_H
