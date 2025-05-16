#include "daiban.h"
#include "ui_daiban.h"

daiban::daiban(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::daiban)
{
    ui->setupUi(this);
    //创建数据库
    CreateDatabase();
    //创建表
    CreateTable();
    loadTasksForData(ui->calendarWidget->selectedDate());

}

daiban::~daiban()
{
    delete ui;
}
//创建数据库
void daiban::CreateDatabase()
{
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("daiban.db");
    if(db.open()==true)
    {
        QMessageBox::information(0,"正确","打开成功",QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(0,"错误","打开失败",QMessageBox::Ok);
    }
}
//创建表
void daiban::CreateTable()
{
    QSqlQuery createQuery;
    // 创建SQL语句
    QString strsql = QString("CREATE TABLE IF NOT EXISTS daibanDate ("
                             "date TEXT NOT NULL, "
                             "youxianji INT NOT NULL, " // 添加逗号
                             "project TEXT NOT NULL, "              // 添加逗号
                             "rest INT NOT NULL, "
                             "work INT NOT NULL);");               // 修正语句结尾
    if (!createQuery.exec(strsql))
    {
        QMessageBox::critical(0, "错误", "创建表失败: " + createQuery.lastError().text(), QMessageBox::Ok);
    }
}

//加载待办列表
void daiban::loadTasksForData(const QDate &date)
{
    ui->listWidget->clear();
    QSqlQuery query;
    query.prepare("SELECT date, youxianji, project, rest, work FROM daibanDate WHERE date = :date");
    query.bindValue(":date",date.toString("yyyy-MM-dd"));
    query.exec();

    while(query.next())
    {
        int youxianji = query.value(1).toInt();
        QString project = query.value(2).toString();
        int rest = query.value(3).toInt();
        int work = query.value(4).toInt();
        // 创建一个包含所有字段的格式化字符串
        QString displayText = QString("Priority: %1, Name: %2, Rest: %3min, Work: %4min")
                                  .arg(youxianji)
                                  .arg(project)
                                  .arg(rest)
                                  .arg(work);

        ui->listWidget->addItem(displayText);
    }
}


void daiban::on_insertButton_clicked()
{
    QSqlQuery sqlquery;
    //获取日期
    QString currentDate = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");

    //获取优先级
    int youxianji = ui->youxianjiBox->currentText().toInt();
    //获取时间
    int work_time = ui->spinBox->value();
    int rest_time = ui->spinBox_2->value();
    //获取项目名称
    QString name = ui->projectEdit->text();
    sqlquery.prepare("INSERT INTO daibanDate (date, youxianji, project, rest, work) VALUES (:date, :youxianji, :project, :rest, :work)");
    sqlquery.bindValue(":date", currentDate);
    sqlquery.bindValue(":youxianji", youxianji);
    sqlquery.bindValue(":project", name);
    sqlquery.bindValue(":rest", rest_time);
    sqlquery.bindValue(":work", work_time);

    if (sqlquery.exec())
    {
        QMessageBox::information(0, "成功", "插入成功", QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(0, "错误", sqlquery.lastError().text(), QMessageBox::Ok);
    }

}



void daiban::on_deleteButton_clicked()
{
    QListWidgetItem* currentItem = ui->listWidget->currentItem();
    if (currentItem == nullptr)
    {
        QMessageBox::warning(0, "警告", "请先选择一个项目", QMessageBox::Ok);
        return;
    }

    // 从listWidget项的文本中解析出日期和项目名称
    QString itemText = currentItem->text();
    QStringList itemDetails = itemText.split(", ");
    QString date = itemDetails[0].split(": ")[1].trimmed();
    QString project = itemDetails[2].split(": ")[1].trimmed();

    // 在数据库中删除相应的条目
    QSqlQuery query;
    query.prepare("DELETE FROM daibanDate WHERE date = :date AND project = :project");
    query.bindValue(":date", date);
    query.bindValue(":project", project);

    if (query.exec())
    {
        QMessageBox::information(0, "成功", "删除成功", QMessageBox::Ok);
        ui->listWidget->removeItemWidget(currentItem);
        delete currentItem; // 确保删除了项的内存
    }
    else
    {
        QMessageBox::critical(0, "错误", "删除失败: " + query.lastError().text(), QMessageBox::Ok);
    }
}



void daiban::on_calendarWidget_clicked(const QDate &date)
{
    loadTasksForData(date);
}




void daiban::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString text = item->text();
    QRegularExpression re("Rest: (\\d+)min, Work: (\\d+)min");
    QRegularExpressionMatch match = re.match(text);
    if(match.hasMatch())
    {
        int restTime = match.captured(1).toInt();
        int workTime = match.captured(2).toInt();

        tomatoClock *p= new tomatoClock(nullptr,workTime,restTime);
        this->hide();
        p->show();
    }
}

void daiban::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pixmap("://photos/bg000.jpeg");
    painter.drawPixmap(this->rect(),pixmap);

}
