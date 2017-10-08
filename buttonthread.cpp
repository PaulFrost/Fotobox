#include "buttonthread.h"
#include <QDebug>
#include <wiringPi.h>

ButtonThread::ButtonThread(QObject *parent) : QObject(parent),
	m_lastState(false)
{
	pullUpDnControl(3, PUD_DOWN);
}

void ButtonThread::checkButtonState()
{
	while(true){
		bool buttonState = digitalRead(3);

		if(buttonState && !m_lastState){
			qDebug() << "buttonPressed()";
			emit buttonPressed();
		}

		m_lastState = buttonState;

		QThread::msleep(10);
	}
}
