#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::playmusic(){
    //解码音乐格式成PCM流
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleFormat(QAudioFormat::Int16);

    audioSink = new QAudioSink(format, this);
    audioDevice = audioSink->start();

    audioDecoder = new QAudioDecoder(this);
    audioDecoder->setSource(QUrl::fromLocalFile("D:/qt_project/music_player/music/song1.mp3"));

    connect(audioDecoder,&QAudioDecoder::bufferReady,this,&MainWindow::isBufferReady);
    connect(audioDecoder,&QAudioDecoder::finished,this,&MainWindow::isBufferFinished);
    connect(audioDecoder, QOverload<QAudioDecoder::Error>::of(&QAudioDecoder::error),
            [](QAudioDecoder::Error error) {
                qDebug() << "Error occurred:" << error;
            });

    audioDecoder->start();
    qDebug() << "开始解码音频...";



    // //播放解码后的PCM流数据
    // sourceFile.setFileName("D:/qt_project/music_player/music/202506051141_7e6d0b.pcm");
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

//播放
void MainWindow::isBufferReady(){
    QAudioBuffer buffer = audioDecoder->read();

    if (!buffer.isValid()) {
        qWarning() << "无效的音频缓冲区";
        return;
    }

    const char *audioData = buffer.constData<char>();
    if (audioDevice && audioDevice->isOpen()) {
        qint64 bytesWritten = audioDevice->write(audioData, buffer.byteCount());
        if (bytesWritten == -1) {
            qWarning() << "写入失败：" << audioDevice->errorString();
        }
    }
}

//判断解码是否finished
void MainWindow::isBufferFinished(){
    qInfo() << "音频解码完成";
    audioSink->stop();
}


MainWindow::~MainWindow()
{
    delete audioSink;
    delete audioDecoder;
    delete ui;
}
