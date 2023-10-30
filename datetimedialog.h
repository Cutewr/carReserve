#ifndef DATETIMEDIALOG_H
#define DATETIMEDIALOG_H

#include <QDialog>
#include <QDateTime>
#include <QDateTimeEdit>

class DateTimeDialog : public QDialog
{
    Q_OBJECT

public:
    DateTimeDialog(QWidget *parent = nullptr);
    QDateTime getSelectedDateTime() const;

private:
    QDateTimeEdit *dateTimeEdit;
};
#endif // DATETIMEDIALOG_H
