#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;


string extractInstruction(string str);
string extractValue(string str);
bool expWithValue(string str);

string extractInstruction(string str){
    int size = str.length();
    string instruction;
    for(int i = 0; i < size; i++){
        if(str[i] != ' '){
            instruction += str[i];
        } else{
            break;
        }
    }
    return instruction;
}

string extractValue(string str){
    int size = str.length();
    bool isSpace = false;
    string value;

    for(int i = 0; i < size; i++){
        if(str[i] == ' '){
            isSpace = true;
        }
        if(isSpace){
            value += str[i];
        }
    }
    return value;
}

bool expWithValue(string str){
    for(unsigned int i = 0; i < str.length(); i ++){
        if(str[i] == ' ') return true;
    }
    return false;
}


//! Nhóm lệnh phép toán (Arithmetic Instructions)
void iadd (StackFrame::myStack<frame>& stack  , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if((a.type == INTEGER) && (b.type == INTEGER)){
            frame c;
            c.data = int(a.data + b.data);
            c.type = INTEGER;
            stack.push(c);
        }
        else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    }
    else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

//! 2
void fadd (StackFrame::myStack<frame>& stack ,  fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        frame c;
        c.data = float(a.data + b.data);
        c.type = FLOAT;
    }
    else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void isub (StackFrame::myStack<frame>& stack  , fstream& file , int lineNumber){
    if(stack.stackSize() >1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if(a.type == INTEGER && b.type == INTEGER){
            frame c;
            c.data = int(b.data - a.data);
            c.type = INTEGER;
            stack.push(c);
        } else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
    
}
void fsub (StackFrame::myStack<frame>& stack  , fstream& file , int lineNumber){
    if(stack.stackSize() >1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        frame c;
        c.data = float(b.data - a.data);
        c.type = FLOAT;
        stack.push(c);
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
    
}

void imul (StackFrame::myStack<frame>& stack  , fstream& file , int lineNumber){
    if(stack.stackSize() >1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if(a.type == INTEGER && b.type == INTEGER){
            frame c;
            c.data = int(b.data * a.data);
            c.type = INTEGER;
            stack.push(c);
        } else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
    
}

void fmul (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() >1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        frame c;
        c.data = float(b.data * a.data);
        c.type = FLOAT;
        stack.push(c);
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
    
}

void idiv (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if((a.type == INTEGER) && (b.type == INTEGER)){
            if(a.data == 0){
                stack.clearStack();
                file.close();
                throw DivideByZero(lineNumber);
            } else {
                frame c;
                c.data = int(b.data / a.data);
                c.type = INTEGER;
                stack.push(c);
            }
        }
        else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    }
    else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void fdiv (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if(a.data == 0){
            stack.clearStack();
            file.close();
            throw DivideByZero(lineNumber);
        } else {
            frame c;
            c.data = float(b.data / a.data);
            c.type = FLOAT;
            stack.push(c);
        }
    }
    else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void irem (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if((a.type == INTEGER) && (b.type == INTEGER)){
            if(a.data == 0){
                stack.clearStack();
                file.close();
                throw DivideByZero(lineNumber);
            } else {
                frame c;
                c.data = int(a.data - (a.data / b.data) * b.data);
                c.type = INTEGER;
                stack.push(c);
            }
        } else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void ineg (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 0){
        frame a;
        a = stack.top(); stack.pop();

        if(a.type == INTEGER){
            frame c;
            c.data = int(-a.data);
            c.type = INTEGER;
            stack.push(c);
        } else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void fneg (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 0){
        frame a;
        a = stack.top(); stack.pop();
        
        frame c;
        c.data = float(-a.data);
        c.type = FLOAT;
        stack.push(c);
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void iand (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if((a.type == INTEGER) && (b.type == INTEGER)){
            int result = int(a.data) & int(b.data);
            frame c;
            c.data = result;
            c.type = INTEGER;
            stack.push(c);
        } else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void ior (StackFrame::myStack<frame>& stack ,  fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if((a.type == INTEGER) && (b.type == INTEGER)){
            int result = int(a.data) | int(b.data);
            frame c;
            c.data = result;
            c.type = INTEGER;
            stack.push(c);
        } else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void ieq (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if((a.type == INTEGER) && (b.type == INTEGER)){
            frame c;
            int result = (a.data == b.data);
            if(result)  c.data = 1;
            else        c.data = 0;
            c.type = INTEGER;
            stack.push(c);
        } else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void feq (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        frame c;
        int result = (a.data == b.data);
        if(result)  c.data = 1;
        else        c.data = 0;
        c.type = FLOAT;
        stack.push(c);
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}
void ineq (StackFrame::myStack<frame>& stack ,fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if((a.type == INTEGER) && (b.type == INTEGER)){
            frame c;
            int result = (a.data == b.data);
            if(!result)  c.data = 1;
            else        c.data = 0;
            c.type = INTEGER;
            stack.push(c);
        } else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void fneq (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        frame c;
        int result = (a.data == b.data);
        if(!result)  c.data = 1;
        else        c.data = 0;
        c.type = FLOAT;
        stack.push(c);
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void ilt (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if(a.type == INTEGER && b.type == INTEGER){
            frame c;
            int result = (a.data > b.data);
            if(result)  c.data = 1;
            else        c.data = 0;
            c.type = INTEGER;
            stack.push(c);
        } else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void flt (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        frame c;
        int result = (a.data > b.data);
        if(result)  c.data = 1;
        else        c.data = 0;
        c.type = FLOAT;
        stack.push(c);
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}
void igt (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if(a.type == INTEGER && b.type == INTEGER){
            frame c;
            int result = (a.data < b.data);
            if(result)  c.data = 1;
            else        c.data = 0;
            c.type = INTEGER;
            stack.push(c);
        } else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void fgt (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        frame c;
        int result = (a.data < b.data);
        if(result)  c.data = 1;
        else        c.data = 0;
        c.type = FLOAT;
        stack.push(c);
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void ibnot (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.stackSize() > 0){
        frame a;
        a = stack.top(); stack.pop();
        if(a.type == INTEGER){
            frame c;
            if(a.data == 0) c.data = 1;
            else c.data = 0;
            c.type = INTEGER;
            stack.push(c);
        } else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}


//! Nhóm lệnh nạp và lưu (Load and Store Instructions)
void iconst (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber , string value){
    if(stack.isFull()){
        stack.clearStack();
        file.close();
        throw StackFull(lineNumber);
    } else {
        frame c;
        c.data = stoi(value);
        c.type = INTEGER;
        stack.push(c);
    }
}
void fconst (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber , string value){
    if(stack.isFull()){
        stack.clearStack();
        file.close();
        throw StackFull(lineNumber);
    } else {
        frame c;
        c.data = stof(value);
        c.type = FLOAT;
        stack.push(c);
    }
}

void iload (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber , string value){
    int index = stoi(value);
    if(array.outOfRange(index)){
        stack.clearStack();
        file.close();
        throw ArrayOutOfRange(lineNumber);
    } else {
        if(!array.checkOccupiedIndex(index)){
            stack.clearStack();
            file.close();
            throw UndefinedVariable(lineNumber);
        } else {
            if(array.getDataType(index) != INTEGER){
                stack.clearStack();
                file.close();
                throw TypeMisMatch(lineNumber);
            } else {
                if(stack.isFull()) {
                    stack.clearStack();
                    file.close();
                    throw StackFull(lineNumber);
                } else {
                    frame c;
                    c.data = (int) array.getValue(index);
                    c.type = INTEGER;
                    stack.push(c);
                }
            }
        }
    }
}

void fload (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber , string value){
    int index = stoi(value);
    if(array.outOfRange(index)){
        stack.clearStack();
        file.close();
        throw ArrayOutOfRange(lineNumber);
    } else {
        if(!array.checkOccupiedIndex(index)){
            stack.clearStack();
            file.close();
            throw UndefinedVariable(lineNumber);
        } else {
            if(array.getDataType(index) != INTEGER){
                stack.clearStack();
                file.close();
                throw TypeMisMatch(lineNumber);
            } else {
                if(stack.isFull()) {
                    stack.clearStack();
                    file.close();
                    throw StackFull(lineNumber);
                } else {
                    frame c;
                    c.data = (float) array.getValue(index);
                    c.type = FLOAT;
                    stack.push(c);
                }
            }
        }
    }
}

void istore (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber , string value){
    int index = stoi(value);
    if(array.outOfRange(index)){
        stack.clearStack();
        file.close();
        throw ArrayOutOfRange(lineNumber);
    } else {
        if(stack.isEmpty()){
            stack.clearStack();
            file.close();
            throw StackEmpty(lineNumber);
        } else {
            frame a;
            a = stack.top(); stack.pop();
            if(a.type == INTEGER){
                array.setNewValue(a.data,a.type,index);
            } else {
                stack.clearStack();
                file.close();
                throw TypeMisMatch(lineNumber);
            }
        }
    }
}

void fstore (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber , string value){
    int index = stoi(value);
    if(array.outOfRange(index)){
        stack.clearStack();
        file.close();
        throw ArrayOutOfRange(lineNumber);
    } else {
        if(stack.isEmpty()){
            stack.clearStack();
            file.close();
            throw StackEmpty(lineNumber);
        } else {
            frame a;
            a = stack.top(); stack.pop();
            if(a.type == FLOAT){
                array.setNewValue(a.data,a.type,index);
            } else {
                stack.clearStack();
                file.close();
                throw TypeMisMatch(lineNumber);
            }
        }
    }
}

//! Nhóm lệnh chuyển đổi kiểu (Type conversion Instructions)

void i2f (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber , string value){
    if(stack.stackSize() > 0){
        frame a;
        a = stack.top(); stack.pop();
        if(a.type == INTEGER){
            a.type = FLOAT;
            stack.push(a);
        } else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}
void f2i (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber , string value){
    if(stack.stackSize() > 0){
        frame a;
        a = stack.top(); stack.pop();
        if(a.type == FLOAT){
            a.type = INTEGER;
            stack.push(a);
        } else {
            stack.clearStack();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}
//! Nhóm lệnh quản lý trạng thái ngăn xếp toán hạng (Operand Stack Management Instructions)
void top (StackFrame::myStack<frame>& stack , fstream& file , int lineNumber){
    if(stack.isEmpty()){
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
    else{
        frame topData;
        topData = stack.top();
        if(topData.type == INTEGER){
            cout << (int)topData.data << "\n";
        }
        else if(topData.type == FLOAT){
            cout << (float)topData.data << "\n";
        }
    }
}
//! Nhóm lệnh quản lý biến cục bộ (Local Variable Management Instructions)
void val (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber , string value){
    int index = stoi(value);
    if(array.outOfRange(index)){
        stack.clearStack();
        file.close();
        throw ArrayOutOfRange(lineNumber);
    }
    else{
        if(!array.checkOccupiedIndex(index)){
            stack.clearStack();
            file.close();
            throw UndefinedVariable(lineNumber);
        }
        else{
            if(array.getDataType(index) == INTEGER){
                cout << (int)array.getValue(index) << "\n";
            }
            else{
                cout << (float)array.getValue(index) << "\n";
            }
        }
    }
}





StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarArrSize(LOCAL_VARIABLE_ARRAY_SIZE) {}


void StackFrame::run(string filename) {
    myStack<frame> stack;
    myLocalVariableArray array;

    fstream file;
    string line;

    int lineNumber = 0;

    file.open(filename, ios::in);
    while(!file.eof()){
        getline(file, line);
        lineNumber ++; 
        string instruction;
        string value;
        instruction = extractInstruction(line);
        value = extractValue(line);

        // Nhóm lệnh phép toán (Arithmetic Instructions)
        if(instruction == "iadd")       iadd(stack,file,lineNumber);
        else if (instruction == "fadd") fadd(stack,file,lineNumber);
        else if (instruction == "isub") isub(stack,file,lineNumber);
        else if (instruction == "fsub") fsub(stack,file,lineNumber);
        else if (instruction == "imul") imul(stack,file,lineNumber);
        else if (instruction == "fmul") fmul(stack,file,lineNumber);
        else if (instruction == "idiv") idiv(stack,file,lineNumber);
        else if (instruction == "fdiv") fdiv(stack,file,lineNumber);
        else if (instruction == "irem") irem(stack,file,lineNumber);
        else if (instruction == "ineg") ineg(stack,file,lineNumber);
        else if (instruction == "fneg") fneg(stack,file,lineNumber);
        else if (instruction == "iand") iand(stack,file,lineNumber);
        else if (instruction == "ior")  ior(stack,file,lineNumber);
        else if (instruction == "ieq")  ieq(stack,file,lineNumber);
        else if (instruction == "feq")  feq(stack,file,lineNumber);
        else if (instruction == "ineq") ineq(stack,file,lineNumber);
        else if (instruction == "fneq") fneq(stack,file,lineNumber);
        else if (instruction == "ilt")  ilt(stack,file,lineNumber);
        else if (instruction == "flt")  flt(stack,file,lineNumber);
        else if (instruction == "igt")  igt(stack,file,lineNumber);
        else if (instruction == "fgt")  fgt(stack,file,lineNumber);
        else if (instruction == "ibnot")ibnot(stack,file,lineNumber);

        // Nhóm lệnh nạp và lưu (Load and Store Instructions)
        else if (instruction == "iconst")    iconst(stack,array,file,lineNumber,value);
        else if (instruction == "fconst")    fconst(stack,array,file,lineNumber,value);
        else if (instruction == "iload")     iload(stack,array,file,lineNumber,value);
        else if (instruction == "fload")     fload(stack,array,file,lineNumber,value);
        else if (instruction == "istore")    istore(stack,array,file,lineNumber,value);
        else if (instruction == "fstore")    fstore(stack,array,file,lineNumber,value);

        // Nhóm lệnh chuyển đổi kiểu (Type conversion Instructions)
        else if (instruction == "i2f")       i2f(stack,file,lineNumber,value);
        else if (instruction == "f2i")       f2i(stack,file,lineNumber,value);

        // Nhóm lệnh quản lý trạng thái ngăn xếp toán hạng (Operand Stack Management Instructions)
        else if (instruction == "top")       top(stack,file,lineNumber);


        // Nhóm lệnh quản lý biến cách bộ (Local Variable Management Instructions)
        else if (instruction == "val") val(stack,array,file,lineNumber,value);

    }
}