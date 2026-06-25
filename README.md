# 🚗 Car Black Box System

An Embedded Systems project developed using the **PIC16F877A Microcontroller** that simulates an automotive **Car Black Box**. The system continuously monitors vehicle events, records them with real-time timestamps, stores them in EEPROM, and allows secure retrieval through a password-protected menu.

The project demonstrates the integration of multiple embedded peripherals including **RTC (DS1307)**, **EEPROM**, **UART**, **ADC**, **CLCD**, and **Matrix Keypad**.

---

## 📌 Project Overview

A Car Black Box is similar to an aircraft flight recorder. It stores important vehicle events and operating conditions, which can later be analyzed in case of accidents or abnormal vehicle behavior.

This project records:

* Vehicle Gear Changes
* Collision Events
* Speed Information
* Real-Time Timestamp

All records are stored in EEPROM and can be viewed or downloaded through UART.

---

## 🎯 Objectives

* Monitor vehicle operating conditions.
* Record critical events with timestamps.
* Store event history in EEPROM.
* Provide secure access through password authentication.
* Allow viewing and downloading of logs.
* Implement RTC-based time management.

---

## 🛠 Hardware Components

| Component       | Purpose             |
| --------------- | ------------------- |
| PIC16F877A      | Main Controller     |
| 16x2 CLCD       | User Interface      |
| Matrix Keypad   | User Input          |
| DS1307 RTC      | Real-Time Clock     |
| Internal EEPROM | Event Storage       |
| Potentiometer   | Speed Simulation    |
| UART Interface  | Log Download        |
| PICSimLab       | Simulation Platform |

---

## 💻 Software Tools

* MPLAB X IDE
* XC8 Compiler
* PICSimLab
* GitHub

---

## 🔧 Features Implemented

### 1. Dashboard

Displays:

* Current Time
* Current Event
* Vehicle Speed

Example:

TIME     EVT SP
12:36:18 G3 53

---

### 2. Event Logging

The following events are recorded:

| Event | Description    |
| ----- | -------------- |
| ON    | Vehicle ON     |
| GN    | Neutral        |
| G1-G5 | Gear Positions |
| GR    | Reverse Gear   |
| C     | Collision      |

Each event is stored with:

* Timestamp
* Event Type
* Speed

---

### 3. Password Protected Login

Access to stored logs is restricted.

Default Password:

1010

Features:

* Hidden password entry
* Limited attempts
* Secure access to menu

---

### 4. Menu Driven Navigation

Menu Options:

View Log

Clear Log

Download Log

Set Time

Navigation Keys:

| Switch | Function |
| ------ | -------- |
| SW2    | Down     |
| SW3    | Up       |
| SW4    | Select   |
| SW5    | Back     |

---

### 5. View Log

Displays stored event records from EEPROM.

Example:

# TIME EV SP

0 12:36:18 G3 53

Users can navigate through logs using:

* SW2 → Next Record
* SW3 → Previous Record
* SW5 → Back

---

### 6. Clear Log

Provides confirmation before deleting logs.

CLEAR LOG?

SW4:YES SW5:NO

All EEPROM records are erased after confirmation.

---

### 7. Download Log (UART)

Stored logs can be downloaded through UART.

Example Output:

DOWNLOAD STARTED

----- LOG DATA -----

0 12:36:18 G4 53

1 12:36:19 G3 53

2 12:36:20 G2 53

3 12:36:20 G1 53

---

---

### 8. Set Time

Allows modification of RTC time.

Editable Fields:

* Hours
* Minutes
* Seconds

Updated values are written directly to DS1307 RTC.

---

## 📂 EEPROM Log Format

Each log occupies 10 bytes:

| Field  | Bytes |
| ------ | ----- |
| Hour   | 2     |
| Minute | 2     |
| Second | 2     |
| Event  | 2     |
| Speed  | 2     |

Total:

10 Bytes per Record

Maximum:

10 Records stored using circular logging.

---

## 🔄 Project Flow

Dashboard
↓
Login
↓
Menu
├── View Log
├── Clear Log
├── Download Log
└── Set Time

---

## 🧩 Peripherals Used

### ADC

Used for speed simulation through potentiometer.

### I2C

Used for communication with DS1307 RTC.

### RTC (DS1307)

Provides accurate timestamp information.

### EEPROM

Stores logged vehicle events.

### UART

Used for downloading logs to serial terminal.

### CLCD

Displays dashboard and menu information.

### Matrix Keypad

Used for user interaction.

---

## 🎓 Learning Outcomes

* Embedded C Programming
* PIC16F877A Firmware Development
* EEPROM Management
* RTC Programming
* UART Communication
* ADC Interfacing
* Menu Driven Embedded UI Design
* State Machine Based Application Development

---

⭐ If you found this project useful, consider giving the repository a star.
