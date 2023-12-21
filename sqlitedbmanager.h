#ifndef SQLITE_DB_MANAGER_H
#define SQLITE_DB_MANAGER_H

#include <QSqlDatabase>

#include "dbmanager.h"

/* Директиви імен таблиці, полів таблиці і бази даних */
#define DATABASE_HOST_NAME   "ExampleDataBase"
#define DATABASE_FILE_NAME   "DataBase.sqlite"

#define TABLE_MESSAGES                   "messages"
#define TABLE_MESSAGES_DATE              "date"
#define TABLE_MESSAGES_TIME              "time"
#define TABLE_MESSAGES_MESSAGE           "message"
#define TABLE_MESSAGES_RANDOM_NUMBER     "random_number"

// Клас, який реалізує логіку абстрактного класу DBManager для роботи із БД SQLite
class SqliteDBManager : public DBManager {

public:
    // Метод для отримання екземпляру даного класу (патерн Singleton)
    static SqliteDBManager* getInstance();

    // Метод для підключення до бази даних
    void connectToDataBase() override;

    // Метод для отримання обробника (хендлера) підключення до БД
    QSqlDatabase& getDB() override;

    // Метод для вставки записів у таблицю
    bool inserIntoTable(const Message& message) override;

    // Метод для отримання повідомлення по id
    Message findMessageById(int id) override;

private:
    // Обробник підключення до БД, через який буде виконуватись робота із БД
    QSqlDatabase db;

    static SqliteDBManager* instance;

    // Приватний конструктор
    SqliteDBManager();

    // Внутрішні методи для роботи з базою даних
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();
};

#endif // SQLITE_DB_MANAGER_H
