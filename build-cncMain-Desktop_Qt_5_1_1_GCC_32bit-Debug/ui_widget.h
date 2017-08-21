/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widgetTitle;
    QLabel *labelLogo;
    QWidget *widgetBottom;
    QWidget *widgetRight;
    QWidget *widgetView;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(851, 592);
        widgetTitle = new QWidget(Widget);
        widgetTitle->setObjectName(QStringLiteral("widgetTitle"));
        widgetTitle->setGeometry(QRect(0, 0, 851, 101));
        labelLogo = new QLabel(widgetTitle);
        labelLogo->setObjectName(QStringLiteral("labelLogo"));
        labelLogo->setGeometry(QRect(0, 0, 101, 101));
        labelLogo->setAlignment(Qt::AlignCenter);
        widgetBottom = new QWidget(Widget);
        widgetBottom->setObjectName(QStringLiteral("widgetBottom"));
        widgetBottom->setGeometry(QRect(0, 490, 851, 101));
        widgetRight = new QWidget(Widget);
        widgetRight->setObjectName(QStringLiteral("widgetRight"));
        widgetRight->setGeometry(QRect(730, 100, 120, 391));
        widgetView = new QWidget(Widget);
        widgetView->setObjectName(QStringLiteral("widgetView"));
        widgetView->setGeometry(QRect(0, 100, 731, 391));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        labelLogo->setText(QApplication::translate("Widget", "LOGO", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
