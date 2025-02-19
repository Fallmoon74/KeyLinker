#ifndef KEYSIMULATOR_H
#define KEYSIMULATOR_H

#include <QObject>
#include <QStringList>
#include <QThread>
#include <QTimer>
#include <interception.h>
#include <QDebug>
#include <windows.h>

class KeySimulator : public QObject {
    Q_OBJECT
public:
    explicit KeySimulator(QObject *parent = nullptr);
    ~KeySimulator();

    void setKeys(const QStringList &keys); // 设置按键序列
    void start(); // 开始执行按键序列
    void stop();  // 停止执行按键序列
    static int MapKeyNameToKeyCode(const QString &keyName);

signals:
    void finished(); // 按键序列执行完成信号
    void startTimer();
    void quitTimer();

private slots:
    void executeNextKey(); // 执行下一个按键或按键组合

public:
    bool isRunning = false; // 是否正在运行

private:
    QStringList keys; // 指令序列
    int currentIndex = 0; // 当前执行的按键索引
    QTimer *timer; // 定时器，用于控制执行频率
};

#endif // KEYSIMULATOR_H
