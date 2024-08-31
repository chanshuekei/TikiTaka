#include "RedLoong.h"
#include "ui_RedLoong.h"


//搜索按钮
void RedLoong::on_searchButton_clicked()
{
    QString getLineText = ui->webLine->text();
    qDebug()<<getLineText.left(7);
    qDebug()<<getLineText.left(8);
    if("http://" == getLineText.left(7) || "https://" == getLineText.left(8))
    {
        qDebug()<<"get lineText:"<<getLineText;
        ui->webWidget->load(QUrl(getLineText));
        nowPage = getLineText;
    }
    else
    {
        ui->webWidget->load(QUrl("https://"+getLineText));
        nowPage ="https://"+getLineText;
        ui->webLine->setText(nowPage);
    }
    qDebug()<<"title:"<<ui->webWidget->title();
}

//设置标题
void RedLoong::slt_setWebTitle(bool flag)
{
    if(flag)
        setWindowTitle(ui->webWidget->title());
}

//void RedLoong::slt_goToNewWeb(QUrl newWeb)
//{
//    if(newWeb.isEmpty())
//        return;
//    if(QUrl(nowPage) == newWeb)
//        return;
//    nowPage = ui->webLine->text().trimmed();
//    QString newPage = newWeb.toString().trimmed();
//    if(nowPage.left(nowPage.count()) == newPage.left(newPage.count()-1))
//        ui->webWidget->load(newWeb);
//    qDebug()<<"now:"<<QUrl(nowPage);
//    qDebug()<<"new:"<<newWeb;
//}

//回到主页
void RedLoong::on_homeButton_clicked()
{
    ui->webWidget->load(QUrl(homePage));
    ui->webLine->setText(homePage);
}

//刷新页面
void RedLoong::on_refreshButton_clicked()
{
    ui->webWidget->reload();
}

//前进页面
void RedLoong::on_nextButton_clicked()
{
    ui->webWidget->forward();
}

//页面后退
void RedLoong::on_prevButton_clicked()
{
    ui->webWidget->back();
}

