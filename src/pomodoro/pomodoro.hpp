#pragma once

#include <qtmetamacros.h>

#include <QObject>
#include <QTimer>

#include "../utils.hpp"

class Pomodoro : public QObject {
    Q_OBJECT

   public:
    Pomodoro(QObject* parent = nullptr);

    void start();
    void pause();
    void reset();
    void setValues(int pom_dur, int short_break, int long_break, int pom_count);
    State getCurrentState() const;
    QString getRemainingTime() const;

   private slots:
    void onTimeout();

   signals:
    void stateChanged();
    void pomodoroComplete();
    void updateClock(float percent, int time, State state);

   private:
    int pom_dur;
    int short_break;
    int long_break;
    int remaining_time;
    State state;
    int pom_total_count;
    int pom_count;

    QTimer* timer;
};
