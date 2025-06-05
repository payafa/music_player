#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::playmusic(){
    // url->QUrl::fromLocalFile("D:/qt_project/music_player/music/song.mp3");

    // QAudioFormat format;
    // format.setSampleRate(44100);
    // format.setChannelCount(2);
    // format.setSampleFormat(QAudioFormat::Int16);

    // audioSink = new QAudioSink(format, this);
    // audioDevice = audioSink->start();

    // decoder = new QAudioDecoder();
    // decoder->setSource(*url);

    // connect(decoder, &QAudioDecoder::bufferReady, this, &MainWindow::onBufferReady);
    // connect(decoder, &QAudioDecoder::finished, this, &MainWindow::onDecodingFinished);

    // decoder->start();
    // qDebug() << "开始解码音频...";

    sourceFile.setFileName("D:/qt_project/music_player/music/202506051141_7e6d0b.pcm");
    sourceFile.open(QIODevice::ReadOnly);

    QAudioFormat format;
    // Set up the format, eg.
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleFormat(QAudioFormat::Int16);

    QAudioDevice info(QMediaDevices::defaultAudioOutput());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    audio = new QAudioSink(format, this);
    audio->start(&sourceFile);
}

// // **当 QAudioDecoder 有新的音频数据时调用此函数**
// void MainWindow::onBufferReady() {
//     QAudioBuffer buffer = decoder->read();
//     if (!buffer.isValid()) {
//         qWarning() << "无效的音频缓冲区";
//         return;
//     }

//     // **将音频数据写入 QAudioSink**
//     audioDevice->write(
//         reinterpret_cast<const char*>(buffer.constData<quint16>()),
//         buffer.byteCount()
//         );
// }

// // **当解码完成时调用**
// void MainWindow::onDecodingFinished() {
//     qInfo() << "音频解码完成";
//     audioSink->stop();
// }

MainWindow::~MainWindow()
{
    delete ui;
}
