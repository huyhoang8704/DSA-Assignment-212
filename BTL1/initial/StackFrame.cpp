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


//! 1
void iadd (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top();
        stack.pop();
        b = stack.top();
        stack.pop();

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
void fadd (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top();
        stack.pop();
        b = stack.top();
        stack.pop();

        if(a.type == FLOAT && b.type == FLOAT){
            frame c;
            c.data = float(a.data + b.data);
            c.type = FLOAT;
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

void isub (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
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
void fsub (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
    if(stack.stackSize() >1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if(a.type == FLOAT && b.type == FLOAT){
            frame c;
            c.data = float(b.data - a.data);
            c.type = FLOAT;
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

void imul (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
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

void fmul (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
    if(stack.stackSize() >1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if(a.type == FLOAT && b.type == FLOAT){
            frame c;
            c.data = float(b.data * a.data);
            c.type = FLOAT;
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

void idiv (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
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

void fdiv (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if((a.type == FLOAT) && (b.type == FLOAT)){
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
            throw TypeMisMatch(lineNumber);
        }
    }
    else {
        stack.clearStack();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void irem (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
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

void ineg (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
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

void fneg (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
    if(stack.stackSize() > 0){
        frame a;
        a = stack.top(); stack.pop();
        
        if(a.type == FLOAT){
            frame c;
            c.data = float(-a.data);
            c.type = FLOAT;
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

void iand (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
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

void ior (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
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

void ieq (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
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

void feq (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if((a.type == FLOAT) && (b.type == FLOAT)){
            frame c;
            int result = (a.data == b.data);
            if(result)  c.data = 1;
            else        c.data = 0;
            c.type = FLOAT;
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
void ineq (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
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

void fneq (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if((a.type == FLOAT) && (b.type == FLOAT)){
            frame c;
            int result = (a.data == b.data);
            if(!result)  c.data = 1;
            else        c.data = 0;
            c.type = FLOAT;
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

void ilt (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
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

void flt (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if(a.type == FLOAT && b.type == FLOAT){
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
void igt (StackFrame::myStack<frame>& stack , StackFrame::myLocalVariableArray& array , fstream& file , int lineNumber){

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

        if(instruction == "iadd") {

        }
    }
}