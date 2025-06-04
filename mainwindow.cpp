#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::playmusic(){
        sourceFile.setFileName("D:/qt_project/music_player/music/song.mp3");
        sourceFile.open(QIODevice::ReadOnly);

        QAudioFormat format;
        format.setSampleRate(8000);          // 采样率
        format.setChannelCount(1);           // 单声道
        format.setSampleFormat(QAudioFormat::UInt8);  // 8位无符号格式

        QAudioDevice info(QMediaDevices::defaultAudioOutput());
        if (!info.isFormatSupported(format)) {
            qWarning() << "Raw audio format not supported by backend, cannot play audio.";
            return;
        }

        audio = new QAudioSink(format, this);

        audio->start(&sourceFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}
