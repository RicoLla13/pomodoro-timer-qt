#pragma once

#include <qstackedwidget.h>

#include <QtWidgets>

#include "../settings/settings.hpp"
#include "../timer/timer.hpp"

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
    Timer* timer_pg;

    QVBoxLayout* main_lyt;

    void openStyleSheet();
};
