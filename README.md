# KeyLinker

This program is a virtual keyboard input tool developed based on system drivers. It simulates a standard 104-key keyboard and enables high-privilege global keyboard event simulation.
By bypassing application-layer restrictions and directly interacting with hardware, it can be used to penetrate the DirectX channel and operate games directly.


## Usage Instructions

The left side of the program interface is the command panel, which displays the list of user input commands. The four buttons on the right are Start, Stop, New Key Command, and New Delay Command.
Clicking Start will trigger the program to automatically loop through and execute the keyboard commands in the list.

A maximum of **four keys** can be pressed simultaneously. Both **tap** and **hold** actions are supported, with tap being the default (literally last for 50ms).

And by default, there is a **50ms** wait time between two key commands to prevent excessive system load.

The program supports saving and loading command lists, which are stored in JSON format.

## Precautions

The program must be run with administrator privileges. Some antivirus software may falsely flag the driver file, so it is recommended to deploy it in a controlled environment.
Supported operating systems: **Windows 10/11** (not yet adapted for macOS or Linux).

The program supports a maximum of four simultaneous key presses. When pressing controlling keys (e.g., Ctrl, Shift, Alt) along with letter/number keys, it is best to place the controlling key first (e.g., "Shift, A, B").

The program **does not** support simulating the "Fn", "Menu", and "," keys.

The program has been tested on several DirectX-based games (e.g., Red Dead Redemption 2, Stellaris, Kenshi). If you find a game that is not supported, please leave feedback on GitHub.

This program is intended for automating actions in single-player games. Do not use it for cheating (if you get banned, that's on you).

## Open-Source Acknowledgment

This program utilizes the open-source Interception library, licensed under GNU GPLv3.

**Original author: oblitum** - GitHub Repository

Original website: https://github.com/oblitum/Interception

## Author & Repository

Author: Fallmoon74

License: GNU GPLv3

<br/>
<br/>

# KeyLinker 程序介绍

本程序是基于系统驱动开发的虚拟键盘输入工具，模拟了104键键盘的输入，能够实现高权限的全局键盘事件模拟，绕过应用层限制，直接与硬件交互，
可用于穿透DirectX通道直接对游戏进行操作等。

## 使用方法：

程序左侧为命令栏，用于显示用户输入的指令列表。右侧四个按钮分别为开始，停止，新建按键指令，新建等待指令。点击开始后程序将按指令列表自动循环输出键盘指令。
按键最多支持四个键同时按下，支持点按与持续按，默认为点按（50ms）。两条按键指令中默认等待50ms，以免给系统带来过高负荷。程序还支持指令列表的保存与读取，以json格式存储。

## 注意事项：

1.需以管理员权限运行，部分杀毒软件可能误报驱动文件，建议在受控环境中部署。支持Windows 10/11，暂未适配macOS、Linux系统。

2.按键模拟最多支持四个键同时点按，在进行控制键与字母键/数字键同时点按时最好把控制键放在前面，如"Shift,A,B"。

3.按键模拟不支持"Fn"、"Menu"以及","键，请注意。

4.本程序已在部分使用DirectX开发的游戏上测试过（荒野大镖客2、群星、kenshi），如果你在使用中发现不支持某个游戏，请在github上留言反馈

5.程序的本意是用来在单机游戏内进行挂机，请勿用于编写外挂

## 开源情况

本程序调用了开源库Interception，采用GNU GPLv3开源协议，原作者oblitum的链接https://github.com/oblitum/Interception

程序作者：Fallmoon74

源代码已在github上开源：https://github.com/Fallmoon74/KeyLinker，未经允许请勿用于商业用途
