#include "buttonthread.h"
#include <QDebug>
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
		qDebug()<< "check" << digitalRead(8);
		bool buttonState = !digitalRead(8);

		if(buttonState && !m_lastState){
			qDebug() << "buttonPressed()";
			emit buttonPressed();
		}

		m_lastState = buttonState;

		QThread::msleep(10);
	}
}
