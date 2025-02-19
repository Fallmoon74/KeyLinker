#ifndef KEYSELECTIONDIALOG_H
#define KEYSELECTIONDIALOG_H

#include <QDialog>
#include "ui_KeySelectionDialog.h"
#include <QPushButton>
#include <QMessageBox>

class KeySelectionDialog : public QDialog, private Ui::KeySelectionDialog
{
    Q_OBJECT

public:
    explicit KeySelectionDialog(QWidget *parent = nullptr);
    int selectedCount;
    QString getSelectedKeys() const;
    void setupKeyConnections();
    int getDuration() const; // 获取用户输入的按键持续毫秒值

private slots:
    void onKeyButtonClicked();
    void onAcceptButtonClicked();
    void onCancelButtonClicked();

private:

    QStringList selectedKeys;
    int durationTime; // 用户输入的按键持续毫秒值

    void updateButtonsState();
};

#endif // KEYSELECTIONDIALOG_H
