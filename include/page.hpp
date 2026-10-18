/* THIS FILE WILL BE THE ROOT/BASE OF
 * ALL PAGE THAT ARE LOADED
 */
#pragma once

#include <QFrame>
#include <QMainWindow>
#include <QObject>
#include <QStatusBar>
#include <QTcpSocket>
#include <QWidget>

constexpr const char *WEB_PAGE = "www.cinecalidad.am";

class Page
{
  public:
    virtual ~Page() = default;

  protected:
    /*!
     * \brief check if we can connect to the web_page.
     * \param s_parent QStatusBar pointer.
     * \param m_parent QMainWindow pointer, must be MainWindow.
     */
    virtual void check_conection(QStatusBar *s_parent, QMainWindow *m_parent)
    {
        auto *socket = new QTcpSocket(m_parent);

        QObject::connect(socket, &QTcpSocket::connected, m_parent,
                         [this, socket]
                         {
                             socket->disconnectFromHost();
                             socket->deleteLater();
                             this->reload();
                         });
        QObject::connect(socket, &QTcpSocket::errorOccurred, m_parent,
                         [this, socket](QAbstractSocket::SocketError)
                         {
                             socket->deleteLater();
                             this->reload();
                         });

        socket->connectToHost(WEB_PAGE, 80);
    }

    virtual void reload() = 0;
    virtual void build_page() = 0;
};

namespace Movie
{
    class Index : private Page, public QFrame
    {
      public:
        explicit Index(QWidget *parent) : QFrame(parent) {}
        ~Index() override;

      private:
        void reload() override;
        void build_page() override;
    };

    class MovieInfo : private Page, public QFrame
    {
      public:
        explicit MovieInfo(QWidget *parent) : QFrame(parent) {}
        ~MovieInfo() override;

      private:
        void reload() override;
        void build_page() override;
    };
} // namespace Movie
