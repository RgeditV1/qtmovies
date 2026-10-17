#include "mainwindow.hpp"
#include <QApplication>
#include <memory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::unique_ptr<MainWindow> main = std::make_unique<MainWindow>();
    main->show();
    return app.exec();
}
