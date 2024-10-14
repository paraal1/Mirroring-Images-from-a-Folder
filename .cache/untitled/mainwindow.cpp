#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QDir"
#include "iostream"
#include "filesystem"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/********************Global Variables*******************************/
QString source_folder, destination_folder;
int mirror_option = Both; // Default value for mirror option
namespace fs = std::filesystem;
/*******************************************************************/

void MainWindow::on_btnSourceFolder_clicked()
{
    QString dir =  QFileDialog::getExistingDirectory(this,tr("Open Directory"),QDir::homePath(),QFileDialog::ShowDirsOnly);
    source_folder = dir;
    ui->txtPathSourceFolder->setText(source_folder);
}


void MainWindow::on_btnDestinationFolder_clicked()
{
    QString dir =  QFileDialog::getExistingDirectory(this,tr("Open Directory"),QDir::homePath(),QFileDialog::ShowDirsOnly);
    destination_folder = dir;
    ui->txtDestinationFolder->setText(destination_folder);
}



void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    mirror_option = value;
}


void MainWindow::on_btnMirrorFolder_clicked()
{
    if (source_folder.isEmpty() == false && destination_folder.isEmpty() == false && (source_folder != destination_folder))
    {
    #ifdef _WIN32 // Automatically decided which convertion of string is best for used platform.
        fs::path folderPath = source_folder.toStdWString(); // Use wide string for Windows
    #else
        fs::path folderPath = source_folder.toStdString(); // Use for other platform
    #endif

        try {
            for (const auto& entry : fs::recursive_directory_iterator(folderPath)){
                //std::cout << entry.path() << std::endl;
                if (entry.is_regular_file())
                {
                    std::string ext = entry.path().extension().string();
                    if (ext == ".jpg" || ext == ".jpeg" || ext == ".png"){
                        // Open image using OpenCV
                        cv::Mat img = cv::imread(entry.path().string());

                        if (img.empty()){
                            std::cerr <<"Failed to open image: " << entry.path().string() << std::endl;
                            continue;
                        }

                        cv::Mat mirrored_img;

                        switch(mirror_option){
                            case Both:
                                 cv::flip(img, mirrored_img, -1);
                                break;
                            case Vertical:
                                cv::flip(img, mirrored_img, 0);
                                break;
                            case Horizontal:
                                cv::flip(img, mirrored_img, 1);
                                break;
                            default:
                                cv::flip(img, mirrored_img, -1);
                        }

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
        } catch (const fs::filesystem_error& e){
            std::cerr <<"Error:" << e.what() << std::endl;
        }
    }
    else if (source_folder.isEmpty() == true && destination_folder.isEmpty() == true)
    {
        QMessageBox msgBox(QMessageBox::Critical,QObject::tr("Error!"),QObject::tr("Please make sure you have selected both folders!"),QMessageBox::Ok);
        msgBox.exec();
    }
    else if (source_folder == destination_folder)
    {
        QMessageBox msgBox(QMessageBox::Critical,QObject::tr("Error!"),QObject::tr("Cannot use the same folders!"),QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Critical,QObject::tr("Error!"),QObject::tr("Unknown error, please restart the program!"),QMessageBox::Ok);
        msgBox.exec();
    }
}

