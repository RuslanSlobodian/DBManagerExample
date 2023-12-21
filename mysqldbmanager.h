#ifndef MYSQL_DB_MANAGER_H
#define MYSQL_DB_MANAGER_H

#include "dbmanager.h"

/* Директиви імен таблиці, полів таблиці і бази даних */
#define DATABASE_HOST_NAME  "127.0.0.1"
#define DATABASE_PORT       3306
#define DATABASE_NAME       "db_manager_example"
#define DATABASE_USER_NAME  "root"
#define DATABASE_PASSWORD   ""

#define TABLE_MESSAGES                   "messages"
#define TABLE_MESSAGES_DATE              "date"
#define TABLE_MESSAGES_TIME              "time"
#define TABLE_MESSAGES_MESSAGE           "message"
#define TABLE_MESSAGES_RANDOM_NUMBER     "random_number"

// Клас, який реалізує логіку абстрактного класу DBManager для роботи із БД MySQL
class MySqlDBManager : public DBManager {

public:
    // Метод для отримання екземпляру даного класу (патерн Singleton)
    static MySqlDBManager* getInstance();

    // Метод для підключення до бази даних
    void connectToDataBase() override;

    // Метод для отримання обробника (хендлера) підключення до БД
    QSqlDatabase& getDB() override;

    // Метод для вставки записів у таблицю
    bool inserIntoTable(const Message& message) override;

    // Метод для отримання повідомлення по id
    Message findMessageById(int id) override;

    ~MySqlDBManager();

private:
    // Обробник підключення до БД, через який буде виконуватись робота із БД
    QSqlDatabase db;

    static MySqlDBManager* instance;

    // Приватний конструктор
    MySqlDBManager();

    // Внутрішні методи для роботи з базою даних
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();
};

#endif // MYSQL_DB_MANAGER_H
