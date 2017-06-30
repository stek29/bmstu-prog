#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);

public slots:
    void inputEdited(const QString& newText);
    void buttonClicked();

private:
    bool nowUpper;
    QString text;

    QLineEdit *_lineEdit;
    QPushButton *_pushButton;
    QPlainTextEdit *_textEdit;
};

#endif // DIALOG_H
