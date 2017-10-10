#ifndef CHALLENGEPARSER_H
#define CHALLENGEPARSER_H

#include <QObject>

class ChallengeParser : public QObject
{
	Q_OBJECT
public:
	explicit ChallengeParser(QObject *parent = 0);

	QString getChallenge();

private:
	QStringList m_challengeStrings;

signals:

public slots:
};

#endif // CHALLENGEPARSER_H
