#include "nordic_clock.hpp"

NordicClock::NordicClock(QWidget* parent)
    : QWidget(parent), prog_angle(360.0f) {
    setFixedSize(310, 310);
    current_color = QColor("#e5a50a");

    title_label = new QLabel("Work", this);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setObjectName("title-label");

    timer_label = new QLabel("00:00", this);
    timer_label->setAlignment(Qt::AlignCenter);
    timer_label->setObjectName("timer-label");
}

void NordicClock::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int radius = 150;
    QPointF center(155, 155);

    QPen contour_pen;
    contour_pen.setColor(QColor("#5e5c64"));
    contour_pen.setWidth(4);
    painter.setPen(contour_pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(center, radius, radius);

    QPen prog_pen;
    prog_pen.setColor(current_color);
    prog_pen.setWidth(10);
    prog_pen.setCapStyle(Qt::RoundCap);
    painter.setPen(prog_pen);

    painter.drawArc(QRectF(center.x() - radius, center.y() - radius, 2 * radius,
                           2 * radius),
                    90 * 16, -prog_angle * 16);

    QFont font = title_label->font();
    painter.setFont(font);

    int titleHeight = 25;
    QRect title_rect(center.x() - 75, center.y() + 50, 150, titleHeight);

    title_label->setGeometry(title_rect);
    title_label->render(&painter, QPoint(0, 0), QRegion());

    font = timer_label->font();
    painter.setFont(font);

    int timerHeight = 65;
    QRect timer_rect(center.x() - 100,
                     center.y() - (static_cast<float>(timerHeight) / 2), 200,
                     timerHeight);

    timer_label->setGeometry(timer_rect);
    timer_label->render(&painter, QPoint(0, 0), QRegion());
}

void NordicClock::updateAngle(float percent, int time, State state) {
    this->prog_angle = 360.0 * percent;

    timer_label->setText(QString::asprintf("%02d:%02d", time / 60, time % 60));

    switch (state) {
        case State::Pomodoro:
            title_label->setText("Work");
            current_color = QColor("#e5a50a");
            break;
        case State::ShortBreak:
            title_label->setText("Short Break");
            current_color = QColor("#33d17a");
            break;
        case State::LongBreak:
            title_label->setText("Long Break");
            current_color = QColor("#1c71d8");
            break;
    }

    if (time == -1) {
        timer_label->setText("00:00");
        title_label->setText("Complete!");
    }

    this->repaint();
}
