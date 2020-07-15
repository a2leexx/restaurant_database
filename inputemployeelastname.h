#ifndef INPUTEMPLOYEELASTNAME_H
#define INPUTEMPLOYEELASTNAME_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>


class InputEmployeeLastName : public QDialog
{
    QLineEdit * m_lineEdit;
public:
    InputEmployeeLastName(const QString & p_title, QWidget * p_widget = 0);
    QString lastName() const;
};

#endif // INPUTEMPLOYEELASTNAME_H
