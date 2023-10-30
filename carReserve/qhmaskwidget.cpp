#include "qhmaskwidget.h"
#include "ui_qhmaskwidget.h"

#include <QEvent>
#include <QPaintEvent>
#include <QGridLayout>
#include <QDebug>
#include <QPalette>

QHMaskWidget::QHMaskWidget(QWidget *parent)
    : QWidget(parent)
    , m_embeddedWindow(nullptr)
{
    parent->installEventFilter(this);

    setVisible(false);

    QPalette pal(palette());
    pal.setColor(QPalette::Window, QColor(0, 0, 0, 100));
    setAutoFillBackground(true);
    setPalette(pal);
}

void QHMaskWidget::show()
{
    resize(parentWidget()->size());
    if(m_embeddedWindow)
    {
        m_embeddedWindow->setVisible(true);
    }
    setVisible(true);
}

void QHMaskWidget::addEmbeddedWindow(QWidget *window)
{
    m_embeddedWindow = window;
    window->setFixedSize(window->size());
    window->installEventFilter(this);

    QGridLayout *gLayout = new QGridLayout();
    gLayout->addWidget(window);
  //  gLayout->setContentsMargins(0);

    setLayout(gLayout);
}

bool QHMaskWidget::eventFilter(QObject *object, QEvent *event)
{
    if (isVisible() && object == parentWidget() && event->type() == QEvent::Resize)
    {
        resize(parentWidget()->size());
    }

    if (isVisible() && m_embeddedWindow && object == m_embeddedWindow && event->type() == QEvent::Close)
    {
        setVisible(false);
    }

    return QWidget::eventFilter(object, event);
}
