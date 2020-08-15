#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP

#include <iostream>
#include <mutex>

namespace cs540 {
    
    std::mutex mtx;

    // Reference Counting Control Block Base Class 
    class RefCountBaseHelper {
        
        template <typename T> friend class SharedPtr;

        private:
            std::size_t refCount;
            
        public:
            RefCountBaseHelper() : refCount{1} {}
            virtual ~RefCountBaseHelper() {}

            virtual void increment() { 
                std::unique_lock<std::mutex> lock(mtx);
                ++refCount; 
            }

            virtual void decrement() {
                std::unique_lock<std::mutex> lock(mtx);
                --refCount;
                if(refCount == 0) {delete this;}
            } 
    };

    //Reference Counting Control Block Derived Class 
    template <typename S> class RefCountHelper : public RefCountBaseHelper {
        private:
            S* ptr;
        public:
            RefCountHelper(S* p) : ptr(p) {};
            virtual ~RefCountHelper() { delete ptr; };
    };

    template <typename T> class SharedPtr {

        public:

            T *ptr;
            RefCountBaseHelper *refPtr;

        // Default Constructor 
        SharedPtr() : ptr(nullptr), refPtr(nullptr) {}

        template <typename U> explicit SharedPtr(U *p) : ptr{p}, refPtr{new RefCountHelper<U>(p)} {}

        //Copy Constructor 
        SharedPtr(const SharedPtr &p) : ptr{p.ptr}, refPtr{p.refPtr} {
            if(refPtr) refPtr->increment();
        }

        template <typename U>
        SharedPtr(const SharedPtr<U> &p) : ptr{static_cast<T *>(p.ptr)}, refPtr{p.refPtr} {
            if(refPtr) refPtr->increment();
        }

        // Move Constructor
        SharedPtr(SharedPtr &&p) : ptr{p.ptr}, refPtr{p.refPtr} {
            p.ptr = nullptr;
            p.refPtr = nullptr;
        }

        template <typename U>
        SharedPtr(SharedPtr<U> &&p) : ptr{static_cast<T *>(p.ptr)}, refPtr{p.refPtr} {
            p.ptr = nullptr;
            p.refPtr = nullptr;
        }

        //Constructor for Casts
        template <typename U> SharedPtr(const SharedPtr<U> &sp, T *p) : ptr{p}, refPtr{sp.refPtr} {
            if(refPtr) refPtr->increment();
        }

        // Assignment Operator
        SharedPtr &operator=(const SharedPtr &p) {
            if(p == *this) return *this;
            if(refPtr) refPtr->decrement();
            ptr = p.ptr;
            refPtr = p.refPtr;
            if(refPtr) refPtr->increment();
            return *this;
        }

        template <typename U> SharedPtr<T> &operator=(const SharedPtr<U> &p) {
            if(p == *this) return *this;
            if(refPtr) refPtr->decrement();
            ptr = p.ptr;
            refPtr = p.refPtr;
            if(refPtr) refPtr->increment();
            return *this;
        }

        //Move Assignment Operator
        SharedPtr &operator=(SharedPtr &&p) {
            ptr = p.ptr;
            refPtr = p.refPtr;
            p.ptr = nullptr;
            p.refPtr = nullptr;
            return *this;
        }
        template <typename U> SharedPtr &operator=(SharedPtr<U> &&p) {
            ptr = p.ptr;
            refPtr = p.refPtr;
            p.ptr = nullptr;
            p.refPtr = nullptr;
            return *this;
        }

        ~SharedPtr() {
            if(refPtr) refPtr->decrement();
        }

        void reset() {
            if(refPtr) refPtr->decrement();
            ptr = nullptr;
            refPtr = nullptr;
        }

        template <typename U> void reset(U *p) {
            if(refPtr) refPtr->decrement();
            ptr = p;
            refPtr = new RefCountHelper<U>(p);
        }

        T *get() const { return ptr; }

        T &operator*() const { return *ptr; }

        T *operator->() const { return ptr; }

        explicit operator bool() const { return (ptr != nullptr); }
    }; 

    //Non-Member (Free) Functions
    template <typename T1, typename T2> bool operator==(const SharedPtr<T1> &p1, const SharedPtr<T2> &p2) {
        return ((p1.get() == p2.get()) || ((p1==nullptr) && (p2==nullptr)));
    }
    
    template <typename T> bool operator==(const SharedPtr<T> &p, std::nullptr_t) {
        return !p;
    }

    template <typename T> bool operator==(std::nullptr_t, const SharedPtr<T> &p) {
        return !p;
    }

    template <typename T1, typename T2> bool operator!=(const SharedPtr<T1> &p1, const SharedPtr<T2> &p2) {
        return !(p1 == p2);
    }
    
    template <typename T> bool operator!=(const SharedPtr<T> &p, std::nullptr_t n) {
        return !(p==n);
    }

    template <typename T> bool operator!=(std::nullptr_t n, const SharedPtr<T> &p) {
        return !(n==p);
    }

    template <typename T, typename U> SharedPtr<T> static_pointer_cast(const SharedPtr<U> &sp) {
        return SharedPtr<T>(sp, static_cast<T *>(sp.get()));
    }

    template <typename T, typename U> SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U> &sp) {
        return SharedPtr<T>(sp, dynamic_cast<T *>(sp.get()));
    }

} 

#endif