#ifndef INPUTPOSITIONDIALOG_H
#define INPUTPOSITIONDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QCheckBox>

class InputPositionDialog : public QDialog
{
    Q_OBJECT

    QLineEdit * m_title;
    QLineEdit * m_salary;
    QLineEdit * m_award;
    QCheckBox * m_checkBox;

public:
    InputPositionDialog(const QString & p_title, QWidget * p_widget = 0);
    void setPositionTitle(const QString & p_title);
    void setPositionSalary(double p_salary);
    void setPositionMaxAward(double p_award);
    void setOnlyOneWorkplace(bool p_param);
    QString positionTitle() const;
    double positionSalary() const;
    double positionMaxAward() const;
    bool onlyOneWorkplace();
};

#endif // INPUTPOSITIONDIALOG_H
