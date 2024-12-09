#include "pomodoro.hpp"

#include <QDebug>

Pomodoro::Pomodoro(QObject* parent)
    : pom_dur(0),
      short_break(0),
      long_break(0),
      pom_total_count(0),
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
    emit stateChanged();
}

void Pomodoro::pause() { timer->stop(); }

void Pomodoro::reset() {
    timer->stop();
    pom_count = 0;
    state = State::Pomodoro;
    remaining_time = 0;
    emit updateClock(100, remaining_time, state);
}

void Pomodoro::setValues(int _pom_dur, int _short_break, int _long_break,
                         int _pom_count) {
    this->pom_dur = _pom_dur * 60;
    this->short_break = _short_break * 60;
    this->long_break = _long_break * 60;
    this->pom_total_count = _pom_count;
}

State Pomodoro::getCurrentState() const { return this->state; }

QString Pomodoro::getRemainingTime() const {
    int mins = remaining_time / 60;
    int secs = remaining_time % 60;

    return QString::asprintf("%02d:%02d", mins, secs);
}

void Pomodoro::onTimeout() {
    if (remaining_time > 0) {
        float percent;
        switch (state) {
            case State::Pomodoro:
                percent = static_cast<float>(remaining_time) /
                          static_cast<float>(pom_dur);
                break;
            case State::ShortBreak:
                percent = static_cast<float>(remaining_time) /
                          static_cast<float>(short_break);
                break;
            case State::LongBreak:
                percent = static_cast<float>(remaining_time) /
                          static_cast<float>(long_break);
                break;
        }
        emit updateClock(percent, remaining_time, state);

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
                emit stateChanged();
                break;
            case State::LongBreak:
                emit pomodoroComplete();
                this->reset();
                break;
            case State::ShortBreak:
                this->state = State::Pomodoro;
                this->remaining_time = pom_dur;
                emit stateChanged();
                break;
        }
        emit updateClock(0, 0, state);
    }
}
