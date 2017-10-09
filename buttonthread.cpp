#include "buttonthread.h"
#include <QDebug>

#ifdef __APPLE__

ButtonThread::ButtonThread(QObject *parent) : QObject(parent),
	m_lastState(false)
{
}


void ButtonThread::checkButtonState()
{
}

#elif
#include <wiringPi.h>

ButtonThread::ButtonThread(QObject *parent) : QObject(parent),
	m_lastState(false)
{
	wiringPiSetup();
	pinMode(8, INPUT);
	pullUpDnControl(8, PUD_DOWN);
}

void ButtonThread::checkButtonState()
{
	while(true){
		bool buttonState = !digitalRead(8);

		if(buttonState && !m_lastState){
			qDebug() << "buttonPressed()";
			emit buttonPressed();
			QThread::msleep(1000);
		}

		m_lastState = buttonState;

		QThread::msleep(10);
	}
}
#endif
