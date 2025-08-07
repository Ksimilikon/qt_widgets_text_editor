#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new MainLayout(this);
    m_layout->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    showFullScreen();
}

Widget::~Widget() {}
