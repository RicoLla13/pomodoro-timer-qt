#include "timer.hpp"

#include <qboxlayout.h>
#include <qnamespace.h>
#include <qspinbox.h>

#include <QtWidgets>

Timer::Timer(QWidget* parent) : QWidget(parent) {
    start_btn = new QPushButton("Start", this);
    stop_btn = new QPushButton("Stop", this);

    button_area = new QHBoxLayout();
    button_area->addWidget(start_btn);
    button_area->addWidget(stop_btn);

    clock = new NordicClock(this);

    main_layout = new QVBoxLayout(this);
    main_layout->setAlignment(Qt::AlignCenter);
    main_layout->addWidget(clock);
    main_layout->addLayout(button_area);

    pomodoro = new Pomodoro(this);

    sound_player = new QSoundEffect(this);
    sound_player->setSource(QUrl::fromLocalFile("./sounds/bell.wav"));
    sound_player->setVolume(0.5);

    connect(start_btn, &QPushButton::clicked, pomodoro,
            [=] { emit requestSettings(); });
    connect(stop_btn, &QPushButton::clicked, pomodoro,
            [=] { pomodoro->reset(); });
    connect(pomodoro, &Pomodoro::stateChanged, this,
            [=] { sound_player->play(); });
    connect(pomodoro, &Pomodoro::pomodoroComplete, this,
            [=] { clock->updateAngle(100, 0, State::Pomodoro); });
    connect(pomodoro, &Pomodoro::updateClock, clock, &NordicClock::updateAngle);
}

void Timer::recieveData(SettingsVal* data) {
    if (data != nullptr) {
        qDebug() << "Received Data:" << data->pom_val << data->short_val
                 << data->long_val << data->num_val;

        pomodoro->setValues(data->pom_val, data->short_val, data->long_val,
                            data->num_val);
        pomodoro->start();
        delete data;
    } else {
        qDebug() << "Data is null";
    }
}
