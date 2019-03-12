#include "widget.h"
#include "ui_widget.h"
#include <QMediaPlayer>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mMediaPlayer = new QMediaPlayer(this);

    connect(mMediaPlayer, &QMediaPlayer::positionChanged, [&](qint64 pos ) {
        ui->advance->setValue(pos);
    });
    connect(mMediaPlayer, &QMediaPlayer::durationChanged, [&](qint64 dur) {
        ui->advance->setMaximum(dur);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_open_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open");
    if (filename.isEmpty()) {
        return;
    }
    mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
    mMediaPlayer->setVolume(ui->volume->value());
    on_play_clicked();
}

void Widget::on_play_clicked()
{
    mMediaPlayer->play();
}

void Widget::on_pause_clicked()
{
    mMediaPlayer->pause();
}

void Widget::on_stop_clicked()
{
    mMediaPlayer->stop();
}

void Widget::on_mute_clicked()
{
    if (ui->mute->text() == "Mute"){
        mMediaPlayer->setMuted(true);
        ui->mute->setText("Unmute");
    } else {
        mMediaPlayer->setMuted(false);
        ui->mute->setText("Mute");
 }

}

void Widget::on_volume_valueChanged(int value)
{
    mMediaPlayer->setVolume(value);
}
