#include "message.h"

Message::Message() {
}

Message::Message(int id, const QDate& date, const QTime& time, const QString& message, int randomNumber) :
    id(id), date(date), time(time), message(message), randomNumber(randomNumber) {
}

int Message::getId() const {
    return id;
}

void Message::setId(int id) {
    this->id = id;
}

QDate Message::getDate() const {
    return date;
}

void Message::setDate(const QDate& date) {
    this->date = date;
}

QTime Message::getTime() const {
    return time;
}

void Message::setTime(const QTime& time) {
    this->time = time;
}

QString Message::getMessage() const {
    return message;
}

void Message::setMessage(const QString& message) {
    this->message = message;
}

int Message::getRandomNumber() const {
    return randomNumber;
}

void Message::setRandomNumber(int randomNumber) {
    this->randomNumber = randomNumber;
}

QString Message::toString()
{
    return "Message(id: " + QString::number(id) +
           ", date: " + date.toString() +
           ", time: " + time.toString() +
           ", message: " + message +
           ", randomNumber: " + QString::number(randomNumber) +
           ")";
}


