### ----------------------------------------------------------------------------
### Copyright (C) 2017 by Alex Fosdick - University of Colorado
###
### Redistribution, modification or use of this software in source or binary
### forms is permitted as long as the files maintain this copyright. Users are
### permitted to modify this and use it to learn about the field of embedded
### software. Alex Fosdick and the University of Colorado are not liable for any
### misuse of this material. 
###
### ----------------------------------------------------------------------------
### Coursera - University of Colorado Boulder
### 
### Introduction to Embedded Systems Software and Development Environments
### 
### Week 4 Final Assignment
### 
### ----------------------------------------------------------------------------
### Author : Kevin Bourne
### Date : 14 Aug 2023
### ----------------------------------------------------------------------------
### NB : This is not an embedded exercise  
### => this is a pure C exercise
### => NOT DONE
### ----------------------------------------------------------------------------

## Purpose

add some new c-programming functions that manipulate memory.

## Assignment specs

### COmpile time switches

#### `-DCOURSE1`

The `main` function consists in calling the function `course1()`.  
`course1()` must be wrapped inside a compile time switch, `-DCOURSE1`, to be enabled or disabled from the `make` command.

### `-DVERBOSE`

The function `print_array` must actually print something only if the `-DVERBOSE`is set at compile time

#### Compile time switches

    make COURSE1=1   # enables course1 code
    make VERBOSE=1   # enables print_array (stat.h/stat.c)

### New functions

#### uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length);

This function takes two byte pointers (1 src and 1 dest) and a length of bytes to move from the src to dest.  
The behavior should handle overlap of source and destination. Copy should occur, with no data corruption.  
All operations need to be performed using pointer arithmetic, not array indexing  
Should return a pointer to the destination (dst).  

#### uint8_t * my_memcopy(uint8_t * src, uint8_t * dst, size_t length);

This function takes two byte pointers (one source and one destination) and a length of bytes to copy from the source location to the destination.  
The behavior is undefined if there is overlap of source and destination. Copy should still occur, but will likely corrupt your data.  
All operations need to be performed using pointer arithmetic, not array indexing  
Should return a pointer to the destination (dst).  

#### uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value);

This should take a pointer to a source memory location, a length in bytes and set all locations of that memory to a given value.  
All operations need to be performed using pointer arithmetic, not array indexing  
Should return a pointer to the source (src).  
You should NOT reuse the set_all() function  

#### uint8_t * my_memzero(uint8_t * src, size_t length);

This should take a pointer to a memory location, a length in bytes and zero out all of the memory.  
All operations need to be performed using pointer arithmetic, not array indexing  
Should return a pointer to the source (src).  
You should NOT reuse the clear_all() function

#### uint8_t * my_reverse(uint8_t * src, size_t length);

This should take a pointer to a memory location and a length in bytes and reverse the order of all of the bytes.  
All operations need to be performed using pointer arithmetic, not array indexing  
Should return a pointer to the source.  

#### int32_t * reserve_words(size_t length);

This should take number of words to allocate in dynamic memory  
All operations need to be performed using pointer arithmetic, not array indexing  
Should return a pointer to memory if successful, or a Null Pointer if not successful  

#### void free_words(int32_t * src);
Should free a dynamic memory allocation by providing the pointer src to the function  
All operations need to be performed using pointer arithmetic, not array indexing































