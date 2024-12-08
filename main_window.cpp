#include "main_window.hpp"

#include <QtWidgets>

MainWindow::MainWindow() : QMainWindow() {
    central_widget = new Central(this);
    this->setCentralWidget(central_widget);
}
