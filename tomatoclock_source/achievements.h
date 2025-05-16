#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H

#include <QWidget>

namespace Ui {
class achievements;
}

class achievements : public QWidget
{
    Q_OBJECT

public:
    explicit achievements(QWidget *parent = nullptr);
    ~achievements();
    void getAchievements(int tomato_num);

private slots:
    void on_firstButton_clicked();

    void on_secondButton_clicked();

    void on_thirdButton_clicked();

    void on_forthButton_clicked();

    void on_fifthButton_clicked();

    void paintEvent(QPaintEvent *);

private:
    Ui::achievements *ui;
    bool first;
    bool second;
    bool third;
    bool forth;
    bool fifth;
};

#endif // ACHIEVEMENTS_H
