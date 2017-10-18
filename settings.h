#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
	Q_OBJECT
	static QJsonValue settingsValue(const QString &key);

public:
	explicit Settings(QObject *parent = 0);

	static QString cameraName();
	static QString challangeStyle();
	static QString folderFotoDestination();
	static QString pictureMainFoto();
	static QString serialPortName();

	static int fontPixelSize();

	static int textYOffset();

	static int timeCaptureOffset();
	static int timeDelayAfterChallenge();
	static int timeTimeoutChallenge();
	static int timeTimeoutAfterCapture();
	static int timeTimeoutBeforeCapture();

	static QString videoFilePath();
	static int videoYOffset();




signals:

public slots:
};

#endif // SETTINGS_H
