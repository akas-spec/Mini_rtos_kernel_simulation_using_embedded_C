# Mini-RTOS-Kernel-Simulation-using-Embedded-C

A modular Mini RTOS Kernel Simulation developed entirely in Embedded C. The project demonstrates the fundamental concepts of an operating system kernel, including task management, cooperative priority-based scheduling, ready queues, software tick management, task delays, and idle task handling.

---

# 📘 Overview

This project was developed to gain a deeper understanding of how an RTOS works internally by implementing the core kernel components from scratch instead of using an existing RTOS such as FreeRTOS.

The kernel is designed using a modular architecture where each module has a clearly defined responsibility. Although this project runs as a software simulation, its organization closely resembles that of a real embedded RTOS and serves as a strong foundation for future hardware-based implementations.

---

# ✨ Features

- Cooperative Priority-Based Scheduler
- Task Management using Task Control Blocks (TCBs)
- Ready Queue Management
- Round Robin Scheduling for Equal Priority Tasks
- Software Tick Management
- Task Delay Mechanism
- Idle Task Implementation
- Modular Kernel Architecture
- Configurable RTOS Parameters
- Function Pointer-Based Task Execution

---

# 🏗️ RTOS Architecture

<p align="center">
  <img src="docs/images/BlockDiagram.png" width="900" alt="Mini RTOS Architecture">
</p>

---

# 📂 Project Structure

```text
MiniRTOS/
│
├── Application/
│   ├── app_task.c
│   └── app_task.h
│
├── Config/
│
├── Core/
│   ├── main.c
│   └── output/
│
├── Include/
│
├── Kernel/
│   ├── kernel.c
│   ├── kernel.h
│   ├── scheduler.c
│   ├── scheduler.h
│   ├── task.c
│   ├── task.h
│   ├── ready_queue.c
│   ├── ready_queue.h
│   ├── tick.c
│   ├── tick.h
│   ├── delay.c
│   └── delay.h
│
├── BlockDiagram/
│   └── RTOS_Architecture.png
│
└── README.md
