#include "RedLoong.h"
#include "ui_RedLoong.h"
#include <QUrl>
#include <QDebug>

RedLoong::RedLoong(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RedLoong)
{
    ui->setupUi(this);
    initRedLoong();
    initMainFace();

    connect(ui->webWidget,SIGNAL(loadFinished(bool)),this,SLOT(slt_setWebTitle(bool)));
    connect(ui->webWidget,SIGNAL(urlChanged(const QUrl&)),this,SLOT(slt_goToNewWeb(QUrl)));
}

RedLoong::~RedLoong()
{
    delete ui;
}

//初始化
void RedLoong::initRedLoong()
{
    ui->webWidget->installEventFilter(this);
    homePage = "https://cn.bing.com/";
}

//初始化界面
void RedLoong::initMainFace()
{
    //设置支持中文编码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
    //设置窗口标题
    setWindowTitle("RedLoong");
    //显示主页
    ui->webWidget->load(QUrl(homePage));
    ui->webLine->setText(homePage);
    //设置搜索快捷键
//    ui->searchButton->setShortcut(Qt::Key_Return | Qt::Key_Enter);
//    ui->homeButton->setShortcut(Qt::Key_Home);
//    ui->refreshButton->setShortcut(Qt::Key_F5);
//    ui->prevButton->setShortcut(Qt::Key_Left);
//    ui->nextButton->setShortcut(Qt::Key_Right);
    //设置按钮风格
    ui->homeButton->setFlat(true);
    ui->prevButton->setFlat(true);
    ui->nextButton->setFlat(true);
    ui->searchButton->setFlat(true);
    ui->refreshButton->setFlat(true);
}


