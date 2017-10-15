#ifndef CAMCONTROLLER_H
#define CAMCONTROLLER_H

#include <QObject>

#include <gphoto2/gphoto2.h>

class CamController : public QObject
{
	Q_OBJECT

	enum CamStatus{
		Active,
		Capturing,
		NotReady
	};

public:
	explicit CamController(QObject *parent = 0);
	~CamController();

	CamStatus currentCamStatus() const;

private:
	Camera *m_camera;
	GPContext *m_context;

	CamStatus m_camStatus;

	void getFileFromCam(CameraFilePath *cameraFilePath);

signals:
	void pictureWasTaken(QString fileName);

public slots:
	void capturePicture();


};

#endif // CAMCONTROLLER_H
