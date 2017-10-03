#include "fotoboxwidget.h"

#include <QPushButton>

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{
	QPushButton *buttonTakePicture = new QPushButton("Take Picture", this);
	connect(buttonTakePicture, SIGNAL(pressed()), &m_camController, SLOT(capturePicture()));
}

Widget::~Widget()
{

}
