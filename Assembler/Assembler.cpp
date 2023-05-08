#include "Assembler.h"
#include "SymbolTable.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * Assembler constructor
 */
Assembler::Assembler() {
   int startAddress = 16;
}

/**
 * Assembler destructor
 */
Assembler::~Assembler() {
}

/**
 * Assembler first pass; populates symbol table with label locations.
 * @param instructions An array of the assembly language instructions.
 * @param symbolTable The symbol table to populate.
 */
void Assembler::buildSymbolTable(SymbolTable* symbolTable, string instructions[], int numOfInst) {
    int line_number;
    int index;

    index = 0;
    line_number = 0;

    while (index < numOfInst)
    {
        if (parseInstructionType(instructions[index]) != L_INSTRUCTION)
        {
            line_number++;
        }
        if (parseInstructionType(instructions[index]) == L_INSTRUCTION)
        {
            string parseSym;

            parseSym = parseSymbol(instructions[index]);

            if(!symbolTable->inTable(parseSym))
            {
                symbolTable->addSymbol(parseSym, line_number);
            }
        }
        index++;
    }
}

// converts a string vector into a string of multiple lines 
string vtos(vector<string> vec)
{
    string  resString;
    int     len;
    len = vec.size();
    resString = "";
    for (int i = 0; i < len; i++){
        resString.append(vec.at(i));
        if (i != (len-1)){
            resString.append("\n");
        }
    }
    return resString;
}

/**
 * Assembler second pass; Translates a set of instructions to machine code.
 * @param instructions An array of the assembly language instructions to be converted to machine code.
 * @param symbolTable The symbol table to reference/update.
 * @return A string containing the generated machine code as lines of 16-bit binary instructions.
 */
string Assembler::generateMachineCode(SymbolTable* symbolTable, string instructions[], int numOfInst) {
    vector<string> resString;
    int i = 0;
    while (i < numOfInst)
    {
        if(parseInstructionType(instructions[i]) == A_INSTRUCTION)
        {
            string resSymbol;
            resSymbol = "0";
            resSymbol.append(translateSymbol(instructions[i]), symbolTable);
            resSymbol.insert(resString.end(), resSymbol);
        }
        else if(parseInstructionType(instructions[i]) == C_INSTRUCTION)
        {
            InstructionComp inComp;
            InstructionDest inDest;
            InstructionJump inJump;
            inComp = parseInstructionComp(instructions[i]);
            inDest = parseInstructionDest(instructions[i]);
            inJump = parseInstructionJump(instructions[i]);
            string resComp;
            resComp = "111";
            resComp.append(translateComp(inComp));       
            resComp.append(translateDest(inDest));
            resComp.append(translateJump(inJump));
            resString.insert(resString.end(), resComp);
        }
        i++;
    }
    string rtnString;
    rtnString = vtos(resString);
    return rtnString;
}

/**
 * Parses the type of the provided instruction
 * @param instruction The assembly language representation of an instruction.
 * @return The type of the instruction (A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION, NULL)
 */
Assembler::InstructionType Assembler::parseInstructionType(string instruction) {

    if (instruction.find("@") != string::npos) {
        return A_INSTRUCTION;
    } else if (instruction.find("(") != string::npos) {
        return L_INSTRUCTION;
    } else if (instruction.find("D") != string::npos) {
        return C_INSTRUCTION;
    } else if (instruction.find("A") != string::npos) {
        return C_INSTRUCTION;
    } else if (instruction.find("M") != string::npos) {
        return C_INSTRUCTION;
    } else if (instruction.find("0") != string::npos) {
        return C_INSTRUCTION;
    } else if (instruction.find("1") != string::npos) {
        return C_INSTRUCTION;
    } else if (instruction.find("-") != string::npos) {
        return C_INSTRUCTION; 
    } else if (instruction.find("!") != string::npos) {
        return C_INSTRUCTION; 
    }                   
    return NULL_INSTRUCTION;
}

/**
 * Parses the destination of the provided C-instruction
 * @param instruction The assembly language representation of a C-instruction.
 * @return The destination of the instruction (A, D, M, AM, AD, MD, AMD, NULL)
 */
Assembler::InstructionDest Assembler::parseInstructionDest(string instruction) {
    
    unsigned long   equalSignPos;
    string  destString;
    equalSignPos = instruction.find("=");
    if (equalSignPos == string::npos)
        return NULL_DEST;

    destString = instruction.substr(0,equalSignPos);

    if (destString == "A"){
        return A;
    } else if (destString == "D"){
        return D;
    } else if (destString == "M"){
        return M;
    } else if (destString == "AM"){
        return AM;
    } else if (destString == "AD"){
        return AD;
    } else if (destString == "MD"){
        return MD;
    } else if (destString == "AMD"){
        return AMD;
    }
    return NULL_DEST;
}

/**
 * Parses the jump condition of the provided C-instruction
 * @param instruction The assembly language representation of a C-instruction.
 * @return The jump condition for the instruction (JLT, JGT, JEQ, JLE, JGE, JNE, JMP, NULL)
 */
Assembler::InstructionJump Assembler::parseInstructionJump(string instruction) {
    // Your code here:
    // for example if "JLT" appear at the comp field return enum label JLT
    if (instruction.find("JLT") != string::npos) {
        return JLT;
    }
    else if (instruction.find("JGT") != string::npos){
        return JGT;
    }
    else if (instruction.find("JEQ") != string::npos){
        return JEQ;
    }
    else if (instruction.find("JLE") != string::npos){
        return JLE;
    }
    else if (instruction.find("JGE") != string::npos){
        return JGE;
    }
    else if (instruction.find("JNE") != string::npos){
        return JNE;
    }
    else if (instruction.find("JMP") != string::npos){
        return JMP;
    }
    return NULL_JUMP;
}

/**
 * Parses the computation/op-code of the provided C-instruction
 * @param instruction The assembly language representation of a C-instruction.
 * @return The computation/op-code of the instruction (CONST_0, ... ,D_ADD_A , ... , NULL)
 */
Assembler::InstructionComp Assembler::parseInstructionComp(string instruction) {
    // Your code here:
    // for example if "0" appear at the comp field return CONST_0
    if (instruction.find("0") != string::npos) {
        return CONST_0;
    } else if (instruction.find("A+1") != string::npos) {
        return A_ADD_1;
    }else if (instruction.find("M+1") != string::npos) {
        return M_ADD_1;
    }else if (instruction.find("D+1") != string::npos) {
        return D_ADD_1;
    }else if (instruction.find("A-1") != string::npos) {
        return A_SUB_1;
    }else if (instruction.find("M-1") != string::npos) {
        return M_SUB_1;
    }else if (instruction.find("D-1") != string::npos) {
        return D_SUB_1;
    }else if (instruction.find("D+A") != string::npos || instruction.find("A+D") != string::npos) {
        return D_ADD_A;
    }else if (instruction.find("D+M") != string::npos || instruction.find("M+D") != string::npos) {
        return D_ADD_M;
    }else if (instruction.find("D-A") != string::npos) {
        return D_SUB_A;
    }else if (instruction.find("D-M") != string::npos) {
        return D_SUB_M;
    }else if (instruction.find("A-D") != string::npos) {
        return A_SUB_D;
    }else if (instruction.find("M-D") != string::npos) {
        return M_SUB_D;
    }else if (instruction.find("D&A") != string::npos || instruction.find("A&D") != string::npos) {
        return D_AND_A;
    }else if (instruction.find("D&M") != string::npos || instruction.find("M&D") != string::npos) {
        return D_AND_M;
    }else if (instruction.find("D|A") != string::npos || instruction.find("A|D") != string::npos) {
        return D_OR_A;
    }else if (instruction.find("D|M") != string::npos || instruction.find("M|D") != string::npos) {
        return D_OR_M;
    }else if (instruction.find("!A") != string::npos) {
        return NOT_A;
    }else if (instruction.find("!M") != string::npos) {
        return NOT_M;
    }else if (instruction.find("!D") != string::npos) {
        return NOT_D;
    }else if (instruction.find("-A") != string::npos) {
        return NEG_A;
    }else if (instruction.find("-D") != string::npos) {
        return NEG_D;
    }else if (instruction.find("-M") != string::npos) {
        return NEG_M;
    }else if (instruction.find("-1") != string::npos) {
        return CONST_NEG_1;
    }else if (instruction.find("1") != string::npos) {
        return CONST_1;
    }else if (instruction.find("=A") != string::npos || instruction.find("A;") != string::npos) {
        return VAL_A;
    }else if (instruction.find("=D") != string::npos || instruction.find("D;") != string::npos) {
        return VAL_D;
    }else if (instruction.find("=M") != string::npos || instruction.find("M;") != string::npos) {
        return VAL_M;
    }else if (instruction[0]=='A') {
        return VAL_A;
    }else if (instruction[0]=='D') {
        return VAL_D;
    }else if (instruction[0]=='M') {
        return VAL_M;
    }
    return NULL_COMP;
}

/**
 * Parses the symbol of the provided A/L-instruction
 * @param instruction The assembly language representation of a A/L-instruction.
 * @return A string containing either a label name (L-instruction),
 *         a variable name (A-instruction), or a constant integer value (A-instruction)
 */
string Assembler::parseSymbol(string instruction) {
    string result = "";
    InstructionType type = parseInstructionType(instruction);

    if(type == NULL_INSTRUCTION){
        return "";
    }else if(type == A_INSTRUCTION){
        for(auto& i : instruction){
            if(i!='@'){
                result = result + i;
            }
        }
        // std::cout<<"symbol: "<<result<<std::endl;
    }else if(type == L_INSTRUCTION){
        for(auto& i : instruction){
            if(i!='(' & i!=')'){
                result = result + i;
            }
        }
    }

    return result;
}

/**
 * Generates the binary bits of the dest part of a C-instruction
 * @param dest The destination of the instruction
 * @return A string containing the 3 binary dest bits that correspond to the given dest value.
 */
string Assembler::translateDest(InstructionDest dest) {
    
    string result = "000";
    if(dest==A){
        result = "100";
    }else if(dest==D){
        result = "010";
    }else if(dest==M){
        result = "001";
    }else if(dest==MD){
        result = "011";
    }else if(dest==AM){
        result = "101";
    }else if(dest==AD){
        result = "110";
    }else if(dest==AMD){
        result = "111";
    }
    return result;
}

/**
 * Generates the binary bits of the jump part of a C-instruction
 * @param jump The jump condition for the instruction
 * @return A string containing the 3 binary jump bits that correspond to the given jump value.
 */
string Assembler::translateJump(InstructionJump jump) {
    
    string result = "000";
    if(jump==JGT){
        result = "001";
    }else if(jump==JEQ){
        result = "010";
    }else if(jump==JGE){
        result = "011";
    }else if(jump==JLT){
        result = "100";
    }else if(jump==JNE){
        result = "101";
    }else if(jump==JLE){
        result = "110";
    }else if(jump==JMP){
        result = "111";
    }
    return result;
}

/**
 * Generates the binary bits of the computation/op-code part of a C-instruction
 * @param comp The computation/op-code for the instruction
 * @return A string containing the 7 binary computation/op-code bits that correspond to the given comp value.
 */
string Assembler::translateComp(InstructionComp comp) {
    
    string result = "";
    if(comp==CONST_0){
        result = "0101010";
    }else if(comp==CONST_1){
        result = "0111111";
    }else if(comp==CONST_NEG_1){
        result = "0111010";
    }else if(comp==VAL_D){
        result = "0001100";
    }else if(comp==VAL_A){
        result = "0110000";
    }else if(comp==NOT_D){
        result = "0001101";
    }else if(comp==VAL_A){
        result = "0110001";
    }else if(comp==NOT_A){
        result = "0110001";
    }else if(comp==NEG_D){
        result = "0001111";
    }else if(comp==NEG_A){
        result = "0110011";
    }else if(comp==D_ADD_1){
        result = "0011111";
    }else if(comp==A_ADD_1){
        result = "0110111";
    }else if(comp==D_SUB_1){
        result = "0001110";
    }else if(comp==A_SUB_1){
        result = "0110010";
    }else if(comp==D_ADD_A){
        result = "0000010";
    }else if(comp==D_SUB_A){
        result = "0010011";
    }else if(comp==A_SUB_D){
        result = "0000111";
    }else if(comp==D_AND_A){
        result = "0000000";
    }else if(comp==D_OR_A){
        result = "0010101";
    }else if(comp==VAL_M){
        result = "1110000";
    }else if(comp==NOT_M){
        result = "1110001";
    }else if(comp==NEG_M){
        result = "1110011";
    }else if(comp==M_ADD_1){
        result = "1110111";
    }else if(comp==M_SUB_1){
        result = "1110010";
    }else if(comp==D_ADD_M){
        result = "1000010";
    }else if(comp==D_SUB_M){
        result = "1010011";
    }else if(comp==M_SUB_D){
        result = "1000111";
    }else if(comp==D_AND_M){
        result = "1000000";
    }else if(comp==D_OR_M){
        result = "1010101";
    }
    return result;

}

/**
 * Generates the binary bits for an A-instruction, parsing the value, or looking up the symbol name.
 * @param symbol A string containing either a label name, a variable name, or a constant integer value
 * @param symbolTable The symbol table for looking up label/variable names
 * @return A string containing the 15 binary bits that correspond to the given sybmol.
 */
string Assembler::translateSymbol(string symbol, SymbolTable* symbolTable) {
    
    int num = 0 ;

    if(symbolTable->getSymbol(symbol)!=-1){
        num = symbolTable->getSymbol(symbol);
    }else{
        num = stoi(symbol);
        // std::cout<<symbol<<std::endl;
    }   

    string result = std::bitset<16>(num).to_string(); 

    return result;
}
