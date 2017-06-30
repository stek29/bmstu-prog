/*
 * dz22
 * Даны текстовые файлы F и G. Переписать в файл H только те слова из файла G,
 *  которые встречаются в файле F. Вместо отсутствующих слов ставить троеточие.
 * Порядок знаков препинания при этом сохранить.
 * Словоформы считать различными словами.
 * Предусмотреть наличие индексных файлов, для поиска совпадения
 *  со словами файла F. Размер файла F – не менее 10 МБ.
 *
 * Проверить работу программы следующим образом.
 * Файл F должен содержать художественные произведения авторов 19-го века,
 * файл H – современные новости или статьи о компьютерных технологиях.
 * Обеспечить время работы алгоритма поиска не более 3 секунд для новости
 *  размером не более 10 кБ.
 */

#include <cstdlib>
#include <functional>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

streamoff readWord(ifstream &from, string &word, string *skipped = nullptr) {
    string::value_type ch;

    word.clear();
    if (skipped != nullptr) skipped->clear();

    while (from.peek() != string::traits_type::eof() && !isalpha(from.peek())) {
        from.get(ch);
        if (skipped != nullptr)
            *skipped += ch;
    }

    streamoff retval = from.tellg();

    while (from.peek() != string::traits_type::eof() && isalpha(from.peek())) {
        from.get(ch);
        word += ch;
    }

    if (!from) from.clear();

    return retval;
}

bool exists(string word, size_t wordHash, fstream &idx, ifstream &from) {
    bool found = false;
    auto fromSeek = from.tellg();

    size_t currHash;
    streamoff pos;

    idx.seekg(0);
    idx.read((char*) &currHash, sizeof(currHash)).read((char*) &pos, sizeof(pos));
    while (idx) {
        if (currHash == wordHash) {
            from.seekg(pos);
            string read; readWord(from, read);
            if (read == word) {
                found = true;
                break;
            }
        }

        idx.read((char*) &currHash, sizeof(currHash)).read((char*) &pos, sizeof(pos));
    }
    idx.clear();
    from.seekg(fromSeek);
    return found;
}

struct w_word {
    string st;
    streamoff off;
};
multimap<size_t, w_word> mp;

fstream createIdxFile(ifstream &from) {
    fstream idxFile("idx.dat", ios_base::in | ios_base::out | ios_base::binary);
    if (!idxFile) {
        idxFile.open("idx.dat", ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc);
    } else {
        return idxFile;
    }

    string word;

    hash<string> hashFn;

    int i = 0;
    from.seekg(0);
    streamoff pos;
    while (pos = readWord(from, word), !word.empty()) {
        size_t wordHash = hashFn(word);
        bool found=false;
        auto range = mp.equal_range(wordHash);
        for (auto it = range.first; it != range.second; it++) {
            if (it->second.st == word) {
                found = true;
                break;
            }
        }
        if (!found) mp.insert(pair<size_t, w_word>(wordHash, {word, pos}));
//        if (!exists(word, wordHash, idxFile, from)) {
//            idxFile.seekp(0, ios_base::end);
//            idxFile.write((char*) &wordHash, sizeof(wordHash));
//            idxFile.write((char*) &pos, sizeof(pos));
//        }
        i++;
        if (i%1000 == 0) {
            cout << "processed " << i << " words" ", current size -- " << mp.size() << endl;
        }
    }

    for (auto &p: mp) {
        idxFile.write((char*) &p.first, sizeof(p.first))
            .write((char*) &p.second.off, sizeof(p.second.off));
    }

    return idxFile;
}

int main(void) {
    ifstream f("f.txt", ios_base::in);
    ifstream g("g.txt", ios_base::in);
    ofstream h("h.txt", ios_base::out | ios_base::trunc);

    if (!(f && g && h)) {
        cerr << "Can't open F,G,H: " << bool(f) << bool(g) << bool(h) << endl;
        return EXIT_FAILURE;
    }

    fstream idx = createIdxFile(f);
    if (!idx) {
        f.close(); g.close(); h.close();
        cerr << "Can't create idx file" << endl;
        return EXIT_FAILURE;
    }

    hash<string> hashFn;
    string word, whitespace;
    while (readWord(g, word, &whitespace), !word.empty()) {
        h << whitespace;
        bool found=false;
        auto range = mp.equal_range(hashFn(word));
        for (auto it = range.first; it != range.second; it++) {
            if (it->second.st == word) {
                found = true;
                break;
            }
        }
//        if (exists(word, hashFn(word), idx, f)) {
        if (found) {
            h << word;
        } else {
            h << "...";
        }
    }

    idx.close();
    f.close(); g.close(); h.close();

    return EXIT_SUCCESS;
}