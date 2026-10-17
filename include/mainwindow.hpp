#pragma once
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QMainWindow *parent = nullptr) : QMainWindow(parent) { build_ui(); }

  private:
    void build_ui();
};
