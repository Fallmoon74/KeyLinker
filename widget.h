#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <keyselectiondialog.h>
#include <setdelaydialog.h>
#include <keysimulator.h>
#include <QThread>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QFile>
#include <QIODevice>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    void saveCommandsToFile(const QStringList &commands);
    QStringList loadCommandsFromFile();
    ~Widget();

private slots:
    void on_SetSingleKey_clicked();
    void on_SetDelay_clicked();

    void onStartButtonClicked(); // 点击开始函数
    void onQuitButtonClicked();


    void on_BtnNew_clicked();

    void on_BtnSave_clicked();

    void on_BtnOpen_clicked();

private:
    Ui::Widget *ui;
    KeySelectionDialog *keySelectionDialog;
    SetDelayDialog *SetDelayDialog;
    QThread *simulatorThread = new QThread();     // 模拟器线程
    KeySimulator *simulator = new KeySimulator();      // 按键模拟器

    QStringList commandStorage;
    QStringList getSelectedKeysFromList() const; // 获取按键序列
};
#endif // WIDGET_H
