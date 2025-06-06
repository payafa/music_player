#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::playmusic(){

    // //播放解码后的PCM流数据
    // sourceFile.setFileName("D:/qt_project/music_player/李宗盛_山丘.pcm");
    // sourceFile.open(QIODevice::ReadOnly);

    // QAudioFormat format;
    // format.setSampleRate(44100);
    // format.setChannelCount(2);
    // format.setSampleFormat(QAudioFormat::Int16);

    // QAudioDevice info(QMediaDevices::defaultAudioOutput());
    // if (!info.isFormatSupported(format)) {
    //     qWarning() << "Raw audio format not supported by backend, cannot play audio.";
    //     return;
    // }

    // audio = new QAudioSink(format, this);
    // audio->start(&sourceFile);
}

MainWindow::~MainWindow()
{
    delete audioSink;
    delete audioDecoder;
    delete ui;
}
