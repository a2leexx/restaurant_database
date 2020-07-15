#include "inputpositiondialog.h"

InputPositionDialog::InputPositionDialog(const QString & p_title, QWidget * p_widget) : QDialog(p_widget, Qt::MSWindowsFixedSizeDialogHint)
{
    m_title = new QLineEdit();
    m_salary = new QLineEdit();
    m_award = new QLineEdit();
    m_checkBox = new QCheckBox();

    setWindowTitle(p_title);

    QLabel * l_label1 = new QLabel("Название должности: ");
    QLabel * l_label2 = new QLabel("Заработная плата:   ");
    QLabel * l_label3 = new QLabel("Максимальный размер премии: ");
    QLabel * l_label4 = new QLabel("Запретить создавать несколько рабочих мест в одном ресторане:");

    QPushButton * l_ok = new QPushButton("OK");
    QPushButton * l_cancel = new QPushButton("Отмена");

    QGridLayout * l_layout = new QGridLayout();

    l_layout->addWidget(l_label1, 0, 0);
    l_layout->addWidget(m_title, 0, 1);
    l_layout->addWidget(l_label2, 1, 0);
    l_layout->addWidget(m_salary, 1, 1);
    l_layout->addWidget(l_label3, 2, 0);
    l_layout->addWidget(m_award, 2, 1);
    l_layout->addWidget(l_label4, 3, 0);
    l_layout->addWidget(m_checkBox, 3, 1);
    l_layout->addWidget(l_ok, 4, 0);
    l_layout->addWidget(l_cancel, 4, 1);

    setLayout(l_layout);

    connect(l_ok, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(l_cancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void InputPositionDialog::setPositionTitle(const QString &p_title)
{
    m_title->setText(p_title);
}

void InputPositionDialog::setPositionSalary(double p_salary)
{
    m_salary->setText(QString("%1").arg(p_salary));
}

void InputPositionDialog::setPositionMaxAward(double p_award)
{
    m_award->setText(QString("%1").arg(p_award));
}

void InputPositionDialog::setOnlyOneWorkplace(bool p_param)
{
    m_checkBox->setChecked(p_param);
}

QString InputPositionDialog::positionTitle() const
{
    return m_title->text();
}

double InputPositionDialog::positionSalary() const
{
    return m_salary->text().toDouble();
}

double InputPositionDialog::positionMaxAward() const
{
    return m_award->text().toDouble();
}

bool InputPositionDialog::onlyOneWorkplace()
{
    return m_checkBox->isChecked();
}
