#ifndef QHMASKWIDGET_H
#define QHMASKWIDGET_H

#include <QWidget>

class QHMaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QHMaskWidget(QWidget *parent);

    void show();

    void addEmbeddedWindow(QWidget *widget);

protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    QWidget *m_embeddedWindow;
};

#endif // QHMASKWIDGET_H
