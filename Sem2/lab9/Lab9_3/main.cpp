#include <QApplication>
#include "calculator.h"
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  auto dialog = new Calculator();
  dialog->show();          // отображаем окно
  return app.exec();       // запускаем цикл обработки сообщений
}