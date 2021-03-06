#-------------------------------------------------
# В базе данных “Мир животных” для каждого животного указаны класс, отряд,
# семейство, вид (например, класс Млекопитающие * отряд Хищные * семейство
# Кошачьи * снежный барс). Программа должна обеспечивать табличный ввод и в
# интерактивном режиме воспринимать каждый из перечисленных вопросов и давать
# на него ответ.
# 1. Получить список животных данного класса с указанием отряда и
#    семейства.
# 2. Выяснить, в каком из двух заданных семейств видов больше, и
#    вывести список животных этого семейства.
# 3. Выяснить, к какому классу, отряду и семейству принадлежит данное животное.
# 4. Построить диаграмму, которая в виде прямоугольников разной высоты
#    отображает количество отрядов в каждом классе.
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = p3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwidget.cpp \
    tablemodel.cpp \
    proxymodel.cpp

HEADERS += \
        mainwidget.h \
    tablemodel.h \
    proxymodel.h \
    animalstuff.h
