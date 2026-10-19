#include "mainwindow.hpp"
#include "page.hpp"
#include <utility>

/*TODO
 *create a single file that contains all styles sheet
 */

MainWindow::~MainWindow()
{
    if (main_frame)
        delete main_frame;
    if (toolbar)
        delete toolbar;
    if (search_bar)
        delete search_bar;
    if (status_bar)
        delete status_bar;
    if (index)
        delete index;
}

void MainWindow::build_ui()
{
    constexpr QSize SIZE(1280, 720);
    this->setWindowTitle("Qtmovies");
    this->resize(SIZE);
    this->setMinimumSize(SIZE);
    this->setMaximumSize(SIZE);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    build_main_frame(this);
    build_status_bar();
    build_toolbar();
}
void MainWindow::build_toolbar()
{
    toolbar = new QToolBar(this);
    toolbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    toolbar->setMovable(false);

    // this is the solution that i found to centre the Search Bar
    auto *spacer_left = new QWidget(this);
    spacer_left->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(spacer_left);

    add_search_bar(toolbar);

    auto *spacer_right = new QWidget(this);
    spacer_right->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(spacer_right);

    this->addToolBar(toolbar);
}

void MainWindow::build_status_bar()
{
    status_bar = statusBar();
    status_bar->setStyleSheet("QStatusBar {"
                              "    background: transparent;"
                              "    color: #ffffff;"
                              "    border: none;"
                              "}");
    status_bar->showMessage("Ready", 2000);
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
    // main_frame->setStyleSheet("background-color: rgb(255, 255, 255);");
    parent->setCentralWidget(main_frame);
    index = new Movie::Index(main_frame);
}

// will be modified in the future, not planed to use yet
template <typename Callback>
void MainWindow::check_conection(QMainWindow *parent, Callback &&callback)
{
    auto *socket = new QTcpSocket(parent);

    QObject::connect(socket, &QTcpSocket::connected, parent,
                     [this, socket, cb = std::forward<Callback>(callback)]() mutable
                     {
                         socket->disconnectFromHost();
                         socket->deleteLater();
                         status_bar->showMessage("Connected", 2000);
                         cb(true);
                         // index = new Movie::Index(main_frame);
                         //  this->reload();
                     });
    QObject::connect(
        socket, &QTcpSocket::errorOccurred, parent,
        [this, socket, cb = std::forward<Callback>(callback)](QAbstractSocket::SocketError)
        {
            socket->deleteLater();
            status_bar->showMessage("Error of Connection", 2000);
            cb(false);
            // this->reload();
        });

    socket->connectToHost(WEB_PAGE, 80);
}
