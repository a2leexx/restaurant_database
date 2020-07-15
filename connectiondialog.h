#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>


class ConnectionDialog : public QDialog
{
    QLineEdit * m_host_name;
    QLineEdit * m_database_name;
    QLineEdit * m_user_name;
    QLineEdit * m_password;
    QLineEdit * m_port;
public:
    ConnectionDialog(const QString & p_title, QWidget * p_widget = 0);
    QString hostname() const;
    QString databaseName() const;
    QString userName() const;
    QString password() const;
    int port();
};

#endif // CONNECTIONDIALOG_H
