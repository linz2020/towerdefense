#include "mainwindow.h"

#include <QApplication>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("一起来塔防");
    w.show();

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/bgm.mp3"));
    player->setVolume(30);
    player->play();

    return a.exec();
}
