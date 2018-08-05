#pragma once

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
    FORMULA_CODON_SUM_RANGE,
    FORMULA_CODON_LOG,
    FORMULA_CODON_RETURN,
    FORMULA_CODON_NUM,
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
        while (!randomOfType(type = (FormulaCodonType)rand(FORMULA_CODON_NUM), pos));
    }

    FormulaCodon(FormulaCodonType type_, size_t pos) {
        assertIsTrue(randomOfType(type = type_, pos));
    }

    float execute(const vector<float>& values, size_t pos) {
        switch(type) {
            case FORMULA_CODON_SYMBOL: return value;
            case FORMULA_CODON_ADD: return getValAtAddress(a, values, pos) + getValAtAddress(b, values, pos);
            case FORMULA_CODON_MUL: return getValAtAddress(a, values, pos) * getValAtAddress(b, values, pos);
            case FORMULA_CODON_DIV: {
                float bVal = getValAtAddress(b, values, pos);
                return bVal != 0 ? getValAtAddress(a, values, pos) / bVal : 0.0f;
            }
            case FORMULA_CODON_SUM_RANGE: {
                float sum = 0;
                for (size_t i = a.jumpDistance; i < b.jumpDistance; ++i) {
                    sum += getValAtAddress(a, values, pos);
                }
                return sum;
            }
            case FORMULA_CODON_LOG: {
                float aVal = getValAtAddress(a, values, pos);
                return log(aVal > 1.0f ? aVal : 1.0f);
            }
            case FORMULA_CODON_RETURN: return getValAtAddress(pos - 1, values, pos);
            default : assertIsTrue(false); return 0;
        }
    }

private:
   inline float getValAtAddress(const Address& add, const vector<float>& values, size_t pos) {
       return getValAtAddress(add.jumpDistance, values, pos);
   }
   inline float getValAtAddress(const size_t& jumpDistance, const vector<float>& values, size_t pos) {
       assertIsGreater(pos, jumpDistance);
       return values[jumpDistance];
   }
   bool randomOfType(FormulaCodonType type, size_t pos) {
        switch (type) {
            case FORMULA_CODON_SYMBOL:
                value = randf(-1.0f, 1.0f);
                return true;
            case FORMULA_CODON_ADD:
            case FORMULA_CODON_MUL:
            case FORMULA_CODON_DIV:
            case FORMULA_CODON_SUM_RANGE:
                if (pos < 1) return false;
                a.jumpDistance = pos > 1 ? rand(0, pos) : 0;
                b.jumpDistance = pos > 1 ? rand(0, pos) : 0;
                assertNotEqual(pos, a.jumpDistance);
                assertNotEqual(pos, b.jumpDistance);
                return true;
            case FORMULA_CODON_LOG:
                if (pos < 1) return false;
                a.jumpDistance = pos > 1 ? rand(0, pos) : 0;
                return true;
            case FORMULA_CODON_RETURN: assertIsGreater(pos, 0); return true;
            default : assertIsTrue(false);
        }
        return false;
   }
};

std::ostream& operator<<(std::ostream& os, const FormulaCodon& fc) {
    switch (fc.type) {
        case FORMULA_CODON_SYMBOL: os << fc.value; break;
        case FORMULA_CODON_ADD: os << "+(" << fc.a.jumpDistance << ", " << fc.b.jumpDistance << ")"; break;
        case FORMULA_CODON_MUL: os << "*(" << fc.a.jumpDistance << ", " << fc.b.jumpDistance << ")"; break;
        case FORMULA_CODON_DIV: os << "/(" << fc.a.jumpDistance << ", " << fc.b.jumpDistance << ")"; break;
        case FORMULA_CODON_SUM_RANGE: os << "+(" << fc.a.jumpDistance << ":" << fc.b.jumpDistance << ")"; break;
        case FORMULA_CODON_LOG: os << "log(" << fc.a.jumpDistance << ")"; break;
        case FORMULA_CODON_RETURN: os << "ret"; break;
        default : assertIsTrue(false);
    }
    return os;
}

}