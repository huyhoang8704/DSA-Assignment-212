#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;


string extractInstruction(string str);
string extractValue(string str);
string removeSpaces(const string &str);

string removeSpaces(const string &str) {
    string result;
    result.reserve(str.length());

    for (char c : str) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}
string extractInstruction(string str){
    int size = str.length();
    string instruction;
    for(int i = 0; i < size; i++){
        if(str[i] != ' ') instruction += str[i];
        else break;
    }
    return instruction;
}

string extractValue(string str){
    int size = str.length();
    bool isSpace = false;
    string value;

    for(int i = 0; i < size; i++){
        if(str[i] == ' ') isSpace = true;
        if(isSpace) value += str[i];
    }
    return value;
}

//! Nhóm lệnh phép toán (Arithmetic Instructions)
void iadd (StackFrame::myStack<frame>& stack  ,StackFrame::AVLTree<frame,string>& localAVLTree ,fstream& file , int lineNumber){
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
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    }
    else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

//! 2
void fadd (StackFrame::myStack<frame>& stack,StackFrame::AVLTree<frame,string>& localAVLTree ,  fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        frame c;
        c.data = float(a.data + b.data);
        c.type = FLOAT;
        stack.push(c);
    }
    else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void isub (StackFrame::myStack<frame>& stack  ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
    
}
void fsub (StackFrame::myStack<frame>& stack  ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
    
}

void imul (StackFrame::myStack<frame>& stack  ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
    
}

void fmul (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
    
}

void idiv (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();
        if((a.type == INTEGER) && (b.type == INTEGER)){
            if((int)a.data == 0){
                stack.clearStack();
                localAVLTree.destroyTree();
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
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    }
    else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void fdiv (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if(a.data == 0){
            stack.clearStack();
            localAVLTree.destroyTree();
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
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void irem (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
    if(stack.stackSize() > 1){
        frame a,b;
        a = stack.top(); stack.pop();
        b = stack.top(); stack.pop();

        if((a.type == INTEGER) && (b.type == INTEGER)){
            if(a.data == 0){
                stack.clearStack();
                localAVLTree.destroyTree();
                file.close();
                throw DivideByZero(lineNumber);
            } else {
                frame c;
                c.data = int(b.data - int(b.data / a.data) * a.data);
                c.type = INTEGER;
                stack.push(c);
            }
        } else {
            stack.clearStack();
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void ineg (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void fneg (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
    if(stack.stackSize() > 0){
        frame a;
        a = stack.top(); stack.pop();
        
        frame c;
        c.data = float(-a.data);
        c.type = FLOAT;
        stack.push(c);
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void iand (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void ior (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree,  fstream& file , int lineNumber){
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
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void ieq (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void feq (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}
void ineq (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree,fstream& file , int lineNumber){
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
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void fneq (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void ilt (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void flt (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}
void igt (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void fgt (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}

void ibnot (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
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
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}


//! Nhóm lệnh nạp và lưu (Load and Store Instructions)
void iconst (StackFrame::myStack<frame>& stack ,StackFrame::AVLTree<frame,string>& localAVLTree , fstream& file , int lineNumber , string value){
    if(stack.isFull()){
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackFull(lineNumber);
    } else {
        frame c;
        c.data = stoi(value);
        c.type = INTEGER;
        stack.push(c);
    }
}
void fconst (StackFrame::myStack<frame>& stack , StackFrame::AVLTree<frame,string>& localAVLTree , fstream& file , int lineNumber , string value){
    if(stack.isFull()){
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackFull(lineNumber);
    } else {
        frame c;
        c.data = stof(value);
        c.type = FLOAT;
        stack.push(c);
    }
}

void iload (StackFrame::myStack<frame>& stack , StackFrame::AVLTree<frame,string>& localAVLTree , fstream& file , int lineNumber , string value){
    if(localAVLTree.search(value)) {
        frame c = localAVLTree.search(value)->getFrame();
        if(c.type == INTEGER) {
            if(!stack.isFull()) stack.push(c);
            else {
                stack.clearStack();
                localAVLTree.destroyTree();
                file.close();
                throw StackFull(lineNumber);
            }
        } else {
            stack.clearStack();
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw UndefinedVariable(lineNumber);
    }
}

void fload (StackFrame::myStack<frame>& stack , StackFrame::AVLTree<frame,string>& localAVLTree , fstream& file , int lineNumber , string value){
    if(localAVLTree.search(value)) {
        frame c = localAVLTree.search(value)->getFrame();
        if(c.type == FLOAT) {
            if(!stack.isFull()) stack.push(c);
            else {
                stack.clearStack();
                localAVLTree.destroyTree();
                file.close();
                throw StackFull(lineNumber);
            }
        } else {
            stack.clearStack();
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    }
}

void istore (StackFrame::myStack<frame>& stack , StackFrame::AVLTree<frame,string>& localAVLTree , fstream& file , int lineNumber , string value){
    if(localAVLTree.getSize() < (LOCAL_VARIABLE_ARRAY_SIZE/2)) {
        if(!stack.isEmpty()) {
            frame c = stack.top(); stack.pop();
            if(localAVLTree.search(value)) {
                if(c.type == INTEGER) localAVLTree.updateData(value,c);
                else {
                    stack.clearStack();
                    localAVLTree.destroyTree();
                    file.close();
                    throw TypeMisMatch(lineNumber);
                }
            } else {
                if(c.type == INTEGER) localAVLTree.insert(value,c);
                else {
                    stack.clearStack();
                    localAVLTree.destroyTree();
                    file.close();
                    throw TypeMisMatch(lineNumber); 
                }
            }
        } else {
            stack.clearStack();
            localAVLTree.destroyTree();
            file.close();
            throw StackEmpty(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw LocalSpaceFull(lineNumber);
    }
}

void fstore (StackFrame::myStack<frame>& stack , StackFrame::AVLTree<frame,string>& localAVLTree , fstream& file , int lineNumber , string value){
    if(localAVLTree.getSize() < (LOCAL_VARIABLE_ARRAY_SIZE/2)) {
        if(!stack.isEmpty()) {
            frame c = stack.top(); stack.pop();
            if(localAVLTree.search(value)) {
                if(c.type == FLOAT) localAVLTree.updateData(value,c);
                else {
                    stack.clearStack();
                    localAVLTree.destroyTree();
                    file.close();
                    throw TypeMisMatch(lineNumber);
                }
            } else {
                if(c.type == FLOAT) localAVLTree.insert(value,c);
                else {
                    stack.clearStack();
                    localAVLTree.destroyTree();
                    file.close();
                    throw TypeMisMatch(lineNumber); 
                }
            }
        } else {
            stack.clearStack();
            localAVLTree.destroyTree();
            file.close();
            throw StackEmpty(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw LocalSpaceFull(lineNumber);
    }
}

//! Nhóm lệnh chuyển đổi kiểu (Type conversion Instructions)

void i2f (StackFrame::myStack<frame>& stack , StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber , string value){
    if(stack.stackSize() > 0){
        frame a = stack.top(); stack.pop();
        if(a.type == INTEGER){
            a.type = FLOAT;
            stack.push(a);
        } else {
            stack.clearStack();
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}
void f2i (StackFrame::myStack<frame>& stack , StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber , string value){
    if(stack.stackSize() > 0){
        frame a = stack.top(); stack.pop();
        if(a.type == FLOAT){
            a.type = INTEGER;
            stack.push(a);
        } else {
            stack.clearStack();
            localAVLTree.destroyTree();
            file.close();
            throw TypeMisMatch(lineNumber);
        }
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw StackEmpty(lineNumber);
    }
}
//! Nhóm lệnh quản lý trạng thái ngăn xếp toán hạng (Operand Stack Management Instructions)
void top (StackFrame::myStack<frame>& stack , StackFrame::AVLTree<frame,string>& localAVLTree, fstream& file , int lineNumber){
    if(stack.isEmpty()){
        stack.clearStack();
        localAVLTree.destroyTree();
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
void val (StackFrame::myStack<frame>& stack , StackFrame::AVLTree<frame,string>& localAVLTree , fstream& file , int lineNumber , string value){
    if(localAVLTree.search(value)) {
        if(localAVLTree.search(value)->getFrame().type == INTEGER) cout << (int)localAVLTree.search(value)->getFrame().data << "\n";
        else if(localAVLTree.search(value)->getFrame().type == FLOAT) cout << (float)localAVLTree.search(value)->getFrame().data << "\n";
    } else {
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw UndefinedVariable(lineNumber);
    }
}
void par (StackFrame::myStack<frame>& stack , StackFrame::AVLTree<frame,string>& localAVLTree , fstream& file , int lineNumber , string value){
    if(localAVLTree.search(value)){
        if(localAVLTree.searchParent(value)) cout << localAVLTree.searchParent(value) ->getKey() <<endl;
        else cout << "null" <<endl;
    }
    else{
        stack.clearStack();
        localAVLTree.destroyTree();
        file.close();
        throw UndefinedVariable(lineNumber);              
    }
        
}




StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarArrSize(LOCAL_VARIABLE_ARRAY_SIZE) {}


void StackFrame::run(string filename) {
    myStack<frame> stack;
    AVLTree<frame,string> localAVLTree;

    fstream file;
    string line;

    int lineNumber = 0;

    file.open(filename, ios::in);
    while(!file.eof()){
        getline(file, line);
        lineNumber ++; 
        string instruction;
        string a;
        instruction = extractInstruction(line);
        a = extractValue(line);
        string value = removeSpaces(a);

        // Nhóm lệnh phép toán (Arithmetic Instructions)
        if(instruction == "iadd")       iadd(stack,localAVLTree,file,lineNumber);
        else if (instruction == "fadd") fadd(stack,localAVLTree,file,lineNumber);
        else if (instruction == "isub") isub(stack,localAVLTree,file,lineNumber);
        else if (instruction == "fsub") fsub(stack,localAVLTree,file,lineNumber);
        else if (instruction == "imul") imul(stack,localAVLTree,file,lineNumber);
        else if (instruction == "fmul") fmul(stack,localAVLTree,file,lineNumber);
        else if (instruction == "idiv") idiv(stack,localAVLTree,file,lineNumber);
        else if (instruction == "fdiv") fdiv(stack,localAVLTree,file,lineNumber);
        else if (instruction == "irem") irem(stack,localAVLTree,file,lineNumber);
        else if (instruction == "ineg") ineg(stack,localAVLTree,file,lineNumber);
        else if (instruction == "fneg") fneg(stack,localAVLTree,file,lineNumber);
        else if (instruction == "iand") iand(stack,localAVLTree,file,lineNumber);
        else if (instruction == "ior")  ior(stack,localAVLTree,file,lineNumber);
        else if (instruction == "ieq")  ieq(stack,localAVLTree,file,lineNumber);
        else if (instruction == "feq")  feq(stack,localAVLTree,file,lineNumber);
        else if (instruction == "ineq") ineq(stack,localAVLTree,file,lineNumber);
        else if (instruction == "fneq") fneq(stack,localAVLTree,file,lineNumber);
        else if (instruction == "ilt")  ilt(stack,localAVLTree,file,lineNumber);
        else if (instruction == "flt")  flt(stack,localAVLTree,file,lineNumber);
        else if (instruction == "igt")  igt(stack,localAVLTree,file,lineNumber);
        else if (instruction == "fgt")  fgt(stack,localAVLTree,file,lineNumber);
        else if (instruction == "ibnot")ibnot(stack,localAVLTree,file,lineNumber);

        // Nhóm lệnh nạp và lưu (Load and Store Instructions)
        else if (instruction == "iconst")    iconst(stack,localAVLTree,file,lineNumber,value);
        else if (instruction == "fconst")    fconst(stack,localAVLTree,file,lineNumber,value);
        else if (instruction == "iload")     iload(stack,localAVLTree,file,lineNumber,value);
        else if (instruction == "fload")     fload(stack,localAVLTree,file,lineNumber,value);
        else if (instruction == "istore")    istore(stack,localAVLTree,file,lineNumber,value);
        else if (instruction == "fstore")    fstore(stack,localAVLTree,file,lineNumber,value);

        // Nhóm lệnh chuyển đổi kiểu (Type conversion Instructions)
        else if (instruction == "i2f")       i2f(stack,localAVLTree,file,lineNumber,value);
        else if (instruction == "f2i")       f2i(stack,localAVLTree,file,lineNumber,value);

        // Nhóm lệnh quản lý trạng thái ngăn xếp toán hạng (Operand Stack Management Instructions)
        else if (instruction == "top")       top(stack,localAVLTree,file,lineNumber);


        // Nhóm lệnh quản lý biến cách bộ (Local Variable Management Instructions)
        else if (instruction == "val") val(stack,localAVLTree,file,lineNumber,value);
        else if (instruction == "par") par(stack,localAVLTree,file,lineNumber,value);
    }
    file.close();
}   