#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

//Global maps:
map <int, string> registers;
map <int, string> Rfuncts;
map <int, string> Ifuncts;

int binToDec(string s){
    int i = stoi(s);
    int num = 0;
    int b = 1;
    int temp = i;
    
    while (temp) {
        int j = temp % 10;
        temp = temp / 10;
        num += j * b;
        b = b * 2;
    }
    return num;
}

void populateMaps(){
    registers.insert(pair <int, string> (0, "zero (R0)"));
    registers.insert(pair <int, string> (1, "at (R1)"  ));
    registers.insert(pair <int, string> (2, "v0 (R2)"  ));
    registers.insert(pair <int, string> (3, "v1 (R3)"  ));
    registers.insert(pair <int, string> (4, "a0 (R4)"  ));
    registers.insert(pair <int, string> (5, "a1 (R5)"  ));
    registers.insert(pair <int, string> (6, "a2 (R6)"  ));
    registers.insert(pair <int, string> (7, "a3 (R7)"  ));
    registers.insert(pair <int, string> (8, "t0 (R8)"  ));
    registers.insert(pair <int, string> (9, "t1 (R9)"  ));
    registers.insert(pair <int, string> (10, "t2 (R10)"));
    registers.insert(pair <int, string> (11, "t3 (R11)"));
    registers.insert(pair <int, string> (12, "t4 (R12)"));
    registers.insert(pair <int, string> (13, "t5 (R13)"));
    registers.insert(pair <int, string> (14, "t6 (R14)"));
    registers.insert(pair <int, string> (15, "t7 (R15)"));
    registers.insert(pair <int, string> (16, "s0 (R16)"));
    registers.insert(pair <int, string> (17, "s1 (R17)"));
    registers.insert(pair <int, string> (18, "s2 (R18)"));
    registers.insert(pair <int, string> (19, "s3 (R19)"));
    registers.insert(pair <int, string> (20, "s4 (R20)"));
    registers.insert(pair <int, string> (21, "s5 (R21)"));
    registers.insert(pair <int, string> (22, "s6 (R22)"));
    registers.insert(pair <int, string> (23, "s7 (R23)"));
    registers.insert(pair <int, string> (24, "t8 (R24)"));
    registers.insert(pair <int, string> (25, "t9 (R25)"));
    registers.insert(pair <int, string> (26, "k0 (R26)"));
    registers.insert(pair <int, string> (27, "k1 (R27)"));
    registers.insert(pair <int, string> (28, "gp (R28)"));
    registers.insert(pair <int, string> (29, "sp (R29)"));
    registers.insert(pair <int, string> (30, "fp (R30)"));
    registers.insert(pair <int, string> (31, "ra (R31)"));
    
    Rfuncts.insert(pair <int, string> (0,  "sll"  ));
    Rfuncts.insert(pair <int, string> (2,  "srl"  ));
    Rfuncts.insert(pair <int, string> (3,  "swcl" ));
    Rfuncts.insert(pair <int, string> (8,  "jr"   ));
    Rfuncts.insert(pair <int, string> (16, "mfhi" ));
    Rfuncts.insert(pair <int, string> (18, "mfl"  ));
    Rfuncts.insert(pair <int, string> (24, "multu"));
    Rfuncts.insert(pair <int, string> (25, "sra"  ));
    Rfuncts.insert(pair <int, string> (26, "div"  ));
    Rfuncts.insert(pair <int, string> (27, "divu" ));
    Rfuncts.insert(pair <int, string> (32, "add"  ));
    Rfuncts.insert(pair <int, string> (33, "addu" ));
    Rfuncts.insert(pair <int, string> (34, "sub"  ));
    Rfuncts.insert(pair <int, string> (35, "subu" ));
    Rfuncts.insert(pair <int, string> (36, "and"  ));
    Rfuncts.insert(pair <int, string> (37, "or"   ));
    Rfuncts.insert(pair <int, string> (39, "nor"  ));
    Rfuncts.insert(pair <int, string> (42, "slt"  ));
    Rfuncts.insert(pair <int, string> (43, "sltu" ));
    
    Ifuncts.insert(pair <int, string> (4,  "beq"  ));
    Ifuncts.insert(pair <int, string> (5,  "bne"  ));
    Ifuncts.insert(pair <int, string> (8,  "addi" ));
    Ifuncts.insert(pair <int, string> (9,  "addiu"));
    Ifuncts.insert(pair <int, string> (10, "slti" ));
    Ifuncts.insert(pair <int, string> (11, "sltiu"));
    Ifuncts.insert(pair <int, string> (12, "andi" ));
    Ifuncts.insert(pair <int, string> (13, "ori"  ));
    Ifuncts.insert(pair <int, string> (15, "lui"  ));
    Ifuncts.insert(pair <int, string> (35, "lw"   ));
    Ifuncts.insert(pair <int, string> (37, "lhu"  ));
    Ifuncts.insert(pair <int, string> (40, "sb"   ));
    Ifuncts.insert(pair <int, string> (43, "sw"   ));
    Ifuncts.insert(pair <int, string> (48, "ll"   ));
    Ifuncts.insert(pair <int, string> (49, "lwc1" ));
    Ifuncts.insert(pair <int, string> (53, "ldc1" ));
    Ifuncts.insert(pair <int, string> (56, "sc"   ));
}

void I_type(string opcode, string rs, string rt, string immBin){
    rs = registers.at(binToDec(rs));
    rt = registers.at(binToDec(rt));
    int immDec = binToDec(immBin);
    int oppCodeDec = binToDec(opcode);
    string type = Ifuncts.at(oppCodeDec);
    cout << "\nInstruction Type: I" << endl;
    cout << "Operation: " << type << endl;
    cout << "Rs: " << rs << endl;
    cout << "Rt: " << rt << endl;
    cout << "Immediate: " << immDec << endl;
}

void R_type(string rs, string rt, string rd, string funct){
    rs = registers.at(binToDec(rs));
    rt = registers.at(binToDec(rt));
    rd = registers.at(binToDec(rd));
    int numFunc = binToDec(funct);
    string type = Rfuncts.at(numFunc);
    cout << "\nInstruction Type: R" << endl;
    cout << "Operation: " << type << endl;
    cout << "Rs: " << rs << endl;
    cout << "Rt: " << rt << endl;
    cout << "Rd: " << rd << endl;
    cout << "Shamt: 0\n";
    cout << "Funct: " << numFunc << endl;
}

void J_type(string opcode, string address){
    string type = "";

    if(opcode == "000011")
        type = "jal";
    else
        type = "j";
    cout << "\nInstruction Type: J" << endl;
    cout << "Operation: " << type << endl;
    cout << "Address: " << stoll(address, nullptr, 2) << endl;
}

void MIPS_DECODER(string mCode){
    string opcode = "000000";
    string funct = "000000";
    string rs = "00000";
    string rt = "00000";
    string rd = "00000";
    string shamt = "00000";
    string immediate = "0000000000000000";
    string address = "00000000000000000000000000";
    for (int i = 0; i < 32; i++){
        if(i < 6)
            opcode[i] = mCode[i];
        if(i > 5 && i < 11)
            rs[i - 6] = mCode[i];
        if(i > 10 && i < 16)
            rt[i - 11] = mCode[i];
        if(i > 15 && i < 21)
            rd[i - 16] = mCode[i];
        if(i > 15)
            immediate[i - 16] = mCode[i];
        if(i > 25)
            funct[i - 26] = mCode[i];
        if(i > 5)
            address[i - 6] = mCode[i];
    }
   
    if(opcode == "000000")
        R_type(rs, rt, rd, funct);
    else if(opcode == "000010" || opcode == "000011")
        J_type(opcode, address);
    else
        I_type(opcode, rs, rt, immediate);
}
int main(){
    populateMaps();
    string machineCode;
    cout << "Enter an instruction in machine code: \n\n";
    cin >> machineCode;
    MIPS_DECODER(machineCode);
}






//R tests:
//1)
//  00000001000010011000100000100000
//  add $s1, $t0, $t1
//
//2)
//  00000010000100010110000000100010
//  sub $t4, $s0, $s1
//3)
//  00000010110101011011100000101010
//  slt $s7, $s6, $s5
//4)
//  00000010000010000000000000000000
//  sll $t0, $s0, 0



//I tests:
//1)
//  00110100001001000000000000000000
//  ori $a0, $at, 0
//
//2)
//  00101010111010010000000001000101
//  slti $t1, $s7, 69
//3)
//  00100001001010000000000001001111
//  addi $t0, $t1, 79



//J tests:
//1)
//  00001000000100000000000000000001
//  j LABEL
//
//2)
//  //Need to get sample test.
//  jal LABEL