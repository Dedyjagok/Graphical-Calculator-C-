## Graphical Calculator

A graphical calculator application built using the SFML (Simple and Fast Multimedia Library). This application provides a user-friendly interface for performing basic arithmetic operations and supports multiple operands and operations in a single expression.

## 🚀 Features

**Basic Arithmetic Operations**
- Supports addition, subtraction, multiplication, and division.
- Handles multiple operands and operations in a single expression.
- Displays the current input and result.

**Graphical User Interface**
- Clean and intuitive graphical user interface.
- Dynamic resizing of buttons and display box based on window size.
- Customizable icon and font.

## Getting Started

**Prerequisites**
- SFML library
- MinGW compiler (for Windows)
- C++ compiler (e.g., g++)

### Installing MinGW Compiler

1. **Download MinGW**:
   - Go to the [SFML download page](https://www.sfml-dev.org/download/sfml/2.6.1/) and download the MinGW version that supports SFML.
   - Extract the downloaded archive to a directory of your choice (e.g., `C:\MinGW`).

2. **Set Up Environment Variables**:
   - Open the Start Menu, search for "Environment Variables," and select "Edit the system environment variables."
   - In the System Properties window, click on the "Environment Variables" button.
   - In the Environment Variables window, find the "Path" variable in the "System variables" section and click "Edit."
   - Click "New" and add the path to the MinGW `bin` directory (e.g., `C:\MinGW\bin`).
   - Click "OK" to close all windows.

3. **Verify Installation**:
   - Open a Command Prompt and type `g++ --version` to verify that MinGW is installed correctly.

### Installation & Setup

1. **Clone the repository**:
   ```sh
   git clone https://github.com/yourusername/graphical-calculator.git
   cd graphical-calculator