#include "fotoboxwidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

Widget::Widget(QWidget *parent)
	: QWidget(parent),
	  m_pixmapItem(new QGraphicsPixmapItem)
{
	m_scene = new QGraphicsScene();
	m_scene->setBackgroundBrush(QBrush(Qt::black));

	QPixmap pixmap("IMG_1139.jpg");
	m_pixmapItem->setPixmap(pixmap);


	m_view = new QGraphicsView(m_scene,this);

	QVBoxLayout *vbl = new QVBoxLayout();
	vbl->addWidget(m_view);

	QPushButton *buttonTakePicture = new QPushButton("Take Picture");
	buttonTakePicture->setFixedHeight(50);
	connect(buttonTakePicture, SIGNAL(pressed()), &m_camController, SLOT(capturePicture()));
	vbl->addWidget(buttonTakePicture);

	setLayout(vbl);

	showFullScreen();

	calculatePixmapItemScale(pixmap);
	m_scene->addItem(m_pixmapItem);
	m_scene->update();

	m_buttonController.startCheckingForButtonPress();
	connect(&m_buttonController, SIGNAL(buttonWasPressed()), &m_camController, SLOT(capturePicture()));

	connect(&m_camController, SIGNAL(pictureWasTaken(QString)), this, SLOT(showPicture(QString)));
}

Widget::~Widget()
{

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

void Widget::showPicture(QString picture)
{
	QPixmap pixmap(picture);

	calculatePixmapItemScale(pixmap);

	m_scene->removeItem(m_pixmapItem);
	m_pixmapItem->setPixmap(pixmap);
	m_scene->addItem(m_pixmapItem);
	m_scene->update();
}

void Widget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	m_sceneRatio = (float)m_scene->width()/(float)m_scene->height();
}
