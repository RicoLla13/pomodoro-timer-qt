#pragma once

#include <qtmetamacros.h>

#include <QtWidgets>

#include "utils.hpp"

class Settings : public QWidget {
    Q_OBJECT

   public:
    Settings(QWidget* parent = nullptr);

   public slots:
    void recieveRequest();

   signals:
    void sendData(SettingsVal* data);

   private:
    QLabel* pom_lbl;
    QLabel* short_lbl;
    QLabel* long_lbl;
    QLabel* num_lbl;

    QSlider* pom_slid;
    QSlider* short_slid;
    QSlider* long_slid;
    QSlider* num_slid;

    QLabel* pom_val;
    QLabel* short_val;
    QLabel* long_val;
    QLabel* num_val;

    QVBoxLayout* main_lyt;

    void updateVal(QLabel* val, int value);
};
