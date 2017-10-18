#include "serialbutton.h"
#include <QDebug>
#include <QTimer>

#include "settings.h"

SerialButton::SerialButton(QObject *parent) : QObject(parent),
	m_serialPort(new QSerialPort(Settings::serialPortName(), this)),
	m_buttonPressed(false)
{
	if(!m_serialPort->open(QIODevice::ReadWrite)){
		qWarning() << "Serial port could not be opened";
	}
	connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(readButtonInput()));
}

void SerialButton::readButtonInput()
{
	while (m_serialPort->bytesAvailable()) {
		QByteArray ba = m_serialPort->readAll();
		if(!m_buttonPressed && (char)m_buttonStatus == Active){

			qDebug()<< (char)m_buttonStatus;
			if(ba.contains('C')){

				m_buttonPressed = true;

				emit captureButtonPressed();

				QTimer::singleShot(1000,this, SLOT(activateButton()));
			}
		}

	}
}

void SerialButton::activateButton()
{
	m_buttonPressed = false;
}

void SerialButton::setButtonStatus(ButtonStatus buttonStatus)
{
	m_serialPort->clear();

	m_buttonStatus = buttonStatus;
	const char charValue = buttonStatus;
	m_serialPort->write(&charValue, 1);
	m_serialPort->flush();
}
