#include "timer.hpp"

#include <qboxlayout.h>
#include <qlayoutitem.h>
#include <qnamespace.h>
#include <qspinbox.h>

#include <QtWidgets>

Timer::Timer(QWidget* parent) : QWidget(parent) {
    start_btn = new QPushButton(this);
    start_btn->setObjectName("start-button");
    QIcon start_ico(":/icons/play.svg");
    start_btn->setIcon(start_ico);
    start_btn->setIconSize(QSize(20, 20));
    start_btn->setFixedSize(50, 50);

    reset_btn = new QPushButton(this);
    reset_btn->setObjectName("reset-button");
    QIcon reset_ico(":/icons/reset.svg");
    reset_btn->setIcon(reset_ico);
    reset_btn->setIconSize(QSize(16, 16));
    reset_btn->setFixedSize(30, 30);

    QWidget* invisible_box = new QWidget(this);
    invisible_box->setObjectName("invisible-box");
    invisible_box->setFixedSize(30, 30);
    invisible_box->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    button_area = new QHBoxLayout();
    button_area->setSpacing(10);
    button_area->addStretch();
    button_area->addWidget(invisible_box);
    button_area->addWidget(start_btn);
    button_area->addWidget(reset_btn);
    button_area->addStretch();

    clock = new NordicClock(this);

    main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(20);
    main_layout->setAlignment(Qt::AlignCenter);
    main_layout->addWidget(clock, 0, Qt::AlignCenter);
    main_layout->addLayout(button_area);

    pomodoro = new Pomodoro(this);

    sound_player = new QSoundEffect(this);
    sound_player->setSource(QUrl::fromLocalFile("./sounds/bell.wav"));
    sound_player->setVolume(1.0);

    connect(start_btn, &QPushButton::clicked, pomodoro,
            [=] { emit requestSettings(); });
    connect(reset_btn, &QPushButton::clicked, pomodoro,
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
