#ifndef FOTOBOXWIDGET_H
#define FOTOBOXWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "camcontroller.h"

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = 0);
	~Widget();

private:
	CamController m_camController;
	QPushButton *m_buttonCapturePicture;
};

#endif // FOTOBOXWIDGET_H
