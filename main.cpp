#include "mainwindow.h"
#include "connectiondialog.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    while (true) {
        ConnectionDialog dialog("Параметры подключения");

        if (dialog.exec() == QDialog::Accepted)
        {
            QSqlDatabase db;

            db = QSqlDatabase::addDatabase("QPSQL");

            db.setHostName(dialog.hostname());
            db.setDatabaseName(dialog.databaseName());
            db.setUserName(dialog.userName());
            db.setPassword(dialog.password());
            db.setPort(dialog.port());

            if (db.open())
            {
                MainWindow w(db);
                w.show();

                return a.exec();
            }
            else {
                QMessageBox msgBox;

                msgBox.setWindowTitle("Ошибка при подключении.");
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setText("Не удалось подключиться к базе данных: " + db.lastError().text());
                msgBox.setInformativeText("Повторить попытку?");
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::Yes);

                if (msgBox.exec() != QMessageBox::Yes)
                    return 1;
            }
        }
        else
            return 1;
    }
}
