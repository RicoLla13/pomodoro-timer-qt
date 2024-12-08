#pragma once

#include <QtWidgets>

#include "central.hpp"

class MainWindow : public QWidget {
    Q_OBJECT

   public:
    MainWindow();

   private slots:

   private:
    // Page Buttons
    QHBoxLayout* page_btn_lyt;
    QButtonGroup* page_btn_grp;
    QPushButton* timer_btn;
    QPushButton* settings_btn;

    Central* central_widget;

    QVBoxLayout* main_lyt;

    void openStyleSheet();
};
