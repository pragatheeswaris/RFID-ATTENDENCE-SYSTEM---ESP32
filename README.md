## RFID-ATTENDENCE-SYSTEM---ESP32

# 📌 RFID Based Attendance System Using ESP32, RTC & Firebase
# 📝 Project Overview

The RFID Based Attendance System using ESP32, MFRC522 RFID Reader, RTC (DS1307), and Firebase Realtime Database is an IoT-based embedded system designed to provide secure, automated, and real-time attendance monitoring. Attendance is marked only for registered RFID cards, within predefined time constraints, and the data is stored live in Firebase Cloud Database with accurate date and time stamps. All system messages and status updates are displayed through the Serial Monitor, with no LCD interface used.

# 🎯 Objectives

-> Automate attendance using RFID and IoT technology

-> Allow attendance only for registered RFID cards

-> Apply strict time-based entry and exit restrictions

-> Prevent unauthorized access and late entries

-> Store attendance records securely in Firebase Realtime Database

-> Display real-time system output via Serial Monitor

# 🛠️ Hardware Components

-> ESP32 Development Board

<img width="101" height="180" alt="image" src="https://github.com/user-attachments/assets/e5d367cc-1eab-416e-a6e3-a39d3a255fc5" />

-> MFRC522 RFID Reader Module 
-> RFID Cards / Tags

<img width="180" height="180" alt="image" src="https://github.com/user-attachments/assets/361204bb-ba33-491a-9eda-f577b1750aad" />

-> RTC Module (DS1307)

<img width="180" height="180" alt="image" src="https://github.com/user-attachments/assets/f77bec9a-ea70-48bc-8acc-b895fe850f1a" />

-> WiFi Network

-> USB Cable

-> Connecting Wires

# 💻 Software Tools

-> Arduino IDE

-> ESP32 Board Package

-> Firebase Realtime Database

-> Serial Monitor

-> Embedded C / C++

# ⚙️ System Working Principle

-> The RFID reader continuously scans for RFID cards

-> The card’s UID is read and converted into a unique string

-> The ESP32 verifies:
-> Whether the card UID is registered
-> Whether the scan time is within the allowed time window

-> RTC (DS1307) provides accurate date and time

-> Based on validation:
-> ENTRY or EXIT is determined
-> Attendance is uploaded to Firebase in real time

-> All status messages are displayed on the Serial Monitor

## ⏰ Attendance Logic
  # ✅ Case 1: Registered Card + Allowed Entry Time

Attendance is marked successfully
Serial Output:

    RFID Detected
    Student Verified
    ENTRY Marked
    Data Uploaded to Firebase

# ❌ Case 2: Registered Card + Late Entry

Attendance NOT marked
Serial Output:

    RFID Detected
    Student Verified
    Denied: Late Entry

# ❌ Case 3: Exit After Allowed Time

Exit NOT allowed
Serial Output:

    RFID Detected
    Student Verified
    Denied: Exit Time Exceeded

# ❌ Case 4: Unregistered Card

Attendance NOT marked
Serial Output:

    Unknown Card Detected
    ACCESS DENIED – Unauthorized Card

## 📊 Results
# ✅ Observed Output (Serial Monitor & Firebase)

-> Attendance recorded only for registered users

-> Time-based access control working accurately

-> Unauthorized cards completely blocked

-> Entry and Exit tracked correctly

-> Real-time cloud storage achieved using Firebase

# 🚀 Applications

-> College & School Attendance Systems

-> Office Employee Entry-Exit Monitoring

-> Secure Access Control Systems

-> Smart Campus & IoT-based Monitoring

# Demo / Output Video

https://github.com/user-attachments/assets/181f61ae-2b49-4557-8cd8-fa83a5d07fb0


