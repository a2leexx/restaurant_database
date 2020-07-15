#include "connectiondialog.h"


ConnectionDialog::ConnectionDialog(const QString & p_title, QWidget * p_widget) : QDialog(p_widget, Qt::MSWindowsFixedSizeDialogHint)
{
    setWindowTitle(p_title);

    m_host_name = new QLineEdit();
    m_user_name = new QLineEdit();
    m_password = new QLineEdit();
    m_password->setEchoMode(QLineEdit::Password);
    m_port = new QLineEdit();
    m_database_name = new QLineEdit();

    QPushButton * l_ok = new QPushButton("OK");
    QPushButton * l_cancel = new QPushButton("Отмена");

    QGridLayout * l_layout = new QGridLayout();

    l_layout->addWidget(new QLabel("Адрес хоста:"), 0, 0);
    l_layout->addWidget(m_host_name, 0, 1);

    l_layout->addWidget(new QLabel("Порт:"), 1, 0);
    l_layout->addWidget(m_port, 1, 1);

    l_layout->addWidget(new QLabel("Имя базы данных:"), 2, 0);
    l_layout->addWidget(m_database_name, 2, 1);

    l_layout->addWidget(new QLabel("Имя пользователя:"), 3, 0);
    l_layout->addWidget(m_user_name, 3, 1);

    l_layout->addWidget(new QLabel("Пароль:"), 4, 0);
    l_layout->addWidget(m_password, 4, 1);

    l_layout->addWidget(l_ok, 5, 0);
    l_layout->addWidget(l_cancel, 5, 1);

    setLayout(l_layout);

    connect(l_ok, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(l_cancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

QString ConnectionDialog::hostname() const
{
    return m_host_name->text();
}

QString ConnectionDialog::databaseName() const
{
    return m_database_name->text();
}

QString ConnectionDialog::userName() const
{
    return m_user_name->text();
}

QString ConnectionDialog::password() const
{
    return m_password->text();
}


int ConnectionDialog::port()
{
    return m_port->text().toInt();
}
