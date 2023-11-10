#include "message.h"

Message::Message() {

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


