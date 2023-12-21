#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSqlTableModel;

class DBManager;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(DBManager* dbManager, QWidget* parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow* ui;

    /* В проекті використовуються об'єкти для взаємодії з інформацією в базі даних
     * і моделлю представлення таблиці бази даних
     * */
    DBManager* dbManager;
    QSqlTableModel* model;

private:
    // Також присутні два методи, які формують модель і зовнішній вид TableView
    void setupModel(const QString& tableName, const QStringList& headers);
    void createUI();
};

#endif // MAINWINDOW_H
