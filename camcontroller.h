#ifndef CAMCONTROLLER_H
#define CAMCONTROLLER_H

#include <QObject>

#include <gphoto2/gphoto2.h>

class CamController : public QObject
{
	Q_OBJECT

public:
	explicit CamController(QObject *parent = 0);
	~CamController();


private:
	Camera *m_camera;
	GPContext *m_context;

signals:


public slots:
	void capturePicture();


};

#endif // CAMCONTROLLER_H
