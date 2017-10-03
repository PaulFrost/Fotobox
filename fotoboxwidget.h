#ifndef FOTOBOXWIDGET_H
#define FOTOBOXWIDGET_H

#include <QWidget>
#include "camcontroller.h"

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = 0);
	~Widget();

private:
	CamController camController;
};

#endif // FOTOBOXWIDGET_H
