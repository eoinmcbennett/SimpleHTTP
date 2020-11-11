//
// Created by Eoin on 06/11/2020.
//

#ifndef SERVERTEST_LISTNODE_H
#define SERVERTEST_LISTNODE_H

template<typename T> class ListNode{
private:
    ListNode<T>* next;
    T data;
public:
    ListNode(T data, ListNode<T>* next){
        this->data = data;
        this->next = next;
    }

    T getData(){
        return this->data;
    }

    ListNode<T>* getNext(){
        return this->next;
    }

    void setNext(ListNode<T>* next){
        this->next = next;
    }

    void setData(T data){
        this->data = data;
    }
};

#endif //SERVERTEST_LISTNODE_H
