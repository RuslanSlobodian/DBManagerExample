#include "mysqldbmanager.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>

MySqlDBManager* MySqlDBManager::instance = nullptr;

MySqlDBManager::MySqlDBManager() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(DATABASE_HOST_NAME);
    db.setPort(DATABASE_PORT);
    db.setDatabaseName(DATABASE_NAME);
    db.setUserName(DATABASE_USER_NAME);
    db.setPassword(DATABASE_PASSWORD);
}

// Метод для отримання екземпляру даного класу (патерн Singleton)
MySqlDBManager* MySqlDBManager::getInstance() {
    if (instance == nullptr) {
        instance = new MySqlDBManager();
    }
    return instance;
}

// Метод для підключення до бази даних
void MySqlDBManager::connectToDataBase() {
    // Якщо підключення вже відкрите, тоді виходимо
    if (db.isOpen())
        return;
    if (!db.open()) {
        qDebug() << "Не вдалось відкрити базу даних";
    }
    this->createTable();
}

// Метод для отримання обробника підключення до БД
QSqlDatabase& MySqlDBManager::getDB() {
    return db;
}

// Метод закриття підключення до бази даних
void MySqlDBManager::closeDataBase() {
    if (db.isOpen()) {
        db.close();
    }
}

// Метод для створення таблиці в базі даних
bool MySqlDBManager::createTable() {
    /* В даному випадку використовується фурмування сирого SQL-запиту
     * з наступним його виконанням.
     * */
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS " TABLE_MESSAGES " ("
                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                    TABLE_MESSAGES_DATE             " DATE          NOT NULL, "
                    TABLE_MESSAGES_TIME             " TIME          NOT NULL, "
                    TABLE_MESSAGES_RANDOM_NUMBER    " INT           NOT NULL, "
                    TABLE_MESSAGES_MESSAGE          " VARCHAR(255)  NOT NULL"
                    " )"
    )) {
        qDebug() << "DataBase: error of create " << TABLE_MESSAGES;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return false;
    } else
        return true;
}

// Метод для вставки записів у таблицю messages
bool MySqlDBManager::inserIntoTable(const Message& message) {
    // SQL-запит формується із об'єкта класу Message
    QSqlQuery query;
    /*
     * Спочатку SQL-запит формується з ключами, які потім зв'язуються методом bindValue
     * для підставки даних із об'єкта класу Message
     * */
    query.prepare("INSERT INTO " TABLE_MESSAGES " ( " TABLE_MESSAGES_DATE ", "
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
Message MySqlDBManager::findMessageById(int id) {
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

MySqlDBManager::~MySqlDBManager() {
    this->closeDataBase();
}
