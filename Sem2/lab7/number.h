#ifndef LABS_NUMBER_H
#define LABS_NUMBER_H

inline int digit_sum(int n) {
    int res = 0;
    while (n > 0) {
        res += n % 10;
        n /= 10;
    }
    return res;
};

class Number {
public:
    Number(int x): number(x) {}

    operator int() const { return number; }

    friend bool operator<(Number a, Number b) {
        return digit_sum(a.number) > digit_sum(b.number);
    }
private:
    int number;
};

#endif //LABS_NUMBER_H
