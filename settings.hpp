#pragma once

#include <qtmetamacros.h>

#include <QtWidgets>

class Settings : public QWidget {
    Q_OBJECT

   public:
    Settings(QWidget* parent = nullptr);

   private:
    QLabel* pom_lbl;
    QVBoxLayout* main_lyt;
};
