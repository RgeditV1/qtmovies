#pragma once
// #include <QLabel>
#include <QFrame>
#include <QIcon>
#include <QLineEdit>
#include <QMainWindow>
#include <QToolBar>
// #include <memory>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QMainWindow *parent = nullptr) : QMainWindow(parent) { build_ui(); }
    ~MainWindow()
    {
        if (main_frame)
            delete main_frame;
        if (toolbar)
            delete toolbar;
        if (search_bar)
            delete search_bar;
    }

  private:
    /* Private Methods Area */
    void build_ui();
    void build_main_frame(QMainWindow *parent);
    void build_toolbar();
    void add_search_bar(QToolBar *parent);

  private:
    /* Pointers Area */
    QFrame *main_frame = nullptr;
    QToolBar *toolbar = nullptr;
    QLineEdit *search_bar = nullptr;
};
