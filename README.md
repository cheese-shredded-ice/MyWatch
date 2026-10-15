# MyWatch 学习记录

这是我的 STM32 智能手表学习项目。这个仓库用于记录学习过程：每次完成一个小任务，就保存当时的代码、遇到的问题、解决方法和验证结果，方便以后回顾。

仓库中已有的代码不代表对应功能已经学完或验证完成，实际进度以这里的记录为准。

## 学习进度

| 任务 | 日期 | 内容 | 状态 |
| --- | --- | --- | --- |
| 01 | 2026-10-15 | 创建 LCD 显示任务 | 已完成：实物显示 Hello |

## 任务 01：创建 LCD 显示任务

### 目标和结果

让手表屏幕显示 `Hello`，并把 LCD 初始化和显示操作放到 FreeRTOS 任务中。这是本项目的第一个学习进度。

已完成 SPI1 通信、TIM3 PWM 背光控制、硬件初始化任务创建和文字显示。此前已编译通过并通过实物照片确认蓝底白字 `Hello` 显示成功。

### 实现流程

```text
main 初始化 HAL、系统时钟和外设
  → 初始化内核、创建任务、启动 FreeRTOS 调度器
  → HardwareInitTask 设置占空比并启动背光 PWM
  → 配置 SPI、初始化 LCD
  → 清屏、显示 Hello、设置 50% 背光亮度
  → 退出初始化任务，保留屏幕画面
```

任务属性只是配置，`osThreadNew()` 才会创建任务；调度器启动后，优先运行优先级最高的就绪任务。

### 遇到的问题

| 问题 | 原因与解决方法 | 学到的内容 |
| --- | --- | --- |
| 早期裸机版本卡在延时 | `delay_ms()` 依赖尚未启动的 SysTick；最终 LCD 驱动改用基于 TIM1 的 `HAL_Delay()` | 调用延时前要确认时基正常运行 |
| Welcome 能显示但闪烁 | 循环中反复复位、清屏；改成一次初始化后退出任务 | 静态画面不需要反复初始化 LCD |
| 其他任务不能运行 | `vTaskSuspendAll()` 后没有配对恢复；移除不必要的暂停调度 | 暂停调度不等于关闭中断 |
| 启动 PWM 后仍然黑屏 | 比较值初始为 0；补上占空比设置 | 启动 PWM 不等于开启背光 |
| 不知道卡在哪一步 | 添加 `lcd_test_stage` 并在 Keil Watch 中观察 | 用阶段标记定位执行位置 |

任务中不再调用 `delay_init()` 重新配置 FreeRTOS 正在使用的 SysTick。排查时把 SPI 从约 50 MHz 降至约 6.25 MHz；这是调试措施，未证实原频率是故障原因。

### 代码入口和调试

- [任务创建](User/Tasks/Src/user_TasksInit.c)：`User_Tasks_Init()`。
- [硬件初始化任务](User/Tasks/Src/user_HardwareInitTask.c)：`HardwareInitTask()`。
- [LCD 底层驱动](BSP/LCD/lcd_init.c)：初始化、SPI 发送和背光控制。
- [绘图和文字显示](BSP/LCD/lcd.c)。

Keil 中进入调试模式，打开 **View → Watch Windows → Watch 1**，添加 `lcd_test_stage`，运行几秒后暂停查看：

| 值 | 含义 |
| --- | --- |
| 0 | 尚未进入任务 |
| 1 | 进入任务 |
| 2 | 背光 PWM 已启动 |
| 3 | SPI 已配置 |
| 4 | LCD 初始化已返回 |
| 5 | 清屏完成 |
| 6 | Hello 数据发送完成 |
| 7 | 背光亮度已设置为 50% |
| 0xE1 | PWM 启动失败 |
| 0xE2 | SPI 初始化失败 |

`lcd_spi_status` 和 `lcd_spi_error` 记录 SPI 发送状态。软件执行完成不等于屏幕正确接收数据，需要结合实物现象判断。

## 工程环境

- MCU：STM32F411CEU6。
- RTOS：FreeRTOS，CMSIS-RTOS v2 接口。
- 当前工程：**`MDK-ARM/MyWatch.uvprojx`**。
- CubeMX 配置：`MyWatch.ioc`。
- 编译器：Keil ARM Compiler 5.06 update 7。
- HEX 输出：`MDK-ARM/MyWatch/MyWatch.hex`，由本地编译生成，不提交生成文件。

| LCD 信号 | 引脚 |
| --- | --- |
| SCK | PB3 / SPI1_SCK |
| MOSI | PB5 / SPI1_MOSI |
| RES | PB7 |
| CS | PB8 |
| DC | PB9 |
| 背光 | PB0 / TIM3_CH3 |

当前文件夹仍有 `MDK-ARM/Watch.uvprojx` 等旧文件。复现任务 01 时，请使用 **MyWatch.uvprojx**；其他功能尚未作为学习任务验证。

## 后续记录方式

每完成一个任务，追加编号、日期、目标、实现过程、问题与解决方法和验证结果，用 Git 提交保存当时的代码。
