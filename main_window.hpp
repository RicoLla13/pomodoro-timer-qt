#pragma once

#include <qstackedwidget.h>

#include <QtWidgets>

#include "central.hpp"
#include "settings.hpp"

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

    // Pages widget
    QStackedWidget* pages_widget;
    // Pages
    Settings* settings_pg;
    Central* timer_pg;

    QVBoxLayout* main_lyt;

    void openStyleSheet();
};
