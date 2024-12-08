#include "main_window.hpp"

#include <QDebug>
#include <QFile>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>

#include "settings.hpp"
#include "timer.hpp"

MainWindow::MainWindow() : QWidget() {
    this->setObjectName("main-window");
    this->openStyleSheet();
    this->setMinimumSize(400, 600);

    timer_btn = new QPushButton("Timer", this);
    timer_btn->setFixedWidth(75);
    timer_btn->setObjectName("option-button");
    timer_btn->setCheckable(true);
    timer_btn->setChecked(true);
    settings_btn = new QPushButton("Settings", this);
    settings_btn->setFixedWidth(75);
    settings_btn->setObjectName("option-button");
    settings_btn->setCheckable(true);
    settings_btn->setChecked(false);

    page_btn_grp = new QButtonGroup();
    page_btn_grp->addButton(timer_btn);
    page_btn_grp->addButton(settings_btn);

    page_btn_lyt = new QHBoxLayout();
    page_btn_lyt->setSpacing(5);
    page_btn_lyt->addWidget(settings_btn);
    page_btn_lyt->addWidget(timer_btn);
    page_btn_lyt->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    settings_pg = new Settings(this);
    timer_pg = new Timer(this);

    pages_widget = new QStackedWidget(this);
    pages_widget->addWidget(timer_pg);
    pages_widget->addWidget(settings_pg);

    main_lyt = new QVBoxLayout(this);
    main_lyt->addLayout(page_btn_lyt);
    main_lyt->addWidget(pages_widget);

    connect(page_btn_grp, &QButtonGroup::buttonToggled, this,
            [=](QAbstractButton* button, bool checked) {
                if (checked) {
                    if (button == timer_btn)
                        pages_widget->setCurrentIndex(0);
                    else if (button == settings_btn)
                        pages_widget->setCurrentIndex(1);
                }
            });

    connect(timer_pg, &Timer::requestSettings, settings_pg,
            &Settings::recieveRequest);
    connect(settings_pg, &Settings::sendData, timer_pg, &Timer::recieveData);
}

void MainWindow::openStyleSheet() {
    QFile file(":/styles/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&file);
        QString style = ts.readAll();
        this->setStyleSheet(style);
    } else {
        qDebug() << "Could not load style sheet";
    }
}
