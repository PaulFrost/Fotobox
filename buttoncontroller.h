#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include <QObject>
#include <QThread>

class ButtonController : public QObject
{
	Q_OBJECT
public:
	explicit ButtonController(QObject *parent = 0);
	~ButtonController();
private:
	QThread parallelThread;

signals:
	void shouldStartChecking();
	void buttonWasPressed();

public slots:
	void startCheckingForButtonPress();

private slots:
	void handleButtonPressed();
};

#endif // BUTTONCONTROLLER_H
