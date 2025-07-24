#ifndef LL_H
#define LL_H

template<typename T>
class stack{
    private:
        struct node{
            T data;
            node* next;
        };
        node* top;
    public:
        stack();
        void push (T x);
        T pop();
        T peek();
        bool isEmpty();  
};

template <typename T>
stack<T>::stack(){
    top = nullptr;
}

template <typename T>
void stack<T>::push(T x){
    top = new node{x, top};
}

template <typename T>
T stack<T>::pop(){
    T tmp = peek();
    node* to_del = top;
    top = top->next;
    delete to_del;
    return tmp;
}

template <typename T>
T stack<T>::peek(){
    if (isEmpty()){
        std::cerr << "STACK IS EMPTY";
        exit(1);
    }
    return top->data;
}

template <typename T>
bool stack<T>::isEmpty(){
    return !top;
}


#endif