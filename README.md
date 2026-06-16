# DSAA Interactive Dashboard v3.0

An immersive, 3D-styled command center designed for Data Structures and Algorithms (DSAA) coursework. This dashboard serves as a unified interface to manage, view, and execute programming assignments across multiple languages.

## 🚀 Features
* **Multi-Language Support:** Seamlessly switch between C, C++, Java, and Python environments.
* **3D Visual Interface:** A high-tech, responsive UI with interactive nodes and animations.
* **Voice-Guided Navigation:** Integrated Web Speech API to provide verbal feedback and system status updates.
* **Direct Integration:** One-click source code viewing (VS Code) and execution command generation for local development.

## 🛠 Tech Stack
* **Frontend:** HTML5, CSS3 (Glassmorphism & 3D Transforms), JavaScript (ES6+).
* **Voice Synthesis:** Web Speech API for system alerts.
* **System Integration:** Custom protocol handling for local file path access.

## 📋 How to Use
1. **Selection:** Click on any program "Node" to access its details.
2. **Action:** Select "VIEW SOURCE" to open the file in your local editor (VS Code).
3. **Execution:** Select "RUN PROGRAM" to copy the execution command to your clipboard, then use `Win + R` to run it in your system terminal.

## ⚠️ Important Note
This dashboard is configured for **local execution**. The path links (e.g., `C:\Users\...`) are hardcoded to a local environment. To use this dashboard, ensure your local directory structure matches the paths defined in the `data-path` and `data-bat` attributes within the `index.html` file.

## 👤 Author
Developed by **Vaishnavi Gupta**

---
*Built as part of the DSAA Project curriculum.*
