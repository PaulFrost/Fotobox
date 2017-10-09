#ifndef FOTOBOXWIDGET_H
#define FOTOBOXWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <QMediaPlayer>
#include <QGraphicsVideoItem>

#include "camcontroller.h"
#include "buttoncontroller.h"

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = 0);
	~Widget();

public slots:
	void startCountdown();
	void showPicture(QString picture);

protected:
	void resizeEvent(QResizeEvent *event);

private slots:
	void mediaPositionChanged(qint64 pos);

private:
	ButtonController m_buttonController;
	CamController m_camController;
	QPushButton *m_buttonCapturePicture;

	QGraphicsView *m_view;
	QGraphicsScene *m_scene;

	QMediaPlayer *m_player;
	QGraphicsVideoItem *m_videoItem;

	QGraphicsPixmapItem *m_pixmapItem;
	void calculatePixmapItemScale(const QPixmap &pixmap);
	float m_sceneRatio;
};

#endif // FOTOBOXWIDGET_H
