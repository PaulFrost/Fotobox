#include "challengeparser.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include <QDateTime>

ChallengeParser::ChallengeParser(QObject *parent) : QObject(parent)
{


	QFile jsonFile("./challenges.json");

	if(!jsonFile.open(QIODevice::ReadOnly)){
		qWarning() << "Could not open challenges.json!";
	}

	QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
	jsonFile.close();

	for(int i = 0; i < doc.array().count(); i++){
		m_challengeStrings.append(doc.array()[i].toString());
	}
}

QString ChallengeParser::getChallenge()
{
	qsrand(QDateTime::currentSecsSinceEpoch());

	if(!m_challengeStrings.isEmpty()){
//		int index = qRound((double)qrand() / (double)RAND_MAX * (double) m_challengeStrings.count());
		int index = qrand() % m_challengeStrings.count();
		return m_challengeStrings[index];
	}

	return "Mach ein Bild";
}
