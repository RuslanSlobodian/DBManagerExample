#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "message.h"
#include <QSqlDatabase>

// Абстрактний клас (інтерфейс) для роботи з базою даних
class DBManager {
public:
    // Суто віртуальний метод для підключення до бази даних
    virtual void connectToDataBase() = 0;

    // Суто віртуальний метод для отримання обробника (хендлера) підключення до БД
    virtual QSqlDatabase& getDB() = 0;

    // Суто віртуальний метод для збереження повідомлення у базі даних
    virtual bool inserIntoTable(const Message& message) = 0;

    // Суто віртуальний метод для отримання повідомлення по id
    virtual Message findMessageById(int id) = 0;
};

#endif // DBMANAGER_H
