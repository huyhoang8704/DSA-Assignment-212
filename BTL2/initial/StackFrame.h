#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>
#include <stack>

#define FLOAT 1
#define INTEGER 0
#define OPERAND_STACK_MAX_SIZE 32
#define LOCAL_VARIABLE_ARRAY_SIZE 256

struct frame {
    float data;
    int type;
};
enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
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
    template <class T , class K >
    class AVLTree {
        public:
            class Node;
        protected:
            Node *root;
        protected:
            int getHeightRec(Node *node){
                if(!node) return 0;
                int left = this->getHeightRec(node->left);
                int right = this->getHeightRec(node->right);
                return (left > right ? left : right) + 1;
            }
        public:
            AVLTree() : root(nullptr) {}
            ~AVLTree(){}

            int getHeight(){ return this->getHeightRec(this->root); }
            int getBalance(Node *subroot) {
                if(!subroot) return 0;
                return getHeightRec(subroot->right) - getHeightRec(subroot->left); 
            }
            bool isLessThan(const K &a, const K &b) {
                int lenA = a.length();
                int lenB = b.length();
                int minLen = lenA < lenB ? lenA : lenB;

                // So sánh từng ký tự tại các vị trí tương ứng trong chuỗi
                for (int i = 0; i < minLen; ++i) {
                    if (a[i] < b[i]) return true;
                    else if (a[i] > b[i]) return false; 
                }

                // Nếu tất cả ký tự từ đầu đến minLen giống nhau, so sánh độ dài
                return lenA < lenB;
            }           


            // Rotate Right
            Node* LLRotation(Node *A){
                Node *B = A->left;
                A->left = B->right;
                B->right = A;
                if(root == A) root = B;
                return B;
            }
            // Rotate Left
            Node* RRRotation(Node* A) {
                Node *C = A->right;
                A->right = C->left;
                C->left = A;
                if(root == A) root = C;
                return C;
            }

            Node* LRRotation(Node* A){
                A->left = RRRotation(A->left);
                return LLRotation(A);
            }
            Node* RLRotation(Node* A){
                A->right = LLRotation(A->right);
                return RRRotation(A);
            }
            Node* insertNode(Node* pNode, K key, T data){
                if(!pNode) return new Node(data,key);

                if(this->isLessThan(key, pNode->key)) pNode->left = insertNode(pNode->left, key, data);
                else if(!this->isLessThan(key, pNode->key)) pNode->right = insertNode(pNode->right, key, data);

                int balance = getBalance(pNode);
                // LL Rotation
                if(balance < LH && key < pNode->left->key) return LLRotation(pNode);
                // RR Rotation
                if(balance > RH && key >= pNode->right->key) return RRRotation(pNode);
                // LR Rotation
                if(balance < LH && key >= pNode->left->key) return LRRotation(pNode);
                // RL Rotation
                if(balance > RH && key < pNode->right->key) return RLRotation(pNode);
                return pNode;
            }
            void insert(const K &key, const T& data){ this->root = insertNode(this->root, key, data);}
            Node * minValueNode(Node *pNode){
                Node *temp = pNode;
                while(temp && temp->left != NULL) temp = temp->left;
                return temp;
            }
            Node *maxValueNode(Node *pNode){
                Node *temp = pNode;
                while(temp && temp->right != NULL) temp = temp->right;
                return temp;
            }
            Node *deleteNodeRec(Node *pNode, K key){
                if(!pNode) return pNode;
                if(key < pNode->key) pNode->left = deleteNodeRec(pNode->left, key);
                else if(key > pNode->key) pNode->right = deleteNodeRec(pNode->right, key);
                else if(key == pNode->key && pNode->left == NULL){
                    Node *temp = pNode->right;
                    delete pNode;
                    return temp;
                }
                else if (key == pNode->key && pNode->right == NULL){
                    Node *temp = pNode->left;
                    delete pNode;
                    return temp;
                }
                else if(key == pNode->key && pNode->right != NULL && pNode->left != NULL){
                    Node *temp = maxValueNode(pNode->left);
                    pNode->data = temp->data;
                    pNode->key = temp->key;
                    pNode->right = deleteNodeRec(pNode->right, temp->key);
                }
                if(pNode == NULL) return pNode;
                int balance = getBalance(pNode);
                if(balance < LH && getBalance(pNode->left) >= RH) return LLRotation(pNode);
                if(balance < LH && getBalance(pNode->left) < RH) return LRRotation(pNode);
                if(balance > RH && getBalance(pNode->right) <= LH) return RRRotation(pNode);
                if(balance > RH && getBalance(pNode->right) > LH) return RLRotation(pNode);
                return pNode;
            }
            void remove(const K &key){ this->root = deleteNodeRec(this->root, key);}
            Node* searchRec(Node* pNode, K key){
                if(!pNode) return NULL;
                if(key == pNode->key) return pNode;
                if(key < pNode->key) return searchRec(pNode->left, key);
                return searchRec(pNode->right, key);
            }
            Node *search(K key){ return searchRec(this->root, key);}
            void destroyTree(){  destroyTreeRec(this->root); }
            void destroyTreeRec(Node *pNode){
                if(!pNode) return ;
                destroyTreeRec(pNode->left);
                destroyTreeRec(pNode->right);
                delete pNode;
                pNode = NULL;
            }
            Node * searchParentRec(Node * pNode , K key){
                if(!pNode) return nullptr;
                if((pNode->left && key == pNode->left->key) || (pNode->right && key == pNode->right->key)) return pNode;
                Node *leftSearch = searchParentRec(pNode->left, key);
                if(leftSearch) return leftSearch;

                return searchParentRec(pNode->right, key);
            }
            Node *searchParent(K key) {
                if(!this->root || this->root->key == key) return nullptr;
                Node *temp = this->searchParentRec(this->root,key);
                if(!temp) return nullptr;
                return temp;
            }
            int countNodeRec(Node *pNode){
                if(!pNode) return 0;
                else return 1 + countNodeRec(pNode->left) + countNodeRec(pNode->right);
            }
            int getSize(){ return countNodeRec(this->root);}
            void updateData(const K &key , const T &newData){
                Node *temp = this->search(key);
                temp->data = newData;
            }
            class Node {
                private:
                    T data;
                    K key;
                    Node *left, *right;
                    BalanceValue balance;
                    friend class AVLTree<T, K>;
                public:
                    Node(T frame, K value) : data(frame), key(value), left(NULL), right(NULL), balance(EH) {}
                    ~Node() {}
                    T getFrame() { return data; }
                    K getKey() { return key; }
            };
    };
    void run(std::string filename);
};

#endif // !__STACK_FRAME_H__



