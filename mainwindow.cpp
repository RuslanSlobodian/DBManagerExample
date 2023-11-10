#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include "sqlitedbmanager.h"

#include <QSqlTableModel>
#include <QDateTime>

MainWindow::MainWindow(DBManager* dbManager, QWidget* parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        db(dbManager) {
    ui->setupUi(this);

    /* Спочатку створюється об'єкт, який буде використовуватись для роботи з динними БД
     * та ініціалізації підключення до бази даних
     * */
//    db = SqliteDBManager::getInstance();  //SqliteDBManager::getInstance();
    db->connectToDataBase();

    /* Після цього виконуємо наповнення таблиці бази даних,
     * який буде відображатись в TableView
     * */
    for (int i = 0; i < 4; i++) {
        QVariantList data;
        int random = rand(); // Отримуємо випадкові цілі числа для вставки в базу даних
        data.append(QDate::currentDate()); // Отримуємо сьогоднішню дату для вставки в БД
        data.append(QTime::currentTime()); // Отримуємо поточний час для вставки в БД
        // Поміщаємо отримане випадкове число в QVariantList
        data.append(random);
        // Поміщаємо повідомлення в QVariantList
        data.append("Отримано повідомлення від " + QString::number(random));
        // Вставляємо дані в БД
        db->inserIntoTable(TABLE_EXAMPLE, data);
    }

    /* Ініціалізуємо модель для представлення даних
     * із вказанням назв стовпців
     * */
    this->setupModel(TABLE_EXAMPLE,
                     QStringList() << tr("id")
                                   << tr("Дата")
                                   << tr("Година")
                                   << tr("Випадкове число")
                                   << tr("Повідомлення")
    );

    /* Ініціалізуємо зовнішній вигляд таблиці з даними
     * */
    this->createUI();
}

MainWindow::~MainWindow() {
    delete ui;
    if (model)
        delete model;
}


/* Метод для ініціалізації моделі представлення даних
 * */
void MainWindow::setupModel(const QString& tableName, const QStringList& headers) {
    /* Виконуємо ініціалізацію моделі представлення даних
     * з вказанням імені таблиці в базі даних, до якої
     * буде виконуватись звернення
     * */
    model = new QSqlTableModel(this, db->getDB());
    model->setTable(tableName);

    /* Встановлюємо назви стовпців в таблиці із сортуванням даних
     * */
    for (int i = 0, j = 0; i < model->columnCount(); i++, j++) {
        model->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
    // Встановлюємо сортування по збільшення даних по нульовому стовпцю
    model->setSort(0, Qt::AscendingOrder);
}


void MainWindow::createUI() {
    ui->tableView->setModel(model);     // Встановлюємо модель на TableView
    ui->tableView->setColumnHidden(0, true);    // Приховуємо колонку з  id записів таблиці БД
    // Дозволяємо виділення рядків
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Встановлюємо режим виділення лише одного рядка в таблиці
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Встановлюємо розмір колонок по вмісту
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    model->select(); // Виконуємо вибірку даних із таблиці
}
