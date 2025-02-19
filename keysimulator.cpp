#include "keysimulator.h"

// 构造函数
KeySimulator::KeySimulator(QObject *parent)
    : QObject(parent), timer(new QTimer(this))
{
    connect(this, &KeySimulator::startTimer, timer, static_cast<void (QTimer::*)()>(&QTimer::start));
    connect(this, &KeySimulator::quitTimer, timer, static_cast<void (QTimer::*)()>(&QTimer::stop));
    connect(timer, &QTimer::timeout, this, &KeySimulator::executeNextKey);
}

// 析构函数
KeySimulator::~KeySimulator() {
    if (isRunning) stop(); // 确保在销毁对象时停止执行
    delete timer;
}

// 设置指令序列
void KeySimulator::setKeys(const QStringList &keys) {
    this->keys = keys;
    currentIndex = 0; // 重置索引
}

// 开始执行按键序列
void KeySimulator::start() {
    if (!isRunning) {
        isRunning = true;
        emit startTimer();
    }
}

// 停止执行按键序列
void KeySimulator::stop() {
    isRunning = false;
    emit quitTimer();
}

// 按指令执行下一个按键或按键组合
void KeySimulator::executeNextKey() {
    if (!isRunning) return;

    if (currentIndex >= keys.size()) {
        currentIndex = 0; // 循环回到开头
    }

    QString currentKey = keys[currentIndex];    // keys 形如["Ctrl,Shift,A", "Alt,F4", "100"]
    // qDebug() << "Executing key:" << currentKey;

    InterceptionContext context = interception_create_context();
    if (!context) {
        qDebug() << "Failed to create interception context.";
        currentIndex++;
        return;
    }

    // 判断当前指令是否为延迟指令
    bool isDelayInstruction = false;
    int delayTime = 0;

    if (currentKey.toInt(&isDelayInstruction) >= 10) { // 如果能转换为大于等于10的整数，则为延迟指令
        if (isDelayInstruction) {
            delayTime = currentKey.toInt(); // 获取延迟时间
            // qDebug() << "Delaying for" << delayTime << "ms";
            Sleep(delayTime); // 执行延迟
            currentIndex++; // 跳过延迟指令
            interception_destroy_context(context); // 销毁上下文
            return; // 延迟指令无需进一步处理
        }
    }

    QStringList subKeys = currentKey.split(","); // 将现有的指令分割成单键存储，处理同时按下的多个键
    int keyCount = subKeys.count();

    // 提取持续时间（最后一个元素）
    bool isValidDuration;
    int holdDuration = subKeys.last().toInt(&isValidDuration);

    if (!isValidDuration || holdDuration < 10) { // 如果不是有效数字或小于10，则默认为50ms
        holdDuration = 50;
        qDebug() << "Invalid or missing duration, using default hold time of" << holdDuration << "ms";
    } else {
        qDebug() << "Hold duration set to" << holdDuration << "ms";
    }

    // 移除持续时间，仅保留按键部分
    subKeys.removeLast(); // 删除最后一个元素（持续时间）
    keyCount--; // 按键数量减一

    // 创建按键按下和释放的序列
    InterceptionKeyStroke keyStrokesDown[keyCount]; // 按键指令中最后一个为持续秒数，不需要加入键盘事件里
    InterceptionKeyStroke keyStrokesUp[keyCount];

    for (int i = 0; i < keyCount; ++i) {
        QString key = subKeys[i].trimmed(); // 去除多余空格

        // 将按键名称映射为虚拟键码再映射为扫描键码
        int virtualKeyCode = MapKeyNameToKeyCode(key);
        if (virtualKeyCode == 0) {
            // qDebug() << "Unknown key:" << key;
            continue;
        }

        UINT scanCode = MapVirtualKey(virtualKeyCode, MAPVK_VK_TO_VSC);
        // qDebug() << scanCode;
        if (scanCode == 0) {
            // qDebug() << "Failed to map virtual key code to scan code for key:" << key;
            continue;
        }

        // 设置按下状态
        keyStrokesDown[i].code = scanCode;
        keyStrokesDown[i].state = INTERCEPTION_KEY_DOWN;

        // 设置释放状态
        keyStrokesUp[i].code = scanCode;
        keyStrokesUp[i].state = INTERCEPTION_KEY_UP;
    }

    // 发送按键按下事件，按50ms的间隔来循环发送按键按下以达到持续按下的目的
    for(int pressTimes = 0;pressTimes < holdDuration/50;pressTimes++){
        interception_send(context, INTERCEPTION_KEYBOARD(0), (InterceptionStroke*)keyStrokesDown, keyCount);
        Sleep(50);
    }

    Sleep(50); // 如果只按下一次，默认50ms

    // 发送按键释放事件
    interception_send(context, INTERCEPTION_KEYBOARD(0), (InterceptionStroke*)keyStrokesUp, keyCount);

    // 检查下一个指令是否为延迟指令
    int nextIndex = currentIndex + 1;
    if (nextIndex < keys.size()) {
        QString nextKey = keys[nextIndex];
        bool isNextDelayInstruction = false;
        delayTime = nextKey.toInt(&isNextDelayInstruction);

        if (isNextDelayInstruction) {
            // qDebug() << "Next instruction is a delay of" << delayTime << "milliseconds";
        } else {
            delayTime = 50; // 默认延迟 50 毫秒
            // qDebug() << "No delay instruction found, using default delay of" << delayTime << "milliseconds";
        }
    } else {
        delayTime = 50; // 如果没有下一个指令，默认延迟 50 毫秒
        // qDebug() << "End of command list reached, using default delay of" << delayTime << "milliseconds";
    }

    Sleep(delayTime); // 执行延迟

    // 销毁上下文
    interception_destroy_context(context);

    currentIndex++;
}

int KeySimulator::MapKeyNameToKeyCode(const QString &keyName) {
    // 定义按键名称到虚拟键码的映射
    // 根据ui界面上按钮上的字符来的
    static QMap<QString, int> keyMap = {
        {"Esc", VK_ESCAPE},
        {"F1", VK_F1}, {"F2", VK_F2}, {"F3", VK_F3}, {"F4", VK_F4},
        {"F5", VK_F5}, {"F6", VK_F6}, {"F7", VK_F7}, {"F8", VK_F8},
        {"F9", VK_F9}, {"F10", VK_F10}, {"F11", VK_F11}, {"F12", VK_F12},

        {"PrtSc", VK_SNAPSHOT}, {"SL", VK_SCROLL}, {"Pause", VK_PAUSE},

        {"Insert", VK_INSERT}, {"Home", VK_HOME}, {"PgUp", VK_PRIOR},
        {"Delete", VK_DELETE}, {"End", VK_END}, {"PgDn", VK_NEXT},

        {"Right", VK_RIGHT}, {"Left", VK_LEFT}, {"Down", VK_DOWN}, {"Up", VK_UP},

        {"NumLock", VK_NUMLOCK}, {"Num0", VK_NUMPAD0}, {"Num1", VK_NUMPAD1},
        {"Num2", VK_NUMPAD2}, {"Num3", VK_NUMPAD3}, {"Num4", VK_NUMPAD4},
        {"Num5", VK_NUMPAD5}, {"Num6", VK_NUMPAD6}, {"Num7", VK_NUMPAD7},
        {"Num8", VK_NUMPAD8}, {"Num9", VK_NUMPAD9}, {"+", VK_ADD},
        {"-", VK_SUBTRACT}, {"*", VK_MULTIPLY}, {"/", VK_DIVIDE},

        {"Backspace", VK_BACK}, {"Tab", VK_TAB}, {"Enter", VK_RETURN},
        {"Space", VK_SPACE}, {"CapsLock", VK_CAPITAL},

        {"Shift", VK_LSHIFT}, {"Ctrl", VK_LCONTROL}, {"Alt", VK_LMENU}, {"Win", VK_LWIN},

        // 字母键
        {"A", 'A'}, {"B", 'B'}, {"C", 'C'}, {"D", 'D'}, {"E", 'E'},
        {"F", 'F'}, {"G", 'G'}, {"H", 'H'}, {"I", 'I'}, {"J", 'J'},
        {"K", 'K'}, {"L", 'L'}, {"M", 'M'}, {"N", 'N'}, {"O", 'O'},
        {"P", 'P'}, {"Q", 'Q'}, {"R", 'R'}, {"S", 'S'}, {"T", 'T'},
        {"U", 'U'}, {"V", 'V'}, {"W", 'W'}, {"X", 'X'}, {"Y", 'Y'},
        {"Z", 'Z'},

        // 数字键
        {"0", '0'}, {"1", '1'}, {"2", '2'}, {"3", '3'}, {"4", '4'},
        {"5", '5'}, {"6", '6'}, {"7", '7'}, {"8", '8'}, {"9", '9'},

        // 符号键
        {".", VK_DECIMAL}, {"`", VK_OEM_3}, {"=", VK_OEM_PLUS}, {"[", VK_OEM_4}, {"]", VK_OEM_6}, {"\\", VK_OEM_5},
        {";", VK_OEM_1}, {"'", VK_OEM_7}, {",", VK_OEM_COMMA} /*{".", VK_OEM_PERIOD}*/
        // Comma 没法正常识别，因为是用,隔开不同的指令的
    };

    // 查找按键名称对应的虚拟键码
    if (keyMap.contains(keyName)) {
        // qDebug() << keyMap[keyName];
        return keyMap[keyName];
    }

    // 如果未找到匹配项，返回 0 表示未知键
    // qDebug() << "Unsupported key:" << keyName;
    return 0;
}



