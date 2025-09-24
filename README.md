# 🦾 Prosthetic Arm Animation (OpenGL)

This project is a **3D animated prosthetic arm** created using **C++**, **OpenGL**, and **FreeGLUT**.  
The arm bends, the hand opens/closes continuously, and textures (metal + carbon fiber) are applied for a realistic effect.  

---

## ✨ Features
- Real-time 3D rendering with OpenGL
- Animated prosthetic arm (bending and hand opening/closing)
- Procedural **metal** and **carbon fiber** textures
- Dynamic background with gradients
- On-screen text overlays (advertising-style captions)

---

## 🛠️ Requirements
Make sure you have the following installed:
- **C++ compiler** (g++, MinGW, MSVC, etc.)
- **OpenGL**
- **FreeGLUT** (or GLUT)
- **GLU**

On Linux (Ubuntu/Debian), install with:
```bash
sudo apt-get install freeglut3-dev
```
On Windows:

Install FreeGLUT (often comes with Code::Blocks or Visual Studio setup)

Link against -lfreeglut -lopengl32 -lglu32

---

🚀 How to Build & Run
Linux / macOS
g++ prosthetic_arm.cpp -o prosthetic_arm -lGL -lGLU -lglut
./prosthetic_arm

Windows (MinGW example)
g++ prosthetic_arm.cpp -o prosthetic_arm.exe -lfreeglut -lopengl32 -lglu32
prosthetic_arm.exe

---

🎮 Controls

The animation runs automatically.

The arm bends slightly over time.

The hand repeatedly opens and closes.

---

📸 Preview

When running, you’ll see:

A futuristic prosthetic arm rendered in 3D

Background gradients

Text like “REVOLUTIONARY PROSTHETIC ARM” displayed on screen
