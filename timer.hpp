#pragma once

#include <QMediaPlayer>
#include <QSoundEffect>
#include <QtWidgets>

#include "pomodoro.hpp"

class Timer : public QWidget {
    Q_OBJECT

   public:
    Timer(QWidget* parent = nullptr);

   private slots:
    void updateTime(const QString& time);
    void updateState(const State& state);

   public slots:
    void recieveData(SettingsVal* data);

   signals:
    void requestSettings();

   private:
    Pomodoro* pomodoro;
    QVBoxLayout* main_layout;

    // Left area
    QLabel* title_label;
    QLabel* timer_label;
    QHBoxLayout* button_area;
    QPushButton* start_btn;
    QPushButton* stop_btn;

    // Notification sound
    QSoundEffect* sound_player;
};
