#include "SymbolTable.h"

#include <string>

/**
 * Symbol Table constructor
 */
SymbolTable::SymbolTable() {
    symbols["SCREEN"] = 16384; 
    symbols["KBD"] = 24576; 
    symbols["SP"] = 0; 
    symbols["LCL"] = 1; 
    symbols["ARG"] = 2; 
    symbols["THIS"] = 3; 
    symbols["THAT"] = 4; 
}

/**
 * Symbol Table destructor
 */
SymbolTable::~SymbolTable() {
}

/**
 * Adds a symbol to the symbol table
 * @param symbol The name of the symbol
 * @param value The address for the symbol
 */
void SymbolTable::addSymbol(string symbol, uint16_t value) {
    symbols[symbol]=value;
}

/**
 * Gets a symbol from the symbol table
 * @param symbol The name of the symbol
 * @return The address for the symbol or -1 if the symbol isn't in the table
 */
int SymbolTable::getSymbol(string symbol) {
    
    if(symbols.find(symbol)!=symbols.end()){
        return symbols[symbol];
    }
    return -1;
}

int SymbolTable::getVarNum(){
    int result = varNum;
    varNum++;
    return result;
}

void SymbolTable::print(){
    for (auto const &pair: symbols) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }    
}