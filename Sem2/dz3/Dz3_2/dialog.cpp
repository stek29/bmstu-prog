#include "dialog.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QFileDialog>
#include <QFontDialog>
#include <QRegularExpression>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    auto saveBtn = new QPushButton("Сохранить");
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveClicked()));
    auto openBtn = new QPushButton("Открыть");
    connect(openBtn, SIGNAL(clicked()), this, SLOT(openClicked()));
    auto fontBtn = new QPushButton("Шрифт");
    connect(fontBtn, SIGNAL(clicked()), this, SLOT(fontClicked()));

    auto btnLayout = new QHBoxLayout();
    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(openBtn);
    btnLayout->addWidget(fontBtn);

    statusLabel = new QLabel("Приложение готово к работе");
    auto font = statusLabel->font();
    font.setPointSize(10);
    statusLabel->setFont(font);
    statusLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    auto explainer = new QLabel("Год - Количество статей");
    explainer->setFont(font);
    explainer->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);

    edit = new QTextEdit();

    auto widgetLayout = new QVBoxLayout();
    widgetLayout->addLayout(btnLayout);
    widgetLayout->addWidget(statusLabel);
    widgetLayout->addWidget(explainer);
    widgetLayout->addWidget(edit);
    setLayout(widgetLayout);
}

void Dialog::openClicked() {
    if (setFile(false)) {
        QDataStream stream(file);
        file->seek(0);

        edit->clear();

        quint32 year, count;
        stream >> year >> count;
        while (!stream.atEnd() && stream.status() == QDataStream::Status::Ok) {
            edit->append(QString("%1 - %2").arg(year).arg(count));
            stream >> year >> count;
        }
        if (stream.status() != QDataStream::Status::Ok) {
            statusLabel->setText(QString("Файл поврежден!"));
        } else {
            edit->append(QString("%1 - %2")
                         .arg(year, 4, 10, QLatin1Char('0'))
                         .arg(count));
            statusLabel->setText(QString("Прочитан файл %1").arg(QFileInfo(*file).fileName()));
        }
    }
};

void Dialog::saveClicked() {
    if (setFile(true)) {
        QDataStream stream(file);
        file->seek(0);

        QRegularExpression regex("^(\\d+)\\s*-\\s*(\\d+)$");

        edit->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);

        while (!edit->textCursor().atEnd()) {
            edit->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
            edit->moveCursor(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
            QString text = edit->textCursor().selectedText();
            auto match = regex.match(text);
            if (!match.hasMatch()) {
                edit->setTextColor(Qt::red);
            } else {
                quint32  year = match.capturedRef(1).toUInt();
                quint32 count = match.capturedRef(2).toUInt();
                stream << year << count;
            }
            edit->moveCursor(QTextCursor::Down, QTextCursor::MoveAnchor);
        }

        statusLabel->setText(QString("Сохранено в %1").arg(QFileInfo(*file).fileName()));
    }
};

bool Dialog::setFile(bool save) {
    QString name;
    if (save) {
        name = QFileDialog::getSaveFileName(
                    this,
                    "Записать в файл", // Caption
                    QString(), // Dir
                    QString("Data (*.dz3)") // Filter
                    );
    } else {
        name = QFileDialog::getOpenFileName(
                    this,
                    "Прочитать из файла", // Caption
                    QString(), // Dir
                    QString("Data (*.dz3)") // Filter
                    );
    }

    bool success = false;

    if (!name.isNull()) {
        if (file != nullptr) {
            file->flush();
            file->close();
            delete file;
        }

        if (QFile::exists(name) && save) {
            QFile::remove(name);
        }

        file = new QFile(name);
        if (file->open(QFile::ReadWrite)) {
            success = true;
        }
    }
    if (success)
        statusLabel->setText(QString("Открыт файл %1").arg(QFileInfo(*file).fileName()));
    else
        statusLabel->setText(QString("Невозможно открыть файл"));
    return success;
}

void Dialog::fontClicked() {
    edit->setFont(QFontDialog::getFont(nullptr, edit->font()));
}

Dialog::~Dialog() {
    if (file != nullptr) {
        file->flush();
        file->close();
        delete file;
    }
}
