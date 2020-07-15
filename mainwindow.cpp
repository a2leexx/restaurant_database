#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectiondialog.h"
#include "inputaddressdialog.h"
#include "inputpositiondialog.h"
#include "inputemployeedialog.h"
#include "inputemployeelastname.h"
#include "positionsqlmodel.h"
#include <QMessageBox>
#include <QStringListModel>
#include <QSortFilterProxyModel>
#include <QInputDialog>
#include <QMenu>
#include <QDebug>

MainWindow::MainWindow(QSqlDatabase & database, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = database;

    m_res_model = new QSqlQueryModel(this);
    ui->res_view->setModel(m_res_model);
    update_restaurant_view();

    m_pos_model = new PositionSqlModel(this);
    //QSortFilterProxyModel * proxy = new QSortFilterProxyModel(this);
    //proxy->setSourceModel(m_pos_model);
    //ui->pos_view->setModel(proxy);
    ui->pos_view->setModel(m_pos_model);
    //ui->pos_view->setSortingEnabled(true);
    ui->pos_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    update_positions_view();

    m_staff_model = new QSqlQueryModel(this);
    //proxy = new QSortFilterProxyModel(this);
    //proxy->setSourceModel(m_staff_model);
    //ui->staff_view->setModel(proxy);
    ui->staff_view->setModel(m_staff_model);
    //ui->staff_view->setSortingEnabled(true);
    ui->staff_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    update_staff_view();

    m_query_model = new QSqlQueryModel(this);
    ui->query_view->setModel(m_query_model);

    ui->comboBox->setModel(new QStringListModel(QStringList({"Расходы на зарплату по каждому ресторану за месяц",
                                                             "Потенциальные расходы на премии по каждому ресторану за месяц",
                                                             "Расходы на зарплату (по всем ресторанам)",
                                                             "Расходы на премию (по всем ресторанам)",
                                                            "Ресторан с самым большим количеством сотрудников",
                                                            "Ресторан с самым маленьким количеством сотрудников",
                                                            "Количество сотрудников в каждом ресторане"})));

    connect(ui->res_add, SIGNAL(clicked(bool)), this, SLOT(add_restaurant()));
    connect(ui->res_update, SIGNAL(clicked(bool)), this, SLOT(update_restaurant_view()));
    connect(ui->res_view->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(on_selectionChanged(QItemSelection,QItemSelection)));
    connect(ui->res_remove, SIGNAL(clicked(bool)), this, SLOT(remove_restaurant()));
    connect(ui->res_change, SIGNAL(clicked(bool)), this, SLOT(change_restaurant()));
    connect(ui->res_search, SIGNAL(clicked(bool)), this, SLOT(search_restaurant()));
    connect(ui->pos_add, SIGNAL(clicked(bool)), this, SLOT(add_position()));
    connect(ui->pos_update, SIGNAL(clicked(bool)), this, SLOT(update_positions_view()));
    connect(ui->pos_view->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(on_pos_selectionChanged(QItemSelection,QItemSelection)));
    connect(ui->pos_edit, SIGNAL(clicked(bool)), this, SLOT(edit_position()));
    connect(ui->pos_remove, SIGNAL(clicked(bool)), this, SLOT(remove_position()));
    connect(ui->staff_add, SIGNAL(clicked(bool)), this, SLOT(add_employee()));
    connect(ui->staff_update, SIGNAL(clicked(bool)), this, SLOT(update_staff_view()));
    connect(ui->staff_view->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(on_staff_selectionChanged(QItemSelection,QItemSelection)));
    connect(ui->staff_remove, SIGNAL(clicked(bool)), this, SLOT(remove_employee()));
    connect(ui->staff_change, SIGNAL(clicked(bool)), this, SLOT(change_employee()));
    connect(ui->staff_search, SIGNAL(clicked(bool)), this, SLOT(search_employee()));

    connect(ui->res_view, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(comboBoxItemSelected(int)));

    comboBoxItemSelected(0);
}

void MainWindow::add_restaurant()
{
    //InputAddressDialog * dialog = new InputAddressDialog("Добавить ресторан", this);

    bool ok;

    QString address = QInputDialog::getText(this, "Добавить ресторан", "Адрес: ",
                                            QLineEdit::Normal,
                                            "", &ok);

    if (ok)
    {
        QSqlQuery query;

        query.exec("SELECT address FROM restaurants WHERE address = '" +
                   address + "';");

        if (!query.next())
        {
            query.exec("INSERT INTO restaurants (address) values('" +
                       address + "');");

            update_restaurant_view();
        }
        else QMessageBox::warning(this, "Ошибка!",
                                  "Ресторан с таким адресом уже существует!");
    }
}

void MainWindow::remove_restaurant()
{
    QModelIndexList list = ui->res_view->selectionModel()->selectedRows();
    QSqlQuery query;

    for (auto i = list.begin(); i != list.end(); i++)
    {
        QString address = m_res_model->data(*i).toString();

        if (!query.exec("DELETE FROM restaurants WHERE address = '" +
                   address + "'"))
            QMessageBox::warning(this, "Ошибка", "Не удалось удалить запись про ресторан по адресу \"" +
                                 address + "\"");

    }

    update_restaurant_view();
}

void MainWindow::change_restaurant()
{
    QModelIndexList list = ui->res_view->selectionModel()->selectedRows();
    QSqlQuery query;
    QModelIndex index = list.first();

    //InputAddressDialog * dialog = new InputAddressDialog("Изменить адрес ресторана", this);

    bool ok;

    QString address = QInputDialog::getText(this, "Изменить адрес ресторана", "Адрес: ",
                                            QLineEdit::Normal,
                                            m_res_model->data(index).toString(), &ok);

    if (ok)
    {
        QSqlQuery query;

        query.exec("SELECT count(Address) FROM restaurants WHERE address = '" +
                   address + "';");
        query.next();

        if (query.value(0).toInt() == 0)
        {
            query.exec("UPDATE restaurants SET address = '" +
                       address + "' WHERE address = '" +
                       m_res_model->data(index).toString() + "'");

            update_restaurant_view();
        }
        else {
            QMessageBox::warning(this, "Ошибка!",
                                  "Ресторан с таким адресом уже существует!");
        }
    }
}

void MainWindow::update_restaurant_view()
{
    if (m_res_search.length() == 0)
        m_res_model->setQuery("SELECT address FROM restaurants ORDER BY Address");
    else {
        m_res_model->setQuery("SELECT address FROM restaurants WHERE Lower(Address) LIKE lower('%" +
                              m_res_search + "%') ORDER BY Address");
    }

    m_res_model->setHeaderData(0, Qt::Horizontal, "Адрес");
}

void MainWindow::on_selectionChanged(const QItemSelection &, const QItemSelection &)
{
    QModelIndexList list = ui->res_view->selectionModel()->selectedRows();

    ui->res_remove->setEnabled(!list.empty());
    ui->res_change->setEnabled(list.count() == 1);
}

void MainWindow::search_restaurant()
{
    if (m_res_search == "")
    {
        InputAddressDialog * dialog = new InputAddressDialog("Найти ресторан по адресу", this);

        if (dialog->exec() == QDialog::Accepted)
        {
            m_res_search = dialog->address();
        }
        else return;

        ui->res_search->setText("Сброс");
        update_restaurant_view();
    }
    else
    {
        ui->res_search->setText("Поиск по адресу");
        m_res_search = "";
        update_restaurant_view();
    }
}

void MainWindow::add_position()
{
    InputPositionDialog * dialog = new InputPositionDialog("Добавить должность", this);

    if (dialog->exec() == QDialog::Accepted)
    {
        QSqlQuery query;

        query.exec("SELECT count(position_id) FROM positions WHERE Title = '" +
                   dialog->positionTitle() + "';");
        query.next();

        if (query.value(0).toInt() == 0)
        {
            bool result = query.exec(QString("INSERT INTO positions (title, salary, max_award, only_one) VALUES ('%1', %2, %3, %4);")
                                .arg(dialog->positionTitle()).arg(dialog->positionSalary()).arg(dialog->positionMaxAward()).
                                    arg(dialog->onlyOneWorkplace() ? "true" : "false"));

            if (result)
            {
                QMessageBox msgBox;

                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setText(query.lastError().driverText());
                msgBox.setDefaultButton(QMessageBox::Ok);
                msgBox.show();
            }

            update_positions_view();
        }
        else QMessageBox::warning(this, "Ошибка!",
                                  "Такая должность уже существует!");
    }

    delete dialog;
}

void MainWindow::update_positions_view()
{
    m_pos_model->setQuery("SELECT title, salary, max_award, only_one FROM positions");
    m_pos_model->setHeaderData(0, Qt::Horizontal, "Наименование");
    m_pos_model->setHeaderData(1, Qt::Horizontal, "Зарплата");
    m_pos_model->setHeaderData(2, Qt::Horizontal, "Максимальный размер премии");
    m_pos_model->setHeaderData(3, Qt::Horizontal, "Запрещено создавать > 1 шт.ед. на ресторан");

    ui->pos_view->resizeColumnsToContents();
}

void MainWindow::on_pos_selectionChanged(const QItemSelection &, const QItemSelection &)
{
    QModelIndexList list = ui->pos_view->selectionModel()->selectedRows();

    ui->pos_remove->setEnabled(!list.empty());
    ui->pos_edit->setEnabled(list.count() == 1);
}

void MainWindow::remove_position()
{
    QModelIndexList list = ui->pos_view->selectionModel()->selectedRows();
    QSqlQuery query;

    for (auto i = list.begin(); i != list.end(); i++)
    {
        QString title = m_pos_model->data(*i).toString();

        if (!query.exec("DELETE FROM positions WHERE title = '" +
                   title + "'"))
            QMessageBox::warning(this, "Ошибка", "Не удалось удалить запись о должности \"" +
                                 title + "\"");

    }

    update_positions_view();
}

void MainWindow::edit_position()
{
    QModelIndexList list = ui->pos_view->selectionModel()->selectedRows();
    QSqlQuery query;
    QModelIndex index = list.first();

    InputPositionDialog * dialog = new InputPositionDialog("Изменить запись", this);

    QString old_title = m_pos_model->data(index).toString();
    QString old_salary = m_pos_model->data(m_pos_model->index(index.row(), 1)).toString();
    QString old_maxaward = m_pos_model->data(m_pos_model->index(index.row(), 2)).toString();
    bool old_onlyOne = m_pos_model->data(m_pos_model->index(index.row(), 3)).toString() == "Да";

    dialog->setPositionTitle(old_title);
    dialog->setPositionSalary(old_salary.toDouble());
    dialog->setPositionMaxAward(old_maxaward.toDouble());
    dialog->setOnlyOneWorkplace(old_onlyOne);

    if (dialog->exec() == QDialog::Accepted)
    {
        QSqlQuery query;

        query.exec("SELECT title FROM positions WHERE Title = '" + dialog->positionTitle() +
                    + "';");
        query.next();

        if (query.value(0).toInt() == 0 || old_title == dialog->positionTitle())
        {
            query.exec(QString("WITH t1 as (SELECT count(employee_id) FROM staff WHERE "
                               "position_id = (SELECT position_id FROM positions WHERE title = '%1') GROUP BY restaurant)"
                               "SELECT max(count) FROM t1;").
                       arg(old_title));
            query.next();

            if (query.value(0).toInt() <= 1 || !dialog->onlyOneWorkplace()) {
                qDebug() << query.value(0).toInt();
                query.exec(QString("UPDATE positions SET  title = '%1', salary = %2, max_award = %3, only_one = %5 WHERE title = '%4'")
                           .arg(dialog->positionTitle()).arg(dialog->positionSalary()).arg(dialog->positionMaxAward())
                           .arg(old_title).arg(dialog->onlyOneWorkplace() ? "true" : "false"));
                update_positions_view();
            }
            else QMessageBox::warning(this, "Ошибка!", "Существуют рестораны, где на этой должности работают несколько человек!");
        }
        else QMessageBox::warning(this, "Ошибка!",
                                  "Такая должность уже существует!");
    }
}

void MainWindow::add_employee()
{
    InputEmployeeDialog * dialog = new InputEmployeeDialog("Добавить сотрудника", this);

    if (dialog->exec() == QDialog::Accepted)
    {
        QSqlQuery query;

        query.exec("SELECT only_one FROM positions WHERE title = '" + dialog->position() + "';");
        query.next();

        bool isOne = query.value(0).toString() == "true";

        query.exec(QString("SELECT count(employee_id) FROM staff WHERE restaurant_id = (SELECT restaurant_id FROM restaurants WHERE address = '%1')"
                           "AND position_id = (SELECT position_id FROM positions WHERE title = '%2')").arg(dialog->address()).arg(dialog->position()));
        query.next();

        if (query.value(0).toInt() == 0 || !isOne)
        {

            bool result = query.exec(QString("INSERT INTO staff (first_name, last_name, restaurant_id, position_id)"
                               " VALUES ('%1', '%2', (SELECT restaurant_id FROM restaurants WHERE address = '%3'),"
                               "(SELECT position_id From positions WHERE title = '%4'));")
                        .arg(dialog->firstName()).arg(dialog->lastName()).arg(dialog->address())
                        .arg(dialog->position()));

            if (!result)
            {
                const QString driver_text = query.lastError().driverText();
                const QString database_text = query.lastError().databaseText();

                qDebug() << driver_text;
                qDebug() << database_text;
            }

            update_staff_view();
        }
        else QMessageBox::warning(this, "Ошибка!", "Запрещено создавать > 1 шт. единице по этой должности на ресторан!");
    }

    delete dialog;
}

void MainWindow::update_staff_view()
{
    if (m_staff_search.length() == 0)
        m_staff_model->setQuery("SELECT staff.employee_id, last_name, first_name, title, address FROM staff, "
                              "restaurants, positions WHERE "
                              "staff.position_id = positions.position_id AND "
                              "staff.restaurant_id = restaurants.restaurant_id;");
    else {
        m_staff_model->setQuery("SELECT staff.employee_id, last_name, first_name, title, address FROM staff, "
                              "restaurants, positions WHERE "
                              "staff.position_id = positions.position_id AND "
                              "staff.restaurant_id = restaurants.restaurant_id AND "
                              "lower(staff.last_name) LIKE lower('%" + m_staff_search + "%');");
    }

    m_staff_model->setHeaderData(0, Qt::Horizontal, "ID сотрудника");
    m_staff_model->setHeaderData(1, Qt::Horizontal, "Фамилия");
    m_staff_model->setHeaderData(2, Qt::Horizontal, "Имя");
    m_staff_model->setHeaderData(3, Qt::Horizontal, "Должность");
    m_staff_model->setHeaderData(4, Qt::Horizontal, "Ресторан");

    ui->staff_view->resizeColumnsToContents();
}

void MainWindow::change_employee()
{
    QModelIndexList list = ui->staff_view->selectionModel()->selectedRows();
    QSqlQuery query;
    QModelIndex index = list.first();

    InputEmployeeDialog * dialog = new InputEmployeeDialog("Редактирование записи о сотруднике", this);

    int id = m_staff_model->data(index).toInt();
    QString old_lastName = m_staff_model->data(m_staff_model->index(index.row(), 1)).toString();
    QString old_firstName = m_staff_model->data(m_staff_model->index(index.row(), 2)).toString();
    QString old_position = m_staff_model->data(m_staff_model->index(index.row(), 3)).toString();
    QString old_address = m_staff_model->data(m_staff_model->index(index.row(), 4)).toString();

    dialog->setPosition(old_position);
    dialog->setFirstName(old_firstName);
    dialog->setAddress(old_address);
    dialog->setLastName(old_lastName);

    if (dialog->exec() == QDialog::Accepted)
    {
        QSqlQuery query;

        query.exec("SELECT only_one FROM positions WHERE title = '" + dialog->position() + "';");
        query.next();

        bool isOne = query.value(0).toString() == "true";

        query.exec(QString("SELECT count(employee_id) from staff WHERE "
                           "restaurant_id = (SELECT restaurant_id FROM restaurants WHERE address = '%1')"
                           "AND position_id = (SELECT position_id FROM positions WHERE title = '%2')").arg(dialog->address()).arg(dialog->position()));
        query.next();

        if (query.value(0).toInt() == 0 || !isOne || dialog->position() == old_position)
        {

            query.exec(QString("UPDATE staff SET first_name = '%1', last_name = '%2', "
                               "restaurant_id = (SELECT restaurant_id FROM restaurants WHERE address = '%3'),"
                               "position_id = (SELECT position_id FROM positions WHERE title = '%4') WHERE employee_id = %5")
                        .arg(dialog->firstName()).arg(dialog->lastName()).arg(dialog->address())
                        .arg(dialog->position()).arg(id));
        }
        else QMessageBox::warning(this, "Ошибка!", "Запрещено создавать > 1 шт. единице по этой должности на ресторан!");

        update_staff_view();
    }

    delete dialog;
}

void MainWindow::remove_employee()
{
    QModelIndexList list = ui->staff_view->selectionModel()->selectedRows();
    QSqlQuery query;

    for (auto i = list.begin(); i != list.end(); i++)
    {
        int id = m_staff_model->data(*i).toInt();

        query.exec(QString("DELETE FROM staff WHERE employee_id = %1").arg(id));
        qDebug() << query.lastError();
    }

    update_staff_view();
}

void MainWindow::search_employee()
{
    if (m_staff_search == "")
    {
        InputEmployeeLastName * dialog = new InputEmployeeLastName("Найти сотрудника по фамилии", this);

        if (dialog->exec() == QDialog::Accepted)
        {
            m_staff_search = dialog->lastName();
        }
        else return;

        ui->staff_search->setText("Сброс");
        update_staff_view();
    }
    else
    {
        ui->staff_search->setText("Поиск по фамилии");
        m_staff_search = "";
        update_staff_view();
    }
}

void MainWindow::on_staff_selectionChanged(const QItemSelection &, const QItemSelection &)
{
    QModelIndexList list = ui->staff_view->selectionModel()->selectedRows();

    ui->staff_remove->setEnabled(!list.empty());
    ui->staff_change->setEnabled(list.count() == 1);
}

void MainWindow::set_query(const QString & query)
{
    m_query_model->setQuery(query);
}

void MainWindow::comboBoxItemSelected(int index)
{
    if (index == 0)
    {
        m_query_model->setQuery("SELECT address, sum(salary) FROM (positions JOIN staff USING(position_id)) "
                                "JOIN restaurants USING(restaurant_id) GROUP BY address");
        m_query_model->setHeaderData(0, Qt::Horizontal, "Адрес");
        m_query_model->setHeaderData(1, Qt::Horizontal, "Расходы");
    }
    else if (index == 1)
    {
        m_query_model->setQuery("SELECT address, sum(max_award) FROM (positions JOIN staff USING(position_id)) "
                                "JOIN restaurants USING(restaurant_id) GROUP BY address");
        m_query_model->setHeaderData(0, Qt::Horizontal, "Адрес");
        m_query_model->setHeaderData(1, Qt::Horizontal, "Расходы");
    }
    else if (index == 2)
    {
        m_query_model->setQuery("SELECT sum(salary) FROM positions JOIN staff USING(position_id)");
        qDebug() << m_query_model->lastError();
         m_query_model->setHeaderData(0, Qt::Horizontal, "Расходы на зарплаты.");
    }
    else if (index == 3)
    {
        m_query_model->setQuery("SELECT sum(max_award) FROM positions JOIN staff USING(position_id)");
        m_query_model->setHeaderData(0, Qt::Horizontal, "Потенциальные расходы на премии");
    }
    else if (index == 4)
    {
        m_query_model->setQuery("WITH t1 AS (SELECT restaurants.restaurant_id, count(staff.employee_id) FROM "
                                "staff JOIN restaurants USING(restaurant_id) GROUP BY restaurants.restaurant_id)"
                                "SELECT address, t1.count from restaurants JOIN t1 USING(restaurant_id)"
                                "WHERE t1.count = (SELECT max(count) FROM t1)");
        m_query_model->setHeaderData(0, Qt::Horizontal, "Адрес");
        m_query_model->setHeaderData(1, Qt::Horizontal, "Кол-во сотрудников");
    }
    else if (index == 5)
    {
        m_query_model->setQuery("WITH t1 AS (SELECT restaurants.restaurant_id, count(staff.employee_id)"
                                "FROM staff JOIN restaurants USING(restaurant_id) GROUP BY restaurants.restaurant_id)"
                                "SELECT address, t1.count FROM restaurants JOIN t1 USING(restaurant_id)"
                                "WHERE t1.count = (SELECT min(count) FROM t1)");
        m_query_model->setHeaderData(0, Qt::Horizontal, "Адрес");
        m_query_model->setHeaderData(1, Qt::Horizontal, "Кол-во сотрудников");
    }
    else if (index == 6)
    {
        m_query_model->setQuery("SELECT restaurants.address, count(staff.employee_id) FROM "
                                "restaurants JOIN staff USING(restaurant_id) GROUP BY restaurants.address");
        m_query_model->setHeaderData(0, Qt::Horizontal, "Адрес");
        m_query_model->setHeaderData(1, Qt::Horizontal, "Кол-во сотрудников");
    }

    ui->query_view->resizeColumnsToContents();
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    QPoint l_globalPos = ui->res_view->mapToGlobal(pos);
    QModelIndexList l_list = ui->res_view->selectionModel()->selectedRows();

    QMenu l_menu;

    if (l_list.count() == 1) l_menu.addAction("Изменить", this, SLOT(change_restaurant()));
    l_menu.addAction("Удалить", this, SLOT(remove_restaurant()));

    l_menu.exec(l_globalPos);
}

MainWindow::~MainWindow()
{
    delete ui;
}
