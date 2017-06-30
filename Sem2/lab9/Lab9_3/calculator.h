#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>
#include <QLineEdit>
#include <QSignalMapper>

class Calculator: public QDialog {
    Q_OBJECT
public:
    Calculator( QWidget * parent = 0);
    virtual ~Calculator() {}
protected:
    inline double  getNumEdit();
    inline QString getStrEdit();
    inline void    setNumEdit(double);
    inline void    setStrEdit(const QString&);

    void clear(bool);

    QSignalMapper *m_pSignalMapper;
    QLineEdit     *m_pLineEdit;

    double prev_val;
    int prev_id;
    bool calcNeeded;
    bool clearOnNumber;

    void calcIfNeeded();
    void calcBinary(int);
private slots:
    void clicked(int id);
};
#endif