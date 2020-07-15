#include "inputemployeedialog.h"

InputEmployeeDialog::InputEmployeeDialog(const QString & p_title, QWidget * p_widget) : QDialog(p_widget, Qt::MSWindowsFixedSizeDialogHint)
{
    setWindowTitle(p_title);

    QLabel * l_label1 = new QLabel("Имя: ");
    QLabel * l_label2 = new QLabel("Фамилия: ");
    QLabel * l_label3 = new QLabel("Ресторан:");
    QLabel * l_label4 = new QLabel("Должность:");

    m_position = new QComboBox();
    m_address = new QComboBox();

    QSqlQueryModel * positions = new QSqlQueryModel();
    positions->setQuery("Select Title From positions;");
    m_position->setModel(positions);

    QSqlQueryModel * address = new QSqlQueryModel();
    address->setQuery("Select Address from restaurants;");
    m_address->setModel(address);

    m_firstName = new QLineEdit();
    m_lastName = new QLineEdit();

    QGridLayout * layout = new QGridLayout();

    QPushButton * l_button1 = new QPushButton("OK");
    QPushButton * l_button2 = new QPushButton("Cancel");

    connect(l_button1, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(l_button2, SIGNAL(clicked(bool)), this, SLOT(reject()));

    layout->addWidget(l_label1, 0, 0);
    layout->addWidget(l_label2, 1, 0);
    layout->addWidget(l_label3, 2, 0);
    layout->addWidget(l_label4, 3, 0);
    layout->addWidget(m_firstName, 0, 1);
    layout->addWidget(m_lastName, 1, 1);
    layout->addWidget(m_address, 2, 1);
    layout->addWidget(m_position, 3, 1);
    layout->addWidget(l_button1, 4, 0);
    layout->addWidget(l_button2, 4, 1);

    setLayout(layout);
}

void InputEmployeeDialog::setPosition(const QString & p_position)
{
    int index = m_position->findText(p_position);
    if (index != -1)
        m_position->setCurrentIndex(index);
}

void InputEmployeeDialog::setAddress(const QString & p_address)
{
    int index = m_address->findText(p_address);
    if (index != -1)
        m_address->setCurrentIndex(index);
}

void InputEmployeeDialog::setFirstName(const QString & p_firstName)
{
    m_firstName->setText(p_firstName);
}

void InputEmployeeDialog::setLastName(const QString & p_lastName)
{
    m_lastName->setText(p_lastName);
}

QString InputEmployeeDialog::position()
{
    return m_position->currentText();
}

QString InputEmployeeDialog::address()
{
    return m_address->currentText();
}

QString InputEmployeeDialog::firstName()
{
    return m_firstName->text();
}

QString InputEmployeeDialog::lastName()
{
    return m_lastName->text();
}
