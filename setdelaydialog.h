#ifndef SETDELAYDIALOG_H
#define SETDELAYDIALOG_H

#include <QDialog>
#include <ui_setdelaydialog.h>

class SetDelayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetDelayDialog(QWidget *parent = nullptr);
    ~SetDelayDialog();

    QString getDelay() const; // 返回用户输入的延迟时间

private slots:
    void onBtnAcceptClicked();
    void onBtnCancelClicked();

private:
    Ui::SetDelayDialog *ui;
};

#endif // SETDELAYDIALOG_H
