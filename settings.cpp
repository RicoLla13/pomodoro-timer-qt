#include "settings.hpp"

Settings::Settings(QWidget* parent) : QWidget(parent) {
    pom_lbl = new QLabel("Pomodoro Duration", this);

    main_lyt = new QVBoxLayout(this);
    main_lyt->addWidget(pom_lbl);
}
