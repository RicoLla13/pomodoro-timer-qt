#include <QApplication>
#include <QtWidgets>

#include "main_window/main_window.hpp"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    MainWindow my_window;

    my_window.show();

    return a.exec();
}
