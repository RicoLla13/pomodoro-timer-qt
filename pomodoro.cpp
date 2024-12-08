#include "pomodoro.hpp"

#include <QDebug>

Pomodoro::Pomodoro(int pom_dur, int short_break, int long_break,
                   int pom_total_count, QObject* parent)
    : pom_dur(pom_dur),
      short_break(short_break),
      long_break(long_break),
      pom_total_count(pom_total_count),
      pom_count(0),
      state(State::Pomodoro),
      remaining_time(0),
      timer(new QTimer(this)),
      QObject(parent) {
    connect(timer, &QTimer::timeout, this, &Pomodoro::onTimeout);
}

void Pomodoro::start() {
    if (remaining_time == 0)
        remaining_time = pom_dur;

    timer->start(1000);
    emit stateChanged(getCurrentState());
}

void Pomodoro::pause() { timer->stop(); }

void Pomodoro::reset() {
    timer->stop();
    pom_count = 0;
    state = State::Pomodoro;
    remaining_time = 0;
}

State Pomodoro::getCurrentState() const { return this->state; }

QString Pomodoro::getRemainingTime() const {
    int mins = remaining_time / 60;
    int secs = remaining_time % 60;

    return QString::asprintf("%02d:%02d", mins, secs);
}

void Pomodoro::onTimeout() {
    if (remaining_time > 0) {
        remaining_time--;
    } else {
        switch (this->state) {
            case State::Pomodoro:
                pom_count++;
                if (pom_count % pom_total_count == 0) {
                    this->state = State::LongBreak;
                    this->remaining_time = long_break;
                } else {
                    this->state = State::ShortBreak;
                    this->remaining_time = short_break;
                }
                emit stateChanged(getCurrentState());
                break;
            case State::LongBreak:
                emit pomodoroComplete();
                this->reset();
                break;
            case State::ShortBreak:
                this->state = State::Pomodoro;
                this->remaining_time = pom_dur;
                emit stateChanged(getCurrentState());
                break;
        }
    }
    emit timeChanged(getRemainingTime());
}
