#ifndef INPUTADDRESSDIALOG_H
#define INPUTADDRESSDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>


class InputAddressDialog : public QDialog
{
    QLineEdit * m_lineEdit;
public:
    InputAddressDialog(const QString & p_title, QWidget * p_widget = 0);
    QString address() const;
};

#endif // INPUTADDRESSDIALOG_H
