/********************************************************************************
** Form generated from reading UI file 'getdatafc.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETDATAFC_H
#define UI_GETDATAFC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GetDataFC
{
public:

    void setupUi(QWidget *GetDataFC)
    {
        if (GetDataFC->objectName().isEmpty())
            GetDataFC->setObjectName(QStringLiteral("GetDataFC"));
        GetDataFC->resize(400, 300);

        retranslateUi(GetDataFC);

        QMetaObject::connectSlotsByName(GetDataFC);
    } // setupUi

    void retranslateUi(QWidget *GetDataFC)
    {
        GetDataFC->setWindowTitle(QApplication::translate("GetDataFC", "GetDataFC", 0));
    } // retranslateUi

};

namespace Ui {
    class GetDataFC: public Ui_GetDataFC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETDATAFC_H
