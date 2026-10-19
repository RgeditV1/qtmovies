#include "page.hpp"

namespace Movie
{
    Index::Index(QFrame *parent) : QFrame(parent)
    {
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->setStyleSheet("background-color: rgb(255, 255, 255);");
        // build_page();
    }

    Index::~Index() = default;

    void Index::reload() {}

    void Index::build_page() {}

} // namespace Movie
