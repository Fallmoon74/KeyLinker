/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *BtnOpen;
    QPushButton *BtnSave;
    QPushButton *BtnNew;
    QSpacerItem *verticalSpacer;
    QListWidget *commandList;
    QVBoxLayout *verticalLayout_2;
    QPushButton *BtnStart;
    QPushButton *BtnQuit;
    QPushButton *SetKeys;
    QPushButton *SetDelay;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(422, 312);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icon_q7l9eog4wo9/TitleIcon.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Widget->setWindowIcon(icon);
        horizontalLayout_3 = new QHBoxLayout(Widget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(30);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(50, -1, 50, -1);
        BtnOpen = new QPushButton(Widget);
        BtnOpen->setObjectName("BtnOpen");

        horizontalLayout->addWidget(BtnOpen);

        BtnSave = new QPushButton(Widget);
        BtnSave->setObjectName("BtnSave");

        horizontalLayout->addWidget(BtnSave);

        BtnNew = new QPushButton(Widget);
        BtnNew->setObjectName("BtnNew");

        horizontalLayout->addWidget(BtnNew);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(10, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        commandList = new QListWidget(Widget);
        commandList->setObjectName("commandList");

        verticalLayout->addWidget(commandList);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(10, 0, 10, 0);
        BtnStart = new QPushButton(Widget);
        BtnStart->setObjectName("BtnStart");
        BtnStart->setMinimumSize(QSize(40, 40));
        BtnStart->setMaximumSize(QSize(40, 40));
        BtnStart->setStyleSheet(QString::fromUtf8("QPushButton { border-image: url(:/icon_q7l9eog4wo9/Start.ico); }\n"
"\n"
"QPushButton::hover { border-image: url(:/icon_q7l9eog4wo9/Startfloat.ico);}"));

        verticalLayout_2->addWidget(BtnStart);

        BtnQuit = new QPushButton(Widget);
        BtnQuit->setObjectName("BtnQuit");
        BtnQuit->setMinimumSize(QSize(40, 40));
        BtnQuit->setMaximumSize(QSize(40, 40));
        BtnQuit->setStyleSheet(QString::fromUtf8("QPushButton { border-image: url(:/icon_q7l9eog4wo9/Quit.ico); }\n"
"QPushButton::hover { border-image: url(:/icon_q7l9eog4wo9/Quitfloat.ico); }"));

        verticalLayout_2->addWidget(BtnQuit);

        SetKeys = new QPushButton(Widget);
        SetKeys->setObjectName("SetKeys");
        SetKeys->setMinimumSize(QSize(40, 40));
        SetKeys->setMaximumSize(QSize(40, 40));
        SetKeys->setStyleSheet(QString::fromUtf8("QPushButton {border-image: url(:/icon_q7l9eog4wo9/New.ico);}\n"
"QPushButton::hover {\n"
"border-image: url(:/icon_q7l9eog4wo9/Newfloat.ico);}"));

        verticalLayout_2->addWidget(SetKeys);

        SetDelay = new QPushButton(Widget);
        SetDelay->setObjectName("SetDelay");
        SetDelay->setMinimumSize(QSize(40, 40));
        SetDelay->setMaximumSize(QSize(40, 40));
        SetDelay->setStyleSheet(QString::fromUtf8("QPushButton {border-image: url(:/icon_q7l9eog4wo9/Delay.ico);}\n"
"QPushButton::hover {\n"
"	border-image: url(:/icon_q7l9eog4wo9/Delayfloat.ico);}"));

        verticalLayout_2->addWidget(SetDelay);


        horizontalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "KeyLinker", nullptr));
        BtnOpen->setText(QCoreApplication::translate("Widget", "Open", nullptr));
        BtnSave->setText(QCoreApplication::translate("Widget", "Save", nullptr));
        BtnNew->setText(QCoreApplication::translate("Widget", "New", nullptr));
        BtnStart->setText(QString());
        BtnQuit->setText(QString());
        SetKeys->setText(QString());
        SetDelay->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
