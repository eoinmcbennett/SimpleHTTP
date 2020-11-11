//
// Created by Eoin on 06/11/2020.
//

#ifndef SERVERTEST_LIST_H
#define SERVERTEST_LIST_H

#include "ListNode.h"

template<typename T> class List{
private:
     ListNode<T>* firstElement;
     unsigned int size;
public:
    List(){

    }

    void push(T data){
        ListNode<T>* node = new ListNode<T>(data,nullptr);
        if(size == 0){
            this->firstElement = node;
        }
        if(size >0){
            ListNode<T>* curNode = this->firstElement->getNext();
            while(curNode){
                if(curNode->getNext() == nullptr){
                    curNode->setNext(node);
                    break;
                } else{
                    curNode = curNode->getNext();
                }
            }
        }
        size++;
    }

    bool remove(int index){
        if(index < 0 || index >= size){
            return false;
        }

        if(index == 0 && size > 1){
            ListNode<T>* temp = this->firstElement->getNext();
            delete this->firstElement;
            this->firstElement = temp;
            return true;
        }else if(index == 0 && size == 1){
            delete this->firstElement;
            return true;
        }
        if(index){

        }
        size--;
    }

};

#endif //SERVERTEST_LIST_H
