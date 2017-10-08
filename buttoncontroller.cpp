#include "buttoncontroller.h"

#include "buttonthread.h"

ButtonController::ButtonController(QObject *parent) : QObject(parent)
{
	ButtonThread *buttonThread = new ButtonThread;
	buttonThread->moveToThread(&parallelThread);
	connect(&parallelThread, SIGNAL(finished()), buttonThread, SLOT(deleteLater()));
	connect(this, SIGNAL(shouldStartChecking()), buttonThread, SLOT(checkButtonState()));
	connect(buttonThread, SIGNAL(buttonPressed()), this, SLOT(handleButtonPressed()));
	parallelThread.start();
}

ButtonController::~ButtonController()
{
	parallelThread.quit();
	parallelThread.wait();
}

void ButtonController::startCheckingForButtonPress()
{
	emit shouldStartChecking();
}

void ButtonController::handleButtonPressed()
{
	emit buttonWasPressed();
}
