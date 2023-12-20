#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDate>
#include <QTime>

class Message {
    int id;
    QDate date;
    QTime time;
    QString message;
    int randomNumber;

public:
    Message();

    Message(int id, const QDate& date, const QTime& time, const QString& message, int randomNumber);

    int getId() const;

    void setId(int id);

    QDate getDate() const;

    void setDate(const QDate& date);

    QTime getTime() const;

    void setTime(const QTime& time);

    QString getMessage() const;

    void setMessage(const QString& message);

    int getRandomNumber() const;

    void setRandomNumber(int randomNumber);

    QString toString();
};

#endif // MESSAGE_H
