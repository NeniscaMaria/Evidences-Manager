/********************************************************************************
** Form generated from reading UI file 'QtGuiApplication2.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIAPPLICATION2_H
#define UI_QTGUIAPPLICATION2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyListTable
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyListTable)
    {
        if (MyListTable->objectName().isEmpty())
            MyListTable->setObjectName(QString::fromUtf8("MyListTable"));
        MyListTable->resize(600, 400);
        centralWidget = new QWidget(MyListTable);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        horizontalLayout->addWidget(tableView);

        MyListTable->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyListTable);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        MyListTable->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyListTable);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MyListTable->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MyListTable);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MyListTable->setStatusBar(statusBar);

        retranslateUi(MyListTable);

        QMetaObject::connectSlotsByName(MyListTable);
    } // setupUi

    void retranslateUi(QMainWindow *MyListTable)
    {
        MyListTable->setWindowTitle(QApplication::translate("MyListTable", "QtGuiApplication2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyListTable: public Ui_MyListTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIAPPLICATION2_H
