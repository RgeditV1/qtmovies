#include "mainwindow.hpp"

void MainWindow::build_ui()
{
    constexpr QSize size(1280, 720);
    this->setWindowTitle("Qtmovies");
    this->resize(size);
    this->setMinimumSize(size);
    this->setMaximumSize(size);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
