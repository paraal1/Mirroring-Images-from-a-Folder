#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum Direction
{
    Vertical = 0,
    Both = 1,
    Horizontal = 2
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnDestinationFolder_clicked();

    void on_btnSourceFolder_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_btnMirrorFolder_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
