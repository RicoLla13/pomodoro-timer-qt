#pragma once

enum class State { Pomodoro, LongBreak, ShortBreak };

typedef struct {
    int pom_val;
    int short_val;
    int long_val;
    int num_val;
} SettingsVal;
