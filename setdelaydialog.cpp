#include "setdelaydialog.h"
#include "ui_setdelaydialog.h"

SetDelayDialog::SetDelayDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetDelayDialog)
{
    ui->setupUi(this);
    connect(ui->BtnAccept, &QPushButton::clicked, this, &SetDelayDialog::onBtnAcceptClicked);
    connect(ui->BtnCancel, &QPushButton::clicked, this, &SetDelayDialog::onBtnCancelClicked);
}

SetDelayDialog::~SetDelayDialog()
{
    delete ui;
}

QString SetDelayDialog::getDelay() const {
    return ui->lineEditDelay->text(); // 用户在输入延迟时间
}

void SetDelayDialog::onBtnAcceptClicked() {
    accept(); // 关闭对话框并返回QDialog::Accepted
}

void SetDelayDialog::onBtnCancelClicked() {
    // 清空选择的按键列表
    ui->lineEditDelay->clear();

    reject(); // 关闭对话框并返回QDialog::Rejected
}
