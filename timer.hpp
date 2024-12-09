#pragma once

#include <QMediaPlayer>
#include <QSoundEffect>
#include <QtWidgets>

#include "nordic_clock.hpp"
#include "pomodoro.hpp"

class Timer : public QWidget {
    Q_OBJECT

   public:
    Timer(QWidget* parent = nullptr);

   public slots:
    void recieveData(SettingsVal* data);

   signals:
    void requestSettings();

   private:
    Pomodoro* pomodoro;
    QVBoxLayout* main_layout;

    // Page area
    QHBoxLayout* button_area;
    QPushButton* start_btn;
    QPushButton* reset_btn;
    NordicClock* clock;

    // Notification sound
    QSoundEffect* sound_player;
};
