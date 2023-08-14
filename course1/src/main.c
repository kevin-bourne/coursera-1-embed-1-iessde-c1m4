/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file main.c
 * @brief Main entry point to the C1M3 Assessment
 *
 * Main calls course1() only if COURSE1 is defined
 *
 * @author Kevin Bourne
 * @date 14.08.2023
 *
 */

#ifdef COURSE1
#include "course1.h"
#endif

int main(void) {

#include <stdio.h>

#ifdef COURSE1
  course1();
#else
  printf("COURSE1 not defined\n");
#endif

#ifdef VERBOSE
  printf("VERBOSE defined\n");
#else
  printf("VERBOSE not defined\n");
#endif

  return 0;
}
