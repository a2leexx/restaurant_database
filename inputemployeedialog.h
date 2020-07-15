#ifndef INPUTEMPLOYEEDIALOG_H
#define INPUTEMPLOYEEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QComboBox>
#include <QtSql>

class InputEmployeeDialog : public QDialog
{
    QComboBox * m_position;
    QComboBox * m_address;
    QLineEdit * m_firstName;
    QLineEdit * m_lastName;

public:
    InputEmployeeDialog(const QString & p_title, QWidget * p_widget = 0);
    void setPosition(const QString & p_position);
    void setAddress(const QString & p_address);
    void setFirstName(const QString & p_firstName);
    void setLastName(const QString & p_lastName);
    QString position();
    QString address();
    QString firstName();
    QString lastName();
};

#endif // INPUTEMPLOYEEDIALOG_H
