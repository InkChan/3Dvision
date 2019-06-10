/********************************************************************************
** Form generated from reading UI file 'moudlewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOUDLEWIDGET_H
#define UI_MOUDLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MoudleWidget
{
public:
    QGraphicsView *graphicsView;
    QPushButton *pushButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_3;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_7;
    QPushButton *pushButton_6;
    QPushButton *pushButton_8;

    void setupUi(QWidget *MoudleWidget)
    {
        if (MoudleWidget->objectName().isEmpty())
            MoudleWidget->setObjectName(QStringLiteral("MoudleWidget"));
        MoudleWidget->resize(1126, 616);
        graphicsView = new QGraphicsView(MoudleWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(260, 50, 621, 531));
        pushButton = new QPushButton(MoudleWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1094, 0, 31, 31));
        pushButton->setFlat(true);
        verticalLayoutWidget = new QWidget(MoudleWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(220, 70, 31, 211));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(verticalLayoutWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        horizontalLayoutWidget = new QWidget(MoudleWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(60, 330, 239, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_7 = new QPushButton(horizontalLayoutWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        horizontalLayout->addWidget(pushButton_7);

        pushButton_6 = new QPushButton(horizontalLayoutWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout->addWidget(pushButton_6);

        pushButton_8 = new QPushButton(horizontalLayoutWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        horizontalLayout->addWidget(pushButton_8);


        retranslateUi(MoudleWidget);

        QMetaObject::connectSlotsByName(MoudleWidget);
    } // setupUi

    void retranslateUi(QWidget *MoudleWidget)
    {
        MoudleWidget->setWindowTitle(QApplication::translate("MoudleWidget", "MoudleWidget", 0));
        pushButton->setText(QApplication::translate("MoudleWidget", "X", 0));
        pushButton_2->setText(QApplication::translate("MoudleWidget", "PushButton", 0));
        pushButton_4->setText(QApplication::translate("MoudleWidget", "PushButton", 0));
        pushButton_5->setText(QApplication::translate("MoudleWidget", "PushButton", 0));
        pushButton_3->setText(QApplication::translate("MoudleWidget", "PushButton", 0));
        pushButton_7->setText(QApplication::translate("MoudleWidget", "PushButton", 0));
        pushButton_6->setText(QApplication::translate("MoudleWidget", "PushButton", 0));
        pushButton_8->setText(QApplication::translate("MoudleWidget", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class MoudleWidget: public Ui_MoudleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOUDLEWIDGET_H
