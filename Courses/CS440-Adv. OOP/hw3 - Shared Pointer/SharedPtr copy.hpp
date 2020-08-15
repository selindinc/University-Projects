#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP

#include <iostream>
#include <atomic>

namespace cs540
{

    class RefCountBaseHelper
    {
        template <typename T> friend class SharedPtr;

    private:
        std::atomic<int>* refCount;
    public:
        RefCountBaseHelper() { 
            refCount = new std::atomic<int>(); 
        };
        virtual ~RefCountBaseHelper() { 
            delete refCount; 
        };
        virtual int increment() { 
            return ++(*refCount); 
        };
        virtual int decrement() { 
            return --(*refCount); 
        };
    };
    
    template <typename S> class RefCountHelper : public RefCountBaseHelper
    {
    private:
        S* ptr;
    public:
        RefCountHelper(S* s) : ptr(s) {};
        virtual ~RefCountHelper() { 
            delete ptr; 
            ptr=nullptr; 
        };
    };


    template <typename T> class SharedPtr 
    {
        public:
            T* ptr;
            RefCountBaseHelper* refPtr;

            SharedPtr() : ptr(nullptr), refPtr(nullptr) {};
            template <typename U> explicit SharedPtr(U *) {};

            SharedPtr(const SharedPtr &p) {};
            template <typename U> SharedPtr(const SharedPtr<U> &p){};

            SharedPtr(SharedPtr &&p){};
            template <typename U> SharedPtr(SharedPtr<U> &&p){};

            SharedPtr &operator=(const SharedPtr &p){};
            template <typename U> SharedPtr<T> &operator=(const SharedPtr<U> &p){};

            SharedPtr &operator=(SharedPtr &&p){};
            template <typename U> SharedPtr &operator=(SharedPtr<U> &&p){};

            ~SharedPtr(){};

            void reset(){};

            template <typename U> void reset(U *p){};

            T *get() const{};

            T &operator*() const {};

            T *operator->() const {};

            explicit operator bool() const {};

    };

    //Non-Member (Free) Functions

    template <typename T1, typename T2> bool operator==(const SharedPtr<T1> &p1, const SharedPtr<T2> &p2) {};

    template <typename T> bool operator==(const SharedPtr<T> &p, std::nullptr_t n) {};

    template <typename T> bool operator==(std::nullptr_t n, const SharedPtr<T> &p) {};

    template <typename T1, typename T2> bool operator!=(const SharedPtr<T1>& p1, const SharedPtr<T2> & p2) {};

    template <typename T> bool operator!=(const SharedPtr<T> &p, std::nullptr_t n) {};

    template <typename T> bool operator!=(std::nullptr_t n, const SharedPtr<T> &p) {};

    template <typename T, typename U> SharedPtr<T> static_pointer_cast(const SharedPtr<U> &sp) {};

    template <typename T, typename U> SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U> &sp) {};


}
#endif