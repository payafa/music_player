# music_player 音乐播放器，使用QT编写
## *目标功能*
- 音乐的播放，暂停
- 调整音乐的播放时间
- 创建存储本地音乐库
- 实现播放音乐的上一首，下一首
- 点击收藏音乐，并存入收藏音乐清单
- 音乐的循环播放机制
- ......

## 音乐播放
    1.创建AVFormatContext并指定AVInputFormat
    2.从AVFormatContext中分流，使用AVStream分出音频流
    3.给音频流解复用成AVPacket包
    4.逐个给AVPacket包解码成PCM流
    5.把整个PCM流存在本地，作为已经听过的歌的缓冲内容
    6.先判断这首歌是否有本地缓冲，如果有直接music_play，如果没有再解成PCM流再播放。
