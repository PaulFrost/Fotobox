#include "fotoboxwidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QTimer>
#include <QCloseEvent>
#include <QDebug>
#include "challengeparser.h"

Widget::Widget(QWidget *parent)
	: QWidget(parent),
	  m_buttonPressed(false),
	  m_camController(nullptr),
	  m_textItem(new QGraphicsTextItem),
	  m_player(new QMediaPlayer(this)),
		m_videoItem(new QGraphicsVideoItem),
	  m_pixmapItem(new QGraphicsPixmapItem)
{
	m_player->setVideoOutput(m_videoItem);
	m_player->setMedia(QUrl::fromLocalFile(QFileInfo("FlashCountdown.mp4").absoluteFilePath()));


	m_scene = new QGraphicsScene();
	m_scene->setBackgroundBrush(QBrush(Qt::black));




	m_view = new QGraphicsView(m_scene,this);


	QVBoxLayout *vbl = new QVBoxLayout();
	vbl->addWidget(m_view);

//	QPushButton *buttonTakePicture = new QPushButton("Take Picture");
//	buttonTakePicture->setFixedHeight(50);
//	connect(buttonTakePicture, SIGNAL(pressed()), this, SLOT(setChallenge()));
//	vbl->addWidget(buttonTakePicture);

	setLayout(vbl);

	showFullScreen();




	connect(&m_TimeoutTimer, SIGNAL(timeout()),this, SLOT(timeOut()));

	m_buttonController.startCheckingForButtonPress();
	connect(&m_buttonController, SIGNAL(buttonWasPressed()), this, SLOT(setChallenge()));
	connect(&m_serialButton, SIGNAL(captureButtonPressed()),this,SLOT(setChallenge()));

	connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(mediaPositionChanged(qint64)));

	QTimer::singleShot(1000, this, SLOT(timeOut()));
}

Widget::~Widget()
{
}

void Widget::setChallenge()
{
	if(!m_buttonPressed) {
		m_camController = new CamController(this);
		connect(m_camController, &CamController::pictureWasTaken, this, &Widget::showPicture);

		m_buttonPressed = true;

		m_serialButton.setButtonStatus(SerialButton::Processing);

		ChallengeParser cp;

		m_scene->removeItem(m_pixmapItem);

		QFont font("Helvetica");
		font.setPixelSize(60);
		m_textItem->setHtml(QString("<style>\
								p {margin: 120px; margin-left: 60px;}\
								h2 {margin-left: 60px;}\
							</style>&nbsp;</ br><h2>The challenge:</h2> <p> %1 </p>").arg(cp.getChallenge()));
		m_textItem->setDefaultTextColor(QColor(Qt::white));
		m_textItem->setFont(font);
		m_textItem->setTextWidth(m_scene->width());
		m_textItem->setY(60);
		m_scene->addItem(m_textItem);
		m_scene->update();
		QTimer::singleShot(4500,this, SLOT(startCountdown()));
		m_TimeoutTimer.start(18000);
	}
}

void Widget::startCountdown()
{
		m_buttonPressed = true;
		qDebug () << Q_FUNC_INFO;
		m_scene->removeItem(m_textItem);
		m_scene->update();
//		m_scene->clear();

		m_videoItem->setSize(m_scene->sceneRect().size());
		m_videoItem->setY(-60);
		m_scene->addItem(m_videoItem);

		m_player->play();
}

void Widget::timeOut()
{
	qDebug() << "Ready for a new picture";

	m_TimeoutTimer.stop();
	m_player->stop();

	m_scene->removeItem(m_pixmapItem);

	QPixmap pixmap("IMG_1139.jpg");
	m_pixmapItem->setPixmap(pixmap);
	calculatePixmapItemScale(pixmap);

	m_scene->addItem(m_pixmapItem);
	m_scene->update();

	m_serialButton.setButtonStatus(SerialButton::Active);
	m_buttonPressed = false;

	if(m_camController){
		m_camController->disconnect();
		delete m_camController;
		m_camController = nullptr;
	}
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
		m_camController->capturePicture();
	}
}

void Widget::showPicture(QString picture)
{
	m_TimeoutTimer.start(6000);
	if(m_buttonPressed){
		m_buttonPressed = false;

		qDebug() << Q_FUNC_INFO << picture;
		QPixmap pixmap(picture);

		calculatePixmapItemScale(pixmap);


		m_pixmapItem->setPixmap(pixmap);
		m_scene->addItem(m_pixmapItem);
		m_scene->update();


		QTimer::singleShot(4000, this, SLOT(timeOut()));
	}
}

void Widget::closeEvent(QCloseEvent *event)
{
	m_serialButton.setButtonStatus(SerialButton::Off);
	event->accept();
}

void Widget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	m_sceneRatio = (float)m_scene->width()/(float)m_scene->height();
}
