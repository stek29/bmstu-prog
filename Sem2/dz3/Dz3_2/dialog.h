#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFile>
#include <QLabel>
#include <QTextEdit>


class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void saveClicked();
    void openClicked();
    void fontClicked();

private:
    bool setFile(bool forWrite);

    QTextEdit *edit;
    QLabel *statusLabel;

    QFile *file;

};

#endif // DIALOG_H
