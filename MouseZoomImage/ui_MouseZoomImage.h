/********************************************************************************
** Form generated from reading UI file 'MouseZoomImage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOUSEZOOMIMAGE_H
#define UI_MOUSEZOOMIMAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MouseZoomImageClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QMainWindow *MouseZoomImageClass)
    {
        if (MouseZoomImageClass->objectName().isEmpty())
            MouseZoomImageClass->setObjectName(QString::fromUtf8("MouseZoomImageClass"));
        MouseZoomImageClass->resize(600, 400);
        centralWidget = new QWidget(MouseZoomImageClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        MouseZoomImageClass->setCentralWidget(centralWidget);

        retranslateUi(MouseZoomImageClass);

        QMetaObject::connectSlotsByName(MouseZoomImageClass);
    } // setupUi

    void retranslateUi(QMainWindow *MouseZoomImageClass)
    {
        MouseZoomImageClass->setWindowTitle(QCoreApplication::translate("MouseZoomImageClass", "MouseZoomImage", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MouseZoomImageClass: public Ui_MouseZoomImageClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOUSEZOOMIMAGE_H
