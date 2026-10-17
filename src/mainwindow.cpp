#include "mainwindow.hpp"

void MainWindow::build_ui()
{
    constexpr QSize size(1280, 720);
    this->setWindowTitle("Qtmovies");
    this->resize(size);
    this->setMinimumSize(size);
    this->setMaximumSize(size);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    build_main_frame(this);
    build_toolbar();
}
void MainWindow::build_toolbar()
{
    toolbar = new QToolBar(this);
    toolbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    toolbar->setMovable(false);

    // this is the solution that i found to centre the Search Bar
    QWidget *spacerLeft = new QWidget(this);
    spacerLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(spacerLeft);

    add_search_bar(toolbar);

    QWidget *spacerRight = new QWidget(this);
    spacerRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(spacerRight);

    this->addToolBar(toolbar);
}

void MainWindow::add_search_bar(QToolBar *parent)
{
    search_bar = new QLineEdit(parent);
    search_bar->setFixedWidth(350);

    search_bar->addAction(QIcon(":res/search.svg"), QLineEdit::LeadingPosition);
    search_bar->setPlaceholderText("Search...");
    parent->addWidget(search_bar);
}

void MainWindow::build_main_frame(QMainWindow *parent)
{
    main_frame = new QFrame(parent);
    main_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_frame->setStyleSheet("background-color: rgb(255, 255, 255);");
    parent->setCentralWidget(main_frame);
}
