#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,player(new QMediaPlayer(this))
    ,audioOutput(new QAudioOutput(this))
{
    ui->setupUi(this);
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);
}

void MainWindow::playmusic(){
    player->setSource(QUrl::fromLocalFile("D:/qt_project/music_player/music/李宗盛 - 山丘.mp3"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
