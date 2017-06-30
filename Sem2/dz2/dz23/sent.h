#pragma once

#include <cstring>
#include <iostream>

using namespace std;

const int MAX_WORD_CNT = 10;
const int MAX_WORD_LEN = 15;

class Sentence {
public:
    Sentence(char *str) {
        char *p = strtok(str, " ");
        size = 0;
        while (size < MAX_WORD_CNT && p != nullptr) {
            strncpy(words[size++], p, MAX_WORD_LEN);
            p = strtok(nullptr, " ");
        }
        print(cerr << "Const: ");
    }

    int longCount() const {
        int ret=0;
        for (int i = 0; i < size; i++)
            if (strlen(words[i]) > 5)
                ret++;
        return ret;
    };

    int count() const {
        return size;
    }

    int wordPosition(const char *str) const {
        int ret = -1;
        for (int i = 0; i < size; i++)
            if (strncmp(words[i], str, MAX_WORD_LEN) == 0) {
                ret = i;
                break;
            }
        return ret;
    }

    void print(ostream &to = cout) const {
        for (int i = 0; i < size; i++)
            to << words[i] << ' ';
        to << endl;
    }

    ~Sentence() {
        print(cerr << "Destr: ");
    }

private:
    char words[MAX_WORD_CNT][MAX_WORD_LEN];
    int size;
};
/*
Counting objects done
Delta compression using up to 2 threads
Compressing objects 100% done
Writing objects KiB bytes done
Total delta reused delta
remote Resolving deltas 100% completed
with local objects
end

*/