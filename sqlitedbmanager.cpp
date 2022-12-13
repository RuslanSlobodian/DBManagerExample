#include "sqlitedbmanager.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>

SqliteDBManager* SqliteDBManager::instance = nullptr;

SqliteDBManager::SqliteDBManager(){
}

// Метод для отримання екземпляру даного класу (патерн Singleton)
SqliteDBManager* SqliteDBManager::getInstance()
{
    if(instance == nullptr){
        instance = new SqliteDBManager();
    }
    return instance;
}

// Метод для підключення до бази даних
void SqliteDBManager::connectToDataBase()
{
    /* Перед підключенням до бази даних виконуємо перевірку на її існування.
     * В залежності від результату виконуємо відкриття бази даних або її відновлення
     * */
    if(QFile(DATABASE_NAME).exists()){
        this->openDataBase();
    } else {
        this->restoreDataBase();
    }
}

// Метод для отримання обробника підключення до БД
QSqlDatabase SqliteDBManager::getDB()
{
    return db;
}

// Метод відновлення бази даних
bool SqliteDBManager::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTables()){
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
bool SqliteDBManager::openDataBase()
{
    /* База даних відкривається по вказаному шляху
     * і імені бази даних, якщо вона існує
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        return true;
    } else
        return false;
}

// Метод закриття бази даних
void SqliteDBManager::closeDataBase()
{
    db.close();
}

// Метод для створення таблиці в базі даних
bool SqliteDBManager::createTables()
{
    /* В даному випадку використовується фурмування сирого SQL-запиту
     * з наступним його виконанням.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE_EXAMPLE " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE_EXAMPLE_DATE      " DATE            NOT NULL,"
                    TABLE_EXAMPLE_TIME      " TIME            NOT NULL,"
                    TABLE_EXAMPLE_RANDOM    " INTEGER         NOT NULL,"
                    TABLE_EXAMPLE_MESSAGE   " VARCHAR(255)    NOT NULL"
                    " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE_EXAMPLE;
        qDebug() << query.lastError().text();
        return false;
    } else
        return true;
}

// Метод для вставки записів у базу даних
bool SqliteDBManager::inserIntoTable(const QString tableName, const QVariantList &data)
{
    //Запит SQL формується із QVariantList, в який передаються данні для вставки в таблицю.
    QSqlQuery query;
    /*
     * Спочатку SQL-запит формується з ключами, які потім зв'язуються методом bindValue
     * для підставки даних із QVariantList
     * */
    if (tableName == TABLE_EXAMPLE){
        qDebug() << tableName;
        query.prepare("INSERT INTO " TABLE_EXAMPLE " ( " TABLE_EXAMPLE_DATE ", "
                      TABLE_EXAMPLE_TIME ", "
                      TABLE_EXAMPLE_RANDOM ", "
                      TABLE_EXAMPLE_MESSAGE " ) "
                                            "VALUES (:Date, :Time, :Random, :Message )");
        query.bindValue(":Date",        data[0].toDate());
        query.bindValue(":Time",        data[1].toTime());
        query.bindValue(":Random",      data[2].toInt());
        query.bindValue(":Message",     data[3].toString());
    }

    // Після чого виконується запит методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << tableName;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();

        return false;
    } else
        return true;
}
