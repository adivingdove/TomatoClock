#ifndef PERSONAL_DETAILS_H
#define PERSONAL_DETAILS_H

#include <QWidget>

namespace Ui {
class personal_details;
}

class personal_details : public QWidget
{
    Q_OBJECT

public:
    explicit personal_details(QWidget *parent = nullptr);
    ~personal_details();

private:
    Ui::personal_details *ui;
};

#endif // PERSONAL_DETAILS_H
