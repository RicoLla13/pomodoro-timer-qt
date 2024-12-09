#include "settings.hpp"

#include <qlabel.h>

Settings::Settings(QWidget* parent) : QWidget(parent) {
    pom_lbl = new QLabel("Work", this);
    pom_lbl->setAlignment(Qt::AlignCenter);
    pom_lbl->setObjectName("settings-label");

    short_lbl = new QLabel("Short Break", this);
    short_lbl->setAlignment(Qt::AlignCenter);
    short_lbl->setObjectName("settings-label");

    long_lbl = new QLabel("Long Break", this);
    long_lbl->setAlignment(Qt::AlignCenter);
    long_lbl->setObjectName("settings-label");

    num_lbl = new QLabel("Rounds", this);
    num_lbl->setAlignment(Qt::AlignCenter);
    num_lbl->setObjectName("settings-label");

    pom_slid = new QSlider(Qt::Horizontal, this);
    pom_slid->setRange(0, 59);
    pom_slid->setValue(25);
    pom_slid->setSingleStep(1);

    short_slid = new QSlider(Qt::Horizontal, this);
    short_slid->setRange(0, 59);
    short_slid->setValue(5);
    short_slid->setSingleStep(1);

    long_slid = new QSlider(Qt::Horizontal, this);
    long_slid->setRange(0, 59);
    long_slid->setValue(10);
    long_slid->setSingleStep(1);

    num_slid = new QSlider(Qt::Horizontal, this);
    num_slid->setRange(0, 10);
    num_slid->setValue(4);
    num_slid->setSingleStep(1);

    pom_val = new QLabel("00:00", this);
    pom_val->setObjectName("settings-val");
    pom_val->setAlignment(Qt::AlignCenter);

    short_val = new QLabel("00:00", this);
    short_val->setObjectName("settings-val");
    short_val->setAlignment(Qt::AlignCenter);

    long_val = new QLabel("00:00", this);
    long_val->setObjectName("settings-val");
    long_val->setAlignment(Qt::AlignCenter);

    num_val = new QLabel("00", this);
    num_val->setObjectName("settings-val");
    num_val->setAlignment(Qt::AlignCenter);

    main_lyt = new QVBoxLayout(this);
    main_lyt->addWidget(pom_lbl);
    main_lyt->addWidget(pom_val);
    main_lyt->addWidget(pom_slid);

    main_lyt->addWidget(short_lbl);
    main_lyt->addWidget(short_val);
    main_lyt->addWidget(short_slid);

    main_lyt->addWidget(long_lbl);
    main_lyt->addWidget(long_val);
    main_lyt->addWidget(long_slid);

    main_lyt->addWidget(num_lbl);
    main_lyt->addWidget(num_val);
    main_lyt->addWidget(num_slid);

    updateVal(pom_val, pom_slid->value());
    updateVal(short_val, short_slid->value());
    updateVal(long_val, long_slid->value());
    updateVal(num_val, num_slid->value());

    connect(pom_slid, &QSlider::valueChanged, this,
            [=](int value) { updateVal(pom_val, value); });
    connect(short_slid, &QSlider::valueChanged, this,
            [=](int value) { updateVal(short_val, value); });
    connect(long_slid, &QSlider::valueChanged, this,
            [=](int value) { updateVal(long_val, value); });
    connect(num_slid, &QSlider::valueChanged, this,
            [=](int value) { updateVal(num_val, value); });
}

void Settings::updateVal(QLabel* val, int value) {
    if (val == num_val)
        val->setText(QString::asprintf("%02d", value));
    else
        val->setText(QString::asprintf("%02d:00", value));
}

void Settings::recieveRequest() {
    SettingsVal* data = new SettingsVal;
    data->pom_val = this->pom_slid->value();
    data->short_val = this->short_slid->value();
    data->long_val = this->long_slid->value();
    data->num_val = this->num_slid->value();

    qDebug() << "Emitting sendData with values:" << data->pom_val
             << data->short_val << data->long_val << data->num_val;

    emit sendData(data);
}
