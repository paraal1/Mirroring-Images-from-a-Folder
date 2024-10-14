#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"     // For file and directory selection dialogs
#include "QMessageBox"     // For displaying messages
#include "QDir"            // For directory operations
#include "iostream"        // For input-output operations
#include "filesystem"      // C++17 standard filesystem for handling file operations
#include <opencv2/core/core.hpp>    // OpenCV core module
#include <opencv2/highgui/highgui.hpp>  // OpenCV high-level GUI for handling images
#include <opencv2/opencv.hpp>       // Full OpenCV library for image processing functions

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setup the user interface for the main window
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    // Clean up the user interface on destruction
    delete ui;
}

/********************Global Variables*******************************/
QString source_folder, destination_folder;  // Variables to store source and destination folder paths
int mirror_option = Both;                   // Default value for mirror option, defined globally
namespace fs = std::filesystem;             // Aliasing the std::filesystem namespace for ease of use
/*******************************************************************/

// Slot for handling "Source Folder" button click
void MainWindow::on_btnSourceFolder_clicked()
{
    // Open a directory selection dialog for the user to choose a source folder
    QString dir =  QFileDialog::getExistingDirectory(this, tr("Open Directory"), QDir::homePath(), QFileDialog::ShowDirsOnly);
    source_folder = dir;
    ui->txtPathSourceFolder->setText(source_folder);  // Display the selected source folder path in the UI
}

// Slot for handling "Destination Folder" button click
void MainWindow::on_btnDestinationFolder_clicked()
{
    // Open a directory selection dialog for the user to choose a destination folder
    QString dir =  QFileDialog::getExistingDirectory(this, tr("Open Directory"), QDir::homePath(), QFileDialog::ShowDirsOnly);
    destination_folder = dir;
    ui->txtDestinationFolder->setText(destination_folder);  // Display the selected destination folder path in the UI
}

// Slot for handling changes in the slider value
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    // Update the mirror option based on the slider value
    mirror_option = value;
}

// Slot for handling the "Mirror Folder" button click
void MainWindow::on_btnMirrorFolder_clicked()
{
    // Ensure both source and destination folders are selected and are not the same
    if (!source_folder.isEmpty() && !destination_folder.isEmpty() && (source_folder != destination_folder))
    {
// Platform-specific handling of string conversion (Windows vs other platforms)
#ifdef _WIN32
        fs::path folderPath = source_folder.toStdWString();  // Use wide string on Windows
#else
        fs::path folderPath = source_folder.toStdString();   // Use standard string on other platforms
#endif

        try {
            // Recursively iterate through all files in the source folder
            for (const auto& entry : fs::recursive_directory_iterator(folderPath))
            {
                if (entry.is_regular_file())  // Check if the current entry is a regular file
                {
                    std::string ext = entry.path().extension().string();  // Get the file extension
                    if (ext == ".jpg" || ext == ".jpeg" || ext == ".png")  // Process only image files
                    {
                        // Open the image using OpenCV
                        cv::Mat img = cv::imread(entry.path().string());

                        if (img.empty())  // Check if the image is loaded successfully
                        {
                            std::cerr <<"Failed to open image: " << entry.path().string() << std::endl;
                            continue;  // Skip this file if image loading fails
                        }

                        cv::Mat mirrored_img;

                        // Mirror the image based on the mirror_option selected
                        switch (mirror_option) {
                        case Both:
                            cv::flip(img, mirrored_img, -1);  // Mirror both horizontally and vertically
                            break;
                        case Vertical:
                            cv::flip(img, mirrored_img, 0);   // Mirror vertically
                            break;
                        case Horizontal:
                            cv::flip(img, mirrored_img, 1);   // Mirror horizontally
                            break;
                        default:
                            cv::flip(img, mirrored_img, -1);  // Default case: mirror both
                        }

                        // Construct the destination path for the mirrored image
                        fs::path destPath = fs::path(destination_folder.toStdString()) / entry.path().filename();
                        std::cout << "Saving file: " << destPath.string() << " with extension: " << ext << std::endl;

                        // Save the mirrored image in the destination folder
                        if (!cv::imwrite(destPath.string(), mirrored_img)) {
                            std::cerr << "Failed to save image: " << destPath.string() << std::endl;
                        } else {
                            std::cout << "Mirrored and saved: " << destPath.string() << std::endl;
                        }
                    }
                }
            }
        } catch (const fs::filesystem_error& e) {
            // Handle filesystem errors and display the error message
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    else if (source_folder.isEmpty() && destination_folder.isEmpty())
    {
        // Display an error message if both source and destination folders are not selected
        QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Error!"), QObject::tr("Please make sure you have selected both folders!"), QMessageBox::Ok);
        msgBox.exec();
    }
    else if (source_folder == destination_folder)
    {
        // Display an error message if source and destination folders are the same
        QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Error!"), QObject::tr("Cannot use the same folders!"), QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        // Display a general error message in case of unknown issues
        QMessageBox msgBox(QMessageBox::Critical, QObject::tr("Error!"), QObject::tr("Unknown error, please restart the program!"), QMessageBox::Ok);
        msgBox.exec();
    }
}
