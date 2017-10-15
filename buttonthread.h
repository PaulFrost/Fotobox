#ifndef BUTTONTHREAD_H
#define BUTTONTHREAD_H

#include <QObject>
#include <QThread>

class ButtonThread : public QObject
{
	Q_OBJECT
public:
	explicit ButtonThread(QObject *parent = 0);
private:

	bool m_lastState;

signals:

public slots:
	void checkButtonState();

signals:
	void buttonPressed();

};

#endif // BUTTONTHREAD_H
