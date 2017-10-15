#ifndef SERIALBUTTON_H
#define SERIALBUTTON_H

#include <QObject>
#include <QSerialPort>

class SerialButton : public QObject
{
	Q_OBJECT



public:
	explicit SerialButton(QObject *parent = 0);

	enum ButtonStatus:char{
		Fault='2',
		Active='1',
		Processing='3',
		Off='0'
	};
private:
	QSerialPort *m_serialPort;

	bool m_buttonPressed;

signals:
	void captureButtonPressed();

public slots:
	void readButtonInput();
	void activateButton();

	void setButtonStatus(ButtonStatus buttonStatus);
};

#endif // SERIALBUTTON_H
