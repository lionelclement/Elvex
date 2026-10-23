#ifndef ELVEX_VARTABLE_H
#define ELVEX_VARTABLE_H

#include <bitset>
#include <cstdint>
#include <string>
#include <unordered_map>

#include "bitset.hpp"
#include "shared_ptr.hpp"

#define CONTAINS_A_FORM "CONTAINS_A_FORM"
#define DOES_NOT_CONTAIN_A_HEAD "DOES_NOT_CONTAIN_A_HEAD"

/**
 * Interns grammar symbols and names into numeric codes/bit positions.
 * Also creates scoped variable names to avoid binding collisions.
 */
class Vartable
{
public:
    using string_to_bitset = std::unordered_map<std::string, bitsetPtr>;
    using string_to_bitset_iterator = string_to_bitset::iterator;
    using string_to_bitset_const_iterator = string_to_bitset::const_iterator;

    using uint32_t_to_string = std::unordered_map<uint32_t, std::string>;
    using uint32_t_to_string_iterator = uint32_t_to_string::iterator;
    using uint32_t_to_string_const_iterator = uint32_t_to_string::const_iterator;

    using string_to_uint32_t = std::unordered_map<std::string, uint32_t>;
    using string_to_uint32_t_iterator = string_to_uint32_t::iterator;
    using string_to_uint32_t_const_iterator = string_to_uint32_t::const_iterator;

public:
    static uint32_t code_for_IS_A_FORM;
    static uint32_t code_for_DOES_NOT_CONTAIN_A_HEAD;

public:
    Vartable();

    static bitsetPtr createSymbol(const std::string& name);
    static bitsetPtr createSymbol(const std::string& name, uint32_t key);

    /** Intern a symbol name and return its stable internal numeric code. */
    static uint32_t nameToCode(const std::string& name);
    static uint32_t nameToCode(const std::string& name, uint32_t key);

    static const std::string& codeToName(uint32_t code);
    static const std::string& bitToName(uint32_t bit);

    static void insertCodeMap(uint32_t key, const std::string& value);

    static uint32_t_to_string_iterator bitMapFind(uint32_t key);
    static uint32_t_to_string_const_iterator bitMapcEnd();

    /** Scope variable occurrences embedded in a textual expression. */
    static void renameVariables(std::string& data, uint32_t key);

private:
    static std::string makeScopedName(const std::string& name, uint32_t key);
    static std::string makeHexSuffix(uint32_t key);

    /** Format the existing diagnostic when no symbol bit remains available. */
    static std::string symbolLimitMessage(const std::string& name);

    /** Return the bit position encoded by the current one-hot index. */
    static size_t currentSymbolBit();

    static bool isVariableStart(unsigned char c);
    static bool isVariableChar(unsigned char c);

private:
    static std::bitset<MAXBITS> variableMapIndex;
    static uint32_t codeMapIndex;

    static string_to_bitset nameToBitsetMap;
    static uint32_t_to_string codeToNameMap;
    static string_to_uint32_t nameToCodeMap;
    static uint32_t_to_string bitToNameMap;
};

#endif // ELVEX_VARTABLE_H