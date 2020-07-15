#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString m_res_search;
    QString m_staff_search;
    QSqlQueryModel * m_res_model;
    QSqlQueryModel * m_pos_model;
    QSqlQueryModel * m_staff_model;
    QSqlQueryModel * m_query_model;
    QSqlDatabase db;

    void set_query(const QString & query);

public:
    explicit MainWindow(QSqlDatabase & database, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void add_restaurant();
    void remove_restaurant();
    void change_restaurant();
    void search_restaurant();
    void update_restaurant_view();
    void on_selectionChanged(const QItemSelection &, const QItemSelection &);

    void add_position();
    void remove_position();
    void edit_position();
    void update_positions_view();

    void add_employee();
    void change_employee();
    void remove_employee();
    void search_employee();

    void on_pos_selectionChanged(const QItemSelection &, const QItemSelection &);
    void on_staff_selectionChanged(const QItemSelection &, const QItemSelection &);
    void update_staff_view();
    void showContextMenu(const QPoint & p_pos);

    void comboBoxItemSelected(int index);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
