#include "tomatoclock.h"
#include "homepage.h"
#include <QApplication>
# include <QSettings>
//#include "shuju.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSettings settings("MyCompany", "MyApp");
    //qDebug()<<settings.value("data1");
    homePage w;
    w.show();
    return a.exec();
}
