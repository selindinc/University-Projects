#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>
#include <initializer_list>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <utility>


namespace cs540
{
    #define MAX_LEVEL_SKIPLIST 30
    template <typename Key_T, typename Mapped_T> 
    
    class Map
    {
        private:
        
            typedef std::pair<const Key_T, Mapped_T> ValueType;
            
            class SkipList
            {
                public:
                    struct Node{
                        std::vector<Node*> forward;
                        std::vector<Node*> backward;
                        bool nodeHasValue;

                        Node(int level, bool init=false): nodeHasValue(init) {
                            for(int i=0; i<=level; i++){
                                forward.push_back(nullptr);
                                backward.push_back(nullptr);
                            }

                        }
                        bool hasValue(){
                            return nodeHasValue;
                        }

                        virtual ~Node() = default;

                    };

                    struct DataNode: public Node {
                        DataNode(const ValueType d, int level):Node(level,true),data(d){} 

                        ValueType& getData(){
                            return data;
                        }
                        private:
                            ValueType data;
                    };

                    SkipList() : probability(0.5), max_level(MAX_LEVEL_SKIPLIST), current_level(0), size(0), head(new Node(max_level)), tail(new Node(max_level)){
                        
                        for (int i = 0; i <= max_level; i++)
                        {
                                head->forward[i] = tail;
                                head->backward[i] = nullptr;

                                tail->backward[i] = head;
                                tail->forward[i] = nullptr;
                        }
                        
                    }

                    ~SkipList(){
                        
                        for(Node *i= head;i != tail;){
                            if(i){
                                auto j = i->forward[0];
                                delete i;
                                i=j;
                            }
                        }
                        delete tail;
                    } 

                    size_t Size(){
                        return size;
                    }

                    void insert(ValueType new_data){
                        Node* curr= head;
                        std::vector<Node*> update = head->forward;

                        for (int i = current_level; i >= 0; i--){
                            while(curr->forward[i] && curr->forward[i] != tail && static_cast<typename SkipList::DataNode *>(curr->forward[i])->getData().first < new_data.first){
                                curr=curr->forward[i];
                            }
                            update[i]=curr;

                        }
                        curr=curr->forward[0];

                        if(curr == nullptr || curr == tail || !(static_cast<typename SkipList::DataNode *>(curr)->getData().first == new_data.first)){
                            
                            

                            int levelToInsert=rand_level();
                            DataNode* newNode = new DataNode(new_data, levelToInsert);
                            //if randlevel is greater than current level, initialize update value with pointer to header for further use 
                            if(levelToInsert>current_level){
                                for(int i=current_level+1; i<=levelToInsert; i++){
                                    update[i]=head;
                                }
                                current_level=levelToInsert;
                            }

                            //update,c insert newNode => update,newNode,c 
                            for(int i=0; i<=levelToInsert;i++){
                                if(update[i]==tail){
                                    newNode->forward[i]=tail;
                                    newNode->backward[i]=tail->backward[i];
                                    tail->backward[i]->forward[i]=newNode;
                                    tail->backward[i]=newNode;
                                }
                                else if(update[i]==head){
                                    newNode->forward[i]=head->forward[i];
                                    newNode->backward[i]=head;
                                    head->forward[i]->backward[i]=newNode;
                                    head->forward[i]=newNode;

                                }
                                else{
                                    //1,3 => insert 2 => 1,2,3 => 2=newNode 1=update
                                    newNode->forward[i]=update[i]->forward[i];
                                    newNode->backward[i]=update[i];
                                    update[i]->forward[i]->backward[i]=newNode;
                                    update[i]->forward[i]=newNode;
                                }
                                
                            
                            }
                            size++;
                        }
                    }

                    Node* search(const Key_T key){
                        Node* curr=head;

                        for(int i=current_level;i>=0;i--){ //start from highest level of skip list
                            while (curr->forward[i] != tail && static_cast<typename SkipList::DataNode *>(curr->forward[i])->getData().first < key)
                            {
                                /*move the current pointer forward while key  
                                is greater than key of node next to current 
                                Otherwise inserted current in update and  
                                move one level down and continue search */
                                curr = curr->forward[i];
                            }

                        }
                        curr=curr->forward[0];
                        if(curr!=nullptr && curr!=head && curr!=tail){
                            if((static_cast<typename SkipList::DataNode *>(curr)->getData().first == key)){
                                return curr;
                            }
                            else{
                                return nullptr;
                            }
                            
                        }
                        else{
                            return nullptr;
                            
                            
                        }
                    }
                    void remove(const Key_T key){
                        Node* curr=head;
                        std::vector<Node*> update = head->forward;

                        for(int i = current_level; i >= 0; i--) 
                        {
                            while (curr->forward[i] != tail && static_cast<typename SkipList::DataNode *>(curr->forward[i])->getData().first < key)
                            {
                                curr = curr->forward[i];
                            }
                            update[i]=curr;
                        }
                        curr=curr->forward[0];

                        if(curr!=tail && (static_cast<typename SkipList::DataNode *>(curr)->getData().first == key)) {
                            
                            for(int i=0; i<=current_level;i++){
                                if(update[i]->forward[i] != curr){// if at level i, next node is not the target then break, no need to move at the level further
                                    break;
                                }
                                update[i]->forward[i]=curr->forward[i];
                                curr->forward[i]->backward[i]=update[i];
                            }

                            delete curr;

                            while(current_level>0 && head->forward[current_level]==tail){ //removing levels that has no elements
                                current_level--;
                            }
                            size--;

                        }
                    }

                    int rand_level() const{
                        float rand=(static_cast<float>(std::rand())/RAND_MAX);
                        int level=0;
                        while(rand<probability && level<MAX_LEVEL_SKIPLIST){
                            level++;
                            rand=(static_cast<float>(std::rand())/RAND_MAX);
                        }
                        return level;
                    }

                    Node* getHead(){
                        return head;
                    }

                    Node* getTail(){
                        return tail;
                    }

            
                private:
                    const float probability;
                    int max_level, current_level, size;
                    Node *head, *tail;

            };
        
        public:
            class ConstIterator;
            class ReverseIterator;
            
            class Iterator
            {
        
            public:
                typename SkipList::Node *node_ptr;

                Iterator() = delete;
                Iterator(typename SkipList::Node *n) : node_ptr(n) {}
                Iterator(const Iterator &iter) : node_ptr(iter.node_ptr) {}
                ~Iterator() {}
                
                Iterator& operator=(const Iterator &n){
                    node_ptr=n.node_ptr;
                    return *this;
                }

                Iterator &operator++(){
                    node_ptr=node_ptr->forward[0];
                    return *this;
                }

                Iterator operator++(int){
                    auto &i=*this;
                    operator++();
                    return i;
                }

                Iterator &operator--(){
                    node_ptr=node_ptr->backward[0];
                    return *this;
                }

                Iterator operator--(int){
                    auto &i = *this;
                    operator--();
                    return i;
                }

                ValueType &operator*() const{
                    return static_cast<typename SkipList::DataNode *>(node_ptr)->getData();
                }

                ValueType *operator->() const{
                    return &(static_cast<typename SkipList::DataNode *>(node_ptr)->getData());
                }

                friend bool operator==(const Iterator &a, const Iterator &b){
                    if(a.node_ptr != nullptr && a.node_ptr->hasValue()){
                        if(b.node_ptr!=nullptr && b.node_ptr->hasValue()){
                            return (static_cast<typename SkipList::DataNode *>(a.node_ptr)->getData() == static_cast<typename SkipList::DataNode *>(b.node_ptr)->getData());
                        }
                        return false;
                    }
                    return a.node_ptr == b.node_ptr;

                }
                friend bool operator!=(const Iterator &a, const Iterator &b){

                    return !(a == b);
                }
                friend bool operator==(const Iterator &a,const ConstIterator &b){
                    if(a.node_ptr != nullptr && a.node_ptr->hasValue()){
                        if(b.node_ptr!=nullptr && b.node_ptr->hasValue()){
                            return (static_cast<typename SkipList::DataNode *>(a.node_ptr)->getData() == static_cast<typename SkipList::DataNode *>(b.node_ptr)->getData());
                        }
                        return false;
                    }
                    return a.node_ptr == b.node_ptr;

                }

                friend bool operator!=(const Iterator &a, const ConstIterator &b){
                    return !(a == b);
                }
                
            };
        
            class ConstIterator
            {
            public:
                typename SkipList::Node *node_ptr;
                ConstIterator() = delete;
                ConstIterator(typename SkipList::Node *n) : node_ptr(n) {}
                ConstIterator(const ConstIterator &iter) : node_ptr(iter.node_ptr) {}
                ConstIterator(const Iterator iter) : node_ptr(iter.node_ptr) {}
                ~ConstIterator() {}
                
                ConstIterator& operator=(const ConstIterator &n){
                    node_ptr = n.node_ptr;
                    return *this;

                }

                ConstIterator &operator++(){
                    node_ptr=node_ptr->forward[0];
                    return *this;
                }

                ConstIterator operator++(int){
                    auto &i=*this;
                    operator++();
                    return i;
                }

                ConstIterator &operator--(){
                    node_ptr=node_ptr->backward[0];
                    return *this;
                }

                ConstIterator operator--(int){
                    auto &i = *this;
                    operator--();
                    return i;
                }

                const ValueType &operator*() const{
                    return static_cast<typename SkipList::DataNode *>(node_ptr)->getData();
                }

                const ValueType *operator->() const{
                    return &(static_cast<typename SkipList::DataNode *>(node_ptr)->getData());
                }

                friend bool operator==(const ConstIterator &a,const ConstIterator &b){
                    if(a.node_ptr != nullptr && a.node_ptr->hasValue()){
                        if(b.node_ptr!=nullptr && b.node_ptr->hasValue()){
                            return (static_cast<typename SkipList::DataNode *>(a.node_ptr)->getData() == static_cast<typename SkipList::DataNode *>(b.node_ptr)->getData());
                        }
                        return false;
                    }
                    return a.node_ptr == b.node_ptr;
                }
                friend bool operator!=(const ConstIterator &a,const ConstIterator &b){
                    return !(a == b);
                }
                friend bool operator==(const ConstIterator &a,const Iterator &b){
                    
                    if(a.node_ptr != nullptr && a.node_ptr->hasValue()){
                        if(b.node_ptr!=nullptr && b.node_ptr->hasValue()){
                            return (static_cast<typename SkipList::DataNode *>(a.node_ptr)->getData() == static_cast<typename SkipList::DataNode *>(b.node_ptr)->getData());
                        }
                        return false;
                    }
                    return a.node_ptr == b.node_ptr;
                }
                friend bool operator!=(const ConstIterator &a,const Iterator &b){
                    return !(a == b);
                }
                
            };
        
            class ReverseIterator
            {
            public:

                typename SkipList::Node *node_ptr;

                ReverseIterator() = delete;
                ReverseIterator(typename SkipList::Node *n) : node_ptr(n) {}
                ReverseIterator(const ReverseIterator &iter) : node_ptr(iter.node_ptr) {}
                ~ReverseIterator() { }
                
                ReverseIterator& operator=(const ReverseIterator &n){
                    node_ptr=n.node_ptr;
                    return *this;
                }

                ReverseIterator &operator++(){
                    node_ptr=node_ptr->backward[0];
                    return *this;
                }

                ReverseIterator operator++(int){
                    auto &i=*this;
                    operator++();
                    return i;
                }

                ReverseIterator &operator--(){
                    node_ptr=node_ptr->forward[0];
                    return *this;
                }

                ReverseIterator operator--(int){
                    auto &i = *this;
                    operator--();
                    return i;
                }

                ValueType &operator*() const{
                    return static_cast<typename SkipList::DataNode *>(node_ptr)->getData();
                }

                ValueType *operator->() const{
                    return &(static_cast<typename SkipList::DataNode *>(node_ptr)->getData());
                }

                friend bool operator==(const ReverseIterator &a,const ReverseIterator &b){
                    if(a.node_ptr != nullptr && a.node_ptr->hasValue()){
                        if(b.node_ptr!=nullptr && b.node_ptr->hasValue()){
                            return (static_cast<typename SkipList::DataNode *>(a.node_ptr)->getData() == static_cast<typename SkipList::DataNode *>(b.node_ptr)->getData());
                        }
                        return false;
                    }
                    return a.node_ptr == b.node_ptr;
                }
                friend bool operator!=(const ReverseIterator &a,const ReverseIterator &b){
                    return !(a == b);
                }
                
            };
            
            Map() : skip_list(new SkipList()) {}

            Map(const Map &oldMap) : skip_list(new SkipList()){
                for (auto i = oldMap.begin(); i != oldMap.end(); i++)
                {
                    skip_list->insert((*i));
                }
            }

            Map &operator=(const Map &oldMAP)  {
                for (auto i = oldMAP.begin(); i != oldMAP.end(); i++)
                {
                    skip_list->insert((*i));
                }
                return *this;
            }

            Map(std::initializer_list<std::pair<const Key_T, Mapped_T>> s_list) : skip_list(new SkipList()){
                
                for (auto it = s_list.begin(); it != s_list.end(); it++){
                    insert(*it);
                }

            }

            ~Map(){
                delete skip_list;
            }
            
            size_t size() const{
                return skip_list->Size();
            }

            bool empty() const{
                return (size()==0);
            }
            
            Iterator begin(){
                return Iterator(skip_list->getHead()->forward[0]);
            }

            Iterator end(){
                return Iterator(skip_list->getTail());
            }

            ConstIterator begin() const{
                return ConstIterator(skip_list->getHead()->forward[0]);
            }

            ConstIterator end() const{
                return ConstIterator(skip_list->getTail());
            }

            ReverseIterator rbegin(){
                return ReverseIterator(skip_list->getTail()->backward[0]);
            }

            ReverseIterator rend(){
                return ReverseIterator(skip_list->getHead());
            }
            
            Iterator find(const Key_T &k){
                auto found = skip_list->search(k);
                if (found!=nullptr){
                    return Iterator(found);
                    
                }
                return end();
                
            }

            ConstIterator find(const Key_T &k) const{
                auto found = skip_list->search(k);
                if (found!=nullptr){
                    return ConstIterator(found);
                    
                }
                return end();
                
            }

            Mapped_T &at(const Key_T &k){
                auto found = skip_list->search(k);

                if( found!=nullptr ){
                    return (static_cast<typename SkipList::DataNode *>(found)->getData().second);
                    
                }
                else{
                    throw std::out_of_range("out of range");
                    
                }
            }

            const Mapped_T &at(const Key_T &k) const{
                
                auto found = skip_list->search(k);

                if( found!=nullptr ){
                    return (static_cast<typename SkipList::DataNode *>(found)->getData().second);
                    
                }
                else{
                    throw std::out_of_range("out of range");
                    
                }
            }


            Mapped_T &operator[](const Key_T &k){
                auto found = skip_list->search(k);

                if( found!=nullptr ){

                    return static_cast<typename SkipList::DataNode *>(found)->getData().second;

                }
                
                skip_list->insert(std::make_pair(k, Mapped_T()));
                auto found2=skip_list->search(k);
                return static_cast<typename SkipList::DataNode *>(found2)->getData().second;
    
            }
            
            std::pair<Iterator, bool> insert(const ValueType &data){
                Iterator found = find(data.first);
                if(found==end()){
                    skip_list->insert(data);
                    return std::make_pair(find(data.first), true);
                }

                return std::make_pair(found, false);
            }

            template <typename IT_T> void insert(IT_T range_beg, IT_T range_end){

                for (auto it = range_beg; it != range_end; it++){
                    insert(*it); // * kaldir ?
                }               
            }

            void erase(Iterator pos){

                if(pos != end()){
                    skip_list->remove(static_cast<typename SkipList::DataNode *>(pos.node_ptr)->getData().first);
                }
                else{
                    throw std::out_of_range("out of range");
                }

            }

            void erase(const Key_T &k){
                auto found= skip_list->search(k);

                if(found != nullptr){
                    skip_list->remove(k);
                }
                else{
                    throw std::out_of_range("out of range");
                }

            }

            void clear(){
                if(!empty()){
                    for(auto it = begin(); it != end();){
                        erase(it);
                    }
                }
            }
            
            friend bool operator==(const Map<Key_T, Mapped_T> &a, const Map<Key_T, Mapped_T> &b){
                if (a.size() != b.size()){
                    return false;
                }
                auto a_iter= a.begin();
                for (auto b_iter=b.begin(); a_iter!=a.end(), b_iter!=b.end(); a_iter++,b_iter++){
                    if(a_iter!=b_iter){
                        return false;
                    }
                }
                return true;
            }

            friend bool operator!=(const Map<Key_T, Mapped_T> &a, const Map<Key_T, Mapped_T> &b){
                return !(a == b);
            }

            friend bool operator<(const Map<Key_T, Mapped_T> &a, const Map<Key_T, Mapped_T> &b){
                
                auto it1=a.begin();

                for(auto it2=b.begin(); it1!=a.end(), it2!=b.end(); it1++, it2++)
                    if( (*it1) < (*it2) )
                        return true;
                if(a.size() < b.size())
                    return true;
                return false;
            }
            
        private:
            Map<Key_T, Mapped_T>::SkipList *skip_list;
        };
}

#endif


