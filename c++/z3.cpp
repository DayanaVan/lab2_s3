#include <iostream>
#include <string>
#include "set.h"

using namespace std;

int main() {
    string genome1, genome2;

    cout << "Введите первый геном:" << endl;
    getline(cin, genome1);
    cout << "Введите второй геном:" << endl;
    getline(cin, genome2);

    // Множество для хранения уникальных пар из второго генома
    Set pairsInGenome2(200000);

    // Заполнение множества парами (двухсимвольными сочетаниями)
    for (size_t i = 0; i + 1 < genome2.length(); ++i) {
        // Кодируем пару как число: символ1 * 26 + символ2
        int char1 = genome2[i] - 'A';
        int char2 = genome2[i+1] - 'A';
        int pairCode = char1 * 26 + char2;
        pairsInGenome2.add(pairCode);
    }

    // Подсчет совпадающих пар в первом геноме
    int similarity = 0;
    for (size_t i = 0; i + 1 < genome1.length(); ++i) {
        int char1 = genome1[i] - 'A';
        int char2 = genome1[i+1] - 'A';
        int pairCode = char1 * 26 + char2;

        if (pairsInGenome2.contains(pairCode)) {
            similarity++;
        }
    }

    cout << "Степень близости: " << similarity << endl;

    return 0;
}
