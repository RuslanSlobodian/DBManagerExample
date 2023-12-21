#include "sqlitedbmanager.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>

SqliteDBManager* SqliteDBManager::instance = nullptr;

SqliteDBManager::SqliteDBManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOST_NAME);
    db.setDatabaseName(DATABASE_FILE_NAME);
}

// Метод для отримання екземпляру даного класу (патерн Singleton)
SqliteDBManager* SqliteDBManager::getInstance() {
    if (instance == nullptr) {
        instance = new SqliteDBManager();
    }
    return instance;
}

// Метод для підключення до бази даних
void SqliteDBManager::connectToDataBase() {
    /* Перед підключенням до бази даних виконуємо перевірку на її існування.
     * В залежності від результату виконуємо відкриття бази даних або її відновлення
     * */
    if (QFile(DATABASE_FILE_NAME).exists()) {
        this->openDataBase();
    } else {
        this->restoreDataBase();
    }
}

// Метод для отримання обробника підключення до БД
QSqlDatabase& SqliteDBManager::getDB() {
    return db;
}

// Метод відновлення бази даних
bool SqliteDBManager::restoreDataBase() {
    if (this->openDataBase()) {
        if (!this->createTable()) {
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не вдалось відновити базу даних";
        return false;
    }
}

// Метод для відкриття бази даних
bool SqliteDBManager::openDataBase() {
    /* База даних відкривається по вказаному шляху
     * та імені бази даних, якщо вона існує
     * */
    if (db.open()) {
        return true;
    } else
        return false;
}

// Метод закриття бази даних
void SqliteDBManager::closeDataBase() {
    db.close();
}

// Метод для створення таблиці в базі даних
bool SqliteDBManager::createTable() {
    /* В даному випадку використовується фурмування сирого SQL-запиту
     * з наступним його виконанням.
     * */
    QSqlQuery query;
    if (!query.exec("CREATE TABLE " TABLE_MESSAGES " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE_MESSAGES_DATE             " DATE            NOT NULL,"
                    TABLE_MESSAGES_TIME             " TIME            NOT NULL,"
                    TABLE_MESSAGES_RANDOM_NUMBER    " INTEGER         NOT NULL,"
                    TABLE_MESSAGES_MESSAGE          " VARCHAR(255)    NOT NULL"
                    " )"
    )) {
        qDebug() << "DataBase: error of create " << TABLE_MESSAGES;
        qDebug() << query.lastError().text();
        return false;
    } else
        return true;
}

// Метод для вставки записів у таблицю messages
bool SqliteDBManager::inserIntoTable(const Message& message) {
    // SQL-запит формується із об'єкта класу Message
    QSqlQuery query;
    /*
     * Спочатку SQL-запит формується з ключами, які потім зв'язуються методом bindValue
     * для підставки даних із об'єкта класу Message
     * */
    query.prepare("INSERT INTO " TABLE_MESSAGES " ( "
                  TABLE_MESSAGES_DATE ", "
                  TABLE_MESSAGES_TIME ", "
                  TABLE_MESSAGES_RANDOM_NUMBER ", "
                  TABLE_MESSAGES_MESSAGE " ) "
                  "VALUES (:Date, :Time, :RandomNumber, :Message )");
    query.bindValue(":Date", message.getDate());
    query.bindValue(":Time", message.getTime());
    query.bindValue(":RandomNumber", message.getRandomNumber());
    query.bindValue(":Message", message.getMessage());

    // Після чого виконується запит методом exec()
    if (!query.exec()) {
        qDebug() << "error insert into " << TABLE_MESSAGES;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();

        return false;
    } else
        return true;
}

// Метод для отримання повідомлення по id
Message SqliteDBManager::findMessageById(int id) {
    QSqlQuery query(this->db);
    Message message;
    // Спочатку формується SQL-запит з ключем (заповнювачем) 'id', який потім замінюється значенням методом bindValue
    query.prepare("SELECT * FROM " TABLE_MESSAGES " WHERE id=:id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        message.setId(query.value("id").toInt());
        message.setDate(query.value(TABLE_MESSAGES_DATE).toDate());
        message.setTime(query.value(TABLE_MESSAGES_TIME).toTime());
        message.setMessage(query.value(TABLE_MESSAGES_MESSAGE).toString());
        message.setRandomNumber(query.value(TABLE_MESSAGES_RANDOM_NUMBER).toInt());
    }
    return message;
}
