#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

//迭代查找音频流索引
int find_audio_stream(AVFormatContext *fmt_ctx) {
    for (unsigned int i = 0; i < fmt_ctx->nb_streams; i++) {
        if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            return i;
        }
    }
    return -1;
}

void MainWindow::ts(){
    //定义AVFromatContext,下面好多东西都要那他做参数
    AVFormatContext *fmt_ctx = NULL;

    //avformat_open_input，填写文件路径来初始化AVFormatContext
    QString absolutePath = "D:/qt_project/music_player/music/song.mp3";
    if (avformat_open_input(&fmt_ctx, absolutePath.toStdString().c_str(), NULL, NULL) < 0) {
        qDebug() << "打不开媒体文件";
        return;
    }

    //查找音频流索引，定义音频流
    int audio_idx = find_audio_stream(fmt_ctx);
    qDebug() << "音频流索引为" <<audio_idx;
    AVStream *audio_stream = fmt_ctx->streams[audio_idx];

    //通过音频流的codecpar成员初始化AVCodecParameter（用来给AVCodecContext初始化），通过codecpar->codec_id初始化AVCodec（用来定义AVCodecContext）
    AVCodecParameters *codecpar = audio_stream->codecpar;
    const AVCodec *codec = avcodec_find_decoder(codecpar->codec_id);
    if (!codec) {
        qDebug() << "不支持的解码器:" << avcodec_get_name(codecpar->codec_id);
        return;
    }

    //通过codec定义AVCodecContext并用codecpar初始化
    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codec_ctx, codecpar);
    if (avcodec_open2(codec_ctx, codec, NULL) < 0) {
        qDebug() << "无法打开解码器";
        avcodec_free_context(&codec_ctx);
        avformat_close_input(&fmt_ctx);
        return;
    }

    //初始化输出音频格式
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleFormat(QAudioFormat::UInt8);

    //使用默认音频
    QAudioDevice info(QMediaDevices::defaultAudioOutput());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    //初始化QAudioSink并启动，返回输出音频的QIODevice，PCM流write进这个QIODevice就可以播放音乐了
    audio = new QAudioSink(format, this);
    ioDevice = audio->start();

    //初始化AVPacket（解码前的原始数据存储容器）和AVFrame（解码后的PCM数据存储容器）
    AVPacket *pkt = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();

    //开始给解码器发包，每发一个pkt就向frame里存储一帧，随即write进QIODevice就可以播放这一帧的音乐了，用while循环反复播放
    while(av_read_frame(fmt_ctx , pkt) >= 0){
        if(pkt -> stream_index == audio_idx){
            if(avcodec_send_packet(codec_ctx , pkt) < 0){
                qDebug() << "发送数据包失败";
                break;
            }

            //下面会写上对frame的处理，还会把数据write进QIODevice，估计还会写重采样
        }
    }
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
    delete ui;
}
