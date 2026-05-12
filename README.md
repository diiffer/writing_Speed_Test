# ⌨️ Writing Speed Test (MGTU Bauman Edition)

A high-performance typing speed measurement application developed as part of a first-year programming project.

## 🚀 Features
- **Real-time Tracking:** Monitors your keystrokes and calculates speed on the fly.
- **Dynamic Difficulty:** Choose between Easy, Medium, and Hard levels to challenge yourself.
- **Beautiful GUI:** Implemented with Dear ImGui for a professional-grade interface.
- **Accurate Metrics:** Calculates WPM (Words Per Minute) and tracks total mistakes.

## 🛠 Tech Stack
- **Core Logic:** C++17
- **GUI Framework:** [Dear ImGui](https://github.com/ocornut/imgui)
- **Window Management:** [GLFW](https://www.glfw.org/)
- **Rendering:** OpenGL 3.3

## 📦 Installation & Setup

### Prerequisites
You need to have `brew` installed on your macOS.
```bash
brew install glfw
```

### Building the Project
The project uses a compilation process that links the GUI libraries. Since this is a GUI app, you can no longer use a simple `g++` command without linking OpenGL and GLFW.

**Recommended build command:**
```bash
g++ -std=c++17 WST/*.cpp -lglfw -lGL -lGLU -framework OpenGL -framework Cocoa -framework IOKit -o typing_test
```
*(Note: Exact flags may vary based on your system configuration).*

## 🎮 How to Use
1. Run the compiled binary: `./typing_test`
2. Select your desired difficulty and the number of words.
3. Click **"Start Test"**.
4. Type the reference text as accurately and quickly as you can.
5. See your final WPM and mistake count!

---
Made with ❤️ by students of MGTU im. Bauman.
