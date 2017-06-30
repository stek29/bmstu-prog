#include <QtWidgets/QPushButton>
#include <QVector>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include "calculator.h"
#include <QDebug>
#include <QtMath>

namespace {

enum class BtnBlock {
    Top,
    Left,
    Grid,
    Right
};

constexpr int GridHorizontalCnt = 4;
constexpr int GridVerticalCnt = 4;
// Grid buttons' ids should go one after another,
// With minimal set to GridIdOffset
constexpr int GridIdOffset = 0;

namespace BtnIds {
enum BtnId {
    // 0-9 -- Цифры
    Invert = 10,
    Dot,

    Backspace,
    ClearEntry,
    Clear,
    Equals,

    Divide,
    Multiply,
    Substract,
    Add,

    LogYX,
    PowXY,
    SinX,
    CosX,
};
}

/// Описатель кнопки
struct BtnDescriptor {
    QString text;
    BtnIds::BtnId id;
    BtnBlock block;

    BtnDescriptor(): text(), id(), block(BtnBlock::Grid) {}
    BtnDescriptor(const QString &str, BtnIds::BtnId bid, BtnBlock blk = BtnBlock::Grid)
        : text(str)
        , id(bid)
        , block(blk)
    { }
    BtnDescriptor(const QString &str, int bid, BtnBlock blk = BtnBlock::Grid)
        : text(str)
        , id(static_cast<BtnIds::BtnId>(bid))
        , block(blk)
    { }
};

auto _btnDescr = QVector<BtnDescriptor>( {
    {"0", 0}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4},
    {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
    {"±", BtnIds::Invert}, {".", BtnIds::Dot},

    {"\u232B", BtnIds::Backspace, BtnBlock::Top},
    {"CE", BtnIds::ClearEntry, BtnBlock::Top},
    {"C", BtnIds::Clear, BtnBlock::Top},
    {"=", BtnIds::Equals, BtnBlock::Top},

    {"/", BtnIds::Divide, BtnBlock::Left},
    {"*", BtnIds::Multiply, BtnBlock::Left},
    {"-", BtnIds::Substract, BtnBlock::Left},
    {"+", BtnIds::Add, BtnBlock::Left},

    {"log_y (x)", BtnIds::LogYX, BtnBlock::Right},
    {"x^y", BtnIds::PowXY, BtnBlock::Right},
    {"sin", BtnIds::SinX, BtnBlock::Right},
    {"cos", BtnIds::CosX, BtnBlock::Right},
});
}

Calculator::Calculator(QWidget *parent): QDialog (parent) {
    // Инициализируем поле результатов
    m_pLineEdit = new QLineEdit(this);
    m_pLineEdit->setReadOnly(true);
    m_pLineEdit->setAlignment(Qt::AlignRight);
    // Создаем лэйауты
    auto topLayout = new QHBoxLayout();
    auto leftLayout = new QVBoxLayout();
    auto gridLayout = new QGridLayout();
    auto rightLayout = new QVBoxLayout();

    // Инициализируем mapper и заполняем форму кнопками
    m_pSignalMapper = new QSignalMapper(this);

    for (const auto &desc : _btnDescr) {
        auto button = new QPushButton(desc.text);

        connect(button, SIGNAL(clicked()), m_pSignalMapper, SLOT(map()));
        m_pSignalMapper->setMapping(button, desc.id);

        switch (desc.block) {
            case BtnBlock::Top:
                topLayout->addWidget(button);
                break;

            case BtnBlock::Left:
                leftLayout->addWidget(button);
                break;

            case BtnBlock::Grid:
                gridLayout->addWidget(
                            button,
                            (desc.id - GridIdOffset) / GridVerticalCnt,
                            (desc.id - GridIdOffset) % GridHorizontalCnt
                );
                break;

            case BtnBlock::Right:
                rightLayout->addWidget(button);
                break;
        }
    }
    connect(m_pSignalMapper, SIGNAL(mapped(int)),
            this, SLOT(clicked(int)));

    auto leftGridRightLayout = new QHBoxLayout();
    leftGridRightLayout->addLayout(leftLayout);
    leftGridRightLayout->addLayout(gridLayout);
    leftGridRightLayout->addLayout(rightLayout);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_pLineEdit);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(leftGridRightLayout);
    this->setLayout(mainLayout);

    // И подготавливаем к работе
    clear(false);
}

void Calculator::clicked(int id) {
    if (id >= 0 && id < 10) {
        if (clearOnNumber) {
            setStrEdit("");
            clearOnNumber = false;
        }
        auto curr_str = getStrEdit();
        curr_str.append(QString::number(id));

        bool valid = false;
        curr_str.toDouble(&valid);
        if (valid) {
            setStrEdit(curr_str);
        }

        return;
    }

    switch (id) {
        case BtnIds::Backspace: {
            auto curr_str = getStrEdit();
            curr_str.chop(1);
            setStrEdit(curr_str);
            break;
        }

        case BtnIds::Dot: {
            auto curr_str = getStrEdit();
            curr_str.append('.');

            bool valid = false;
            curr_str.toDouble(&valid);

            if (valid) {
                setStrEdit(curr_str);
            }

            break;
        }

        case BtnIds::Invert:
            setNumEdit(-getNumEdit());
            break;
        case BtnIds::ClearEntry:
        case BtnIds::Clear:
            clear(id == BtnIds::ClearEntry);
            break;

        case BtnIds::Equals:
            calcIfNeeded();
            break;

        case BtnIds::CosX: {
            calcIfNeeded();
            auto curVal = getNumEdit();
            setNumEdit(qCos(curVal));
            break;
        }

        case BtnIds::SinX: {
            calcIfNeeded();
            auto curVal = getNumEdit();
            setNumEdit(qSin(curVal));
            break;
        }

        default: // бинарная функция
            calcBinary(id);
    }
};
// Получить число из m_pLineEdit
double Calculator::getNumEdit() {
    return getStrEdit().toDouble();
};
QString Calculator::getStrEdit() {
    return m_pLineEdit->text();
};
// записать число в m_pLineEdit
void Calculator::setNumEdit(double num) {
    if (!isfinite(num)) {
        setStrEdit(""); m_pLineEdit->setPlaceholderText("ERROR");
        return;
    } else { m_pLineEdit->setPlaceholderText(""); }

    QString str;
    str.setNum(num, 'g', 10);
    setStrEdit(str);
};
void Calculator::setStrEdit(const QString &str) {
    m_pLineEdit->setText(str);
};

void Calculator::calcBinary(int id) {
    calcIfNeeded();

    prev_val = getNumEdit();
    prev_id = id;
    clearOnNumber = true;

    calcNeeded = true;
}

void Calculator::clear(bool justEntry) {
    m_pLineEdit->setPlaceholderText("");
    setStrEdit("");
    clearOnNumber = false;
    if (!justEntry) {
        prev_val = 0;
        prev_id = 0;
        calcNeeded = false;
    }
}

void Calculator::calcIfNeeded() {
    if (calcNeeded) {
        switch (prev_id) {
            case BtnIds::Add:
                setNumEdit(prev_val + getNumEdit());
                break;
            case BtnIds::Substract:
                setNumEdit(prev_val - getNumEdit());
                break;
            case BtnIds::Divide:
                setNumEdit(prev_val / getNumEdit());
                break;

            case BtnIds::Multiply:
                setNumEdit(prev_val * getNumEdit());
                break;

            case BtnIds::LogYX:
                setNumEdit(qLn(prev_val) / qLn(getNumEdit()));
                break;
            case BtnIds::PowXY:
                setNumEdit(qPow(prev_val, getNumEdit()));
                break;
        }

        calcNeeded = false;
    }
}
