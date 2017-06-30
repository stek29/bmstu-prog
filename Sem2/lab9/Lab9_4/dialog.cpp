#include "dialog.h"
#include <QVBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    _lineEdit = new QLineEdit();
    connect(_lineEdit, SIGNAL(textEdited(const QString&)),
            this, SLOT(inputEdited(const QString&)));

    _pushButton = new QPushButton("Convert");
    connect(_pushButton, SIGNAL(clicked()),
            this, SLOT(buttonClicked()));

    _textEdit = new QPlainTextEdit();
    _textEdit->setReadOnly(true);

    auto layout = new QVBoxLayout();
    layout->addWidget(_lineEdit);
    layout->addWidget(_pushButton);
    layout->addWidget(_textEdit);
    this->setLayout(layout);

    nowUpper = false;
    text = QString();
}

void Dialog::buttonClicked() {
    if (!text.isEmpty()) {
        QString str;
        if (nowUpper) {
            str = "<b>UPPER: </b><pre>";
            str += text.toUpper();
        } else {
            str = "<b>lower: </b><pre>";
            str += text.toLower();
        }
        str += "</pre>";

        _textEdit->appendHtml(str);
        nowUpper = !nowUpper;
    }
}

void Dialog::inputEdited(const QString &newText) {
    text = newText.toHtmlEscaped();
    _textEdit->clear();
    _textEdit->appendHtml("<b>Input: </b><pre>" + text + "</pre>");
}