#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "IMPlayer/implayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openButton_clicked();

    void on_playButton_clicked();

    void on_stopButton_clicked();

    void on_lockButton_clicked();

    void on_BigButton_clicked();

    void on_playPosionSlider_sliderMoved(int position);

    void on_volumeSlider_sliderMoved(int position);

    void on_volumeSlider_valueChanged(int value);

    void on_volumeButton_clicked();

    void on_prevButton_clicked();

    void on_nextButton_clicked();

    void on_listButton_clicked();

    void on_internetButton_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    ///获取播放器状态变化
    void slt_getPlayerState(QMediaPlayer::State state);
    ///设置进度条进度与播放进度同步
    void slt_synSlideToPlayPosion(qint64 posion);
    ///设置范围进度条范围
    void slt_setSliderRange(qint64 range);
    ///处理播放异常
    void slt_handleError(QMediaPlayer::Error error);

private:
    Ui::MainWindow *ui;

    //初始话MediaPlayer播放器
    void InitPlayer(void);
    //设置初始界面
    void InitInterFace(void);
    //连接信号与槽
    void connectSigToSlot(void);

    ///IMplayer
    //播放多媒体
    bool playMedia(void);
    //获取播放列表
    bool getPlayList(void);
    //添加播放列表
    bool addPlayList(void);

    QMediaPlayer *implayer;
    QString fileName;
    QString dirPath;
    QStringList videoList;
    bool volFlag;
    bool lockFlag;
    bool listFlag;
    int cntFlag;
    QMap<int,QString> listMap;
};


#endif // MAINWINDOW_H
