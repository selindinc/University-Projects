#ifndef DEQUE_HPP
#define DEQUE_HPP
#include <stddef.h>
#include <iostream>


#define Deque_DEFINE(type)\
  \
  struct Deque_##type##_Iterator;\
  struct Deque_##type;\
  struct Deque_##type##_Iterator{ \
\
    int current_index;\
    Deque_##type* data;\
    /*increment, equal,deref*/\
    void (*inc) (Deque_##type##_Iterator* iter);\
    void (*dec) (Deque_##type##_Iterator* iter);\
    type& (*deref) (Deque_##type##_Iterator* iter);\
\
  };\
  struct Deque_##type{\
\
    int  head,tail;\
    int number_of_elements;\
    int capacity;\
    type* data;\
    const char type_name[sizeof("Deque_"#type)] = "Deque_"#type;\
    bool (*type##_comparator)(const type& o1,const type& o2);\
    Deque_##type##_Iterator& (*begin)(Deque_##type *deq);\
    Deque_##type##_Iterator& (*end)(Deque_##type *deq);\
    \
    bool isFull(Deque_##type *deq){\
      return ((deq -> head-1+deq -> capacity)%deq -> capacity==deq -> tail)||((deq -> tail+1)%deq -> capacity==deq -> head);\
    }\
    bool empty(Deque_##type *deq){\
      if(deq->number_of_elements==0){\
        return true;\
      }\
      else{\
        return false;\
      }\
    }\
    void push_back(Deque_##type *deq,type x){\
      if(isFull(deq)==true){\
        deq->capacity+=20;\
        deq->data = (type*) realloc(deq->data,(size_t)deq->capacity*sizeof(type)); \
      }\
      if(empty(deq)==true){\
        deq->head=0;\
      }\
      else if(deq->tail==deq->capacity-1){\
        deq->tail=0;\
      }\
      else{\
        deq->tail++;\
      }\
      deq->data[deq->tail]=x;\
      deq->number_of_elements++;\
    }\
    void push_front(Deque_##type *deq,type x){\
      if(isFull(deq)==true){\
        deq->capacity+=20;\
        deq->data = (type*) realloc(deq->data,(size_t)deq->capacity*sizeof(type)); \
      }\
      if(empty(deq)==true){\
        deq->head=0;\
        deq->tail=0;\
      }\
      else if(deq->head==0){\
        deq->head=deq->capacity-1;\
      }\
      else{\
        deq->head=deq->head-1;\
      }\
      deq->data[deq->head]=x;\
      deq->number_of_elements++;\
    }\
    void pop_front(Deque_##type *deq){\
      if (empty(deq)==true) { \
        return ; \
      } \
      if (deq->head == deq->tail) { \
          deq->head = -1; \
          deq->tail = -1; \
          deq->number_of_elements--;\
      } \
      else{\
        deq->head = (deq->head+1)%(deq->capacity);\
        deq->number_of_elements--;\
      }\
    }\
    void pop_back(Deque_##type *deq){\
      if (empty(deq)==true) { \
        return ; \
      } \
      if (deq->head == deq->tail) { \
          deq->head = -1; \
          deq->tail = -1; \
          deq->number_of_elements--;\
      } \
      else if (deq->tail == 0){ \
          deq->tail = deq->number_of_elements-1; \
          deq->number_of_elements--;\
      }\
      else{\
          deq->tail = deq->tail-1; \
          deq->number_of_elements--;\
      }\
    }\
    \
    type& front(Deque_##type *deq){\
      \
      return deq->data[deq->head];\
      \
    }\
    type& back(Deque_##type *deq){\
      \
      return deq->data[deq->tail];\
      \
    }\
    type& at(Deque_##type* deq,int pos){\
      int i = (deq->head+(pos))%(deq->capacity);\
    	return deq->data[i];\
    }\
    \
    size_t size(Deque_##type *deq){\
      return deq->number_of_elements;\
    }\
    \
    void clear(Deque_##type *deq){\
      free(deq->data);\
      deq->number_of_elements=0;\
      deq->head=-1;\
      deq->tail=0;\
      deq->data = (type*) malloc((size_t)deq->capacity * sizeof(type));\
    }\
    \
    void dtor(Deque_##type *deq){\
      free(deq->data);\
    }\
    void sort(Deque_##type *deq, Deque_##type##_Iterator& iter1, Deque_##type##_Iterator& iter2){\
      int a=deq->head + iter1.current_index+iter2.current_index;/*i did to avoid the warnings,couldnt figure out the sort*/\
      a++;\
    }\
    /*push_back, push_front,front,back,equal, at,clear, dtor, pop_back, pop_front, sort,size,begin,end,isFull*/\
\
  };\
  bool Deque_##type##_Iterator_equal(Deque_##type##_Iterator& iter1, Deque_##type##_Iterator& iter2){\
    if(iter1.current_index != iter2.current_index){\
      return false;\
    }\
	  return true;\
  }\
  void inc(Deque_##type##_Iterator* iter){\
      if(iter->current_index==iter->data->capacity-1){\
        iter->current_index=0;\
      }\
      else{\
        iter->current_index++;\
      }\
  }\
  void dec(Deque_##type##_Iterator* iter){\
      if(iter->current_index==0){\
        iter->current_index=iter->data->capacity-1;\
      }\
      else{\
        iter->current_index--;\
      }\
  }\
  type& deref(Deque_##type##_Iterator* iter){\
    return iter->data->data[iter->current_index];\
  }\
  void Deque_##type##_Iterator_ctor(Deque_##type##_Iterator *iter,Deque_##type *q,int index){\
    iter->data=q;\
    iter->inc=&inc;\
    iter->deref=&deref;\
    iter->dec=&dec;\
    iter->current_index=index;\
  }\
  Deque_##type##_Iterator& begin(Deque_##type *deq){\
    Deque_##type##_Iterator* it = (Deque_##type##_Iterator*)malloc(sizeof(Deque_##type##_Iterator));\
    Deque_##type##_Iterator_ctor(it,deq,deq->head);\
    return *it;\
  }\
  Deque_##type##_Iterator& end(Deque_##type *deq){\
    Deque_##type##_Iterator* it = (Deque_##type##_Iterator*)malloc(sizeof(Deque_##type##_Iterator));\
    Deque_##type##_Iterator_ctor(it,deq,deq->tail+1);\
    return *it;\
  }\
  bool Deque_##type##_equal(Deque_##type& q1, Deque_##type& q2){\
    if(q1.number_of_elements!=q2.number_of_elements){\
      return false;\
    }\
    Deque_##type##_Iterator it2=q2.begin(&q2);\
    for (Deque_##type##_Iterator it = q1.begin(&q1); !Deque_##type##_Iterator_equal(it, q1.end(&q1)) ;it.inc(&it) ){\
      if( q1.type##_comparator(deref(&it),deref(&it2)) || q1.type##_comparator(deref(&it2),deref(&it)) ){\
        return false;\
      }\
      it2.inc(&it2);\
    }\
    return true;\
  }\
  void Deque_##type##_ctor(Deque_##type *deq,bool (*fptr)(const type& o1, const type& o2)){\
    deq->head=-1;\
    deq->tail=0;\
    deq->number_of_elements=0;\
    deq->capacity=50;\
    deq->data = (type*) malloc((size_t)deq->capacity * sizeof(type));\
    deq->type##_comparator = fptr;\
    deq->begin=&begin;\
    deq->end=&end;\
  }\

#endif