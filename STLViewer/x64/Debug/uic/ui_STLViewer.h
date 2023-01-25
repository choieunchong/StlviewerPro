/********************************************************************************
** Form generated from reading UI file 'STLViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STLVIEWER_H
#define UI_STLVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "customvtkwidget.h"

QT_BEGIN_NAMESPACE

class Ui_STLViewer
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionExit;
    QAction *actionColor;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QSlider *opacitySlider;
    CustomVTKWidget *openGLWidget;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *STLViewer)
    {
        if (STLViewer->objectName().isEmpty())
            STLViewer->setObjectName(QString::fromUtf8("STLViewer"));
        STLViewer->resize(800, 600);
        actionOpen = new QAction(STLViewer);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(STLViewer);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_as = new QAction(STLViewer);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionExit = new QAction(STLViewer);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionColor = new QAction(STLViewer);
        actionColor->setObjectName(QString::fromUtf8("actionColor"));
        centralwidget = new QWidget(STLViewer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        opacitySlider = new QSlider(centralwidget);
        opacitySlider->setObjectName(QString::fromUtf8("opacitySlider"));
        opacitySlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(opacitySlider, 0, 0, 1, 1);

        openGLWidget = new CustomVTKWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));

        gridLayout->addWidget(openGLWidget, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        STLViewer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(STLViewer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        STLViewer->setMenuBar(menubar);
        statusbar = new QStatusBar(STLViewer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        STLViewer->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionOpen);
        menuMenu->addAction(actionSave);
        menuMenu->addAction(actionSave_as);
        menuMenu->addSeparator();
        menuMenu->addAction(actionColor);
        menuMenu->addSeparator();
        menuMenu->addAction(actionExit);

        retranslateUi(STLViewer);

        QMetaObject::connectSlotsByName(STLViewer);
    } // setupUi

    void retranslateUi(QMainWindow *STLViewer)
    {
        STLViewer->setWindowTitle(QCoreApplication::translate("STLViewer", "STLViewer", nullptr));
        actionOpen->setText(QCoreApplication::translate("STLViewer", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("STLViewer", "Save", nullptr));
        actionSave_as->setText(QCoreApplication::translate("STLViewer", "Save as...", nullptr));
        actionExit->setText(QCoreApplication::translate("STLViewer", "Exit", nullptr));
        actionColor->setText(QCoreApplication::translate("STLViewer", "Color", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("STLViewer", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class STLViewer: public Ui_STLViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STLVIEWER_H
