#pragma once

#include <QtWidgets>

#include "central.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow();

   private slots:

   private:
    Central* central_widget;
};
