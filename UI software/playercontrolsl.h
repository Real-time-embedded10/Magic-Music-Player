
#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <QMediaPlayer>
#include <QWidget>
#include "server.h"
#include <QThread>

class QAbstractButton;
class QAbstractSlider;
class QComboBox;

class PlayerControlsL : public QWidget
{
    Q_OBJECT

public:
    PlayerControlsL(QWidget *parent = 0);
    ~PlayerControlsL();

    QMediaPlayer::State state() const;
    int volume() const;
    bool isMuted() const;
    qreal playbackRate() const;
protected:
    virtual void showEvent(QShowEvent *event);
public slots:
    void setState(QMediaPlayer::State state);
    void setVolume(int volume);
    void setMuted(bool muted);
    void setPlaybackRate(float rate);

signals:
    void sendConfig(QString ,int);
    void sendMSG(QString);
    void play();
    void pause();
    void stop();
    void next();
    void previous();
    void changeVolume(int volume);
    void changeMuting(bool muting);
    void changeRate(qreal rate);

private slots:
    void slotUpdate(QByteArray datagram);
    void playClicked();
    void muteClicked();
    void updateRate();

private:
    QMediaPlayer::State playerState;
    bool playerMuted;
    QAbstractButton *playButton;
    QAbstractButton *stopButton;
    QAbstractButton *nextButton;
    QAbstractButton *previousButton;
    QAbstractButton *muteButton;
    QAbstractSlider *volumeSlider;
    QComboBox *rateBox;
    QThread workThread;
    Server *server;
    int m_volume;
    int speed;
};

#endif // PLAYERCONTROLS_H
