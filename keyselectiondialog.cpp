#include "keyselectiondialog.h"

KeySelectionDialog::KeySelectionDialog(QWidget *parent) :
    QDialog(parent),
    selectedCount(0)
{
    setupUi(this); // 初始化UI

    // 连接所有按键的点击信号到槽函数
    setupKeyConnections();

    // 连接确认和取消按钮的点击信号
    connect(Btnaccept, &QPushButton::clicked, this, &KeySelectionDialog::onAcceptButtonClicked);
    connect(Btncancel, &QPushButton::clicked, this, &KeySelectionDialog::onCancelButtonClicked);

    // 初始状态更新按钮状态
    updateButtonsState();
    lineEditDuration->setText("50");    // 初始化持续时间，默认为50ms
}

void KeySelectionDialog::onKeyButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString keyText = button->text();

    if (selectedCount < 4) { // 如果未达到最大选择数量
        selectedKeys.append(keyText);
        selectedCount++;
        button->setEnabled(false); // 禁用已选择的按钮
    } else {
        QMessageBox::warning(this, tr("Warning"), tr("You can only select up to 4 keys."));
        return;
    }

    // 更新所有按钮的状态
    updateButtonsState();
}

QString KeySelectionDialog::getSelectedKeys() const {
    return selectedKeys.join(", ");
}

void KeySelectionDialog::updateButtonsState() {
    // 获取所有QPushButton类型的子控件
    QList<QPushButton*> buttons = findChildren<QPushButton*>();
    for (QPushButton *button : buttons) {
        // 如果按钮是接受或取消按钮，则跳过它们
        if (button->objectName() == "Btnaccept" || button->objectName() == "Btncancel") {
            continue;
        }
        // 根据是否已选择该键或已达到最大选择数量来设置按钮状态
        if (selectedKeys.contains(button->text()) || selectedCount >= 4) {
            button->setEnabled(false);
        } else {
            button->setEnabled(true);
        }
    }
}


void KeySelectionDialog::onAcceptButtonClicked() {
    accept(); // 关闭对话框并返回QDialog::Accepted

    durationTime = getDuration();   // 设定好持续时间
}

void KeySelectionDialog::onCancelButtonClicked() {
    // 清空选择的按键列表
    selectedKeys.clear();
    selectedCount = 0;

    // 更新所有按钮的状态
    updateButtonsState();

    reject(); // 关闭对话框并返回QDialog::Rejected
}


void KeySelectionDialog::setupKeyConnections() {
    // 这里输入键的名字（省略Key）
    const QStringList letters = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
                                 "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
                                 "U", "V", "W", "X", "Y", "Z", "LeftShift", "RightShift",
                                 "Esc", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
                                 "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
                                 "Substract", "Equal", "BackSpace", "Wave", "Tab", "LeftBracket", "RightBracket", "BackSlash",
                                 "CapsLock", "Semicolon", "Quotation", "Enter", "Comma", "Period", "Divide",
                                 "LeftCtrl", "RightCtrl", "LeftWin", "RightWin", "LeftAlt", "RightAlt", /*"Menu"*/ "Space",
                                 "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "Num0",
                                 "NumLock", "NumDecimal", "NumDivide", "NumMultiply", "NumSubstract", "NumAdd", "NumEnter",
                                 "Insert", "Home", "PageUp", "Delete", "End", "PageDown", "UpArrow", "DownArrow", "LeftArrow", "RightArrow",
                                 "PrintScreen", "ScrollLock", "Palse"};

    for (const QString &letter : letters) {
        QPushButton *button = findChild<QPushButton*>(QString("Key%1").arg(letter));
        if (button) {
            connect(button, &QPushButton::clicked, this, &KeySelectionDialog::onKeyButtonClicked);
        } else {
            qWarning() << "Button 'Key" << letter << "' not found!";
        }
    }
}

int KeySelectionDialog::getDuration() const {
    bool ok;
    int delay = lineEditDuration->text().toInt(&ok);
    if (ok && delay >= 0) {
        return delay;
    } else {
        // qWarning() << "Invalid delay value, using default value of 50ms.";
        return 50; // 如果输入无效，返回默认值
    }
}
