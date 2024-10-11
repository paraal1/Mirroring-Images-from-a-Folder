#include <QApplication>
#include <QWidget>
#include <QPushButton>

int main(int argc, char *argv[])
{
    // Create a QApplication object. It manages application-wide resources.
    QApplication app(argc, argv);

    // Create a main window (QWidget).
    QWidget window;
    window.resize(300, 200);  // Set window size
    window.setWindowTitle("Simple Qt Window");

    // Create a QPushButton widget and set its text.
    QPushButton *button = new QPushButton("Click to Quit", &window);
    button->setGeometry(100, 80, 100, 30);  // Set position and size of the button

    // Ensure the window and button are shown.
    window.show();

    // Connect the button's "clicked" signal to the application's "quit" slot.
    QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));

    // Run the application event loop.
    return app.exec();
}
