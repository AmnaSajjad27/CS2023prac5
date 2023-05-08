#include "SymbolTable.h"
#include <string>
/**
 * Symbol Table constructor
 */
SymbolTable::SymbolTable() {
    symbolAddress["SP"] = 0;
    symbolAddress["LCL"] = 1;
    symbolAddress["ARG"] = 2;
    symbolAddress["THIS"] = 3;
    symbolAddress["THAT"] = 4;
    symbolAddress["R0"] = 0;
    symbolAddress["R1"] = 1;
    symbolAddress["R2"] = 2;
    symbolAddress["R3"] = 3;
    symbolAddress["R4"] = 4;
    symbolAddress["R5"] = 5;
    symbolAddress["R6"] = 6;
    symbolAddress["R7"] = 7;
    symbolAddress["R8"] = 8;
    symbolAddress["R9"] = 9;
    symbolAddress["R10"] = 10;
    symbolAddress["R11"] = 11;
    symbolAddress["R12"] = 12;
    symbolAddress["R13"] = 13;
    symbolAddress["R14"] = 14;
    symbolAddress["R15"] = 15;
    symbolAddress["SCREEN"] = 16384;
    symbolAddress["KBD"] = 24576;
}
/**
 * Symbol Table destructor
 */
SymbolTable::~SymbolTable() {
    // Your code here
}
/**
 * Adds a symbol to the symbol table
 * @param symbol The name of the symbol
 * @param value The address for the symbol
 */
void SymbolTable::addSymbol(string symbol, uint16_t value) {
    if (symbolAddress.find(symbol) == symbolAddress.end())
        symbolAddress[symbol] = value;
}
/**
 * Gets a symbol from the symbol table
 * @param symbol The name of the symbol
 * @return The address for the symbol or -1 if the symbol isn't in the table
 */
int SymbolTable::getSymbol(string symbol) {
     if (symbolAddress.find(symbol) != symbolAddress.end())
        return symbolAddress[symbol];
    return -1;
}
/**
 * Returns whether a symbol is in the Symbol Table
 * @param symbol The name of the symbol
 * @return 1 if found, 0 if not found
 */
bool SymbolTable::inTable(string symbol){
    return (symbolAddress.find(symbol) != symbolAddress.end());
}