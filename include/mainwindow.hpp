#pragma once

/* page.hpp has
 * include <QFrame>
 * include <QMainWindow>
 * include <QObject>
 * include <QStatusBar>
 * include <QTcpSocket>
 * include <QWidget>
 */
#include "page.hpp"

#include <QIcon>
#include <QLineEdit>
#include <QMainWindow>
#include <QToolBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QMainWindow *parent = nullptr) : QMainWindow(parent) { build_ui(); }
    ~MainWindow() override;

  protected:
    /*!
     * \brief checck Connection.
     * \param[in] parent windows itself.
     * \param[in] callback return true or false if you need a boolean func.
     */
    template <typename Callback> void check_conection(QMainWindow *parent, Callback &&callback);

  private:
    /* Private Methods Area */
    void build_ui();
    void build_main_frame(QMainWindow *parent);
    void build_status_bar();
    void build_toolbar();
    void add_search_bar(QToolBar *parent);

    /* Pointers Area */
    QFrame *main_frame = nullptr;
    QToolBar *toolbar = nullptr;
    QLineEdit *search_bar = nullptr;
    QStatusBar *status_bar = nullptr;
    Movie::Index *index = nullptr;
};
