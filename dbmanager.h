#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QVariantList>

// Абстрактний клас (інтерфейс) для роботи з базою даних
class DBManager {
public:
    // Суто віртуальний метод для підключення до бази даних
    virtual void connectToDataBase() = 0;

    // Суто віртуальний метод для отримання обробника (хендлера) підключення до БД
    virtual QSqlDatabase getDB() = 0;

    // Суто віртуальний метод для вставки записів у таблицю
    virtual bool inserIntoTable(const QString tableName, const QVariantList& data) = 0;
};

#endif // DBMANAGER_H
