#include "mainwindow.h"
#include "sqlitedbmanager.h"
#include "mysqldbmanager.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);

    // Отримуємо вказівник на об'єкт класу SqliteDBManager для роботи із локальною СКБД SQLite,
    // який використовуємо через інтерфейс (абстрактний клас) DBManager
    // DBManager* dbManager = SqliteDBManager::getInstance();

    // Отримуємо вказівник на об'єкт класу SqliteDBManager для роботи із СКБД MySQL
    DBManager* dbManager = MySqlDBManager::getInstance();

    // Підключаємось до бази даних
    dbManager->connectToDataBase();

    // Створюємо головне вікно передаючи в нього вказівник на об'єкт для взаємодії з базою даних
    MainWindow window(dbManager);
    window.show();

    return application.exec();
}
