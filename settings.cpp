#include "settings.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>

QJsonValue Settings::settingsValue(const QString &key)
{
	QFile jsonFile("./settings.json");

	if(!jsonFile.open(QIODevice::ReadOnly)){
		qWarning() << "Could not open settings.json!";
		return QJsonValue();
	}

	QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
	jsonFile.close();

	return doc.object().value(key);
}


Settings::Settings(QObject *parent) : QObject(parent)
{

}

QString Settings::cameraName()
{
	QJsonValue jValue = Settings::settingsValue("cameraName");

	return jValue.toString("Sony Alpha-A6000 (Control)");
}

QString Settings::challangeStyle()
{
	QString challangeString = "<style> p {margin: 120px; margin-left: 60px;} h2 {margin-left: 60px;} </style>&nbsp;</ br><h2>The challenge:</h2> <p> %1 </p>";

	QJsonValue jValue = Settings::settingsValue("challangeStyle");

	return jValue.toString(challangeString);
}

QString Settings::folderFotoDestination()
{
	QJsonValue jValue = Settings::settingsValue("folderFotoDestination");

	QString filePath = jValue.toString("./");

	if(filePath.right(1) != "/"){
		filePath.append("/");
	}

	return filePath;
}

QString Settings::pictureMainFoto()
{
	QJsonValue jValue = Settings::settingsValue("pictureMainFoto");

	return jValue.toString("IMG_1139.jpg");
}

QString Settings::serialPortName()
{
	QJsonValue jValue = Settings::settingsValue("serialPortName");

	return jValue.toString("/dev/cu.usbmodem1411");
}

int Settings::fontPixelSize()
{
	QJsonValue jValue = Settings::settingsValue("fontPixelSize");

	return (int)jValue.toDouble(60.0);
}

int Settings::textYOffset()
{
	QJsonValue jValue = Settings::settingsValue("textYOffset");

	return (int)jValue.toDouble(60.0);
}

int Settings::timeCaptureOffset()
{
	QJsonValue jValue = Settings::settingsValue("timeCaptureOffset");

	return (int)jValue.toDouble(1000.0);
}

int Settings::timeDelayAfterChallenge()
{
	QJsonValue jValue = Settings::settingsValue("timeDelayAfterChallenge");

	return (int)jValue.toDouble(4500.0);
}

int Settings::timeTimeoutChallenge()
{
	QJsonValue jValue = Settings::settingsValue("timeTimeoutChallenge");

	return (int)jValue.toDouble(18000.0);
}

int Settings::timeTimeoutAfterCapture()
{
	QJsonValue jValue = Settings::settingsValue("timeTimeoutAfterCapture");

	return (int)jValue.toDouble(4000.0);
}

int Settings::timeTimeoutBeforeCapture()
{
	QJsonValue jValue = Settings::settingsValue("timeTimeoutBeforeCapture");

	return (int)jValue.toDouble(6000.0);
}

int Settings::videoYOffset()
{
	QJsonValue jValue = Settings::settingsValue("videoYOffset");

	return (int)jValue.toDouble(-60.0);
}

QString Settings::videoFilePath()
{
	QJsonValue jValue = Settings::settingsValue("videoFilePath");

	return jValue.toString("FlashCountdown.mp4");
}
