#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

// 刚开始写的时候本来打算分成同时按下单个键和多个键的情况，不过后来发现一块写了也好，这里所有的single都应该改成multiple
// 不过我懒得改了XD

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);  // 初始化页面

    setWindowIcon(QIcon("://icon_q7l9eog4wo9/TitleIcon.ico"));  // 设置程序图标

    simulator->moveToThread(simulatorThread);

    connect(ui->SetKeys, &QPushButton::clicked, this, &Widget::on_SetSingleKey_clicked);

    connect(ui->BtnStart, &QPushButton::clicked, this, &Widget::onStartButtonClicked);
    ui->BtnStart->setStyleSheet("border-image: url(:/icon_q7l9eog4wo9/Start.ico);"); // 初始化开始键的图标
    // ui->BtnStart->setStyleSheet("QPushButton::hover {border-image: url(:/icon_q7l9eog4wo9/Startfloat.ico);}"); // 设置鼠标悬浮下的图标
    connect(ui->BtnQuit, &QPushButton::clicked, this, &Widget::onQuitButtonClicked);

    simulatorThread->start();   // 启动独立进程
}

Widget::~Widget() {
    if (simulator && simulatorThread) {
        simulator->stop();          // 停止模拟器
        simulatorThread->quit();    // 退出线程
        simulatorThread->wait();    // 等待线程结束
    }
    delete ui;
}

void Widget::on_SetSingleKey_clicked() {
    static int callCount = 0;
    // qDebug() << "SetSingleKey clicked" << ++callCount;
    // 创建KeySelectionDialog的一个实例
    KeySelectionDialog singledialog(this);

    // 显示对话框并等待用户完成操作
    if (singledialog.exec() == QDialog::Accepted) {
        // 如果用户点击确定，获取选择的键值
        QString selectedKeys = singledialog.getSelectedKeys();
        // 这一步返回的是形如"D,C,B"的有分隔符的字符串
        int keyDurationTime = singledialog.getDuration(); // 获取延迟时间

        // 检查是否选择了任何按键
        if (!selectedKeys.isEmpty()) {
            // 将指令存入
            QString fullCommand = QString("%1,%2").arg(selectedKeys).arg(keyDurationTime);
            commandStorage.append(fullCommand);

            // qDebug() << "New command:" << selectedKeys;
            // qDebug() << "Stored command" << commandStorage;

            // 左边栏commandList是一个QListWidget*类型的成员变量，用于展示指令

            QListWidgetItem *item = new QListWidgetItem(selectedKeys);
            item->setText(QString("Press %1 for %2 ms").arg(selectedKeys).arg(keyDurationTime));
            // qDebug() << "Item content:" << item->text();
            ui->commandList->addItem(item); // 将新的指令添加到命令列表中显示出来
        }

    }
}

void Widget::on_SetDelay_clicked() {

    class SetDelayDialog delaydialog(this);

    // 显示对话框并等待用户完成操作
    if (delaydialog.exec() == QDialog::Accepted) {
        QString selectedDelay = delaydialog.getDelay();
        // 这一步返回的是一个数字

        bool isValidNumber;
        int delayValue = selectedDelay.toInt(&isValidNumber);
        if (!isValidNumber || delayValue < 10) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid number over 10ms for the delay.");
            return; // 如果输入无效，直接退出函数
        }

        // 将指令存入，是一个数字
        commandStorage.append(selectedDelay);

        // 左边栏commandList是一个QListWidget*类型的成员变量，用于展示指令
        QListWidgetItem *item = new QListWidgetItem(selectedDelay);
        item->setText(QString("Delay %1 ms").arg(selectedDelay));
        // qDebug() << "Item content:" << item->text();
        ui->commandList->addItem(item); // 将新的指令添加到命令列表中
    }
}

void Widget::onStartButtonClicked() {
    // qDebug() << "Start button clicked!";
    ui->BtnStart->setStyleSheet("border-image: url(:/icon_q7l9eog4wo9/Running.ico);");  // 点击后改变开始键图标

    // 获取当前设置的按键序列
    QStringList keys = commandStorage;

    if (!keys.isEmpty()) {
        // 设置按键序列到模拟器
        simulator->setKeys(keys);
        // qDebug() << "the keys are" << keys;
        // 开始执行按键序列
        simulator->start();

        // qDebug() << "Simulation started with keys:" << keys;
    } else {
        // qDebug() << "No keys selected to simulate.";
    }
}

void Widget::onQuitButtonClicked(){
    // qDebug() << "Quit button clicked!";

    // 现存的问题是，程序会完成当前指令再停止。未解决

    ui->BtnStart->setStyleSheet("border-image: url(:/icon_q7l9eog4wo9/Start.ico);");    // 把开始键的图标改回来
    if (simulator && simulator->isRunning) {
        simulator->stop(); // 停止按键模拟器
        // qDebug() << "Simulation stopped.";
    }
}

// 新建一个指令表
void Widget::on_BtnNew_clicked()
{
    ui->commandList->clear();
    commandStorage.clear();
}


void Widget::on_BtnSave_clicked()
{
    if(!commandStorage.isEmpty()){
        saveCommandsToFile(commandStorage);
    }else{
        // qDebug() << "No keys selected to save.";
    }
}


void Widget::saveCommandsToFile(const QStringList &commandStorage) {
    // 创建 JSON 数组
    QJsonArray jsonArray;

    for (const QString &command : commandStorage) {
        if (command.isEmpty()) {
            continue; // 跳过空指令
        }

        // 解析指令
        QStringList parts = command.split(",");
        if (parts.size() >= 2) {
            // 按键指令
            QJsonObject jsonObject;
            jsonObject["type"] = "key";

            // 提取按键列表
            QStringList keys = parts.mid(0, parts.size() - 1); // 去掉最后一个持续时间字段
            QJsonArray keyArray;
            for (const QString &key : keys) {
                keyArray.append(key);
            }
            jsonObject["keys"] = keyArray;

            // 提取持续时间
            bool isValidDuration;
            int duration = parts.last().toInt(&isValidDuration);
            if (!isValidDuration || duration < 0) {
                duration = 50; // 如果解析失败，默认设置为 50
            }
            jsonObject["duration"] = duration;

            jsonArray.append(jsonObject);
        } else {
            // 延迟指令
            bool isValidTime;
            int time = command.toInt(&isValidTime);
            if (isValidTime && time >= 0) {
                QJsonObject jsonObject;
                jsonObject["type"] = "delay";
                jsonObject["time"] = time;
                jsonArray.append(jsonObject);
            }
        }
    }

    // 创建 JSON 文档
    QJsonDocument jsonDoc(jsonArray);

    // 弹出文件保存对话框
    QString filePath = QFileDialog::getSaveFileName(this, "Save Commands", "", "JSON Files (*.json);;All Files (*)");
    if (filePath.isEmpty()) {
        return; // 用户取消操作
    }

    // 写入文件
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Cannot open file for writing.");
        return;
    }

    file.write(jsonDoc.toJson());
    file.close();

    QMessageBox::information(this, "Success", "KeyLinker file saved successfully");
}

QStringList Widget::loadCommandsFromFile() {
    // 弹出文件打开对话框
    QString filePath = QFileDialog::getOpenFileName(this, "Load Commands", "", "JSON Files (*.json);;All Files (*)");
    if (filePath.isEmpty()) {
        return {}; // 返回空列表
    }

    // 读取文件内容
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Cannot open file for reading.");
        return {};
    }

    QByteArray jsonData = file.readAll();
    file.close();


    // 解析 JSON 文档
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if (!jsonDoc.isArray()) {
        QMessageBox::critical(this, "Error", "Invalid JSON format. The file does not appear to be a valid KeyLinker file.");
        return {};
    }

    QJsonArray jsonArray = jsonDoc.array();
    ui->commandList->clear(); // 清空界面中的命令列表
    commandStorage.clear(); // 清空存储的指令

    for (const QJsonValue &value : jsonArray) {
        if (!value.isObject()) {
            continue; // 跳过非对象类型的值
        }

        QJsonObject jsonObject = value.toObject();

        if (jsonObject["type"].toString() == "key") {
            // 按键指令
            QStringList keys;
            QJsonArray keyArray = jsonObject["keys"].toArray();
            for (const QJsonValue &keyValue : keyArray) {
                keys.append(keyValue.toString());
            }

            int duration = jsonObject["duration"].toInt(50); // 默认持续时间为 50
            QString command1 = keys.join(",");
            commandStorage.append(command1+ "," + QString::number(duration));
            QListWidgetItem *item = new QListWidgetItem(command1);
            item->setText(QString("Press %1 for %2 ms").arg(command1).arg(duration));
            ui->commandList->addItem(item); // 将新的指令添加到命令列表中

        } else if (jsonObject["type"].toString() == "delay") {
            // 延迟指令
            int time = jsonObject["time"].toInt();
            QString command2 = QString::number(time);
            commandStorage.append(QString::number(time));
            QListWidgetItem *item = new QListWidgetItem(command2);
            item->setText(QString("Delay %1 ms").arg(command2));
            ui->commandList->addItem(item); // 将新的指令添加到命令列表中
        }
    }

    return commandStorage;
}

void Widget::on_BtnOpen_clicked()
{
    loadCommandsFromFile();
}

