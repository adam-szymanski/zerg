#ifndef LIB_GENETIC_FORMULA_CODON_H
#define LIB_GENETIC_FORMULA_CODON_H

#include "lib/util/Random.h"
#include "lib/assert/Assert.h"

#include <vector>

using namespace std;

namespace Zerg {

enum FormulaCodonType {
    FORMULA_CODON_SYMBOL,
    FORMULA_CODON_ADD,
    FORMULA_CODON_MUL,
    FORMULA_CODON_DIV,
    FORMULA_CODON_RETURN,
    FORMULA_CODON_NUM
};

struct Address {
    size_t jumpDistance;
};

class FormulaCodon {
public:
    FormulaCodonType type;
    float value;
    Address a;
    Address b;

    FormulaCodon(size_t pos) {
        bool ok = false;
        while (!ok) {
            type = (FormulaCodonType)rand(FORMULA_CODON_NUM);
            switch (type) {
                case FORMULA_CODON_SYMBOL:
                    value = randf(-1.0f, 1.0f);
                    ok = true;
                    break;
                case FORMULA_CODON_ADD:
                case FORMULA_CODON_MUL:
                case FORMULA_CODON_DIV:
                    if (pos < 1) break;
                    a.jumpDistance = pos > 1 ? rand(1, pos) : 1;
                    b.jumpDistance = pos > 1 ? rand(1, pos) : 1;
                    ok = true;
                    break;
                case FORMULA_CODON_RETURN:
                    if (pos < 1) break;
                    ok = true;
                    a.jumpDistance = pos > 1 ? rand(1, pos) : 1;
                    break;
                default : assertIsTrue(false);
            }
        }
    }

    float execute(const vector<float>& values, size_t pos) {
        switch(type) {
            case FORMULA_CODON_SYMBOL: return value;
            case FORMULA_CODON_ADD: return getValAtAddress(a, values, pos) + getValAtAddress(b, values, pos);
            case FORMULA_CODON_MUL: return getValAtAddress(a, values, pos) * getValAtAddress(b, values, pos);
            case FORMULA_CODON_DIV: return getValAtAddress(a, values, pos) / (std::max(getValAtAddress(b, values, pos), 0.0001f));
            case FORMULA_CODON_RETURN: return getValAtAddress(a, values, pos);
            default : assertIsTrue(false); return 0;
        }
    }

private:
   inline float getValAtAddress(const Address& add, const vector<float>& values, size_t pos) {
       assertIsGreaterOrEqual(pos, add.jumpDistance);
       return values[pos - add.jumpDistance];
   }
};

std::ostream& operator<<(std::ostream& os, const FormulaCodon& fc) {
    switch (fc.type) {
        case FORMULA_CODON_SYMBOL: os << fc.value; break;
        case FORMULA_CODON_ADD: os << "+(" << fc.a.jumpDistance << ", " << fc.b.jumpDistance << ")"; break;
        case FORMULA_CODON_MUL: os << "*(" << fc.a.jumpDistance << ", " << fc.b.jumpDistance << ")"; break;
        case FORMULA_CODON_DIV: os << "/(" << fc.a.jumpDistance << ", " << fc.b.jumpDistance << ")"; break;
        case FORMULA_CODON_RETURN: os << "ret(" << fc.a.jumpDistance << ")"; break;
        default : assertIsTrue(false);
    }
    return os;
}

}

#endif