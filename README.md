# Image Mirror Application

## Overview

This C++ application provides a graphical user interface (GUI) for mirroring images in selected folders using the Qt framework and OpenCV library. Users can choose a source folder containing images and a destination folder where the mirrored images will be saved. The application supports mirroring options, allowing users to flip images vertically, horizontally, or both.

## Features

- **Folder Selection**: Users can select both a source folder and a destination folder through a file dialog.
- **Image Processing**: The application processes images with the following formats: `.jpg`, `.jpeg`, and `.png`.
- **Mirror Options**: Users can select the mirroring option through a slider:
  - **Vertical**: Flips the image vertically.
  - **Horizontal**: Flips the image horizontally.
  - **Both**: Flips the image both horizontally and vertically.
- **Error Handling**: The application provides user-friendly error messages for common issues, such as unselected folders or identical source and destination folders.

## Implementation

- Utilizes **Qt** for the GUI components, including buttons, sliders, and message boxes.
- Employs the **OpenCV** library for image processing, including reading, flipping, and saving images.
- Uses **C++17** standard filesystem library for handling file operations.

## Code Structure

- **MainWindow** Class: The main class responsible for managing the GUI and user interactions.
- **Global Variables**: 
  - `source_folder`: Stores the path to the selected source folder.
  - `destination_folder`: Stores the path to the selected destination folder.
  - `mirror_option`: Represents the selected mirroring option.

## Usage

1. Select a source folder containing the images you want to mirror.
2. Select a destination folder where the mirrored images will be saved.
3. Adjust the mirror option using the slider.
4. Click the "Mirror Folder" button to process the images.

## Requirements

- Qt Framework
- OpenCV
- C++17 or later

## Installation

Instructions for setting up the project locally.

---
