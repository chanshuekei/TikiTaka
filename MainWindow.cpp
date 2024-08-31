#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //播放器
    InitPlayer();
    //设置初始界面
    InitInterFace();
    //连接信号与槽
    connectSigToSlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//连接信号与槽
void MainWindow::connectSigToSlot()
{
    connect(implayer,SIGNAL(positionChanged(qint64)),this,SLOT(slt_synSlideToPlayPosion(qint64)));
    connect(implayer,SIGNAL(durationChanged(qint64)),this,SLOT(slt_setSliderRange(qint64)));
    connect(implayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(slt_getPlayerState(QMediaPlayer::State)));
    connect(implayer,SIGNAL(error(QMediaPlayer::Error)),this,SLOT(slt_handleError(QMediaPlayer::Error)));
}


