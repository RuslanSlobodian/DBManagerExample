#include "mainwindow.h"
#include "message.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include "sqlitedbmanager.h"

#include <QSqlTableModel>
#include <QDateTime>

MainWindow::MainWindow(DBManager* dbManager, QWidget* parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        dbManager(dbManager) {
    ui->setupUi(this);

    // Виконуємо наповнення таблиці бази даних, яка буде відображатись в TableView
    for (int i = 0; i < 4; i++) {

        int random = rand(); // Отримуємо випадкові цілі числа для вставки в базу даних
        // Створюємо і заповнюємо даними новий об'єкт класу Message для вставки його у базу даних
        Message message;
        message.setRandomNumber(random);
        message.setDate(QDate::currentDate());  // Отримуємо сьогоднішню дату для вставки в БД
        message.setTime(QTime::currentTime());  // Отримуємо поточний час для вставки в БД
        message.setMessage("Отримано повідомлення від " + QString::number(random));
        // Вставляємо дані в БД
        dbManager->inserIntoTable(message);
    }

    // Ініціалізуємо модель для представлення даних із вказанням назв стовпців
    this->setupModel(TABLE_MESSAGES,
                     QStringList() << tr("id")
                                   << tr("Дата")
                                   << tr("Година")
                                   << tr("Випадкове число")
                                   << tr("Повідомлення")
    );

    // Ініціалізуємо зовнішній вигляд таблиці з даними
    this->createUI();
}

MainWindow::~MainWindow() {
    delete ui;
    if (model)
        delete model;
}

// Метод для ініціалізації моделі представлення даних
void MainWindow::setupModel(const QString& tableName, const QStringList& headers) {
    /* Виконуємо ініціалізацію моделі представлення даних
     * з вказанням імені таблиці в базі даних, до якої
     * буде виконуватись звернення
     * */
    model = new QSqlTableModel(this, dbManager->getDB());
    model->setTable(tableName);

    // Встановлюємо назви стовпців в таблиці із сортуванням даних
    for (int i = 0, j = 0; i < model->columnCount(); i++, j++) {
        model->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
    // Встановлюємо сортування по збільшення даних по нульовому стовпцю
    model->setSort(0, Qt::AscendingOrder);
}

void MainWindow::createUI() {
    // Встановлюємо модель для TableView
    ui->tableView->setModel(model);
    // Приховуємо колонку з id таблиці БД
    ui->tableView->setColumnHidden(0, true);
    // Дозволяємо виділення рядків
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Встановлюємо режим виділення лише одного рядка в таблиці
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Встановлюємо розмір колонок по вмісту
    ui->tableView->resizeColumnsToContents();
    // Встановлюємо стратегію редагування - при подвійному кліку
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    // Розтягуємо останній стовпчик tableView на всю ширину вікна
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    // Виконуємо вибірку даних із таблиці
    model->select();
}
