/********************************************************************************
** Form generated from reading UI file 'setdelaydialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETDELAYDIALOG_H
#define UI_SETDELAYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetDelayDialog
{
public:
    QPushButton *BtnAccept;
    QPushButton *BtnCancel;
    QLineEdit *lineEditDelay;
    QLabel *IntroLabel;

    void setupUi(QDialog *SetDelayDialog)
    {
        if (SetDelayDialog->objectName().isEmpty())
            SetDelayDialog->setObjectName("SetDelayDialog");
        SetDelayDialog->resize(340, 230);
        SetDelayDialog->setMinimumSize(QSize(340, 230));
        SetDelayDialog->setMaximumSize(QSize(340, 230));
        BtnAccept = new QPushButton(SetDelayDialog);
        BtnAccept->setObjectName("BtnAccept");
        BtnAccept->setGeometry(QRect(50, 160, 81, 31));
        BtnCancel = new QPushButton(SetDelayDialog);
        BtnCancel->setObjectName("BtnCancel");
        BtnCancel->setGeometry(QRect(210, 160, 81, 31));
        lineEditDelay = new QLineEdit(SetDelayDialog);
        lineEditDelay->setObjectName("lineEditDelay");
        lineEditDelay->setGeometry(QRect(50, 80, 241, 31));
        IntroLabel = new QLabel(SetDelayDialog);
        IntroLabel->setObjectName("IntroLabel");
        IntroLabel->setGeometry(QRect(50, 30, 241, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft JhengHei")});
        font.setPointSize(12);
        font.setWeight(QFont::Medium);
        IntroLabel->setFont(font);

        retranslateUi(SetDelayDialog);

        QMetaObject::connectSlotsByName(SetDelayDialog);
    } // setupUi

    void retranslateUi(QDialog *SetDelayDialog)
    {
        SetDelayDialog->setWindowTitle(QCoreApplication::translate("SetDelayDialog", "Dialog", nullptr));
        BtnAccept->setText(QCoreApplication::translate("SetDelayDialog", "Accept", nullptr));
        BtnCancel->setText(QCoreApplication::translate("SetDelayDialog", "Cancel", nullptr));
        IntroLabel->setText(QCoreApplication::translate("SetDelayDialog", "\350\257\267\350\276\223\345\205\245\345\273\266\350\277\237\346\227\266\351\227\264\357\274\210\345\215\225\344\275\215\344\270\272ms\357\274\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetDelayDialog: public Ui_SetDelayDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETDELAYDIALOG_H
