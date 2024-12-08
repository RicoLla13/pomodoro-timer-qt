#pragma once

#include <QtWidgets>

#include "pomodoro.hpp"

class Central : public QWidget {
    Q_OBJECT

   public:
    Central(QWidget* parent = nullptr);

   private slots:
    void updateTime(const QString& time);
    void updateState(const State& state);

   private:
    Pomodoro* pomodoro;
    QHBoxLayout* main_layout;
    QVBoxLayout* left_area;
    QHBoxLayout* right_area;

    // Left area
    QLabel* title_label;
    QLabel* timer_label;
    QHBoxLayout* button_area;
    QPushButton* start_btn;
    QPushButton* stop_btn;

    // Right area
    int max_vals[3] = {59, 59, 10};
    QString spin_lbl_text[3] = {"Pomodoro Duration", "Break Duration",
                                "Number of Pomodoros"};
    QVBoxLayout* spin_labels_lyt;
    QVBoxLayout* spin_lyt;
    QList<QLabel*> spin_labels;
    QList<QSpinBox*> spinners;
};
