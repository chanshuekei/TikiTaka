#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

//初始化播放器
void MainWindow::InitPlayer()
{
    //创建implayer播放器
    implayer = new QMediaPlayer(this);
    //设置播放imPlayer的QVideoWidget播放窗口
    implayer->setVideoOutput(ui->mediaWidget);
    ui->mediaWidget->raise();
    lockFlag = false;
    volFlag = true;
    listFlag = false;
    listMap.clear();
}

//播放多媒体
bool MainWindow::playMedia()
{
    implayer->setMedia(QUrl::fromLocalFile(fileName));
    implayer->play();
    qDebug()<<"volume:"<<implayer->volume();
    implayer->setVolume(80);
    ui->volumeSlider->setValue(implayer->volume());
    ui->volumeButton->setDisabled(false);
    ui->BigButton->hide();
    qDebug()<<"file name:"<<fileName;
    qDebug()<<implayer->state();
    getPlayList();
    addPlayList();
    return true;
}

//点击openButton按钮获取文件地址
void MainWindow::on_openButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,
                                            QString::fromLocal8Bit("选择要播放的文件:"),
                                            "../",
                                            QString::fromLocal8Bit("视频文件(*.mp4 *.wmv *.avi *.mkv);;音频文件(*.mp3 *.wma *.acc *.flac)"));
    if(fileName.isEmpty())
        return;
    playMedia();

}

//点击play按钮播放暂时视频
void MainWindow::on_playButton_clicked()
{
    switch(implayer->state())
    {
    case QMediaPlayer::PlayingState:
        implayer->pause();
        break;
    case QMediaPlayer::PausedState:
        implayer->play();
        break;
    case QMediaPlayer::StoppedState:
        if(!fileName.isEmpty())
        {
            implayer->setMedia(QUrl::fromLocalFile(fileName));
            playMedia();
        }
        else
        {
            fileName = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择要播放的文件:"),
                                                    "../",
                                                    QString::fromLocal8Bit("视频文件(*.mp4 *.wmv *.avi *.mkv);;音频文件(*.mp3 *.wma *.acc *.flac)"));
            if(fileName.isEmpty())
                return;
            playMedia();
        }
        break;
    }
}

//大按钮
void MainWindow::on_BigButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择要播放的文件:"),
                                            "../",
                                            QString::fromLocal8Bit("视频文件(*.mp4 *.wmv *.avi *.mkv);;音频文件(*.mp3 *.wma *.acc *.flac)"));
    if(fileName.isEmpty())
        return;
    playMedia();
}

//点击stop按钮停止播放视频
void MainWindow::on_stopButton_clicked()
{
    implayer->stop();
    //fileName.clear();
    ui->playButton->setIcon(QIcon(":/images/Play.png"));
    ui->mediaWidget->setStyleSheet(QString("color:rbg(0,0,0)"));
    ui->BigButton->show();
    return;
}

//拖动进度改变播放位置
void MainWindow::on_playPosionSlider_sliderMoved(int position)
{
    if(implayer->state() == QMediaPlayer::PlayingState || implayer->state() == QMediaPlayer::PausedState)
        implayer->setPosition(position);
}

//前一部
void MainWindow::on_prevButton_clicked()
{
    if(listMap.isEmpty())
        return;
    if(cntFlag == 0)
        cntFlag = videoList.count()-1;
    else
        cntFlag--;
    fileName = listMap.value(cntFlag);
    implayer->setMedia(QUrl::fromLocalFile(fileName));
    implayer->play();

}

//后一部
void MainWindow::on_nextButton_clicked()
{
    if(listMap.isEmpty())
        return;
    if(cntFlag == videoList.count()-1)
        cntFlag = 0;
    else
        cntFlag++;
    fileName = listMap.value(cntFlag);
    implayer->setMedia(QUrl::fromLocalFile(fileName));
    implayer->play();
}

//显示播放列表
void MainWindow::on_listButton_clicked()
{
    if(!listFlag)
    {
        ui->listWidget->show();
        listFlag = true;
    }
    else
    {
        ui->listWidget->hide();
        listFlag = false;
    }
}

//播放列表文件
void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    cntFlag = index.row();
    fileName = dirPath + "/" + ui->listWidget->item(index.row())->text();
    qDebug()<<"choose file:"<<fileName;
    playMedia();
}

//设置音量大小
void MainWindow::on_volumeSlider_sliderMoved(int position)
{
    implayer->setVolume(position);
    if(position == 0)
        ui->volumeButton->setIcon(QIcon(":/images/volume_ban.png"));
    else if(position < 40)
        ui->volumeButton->setIcon(QIcon(":/images/volume_small.png"));
    else if(position < 80)
        ui->volumeButton->setIcon(QIcon(":/images/volume_medium.png"));
    else
        ui->volumeButton->setIcon(QIcon(":/images/volume_big.png"));
}

//设置音量大小
void MainWindow::on_volumeSlider_valueChanged(int value)
{
    implayer->setVolume(value);
    implayer->setVolume(value);
    if(value == 0)
        ui->volumeButton->setIcon(QIcon(":/images/volume_ban.png"));
    else if(value < 40)
        ui->volumeButton->setIcon(QIcon(":/images/volume_small.png"));
    else if(value < 80)
        ui->volumeButton->setIcon(QIcon(":/images/volume_medium.png"));
    else
        ui->volumeButton->setIcon(QIcon(":/images/volume_big.png"));
}

//静音按钮
void MainWindow::on_volumeButton_clicked()
{
    if(volFlag)
    {
        qDebug()<<"set volume zero";
        implayer->setVolume(0);
        ui->volumeSlider->setValue(0);
        ui->volumeButton->setIcon(QIcon(":/images/volume_ban.png"));
        volFlag = false;
    }
    else
    {
        implayer->setVolume(80);
        ui->volumeSlider->setValue(80);
        ui->volumeButton->setIcon(QIcon(":/images/volume_medium.png"));
        volFlag = true;
    }
}

//锁定按钮
void MainWindow::on_lockButton_clicked()
{
    //解锁播放器
        if(lockFlag)
        {
            ui->openButton->setDisabled(false);
            ui->nextButton->setDisabled(false);
            ui->prevButton->setDisabled(false);
            ui->playButton->setDisabled(false);
            ui->stopButton->setDisabled(false);
            ui->listButton->setDisabled(false);
            ui->internetButton->setDisabled(false);
            ui->volumeButton->setDisabled(false);
            ui->playPosionSlider->setDisabled(false);
            ui->volumeSlider->setDisabled(false);
            ui->lockButton->setIcon(QIcon(":/images/lock.png"));

            lockFlag =  false;
        }
        else //锁定播放器
        {
            ui->openButton->setDisabled(true);
            ui->nextButton->setDisabled(true);
            ui->prevButton->setDisabled(true);
            ui->playButton->setDisabled(true);
            ui->stopButton->setDisabled(true);
            ui->listButton->setDisabled(true);
            ui->internetButton->setDisabled(true);
            ui->volumeButton->setDisabled(true);
            ui->playPosionSlider->setDisabled(true);
            ui->volumeSlider->setDisabled(true);
            ui->lockButton->setIcon(QIcon(":/images/unlock.png"));

            lockFlag = true;
        }
}

//打卡浏览器
void MainWindow::on_internetButton_clicked()
{
    RedLoong *redloong = new RedLoong();
    redloong->show();
}

//获取播放器状态的变化
void MainWindow::slt_getPlayerState(QMediaPlayer::State state)
{
    qDebug()<<"changed player state";
    switch(state)
    {
    case QMediaPlayer::PlayingState:
        ui->playButton->setIcon(QIcon(":/images/pause.png"));
        ui->playButton->setToolTip(QString::fromLocal8Bit("播放"));
        ui->playPosionSlider->setDisabled(false);
        ui->volumeSlider->setDisabled(false);
        break;
    case QMediaPlayer::PausedState:
        ui->playButton->setIcon(QIcon(":/images/Play.png"));
        ui->playButton->setToolTip(QString::fromLocal8Bit("暂停"));
        ui->playPosionSlider->setDisabled(false);
        ui->volumeSlider->setDisabled(false);
        break;
    case QMediaPlayer::StoppedState:
        ui->playButton->setIcon(QIcon(":/images/Play.png"));
        ui->playButton->setToolTip(QString::fromLocal8Bit("播放"));
        ui->playPosionSlider->setDisabled(true);
        ui->volumeSlider->setDisabled(true);
        ui->volumeButton->setDisabled(true);
        break;

    }
}

//同步进度条和播放进度
void MainWindow::slt_synSlideToPlayPosion(qint64 posion)
{
    ui->playPosionSlider->setValue(posion);
}


//设置进度条的范围
void MainWindow::slt_setSliderRange(qint64 range)
{
    ui->playPosionSlider->setRange(0,range);
}

//异常处理
void MainWindow::slt_handleError(QMediaPlayer::Error error)
{
    qDebug()<<"Play Error:"<<error;
    playMedia();
}

//获取播放列表
bool MainWindow::getPlayList()
{
    if(fileName.isEmpty()) //判断fileName路径是否为空
        return false;
    QFile file(fileName);
    if(!file.exists())  //判断文件是否存在
        return false;
    videoList.clear();
    QFileInfo fileInfo(fileName);  //获取文件的信息
    dirPath = fileInfo.absolutePath(); //获取文件的绝对路径
    QDir dir(dirPath); //打开文件夹
    QStringList Videofilter; //视频文件格式
    Videofilter <<"*.mp4" <<"*.avi" <<"*.wmv" <<"*.mkv"; //获取视频格式的文件

    //获取视频文件
    dir.setNameFilters(Videofilter);
    videoList = dir.entryList();
    QString testName = NULL;
    listMap.clear();
    cntFlag = 0;
    for(int i = 0; i<videoList.count(); i++)
    {
        qDebug()<<"video:"<<videoList.at(i);
        testName = dirPath+"/"+videoList.at(i);
        if(fileName == testName)
        {
            cntFlag = i;
            qDebug()<<"number of playlist"<<cntFlag;
        }
        listMap.insert(i,testName);
    }

    return true;
}

//添加播放列表
bool MainWindow::addPlayList()
{
    if(videoList.isEmpty())
        return false;
    ui->listWidget->clear();
    QListWidgetItem *itemList;
    for(int i = 0; i<videoList.count(); i++)
    {
        itemList = new QListWidgetItem(videoList.at(i));
        ui->listWidget->addItem(itemList);
    }
    return true;
}





