#include "inputemployeelastname.h"

InputEmployeeLastName::InputEmployeeLastName(const QString & p_title, QWidget * p_widget) : QDialog(p_widget, Qt::MSWindowsFixedSizeDialogHint)
{
    setWindowTitle(p_title);

    m_lineEdit = new QLineEdit();

    QLabel * l_label = new QLabel("Введите фамилию:");

    QPushButton * l_ok = new QPushButton("OK");
    QPushButton * l_cancel = new QPushButton("Отмена");

    QGridLayout * l_layout = new QGridLayout();

    l_layout->addWidget(l_label, 0, 0);
    l_layout->addWidget(m_lineEdit, 0, 1);
    l_layout->addWidget(l_ok, 1, 0);
    l_layout->addWidget(l_cancel, 1, 1);

    setLayout(l_layout);

    connect(l_ok, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(l_cancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

QString InputEmployeeLastName::lastName() const
{
    return m_lineEdit->text();
}

