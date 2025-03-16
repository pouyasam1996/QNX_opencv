# QNX OpenCV Project

## Overview
This project implements a video capture and processing pipeline using OpenCV on a QNX system. It captures frames from a camera, displays them in a live window, and allows saving the video to a file. The project demonstrates the integration of OpenCV with QNX, including features like toggling video saving with a keypress.

### Features
- Capture live video from a camera using OpenCV.
- Display video frames in a resizable window with a "Saving Video" or "Not Saving" status overlay.
- Toggle video saving with the 's' key (press to start, press again to stop).
- Exit the program with the 'q' key.
- Multi-threaded encoding for efficient video processing.

## Prerequisites
- **Operating System**: macOS (for development, as indicated by the build path).
- **QNX**: Ensure you have a QNX development environment if targeting QNX systems.
- **OpenCV**: Version 4.11.0 or higher.
- **CMake**: For building the project.
- **Compiler**: Clang++ (as used in the build command).
- **Dependencies**:
  - OpenCV libraries (installed via Homebrew on macOS: `/opt/homebrew/Cellar/opencv/4.11.0`).
  - POSIX threads (`pthread`) for multi-threading.

## Installation
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/pouyasam1996/QNX_opencv.git
   cd QNX_opencv
