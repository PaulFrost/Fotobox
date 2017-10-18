#ifndef FOTOBOXWIDGET_H
#define FOTOBOXWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <QMediaPlayer>
#include <QGraphicsVideoItem>
#include <QTimer>

#include "camcontroller.h"
#include "buttoncontroller.h"
#include "serialbutton.h"

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = 0);
	~Widget();

public slots:
	void setChallenge();
	void startCountdown();
	void timeOut();
	void showPicture(QString picture);

protected:
	void closeEvent(QCloseEvent *event);
	void resizeEvent(QResizeEvent *event);

private slots:
	void mediaPositionChanged(qint64 pos);

private:
	ButtonController m_buttonController;
	SerialButton m_serialButton;
	QTimer m_TimeoutTimer;

	CamController *m_camController;
	QPushButton *m_buttonCapturePicture;

	bool m_buttonPressed;

	QGraphicsView *m_view;
	QGraphicsScene *m_scene;

	QGraphicsTextItem *m_textItem;
	QMediaPlayer *m_player;
	QGraphicsVideoItem *m_videoItem;

	QGraphicsPixmapItem *m_pixmapItem;
	void calculatePixmapItemScale(const QPixmap &pixmap);
	float m_sceneRatio;

	const QString m_settingChallangeStyle;
	const QString m_settingPictureMainFoto;
	const int m_settingFontPixelSize;
	const int m_settingTextYOffset;
	const int m_settingTimeCaptureOffset;
	const int m_settingTimeDelayAfterChallenge;
	const int m_settingTimeTimeoutChallenge;
	const int m_settingTimeTimeoutAfterCapture;
	const int m_settingTimeTimeoutBeforeCapture;
	const int m_settingVideoYOffset;
	const QString m_settingVideoFilePath;
};

#endif // FOTOBOXWIDGET_H
