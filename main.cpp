#include "main_window.hpp"
#include <QtWidgets>
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    MainWindow* my_window = new MainWindow();

    my_window->show();

    return a.exec();
}
