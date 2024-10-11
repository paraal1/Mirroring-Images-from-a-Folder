#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QDir"
#include <iostream>
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
QString source_folder, destination_folder;

int mirror_option = Both;

void MainWindow::on_btnSourceFolder_clicked()
{
    QString dir =  QFileDialog::getExistingDirectory(this,tr("Open Directory"),QDir::currentPath(),QFileDialog::ShowDirsOnly);
    source_folder = dir;
    ui->txtPathSourceFolder->setText(source_folder);
}


void MainWindow::on_btnDestinationFolder_clicked()
{
    QString dir =  QFileDialog::getExistingDirectory(this,tr("Open Directory"),QDir::currentPath(),QFileDialog::ShowDirsOnly);
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
       // todo create implementation for mirroring.
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

