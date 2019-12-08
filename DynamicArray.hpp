#ifndef __DYNAMICARRAY_H__
#define __DYNAMICARRAY_H__

#include <stddef.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//using namespace std;

#define LOCAL_VECTOR_BUFFER_SIZE 16

/*
 *An array that supports dynamic expansion 
*/
template <typename T>
class DynamicArray
 {
 private:
 	size_t size_;
	size_t capacity_;
	T* ptr_;
	T buffer_[LOCAL_VECTOR_BUFFER_SIZE];

	void init_() {
		ptr_ = buffer_;
		size_ = 0;
		capacity_ = LOCAL_VECTOR_BUFFER_SIZE;
	}
 public:
 	DynamicArray() {
 		init_();
 	}

 	DynamicArray(const DynamicArray<T>& array) {
 		init_();
 		*this = array;
 	}

 	~DynamicArray(){
 		if ( ptr_ != buffer_ ) {
 			free(ptr_);
 		}
 	}
 public:
 	DynamicArray<T>& operator =(const DynamicArray<T>& array) {
 		clear();

 		size_ = array.size();
 		capacity_ = array.capacity();
 		if ( array.ptr_ == array.buffer_ ) {
 			memcpy(buffer_, array.buffer_, sizeof(T)*size_);
 			ptr_ = buffer_;
 		}
 		else {
 			ptr_ = (T*)calloc(sizeof(T), capacity_);
 			assert(ptr_);
 			memcpy(ptr_, array.ptr_, sizeof(T)*size_);
 		}
 		return *this;
 	}

 	T& operator [](size_t i) {
 		return ptr_[i];
 	}

 	const T& operator [](size_t i) const {
 		return ptr_[i];
 	}

 	size_t push_back(T& t) {
 		if ( size_ == capacity_ ) {
 			assert(ptr_);
 			reserve(capacity_ * 2);
 		}
 		ptr_[size_++] = t;
 		return size_;
 	}

 	void reserve(size_t size) {
 		if ( size <= capacity_ ) {
 			return;
 		}
 		if ( ptr_ == buffer_ ) {
 			ptr_ = (T*)calloc(sizeof(T), size);
 			assert(ptr_);
 			memcpy(ptr_, buffer_, sizeof(T) * capacity_);
 		} else {
 			ptr_ = (T*)realloc(ptr_, sizeof(T)*size);
 			assert(ptr_);
 		}
 		capacity_ = size;
 	}

	bool empty() {
		return 0 == size_;
	}

	size_t size() {
		return size_;
	}

	size_t capacity() {
		return capacity_;
	}

	void clear(){
		if ( ptr_ != buffer_ ) {
			free(ptr_);
		}
		init_();
	}
 };

/*
 *A fixed array that supports add, delete, and change operations
*/

#endif//__DYNAMICARRAY_H__
