#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTextCodec>

///设置主界面
void MainWindow::InitInterFace()
{

    //设置支持中文
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
    //设置运行窗口标题
    setWindowTitle("TiKi-TaKa");

    //设置按钮透明
    ui->playButton->setFlat(true);
    ui->stopButton->setFlat(true);
    ui->prevButton->setFlat(true);
    ui->nextButton->setFlat(true);
    ui->openButton->setFlat(true);
    ui->lockButton->setFlat(true);
    ui->listButton->setFlat(true);
    ui->BigButton->setFlat(true);
    ui->internetButton->setFlat(true);

    //设置进度条
    ui->playPosionSlider->setValue(0);
    ui->playPosionSlider->setDisabled(true);

    //默认设置播放列表隐藏
    ui->listWidget->hide();

    //设置音量条
    ui->volumeButton->setFlat(true);
    ui->volumeButton->setDisabled(true);
    ui->volumeSlider->setRange(0,100);
    ui->volumeSlider->setDisabled(true);
    ui->volumeSlider->setValue(0);

}

