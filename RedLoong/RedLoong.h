#ifndef REDLOONG_H
#define REDLOONG_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QTextCodec>

namespace Ui {
class RedLoong;
}

class RedLoong : public QMainWindow
{
    Q_OBJECT

public:
    explicit RedLoong(QWidget *parent = nullptr);
    ~RedLoong();

private slots:
    void on_searchButton_clicked();

    void on_homeButton_clicked();

    void on_refreshButton_clicked();

    void on_nextButton_clicked();

    void on_prevButton_clicked();

    void slt_setWebTitle(bool flag);

//    void slt_goToNewWeb(QUrl newWeb);

private:
    Ui::RedLoong *ui;

    void initRedLoong(void);
    void initMainFace(void);

    QString homePage;
    QString nowPage;

};


#endif // REDLOONG_H
