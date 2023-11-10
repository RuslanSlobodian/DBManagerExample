#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDate>
#include <QTime>

class Message {
    QDate date;
    QTime time;
    QString message;
    int randomNumber;

public:
    Message();

    QDate getDate() const;

    void setDate(const QDate& date);

    QTime getTime() const;

    void setTime(const QTime& time);

    QString getMessage() const;

    void setMessage(const QString& message);

    int getRandomNumber() const;

    void setRandomNumber(int randomNumber);
};

#endif // MESSAGE_H
