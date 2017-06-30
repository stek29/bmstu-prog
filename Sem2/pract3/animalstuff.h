#ifndef ANIMALSTUFF_H
#define ANIMALSTUFF_H

#include <QVariant>

struct Animal {
    QVariant klass, otryad, semeystvo, vid;
};

enum AnimalProps {
    A_KLASS, A_OTRYAD, A_SEMEYSTVO, A_VID, A_PROP_COUNT
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc99-extensions"
static QString animalHeaders[] {
    [A_KLASS] = "Класс",
    [A_OTRYAD] = "Отряд",
    [A_SEMEYSTVO] = "Семейство",
    [A_VID] = "Вид"
};
#pragma clang diagnostic pop

static QVariant* getAnimalProperty(Animal& animal, int idx) {
    switch (idx) {
        case A_KLASS: return &animal.klass;
        case A_OTRYAD: return &animal.otryad;
        case A_SEMEYSTVO: return &animal.semeystvo;
        case A_VID: return &animal.vid;
        default: return nullptr;
    }
};

static const QVariant getAnimalProperty(const Animal& animal, int idx) {
    auto res = getAnimalProperty(const_cast<Animal&>(animal), idx);
    if (res != nullptr)
        return *res;
    else
        return QVariant();
};

#endif // ANIMALSTUFF_H