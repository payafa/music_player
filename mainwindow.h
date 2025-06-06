#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QUrl>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void playmusic();
    void ts();

private:
    Ui::MainWindow *ui;


public slots:

};
#endif // MAINWINDOW_H
