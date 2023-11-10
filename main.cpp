#include "mainwindow.h"
#include <QApplication>
#include "sqlitedbmanager.h"

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);

    /*  Отримуємо вказівник на об'єкт класу SqliteDBManager для роботи із локальною БД SQLite,
     *  який використовуємо через інтерфейс (абстрактний клас) DBManager
     * */
    DBManager* dbManager = SqliteDBManager::getInstance();
    // Підключаємось до бази даних
    dbManager->connectToDataBase();

    // Створюємо головне вікно передаючи в нього вказівник на об'єкт для взаємодії з базою даних
    MainWindow window(dbManager);
    window.show();

    return application.exec();
}
