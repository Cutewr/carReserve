#include "datetimedialog.h"
#include <QDateTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDateTimeEdit>

DateTimeDialog::DateTimeDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Set Date and Time");

    dateTimeEdit = new QDateTimeEdit(this);
    dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    QPushButton *okButton = new QPushButton("OK", this);
    QPushButton *cancelButton = new QPushButton("Cancel", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(dateTimeEdit);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);

    connect(okButton, &QPushButton::clicked, this, &DateTimeDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &DateTimeDialog::reject);
}

QDateTime DateTimeDialog::getSelectedDateTime() const
{
    return dateTimeEdit->dateTime();
}
