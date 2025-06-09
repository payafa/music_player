#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QUrl>
#include <QAudioFormat>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QAudioSink>
#include <QIODevice>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/samplefmt.h>
#include <libswresample/swresample.h>
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
    AVFormatContext *fmt_ctx;
    QAudioSink* audio;
    QIODevice* ioDevice;

public slots:

};
#endif // MAINWINDOW_H
