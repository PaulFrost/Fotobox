#include "fotoboxwidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QTimer>
#include <QDebug>
#include "challengeparser.h"

Widget::Widget(QWidget *parent)
	: QWidget(parent),
	  m_textItem(new QGraphicsTextItem),
	  m_player(new QMediaPlayer(this)),
	  m_videoItem(new QGraphicsVideoItem),
	  m_pixmapItem(new QGraphicsPixmapItem),
	  m_buttonPressed(false)
{
	m_player->setVideoOutput(m_videoItem);
	m_player->setMedia(QUrl::fromLocalFile(QFileInfo("FlashCountdown.mp4").absoluteFilePath()));


	m_scene = new QGraphicsScene();
	m_scene->setBackgroundBrush(QBrush(Qt::black));

	QPixmap pixmap("IMG_1139.jpg");
	m_pixmapItem->setPixmap(pixmap);


	m_view = new QGraphicsView(m_scene,this);

	QVBoxLayout *vbl = new QVBoxLayout();
	vbl->addWidget(m_view);

	QPushButton *buttonTakePicture = new QPushButton("Take Picture");
	buttonTakePicture->setFixedHeight(50);
	connect(buttonTakePicture, SIGNAL(pressed()), this, SLOT(setChallenge()));
	vbl->addWidget(buttonTakePicture);

	setLayout(vbl);

	showFullScreen();

	calculatePixmapItemScale(pixmap);
	m_scene->addItem(m_pixmapItem);
	m_scene->update();

	m_buttonController.startCheckingForButtonPress();
	connect(&m_buttonController, SIGNAL(buttonWasPressed()), this, SLOT(setChallenge()));
	connect(&m_serialButton, SIGNAL(captureButtonPressed()),this,SLOT(setChallenge()));
	connect(&m_camController, SIGNAL(pictureWasTaken(QString)), this, SLOT(showPicture(QString)));
	connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(mediaPositionChanged(qint64)));
	m_serialButton.setButtonStatus(SerialButton::Active);
}

Widget::~Widget()
{
}

void Widget::setChallenge()
{
	m_serialButton.setButtonStatus(SerialButton::Processing);

	ChallengeParser cp;

	m_scene->removeItem(m_pixmapItem);

	QFont font("Helvetica");
	font.setPixelSize(60);
	m_textItem->setHtml(QString("<style>\
							p {margin: 6em;}\
							h1 {margin: 3em;}\
						</style>&nbsp;</ br><h1>The challenge:</h1> <p> %1 </p>").arg(cp.getChallenge()));
	m_textItem->setDefaultTextColor(QColor(Qt::white));
	m_textItem->setFont(font);
	m_textItem->setTextWidth(m_scene->width());
	m_scene->addItem(m_textItem);
	m_scene->update();
	QTimer::singleShot(4500,this, SLOT(startCountdown()));
}

void Widget::startCountdown()
{
	qDebug () << Q_FUNC_INFO;
	m_scene->removeItem(m_textItem);

	m_buttonPressed = true;



//	m_scene->addText("nichts hören, nichts sehen, nichts sagen",font);

	m_scene->update();

//	QThread::msleep(4500);

	m_videoItem->setSize(m_scene->sceneRect().size());
	m_scene->addItem(m_videoItem);
	m_player->play();
}

void Widget::calculatePixmapItemScale(const QPixmap &pixmap)
{
	float pixRatio = (float)pixmap.size().width()/(float)pixmap.size().height();

	float scale;

	if(pixRatio / m_sceneRatio > 1.f){
		scale = (float)m_view->height() / (float)pixmap.height();
	}
	else
	{
		scale = (float)m_view->width() / (float)pixmap.width();
	}

	m_pixmapItem->setScale(scale);
}

void Widget::mediaPositionChanged(qint64 pos)
{
	if(pos > m_player->duration() -1000 && m_buttonPressed){

		m_buttonPressed = false;

//		m_scene->removeItem(m_videoItem);
//		m_player->stop();

//		m_scene->addItem(m_pixmapItem);
		m_camController.capturePicture();
	}
}

void Widget::showPicture(QString picture)
{
	QPixmap pixmap(picture);

	calculatePixmapItemScale(pixmap);

	m_scene->removeItem(m_videoItem);
	m_pixmapItem->setPixmap(pixmap);
	m_scene->addItem(m_pixmapItem);
	m_scene->update();
	m_serialButton.setButtonStatus(SerialButton::Active);
}

void Widget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	m_sceneRatio = (float)m_scene->width()/(float)m_scene->height();
}
