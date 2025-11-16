# ESP8266 Panel Control

这是一个 ESP8266 舵机控制项目，通过 Web 界面控制舵机的动作。

## 功能特性

- 📡 WiFi 连接和 Web 服务器
- 🕐 NTP 时间同步（时区：UTC+8）
- 🤖 舵机控制（GPIO14）
- 🌐 Web 界面控制（仅在 20:00-01:00 运行）
- 💤 非工作时间自动进入深度睡眠

## 硬件要求

- ESP8266 或 NodeMCU v2
- 舵机（连接到 GPIO14）
- USB 数据线（用于编程）

## 开发环境设置

### 前置要求

1. 安装 [VS Code](https://code.visualstudio.com/)
2. 安装 [PlatformIO IDE 扩展](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)

### 快速开始

1. 打开项目文件夹
2. PlatformIO 会自动检测并配置环境
3. 连接 ESP8266 到电脑
4. 修改 WiFi 凭证在 `src/main.cpp` 中

## 编译和上传

### 快捷键
- 编译：`Ctrl+Alt+B` 
- 上传：`Ctrl+Alt+U`
- 监视器：`Ctrl+Alt+S`

### 通过 PlatformIO 工具栏
- 点击 VS Code 左侧的 PlatformIO 图标
- 在项目任务中选择编译/上传/监视

## 文件结构

```
esp32_panel_control/
├── src/
│   └── main.cpp          # 主程序代码
├── .gitignore            # Git 忽略文件
├── platformio.ini        # PlatformIO 配置
└── README.md             # 项目说明
```
