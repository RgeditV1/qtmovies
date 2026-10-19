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
    virtual void reload() = 0; /* Not Planed yet */
    virtual void build_page() = 0;
};

namespace Movie
{
    class Index : private Page, public QFrame
    {
      public:
        explicit Index(QFrame *parent);
        ~Index() override;

      private:
        void reload() override;
        void build_page() override;
    };

    class MovieInfo : private Page, public QFrame
    {
      public:
        explicit MovieInfo(QWidget *parent);
        ~MovieInfo() override;

      private:
        void build_page() override;
    };
} // namespace Movie
