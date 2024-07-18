#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>
#include <iostream>

#define FLOAT 1
#define INTEGER 0
#define OPERAND_STACK_MAX_SIZE 32
#define LOCAL_VARIABLE_ARRAY_SIZE 256

struct frame {
    float data;
    int type;
};

class StackFrame {
    int opStackMaxSize; // max size of operand stack
    int localVarArrSize; // size of local variable array
public:
    StackFrame();

    template <class T>
    class SLinkedList {
    public:
        class Node;
    protected:
        Node* head;
        Node* tail;
        int count;
    public:
        SLinkedList(): head(nullptr), tail(nullptr), count(0) {}
        ~SLinkedList() { clear(); }

        void add(const T& data){
            Node* newNode = new Node(data, NULL);
            if(this->count == 0){
                this->head = newNode;
                this->tail = newNode;
            }
            else{
                this->tail->next = newNode;
                this->tail = newNode;
            }
            this->count++;
        }
        int size(){ return this->count; }
        T get(int index){
            if(index <0 || index > size()) throw("The index is out of range!");
            if(size() == 0) throw("List is empty");
            else{
                Node* temp = this->head;
                for (int i = 0; i < index; i++)  temp = temp->next;
                return temp->data; 
            }
        }
        bool isEmpty(){ return size() == 0; }
        void clear(){
            while(size() != 0){
                removeAt(0);
            }        
        }
        void removeAt(int index){
            if(index <0 || index >size())   throw("The index is out of range!");
            
            if(isEmpty())                   throw("List is empty");

            Node* temp = this->head;

            if(index == 0 && size()> 1){
                this->head = temp->next;
                delete temp;
            }


            else if(index == size()-1){
                for(int i = 0; i < size()-2; i ++){
                    temp = temp->next;
                }
                delete this->tail;
                this->tail = temp;
                temp->next = NULL;
            }

            else if(index > 0 && index < size()-1){
                for(int i = 0; i < index - 1; i++){
                    temp = temp->next;
                }
                Node* temp2 = temp->next;
                temp->next = temp2->next;
                delete temp2;
                temp2 = NULL;
            }

            else if(index == 0 && size() == 1){
                delete this->head;
                this->head = NULL;
                this->tail = NULL;
            }
            this->count--;
        }

        class Node {
        private:
            T data;
            Node* next;
            friend class SLinkedList<T>;
        public:
            Node() : next(nullptr) {}
            Node(Node* next) : next(next) {}
            Node(const T& data, Node* next) : data(data), next(next) {}
        };
    };
    
    //! Ngăn xếp toán hạng (Operand stack)
    template <class T>
    class myStack {
    private:
        int capacity;
    protected:
        SLinkedList<T> initStack;
    public:
        myStack(): capacity((OPERAND_STACK_MAX_SIZE/2)) {}

        void push(T data) { this->initStack.add(data); }
        void pop () { this->initStack.removeAt(initStack.size() - 1);}
        int stackSize() { return initStack.size(); }
        T top() { return this->initStack.get(stackSize() - 1); }
        bool isEmpty() { return initStack.size() == 0; }
        bool isFull() { return initStack.size() == capacity; }
        void clearStack() { return initStack.clear(); }
    };

    //! Không gian biến cục bộ (Local variable space)
    class myLocalVariableArray {
    private:
        int occupiedIndex[LOCAL_VARIABLE_ARRAY_SIZE -1];
        float localArray[LOCAL_VARIABLE_ARRAY_SIZE -1];
    public:
        myLocalVariableArray(){
            for(int i = 0; i < LOCAL_VARIABLE_ARRAY_SIZE; i++){
                occupiedIndex[i] = -1;
            }
        }

        bool checkOccupiedIndex(int index){
            if(this->occupiedIndex[index] == -1) return false;
            else return true;
        }

        bool outOfRange(int index){
            if(index > LOCAL_VARIABLE_ARRAY_SIZE || index < 0) return true;
            else return false;
        }
        int getDataType(int index){ return (int) localArray[index]; }
        float removeDataValue(int index){
            occupiedIndex[index] = -1;
            return localArray[index + 1];
        }

        float getValue(int index){ return localArray[index + 1]; }

        void setNewValue(float value, int type, int index){
            occupiedIndex[index] = 1;
            localArray[index] = type;
            localArray[index + 1] = value;
        }
    };
    void run(std::string filename);
};

#endif // !__STACK_FRAME_H__



