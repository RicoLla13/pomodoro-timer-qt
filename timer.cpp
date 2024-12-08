#include "timer.hpp"

#include <qboxlayout.h>
#include <qnamespace.h>
#include <qspinbox.h>

#include <QtWidgets>

Timer::Timer(QWidget* parent) : QWidget(parent) {
    start_btn = new QPushButton("Start", this);
    stop_btn = new QPushButton("Stop", this);

    title_label = new QLabel("Pomodoro Timer", this);
    title_label->setMinimumWidth(230);
    title_label->setAlignment(Qt::AlignCenter);

    timer_label = new QLabel("00:00", this);
    timer_label->setAlignment(Qt::AlignCenter);
    timer_label->setStyleSheet("QLabel { font-size: 40px; }");

    button_area = new QHBoxLayout();
    button_area->addWidget(start_btn);
    button_area->addWidget(stop_btn);

    main_layout = new QVBoxLayout(this);
    main_layout->addWidget(title_label);
    main_layout->addWidget(timer_label);
    main_layout->addLayout(button_area);

    pomodoro = new Pomodoro(this);

    sound_player = new QSoundEffect(this);
    sound_player->setSource(QUrl::fromLocalFile("./sounds/bell.wav"));
    sound_player->setVolume(0.5);

    connect(start_btn, &QPushButton::clicked, pomodoro,
            [=] { emit requestSettings(); });
    connect(stop_btn, &QPushButton::clicked, pomodoro, [=] {
        title_label->setText("Pomodoro Timer");
        timer_label->setText("00:00");
        pomodoro->reset();
    });
    connect(pomodoro, &Pomodoro::timeChanged, this, &Timer::updateTime);
    connect(pomodoro, &Pomodoro::stateChanged, this, &Timer::updateState);
    connect(pomodoro, &Pomodoro::pomodoroComplete, this,
            [=] { title_label->setText("Pomodoro Session Completed!"); });
}

void Timer::updateTime(const QString& time) { timer_label->setText(time); }

void Timer::updateState(const State& state) {
    switch (state) {
        case State::Pomodoro:
            title_label->setText("Working...");
            break;
        case State::ShortBreak:
            title_label->setText("Short Break");
            break;
        case State::LongBreak:
            title_label->setText("Long Break");
            break;
    }
    sound_player->play();
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
        qDebug() << "Data is null";  // Check for issues
    }
}
