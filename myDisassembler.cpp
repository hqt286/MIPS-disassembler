#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <iomanip>
#include <utility>
enum INSTRUCTION_TYPE {R_type,I_type,J_type, None_type} ;
std::map<char,std::string> HexMap()
{
    std::map<char,std::string> storedHexMap;
    storedHexMap['0']  = "0000";
    storedHexMap['1']  = "0001";
    storedHexMap['2']  = "0010";
    storedHexMap['3']  = "0011";
    storedHexMap['4']  = "0100";
    storedHexMap['5']  = "0101";
    storedHexMap['6']  = "0110";
    storedHexMap['7']  = "0111";
    storedHexMap['8']  = "1000";
    storedHexMap['9']  = "1001";
    storedHexMap['a']  = "1010";
    storedHexMap['b']  = "1011";
    storedHexMap['c']  = "1100";
    storedHexMap['d']  = "1101";
    storedHexMap['e']  = "1110";
    storedHexMap['f']  = "1111";   

    return storedHexMap;        
}

std::map<std::string,std::string> R_Map()
{
    std::map<std::string,std::string> storedR_map;
    storedR_map["100000"] = "add";
    storedR_map["100001"] = "addu";
    storedR_map["100100"] = "and";
    storedR_map["001000"] = "jr";
    storedR_map["100111"] = "nor";
    storedR_map["100101"] = "or";
    storedR_map["101010"] = "slt";
    storedR_map["101011"] = "sltu";
    storedR_map["000000"] = "sll";
    storedR_map["000010"] = "srl";
    storedR_map["100010"] = "sub";
    storedR_map["100011"] = "subu";

    return storedR_map;
}

std::map<std::string,std::string> I_Map()
{
   std::map<std::string,std::string> storedI_map;

   storedI_map["001000"] = "addi";
   storedI_map["001001"] = "addiu";
   storedI_map["001100"] = "andi";
   storedI_map["000100"] = "beq";
   storedI_map["000101"] = "bne";
   storedI_map["100100"] = "lbu";
   storedI_map["100101"] = "lhu";
   storedI_map["110000"] = "ll";
   storedI_map["001111"] = "lui";
   storedI_map["100011"] = "lw";
   storedI_map["001101"] = "ori";
   storedI_map["001010"] = "slti";
   storedI_map["001011"] = "sltiu";
   storedI_map["101000"] = "sb";
   storedI_map["111000"] = "sc";
   storedI_map["101001"] = "sh";
   storedI_map["101011"] = "sw";

   return storedI_map;
}

std::string intToStringHex(int value)
{
    std::stringstream streamValue;
    streamValue << std::setfill('0') << std::setw(4) << std::hex << value;

    return streamValue.str();
}

std::map<std::string,std::string> register_Map()
{
    std::map<std::string,std::string> storeRegister_Map;

    storeRegister_Map["00000"] = "$zero";
    storeRegister_Map["00001"] = "$at";
    storeRegister_Map["00010"] = "$v0";
    storeRegister_Map["00011"] = "$v1";

    storeRegister_Map["00100"] = "$a0";
    storeRegister_Map["00101"] = "$a1";
    storeRegister_Map["00110"] = "$a2";
    storeRegister_Map["00111"] = "$a3";

    storeRegister_Map["01000"] = "$t0";
    storeRegister_Map["01001"] = "$t1";
    storeRegister_Map["01010"] = "$t2";
    storeRegister_Map["01011"] = "$t3";
    storeRegister_Map["01100"] = "$t4";
    storeRegister_Map["01101"] = "$t5";
    storeRegister_Map["01110"] = "$t6";
    storeRegister_Map["01111"] = "$t7";
    
    storeRegister_Map["10000"] = "$s0";
    storeRegister_Map["10001"] = "$s1";
    storeRegister_Map["10010"] = "$s2";
    storeRegister_Map["10011"] = "$s3";
    storeRegister_Map["10100"] = "$s4";
    storeRegister_Map["10101"] = "$s5";
    storeRegister_Map["10110"] = "$s6";
    storeRegister_Map["10111"] = "$s7";

    storeRegister_Map["11000"] = "$t8";
    storeRegister_Map["11001"] = "$t9";

    storeRegister_Map["11010"] = "$k0";
    storeRegister_Map["11011"] = "$k1";

    storeRegister_Map["11100"] = "$gp";
    storeRegister_Map["11101"] = "$sp";
    storeRegister_Map["11110"] = "$fp";
    storeRegister_Map["11111"] = "$ra";

    return storeRegister_Map;
}

std::string to2complement (std::string value)
{   
    std::string returnVariable = "";
    unsigned int i = value.size() - 1;

    while (value[i] != '1' && i >= 0) 
        i--;

    std::string first = value.substr(0,i);
    std::string second = value.substr(i,value.size() - i);

    for (auto a : first)
    {
        if (a == '1') 
            returnVariable.push_back('0');
        if (a == '0') 
            returnVariable.push_back('1');
    }

    returnVariable += second;
    return returnVariable;
}


bool UseUnsigned(std::string op)
{
    bool returnVariable = false;
    if (op == "addiu" || op == "addu" || op == "lbu" || op == "lhu" ||
        op == "sltiu" || op == "sltu" || op == "subu")
        returnVariable = true;
    return returnVariable;
}

std::string convertHexToBi(std::string inputLine)
{
    std::string BinaryValue = "";
    std::map<char,std::string> ASCII = HexMap();
    for (int i = 0; i < inputLine.size(); i++)
    {        
        auto found = ASCII.find(inputLine[i]);
        BinaryValue += found->second;
    }

    return BinaryValue;
}

INSTRUCTION_TYPE CheckType (std::string BinaryValue)
{
    std::string opCode = "";
    INSTRUCTION_TYPE type;
    opCode = BinaryValue.substr(0,6);
    std::map<std::string,std::string> Imap = I_Map();

    if (opCode == "000000")
        type = R_type;
    else if (opCode == "000010" || opCode == "000011")
        type = J_type;
    else if (Imap.find(opCode) != Imap.end())
        type = I_type;
    else
        type = None_type;

    return type;
}

bool Good_rd_rs_Rtype (std::string value)
{
    bool returnVariable = true;
     if (value == "$ra" || value == "$fp" || value == "$sp" || value == "$gp"
     || value == "$k0"
     || value == "$k1")
     returnVariable = false;

     return returnVariable;
}

std::string getSignedNumber(std::string value)
{
    std::string returnVariable = "";
    if (value[0] == '1')
    {
        std::string complement = to2complement (value);
        int Numberint = std::stoi(complement, nullptr, 2) * -1;
        returnVariable = std::to_string(Numberint); 
    }
    else
    {
        int Numberint = std::stoi(value, nullptr, 2);
        returnVariable = std::to_string(Numberint);
    }

    return returnVariable;
}

std::string getUnsignedNumber(std::string value)
{
    int Numberint = std::stoi(value, nullptr, 2);
    return std::to_string(Numberint);    
}


void processRtype(std::string BinaryValue, std::vector <std::string> & valid_output, std::vector <std::string> & invalid_output, int line_count)
{
    std::string rs = "", rt = "", rd = "", shamt = "", funct = "", result = "";

    rs = BinaryValue.substr(6,5);
    rt = BinaryValue.substr(11,5);
    rd = BinaryValue.substr(16,5);
    shamt = BinaryValue.substr(21,5);
    funct = BinaryValue.substr(26,6);

    auto regMap = register_Map();
    auto rTypeMap = R_Map();

    std::string Found_rs = regMap.find(rs)->second;
    std::string Found_rt = regMap.find(rt)->second;
    std::string Found_rd = regMap.find(rd)->second;
    auto Found_function  = rTypeMap.find(funct);

    // check error.

    if (Found_function == rTypeMap.end())
    {
        invalid_output.push_back("Error, cant find function " + funct + " at line " + std::to_string(line_count));
    }
    else if (!Good_rd_rs_Rtype(Found_rs))
    {
        invalid_output.push_back("rs can't be in " + Found_rs + " at line " + std::to_string(line_count));
    }
    else if (!Good_rd_rs_Rtype(Found_rt))
    {
        invalid_output.push_back("rt can't be in " + Found_rt + " at line " + std::to_string(line_count));  
    }
    else if (Found_rd == "$k0" || Found_rd == "$k1" || Found_rd == "$fp" || Found_rd == "$sp" || Found_rd == "$gp")
    {
        invalid_output.push_back("rd can't be in " + Found_rd + " at line " + std::to_string(line_count)); 
    }
    else if (Found_function->second == "sll" || Found_function->second == "srl")
    {
        result = "\t" + Found_function->second + "\t" + Found_rd + ", " + Found_rt + ", " + getUnsignedNumber(shamt);
        valid_output.push_back(result);
    }
    else
    {
        result = "\t" + Found_function->second + "\t" + Found_rd + ", " + Found_rs + ", " + Found_rt;
        valid_output.push_back(result);
    }
}

bool outputFormatIType1 (std::string Value)
{
    bool returnVariable = false;
    if (Value == "addi" || Value == "addiu" || Value == "andi" || 
        Value == "ori" || Value == "slti" || Value == "sltiu" || 
        Value == "lui")
        returnVariable = true;

    return returnVariable;
}

void processItype(std::string BinaryValue, std::vector <std::string> & valid_output, std::vector <std::string> & invalid_output, int line_count, std::map <std::string,int> & address_file)
{
    std::string rs = "", rt = "", immediate = "", result = "", op = "";
    op = BinaryValue.substr(0,6);
    rs = BinaryValue.substr(6,5);
    rt = BinaryValue.substr(11,5);
    immediate = BinaryValue.substr(16,16);

    auto regMap = register_Map();
    auto iTypeMap = I_Map();
    auto Found_function  = iTypeMap.find(op);

    std::string Found_rs = regMap.find(rs)->second;
    std::string Found_rt = regMap.find(rt)->second;

    if (Found_function == iTypeMap.end())
        invalid_output.push_back("Error, cant find function " + op + " at line " + std::to_string(line_count));
    
    else if (Found_function->second == "beq" || Found_function->second == "bne")
    {
        int position = std::stoi(getSignedNumber(immediate)); // get the number it wants to jump 3

        position = 1 + position + line_count; // this will be actual location were it shoud be (not memory address) -17
        int address_position = position * 4; // 68
        std::string address = "Addr_" + intToStringHex(address_position);

        result = "\t" + Found_function->second + "\t" + Found_rs + ", " + Found_rt + ", " + address;

        std::pair <std::string,int> checking (address,position);
        address_file.insert(checking);
        valid_output.push_back(result);
    }

    else if (outputFormatIType1(Found_function->second))
    {
        if (UseUnsigned(Found_function->second))
            immediate = getUnsignedNumber(immediate);
        else 
            immediate = getSignedNumber(immediate);

        result = "\t" + Found_function->second + "\t" + Found_rt + ", " + Found_rs + ", " + immediate;
        valid_output.push_back(result);
    }
        
    else
    {
        if (UseUnsigned(Found_function->second))
            immediate = getUnsignedNumber(immediate);
        else 
            immediate = getSignedNumber(immediate);

        result = "\t" + Found_function->second + "\t" + Found_rt + ", " + immediate + "(" + Found_rs + ")";
        valid_output.push_back(result);
    }
}

void evalEachLine(std::string inputLine, std::vector <std::string> & valid_output, std::vector <std::string> & invalid_output, int line_count, std::map <std::string,int> & address_file)
{
    if (inputLine.size() != 8)
        invalid_output.push_back("Cannot disassemble " + inputLine + " at line " + std::to_string(line_count));  
    else
        {
            std::string binaryValue =  convertHexToBi(inputLine);
            INSTRUCTION_TYPE type = CheckType(binaryValue);
            if (type == R_type)
                processRtype(binaryValue, valid_output, invalid_output, line_count);
             else if (type == I_type)
                processItype(binaryValue, valid_output, invalid_output, line_count, address_file);
             else
                invalid_output.push_back("Cannot disassemble " + inputLine + " at line " + std::to_string(line_count) + "not either I or R type");
        }   
}

std::string getInputName(std::string value)
{
    unsigned int i = value.size() - 1;

    while (value[i] != '.' && i >= 0) 
        i--;   
         
    return value.substr(0,i);
}

int main(int argc, char const *argv[])
{
    std::string eachLine;
    std::vector <std::string> valid_output;
    std::vector <std::string> invalid_output;
    std::map <std::string,int> address_file;
    int line_count = 0;
    if (argc == 2)
    {
    std::ifstream in (argv[1]);
    if (!in)
    {
        std::cout << "Cant open the file" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        while (!in.eof())
        {
           getline(in,eachLine, '\n');
           evalEachLine(eachLine, valid_output, invalid_output, line_count, address_file);
           line_count++;
        }
    }

    std::map <int,std::string> swapped_address_file;

    if (invalid_output.empty())
    {
        std::string output_name =  getInputName(argv[1]) + ".s";
        std::ofstream out (output_name);
        if (!address_file.empty())
        {
            for (auto a: address_file)
                swapped_address_file[a.second] = a.first;

            int index = 0;
            for (auto a : swapped_address_file)
            {
                auto vectorbegin = valid_output.begin();
                valid_output.insert(vectorbegin + index + a.first,a.second);
                index++;
            }
        }

        for (auto a : valid_output)
            out << a << std::endl;
    }
    else 
    {
        for (auto a : invalid_output)
            std::cout << a << std::endl;
    }
    }

    else
        std::cout << "please enter the object file" << std::endl;

    return EXIT_SUCCESS;
}
