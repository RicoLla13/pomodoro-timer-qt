#pragma once

#include <qtmetamacros.h>

#include <QtWidgets>

#include "utils.hpp"

class NordicClock : public QWidget {
    Q_OBJECT

   public:
    NordicClock(QWidget* parent = nullptr);

   public slots:
    void updateAngle(float percent, int time, State state);

   private:
    float prog_angle;
    QColor current_color;

    QLabel* title_label;
    QLabel* timer_label;

    void paintEvent(QPaintEvent* event) override;
};
