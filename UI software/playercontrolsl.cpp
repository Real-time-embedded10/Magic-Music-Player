
#include "playercontrolsl.h"

#include <QBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QComboBox>

PlayerControlsL::PlayerControlsL(QWidget *parent)
    : QWidget(parent)
    , playerState(QMediaPlayer::StoppedState)
    , playerMuted(false)
    , playButton(0)
    , stopButton(0)
    , nextButton(0)
    , previousButton(0)
    , muteButton(0)
    , volumeSlider(0)
    , rateBox(0)
{
    server = new Server();
    connect(server, SIGNAL(updateMsg(QByteArray)),
            this, SLOT(slotUpdate(QByteArray)));
    connect(&workThread, &QThread::finished, server, &QObject::deleteLater);
    connect(this, SIGNAL(sendMSG(QString)),server, SLOT(sendMSG(QString)));
    connect(this, SIGNAL(sendConfig(QString ,int)),server, SLOT(acceptConfig(QString ,int)));

    server->moveToThread(&workThread);

    workThread.start();

    playButton = new QToolButton(this);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playButton, SIGNAL(clicked()), this, SLOT(playClicked()));
    stopButton = new QToolButton(this);
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setEnabled(false);
    connect(stopButton, SIGNAL(clicked()), this, SIGNAL(stop()));
    nextButton = new QToolButton(this);
    nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    connect(nextButton, SIGNAL(clicked()), this, SIGNAL(next()));
    previousButton = new QToolButton(this);
    previousButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    connect(previousButton, SIGNAL(clicked()), this, SIGNAL(previous()));
    muteButton = new QToolButton(this);
    muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    connect(muteButton, SIGNAL(clicked()), this, SLOT(muteClicked()));
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    m_volume = 100;
    connect(volumeSlider, SIGNAL(sliderMoved(int)), this, SIGNAL(changeVolume(int)));
    rateBox = new QComboBox(this);
    rateBox->addItem("0.5x", QVariant(0.5));
    rateBox->addItem("1.0x", QVariant(1.0));
    rateBox->addItem("2.0x", QVariant(2.0));
    rateBox->setCurrentIndex(1);
    connect(rateBox, SIGNAL(activated(int)), SLOT(updateRate()));
    QBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(stopButton);
    layout->addWidget(previousButton);
    layout->addWidget(playButton);
    layout->addWidget(nextButton);
    layout->addWidget(muteButton);
    layout->addWidget(volumeSlider);
    layout->addWidget(rateBox);
    setLayout(layout);
}

PlayerControlsL::~PlayerControlsL()
{
    workThread.quit();
    workThread.wait();
}

void PlayerControlsL::slotUpdate(QByteArray datagram)
{
    qDebug()<<"datagram---"<<datagram;
    QString cmd(datagram);
    if(cmd == "1"){//PLAY
        emit play();
    }else if(cmd == "2"){//Pause
        emit  pause();
    }else if(cmd == "3"){//STOP
        emit stop();
    }else if(cmd == "4"){//NEXT SONG
        emit  next();
    }else if(cmd == "5"){//PREVIOUS
        emit  previous();
    }else if(cmd == "6"){//VOLUME++
        m_volume++;
        emit changeVolume(m_volume);
    }else if(cmd == "7"){//VOLUME--
        m_volume--;
        emit changeVolume(m_volume);
    }else if(cmd == "8"){//MUTE
        emit changeMuting();
    }else if(cmd == "9"){//CHANGERATE
       emit  changeRate();
    }
}

QMediaPlayer::State PlayerControlsL::state() const
{
    return playerState;
}

void PlayerControlsL::setState(QMediaPlayer::State state)
{
    if (state != playerState) {
        playerState = state;

        switch (state) {
        case QMediaPlayer::StoppedState:
            stopButton->setEnabled(false);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        case QMediaPlayer::PlayingState:
            stopButton->setEnabled(true);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        case QMediaPlayer::PausedState:
            stopButton->setEnabled(true);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        }
    }
}

int PlayerControlsL::volume() const
{
    return volumeSlider ? volumeSlider->value() : 0;
}

void PlayerControlsL::setVolume(int volume)
{
    if (volumeSlider)
        volumeSlider->setValue(volume);
}

bool PlayerControlsL::isMuted() const
{
    return playerMuted;
}

void PlayerControlsL::setMuted(bool muted)
{
    if (muted != playerMuted) {
        playerMuted = muted;

        muteButton->setIcon(style()->standardIcon(muted
                                                  ? QStyle::SP_MediaVolumeMuted
                                                  : QStyle::SP_MediaVolume));
    }
}

void PlayerControlsL::playClicked()
{
    switch (playerState) {
    case QMediaPlayer::StoppedState:
    case QMediaPlayer::PausedState:
        emit play();
        break;
    case QMediaPlayer::PlayingState:
        emit pause();
        break;
    }
}

void PlayerControlsL::muteClicked()
{
    emit changeMuting(!playerMuted);
}

qreal PlayerControlsL::playbackRate() const
{
    return rateBox->itemData(rateBox->currentIndex()).toDouble();
}

void PlayerControlsL::showEvent(QShowEvent *event)
{
    emit sendConfig("127.0.0.1",520);
}

void PlayerControlsL::setPlaybackRate(float rate)
{
    for (int i = 0; i < rateBox->count(); ++i) {
        if (qFuzzyCompare(rate, float(rateBox->itemData(i).toDouble()))) {
            rateBox->setCurrentIndex(i);
            return;
        }
    }

    rateBox->addItem(QString("%1x").arg(rate), QVariant(rate));
    rateBox->setCurrentIndex(rateBox->count() - 1);
}

void PlayerControlsL::updateRate()
{
    emit changeRate(playbackRate());
}

