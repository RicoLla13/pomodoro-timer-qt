#include "central.hpp"

#include <qboxlayout.h>
#include <qnamespace.h>
#include <qspinbox.h>

#include <QtWidgets>

Central::Central(QWidget* parent) : QWidget(parent) {
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

    left_area = new QVBoxLayout();
    left_area->addWidget(title_label);
    left_area->addWidget(timer_label);
    left_area->addLayout(button_area);

    right_area = new QHBoxLayout();
    spin_lyt = new QVBoxLayout();
    spin_labels_lyt = new QVBoxLayout();

    for (int i = 0; i < 3; i++) {
        QLabel* label = new QLabel(spin_lbl_text[i], this);

        QSpinBox* spinner = new QSpinBox(this);
        spinner->setMaximum(max_vals[i]);
        spinner->setMinimum(0);
        spinner->setSingleStep(1);
        spinner->setMinimumWidth(70);

        spin_labels.append(label);
        spinners.append(spinner);

        spin_lyt->addWidget(spinner);
        spin_labels_lyt->addWidget(label);
    }
    right_area->addLayout(spin_labels_lyt);
    right_area->addLayout(spin_lyt);

    QFrame* separator = new QFrame(this);
    separator->setFrameShape(QFrame::VLine);
    separator->setFrameShadow(QFrame::Raised);

    main_layout = new QHBoxLayout(this);
    main_layout->addLayout(left_area);
    main_layout->addWidget(separator);
    main_layout->addLayout(right_area);

    pomodoro = new Pomodoro(3, 3, 3, 2, this);

    connect(start_btn, &QPushButton::clicked, pomodoro, &Pomodoro::start);
    connect(stop_btn, &QPushButton::clicked, pomodoro, [=] {
        title_label->setText("Pomodoro Timer");
        timer_label->setText("00:00");
        if (pomodoro != nullptr)
            pomodoro->reset();
    });
    connect(pomodoro, &Pomodoro::timeChanged, this, &Central::updateTime);
    connect(pomodoro, &Pomodoro::stateChanged, this, &Central::updateState);
    connect(pomodoro, &Pomodoro::pomodoroComplete, this,
            [=] { title_label->setText("Pomodoro Session Completed!"); });
}

void Central::updateTime(const QString& time) { timer_label->setText(time); }

void Central::updateState(const State& state) {
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
}
