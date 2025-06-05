#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QUrl>
#include <QAudioSink>
#include <QIODevice>
#include <QAudioDecoder>

#include <QMediaPlayer>
#include <QAudioOutput>

#include <QMediaDevices>
#include <QFile>

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

private:
    Ui::MainWindow *ui;
    QUrl* url;
    // QAudioSink* audioSink;
    // QIODevice* audioDevice;
    // QAudioDecoder* decoder;

    QAudioSink* audio;
    QFile sourceFile;



public slots:
    // void onBufferReady();
    // void onDecodingFinished();
};
#endif // MAINWINDOW_H
