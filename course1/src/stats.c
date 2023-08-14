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
 * @file stat.c
 * @brief <Add Brief Description Here >
 *
 * <Add Extended Description Here>
 *
 * @author Kevin Bourne
 * @date 10 Aug 2023
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "stats.h"

/* Size of the Data Set */
#define SIZE (40)

/* unit tests */
bool test_all();

/* -------------------------------------------------------------------------- */
void main() {

  uchar test[SIZE] = { 34, 201, 190, 154,   8, 194,   2,   6,
                      114,  88,  45,  76, 123,  87,  25,  23,
                      200, 122, 150,  90,  92,  87, 177, 244,
                      201,   6,  12,  60,   8,   2,   5,  67,
                        7,  87, 250, 230,  99,   3, 100,  90};

  assert(test_all());

  print_statistics(test, SIZE);
  sort_array(test, SIZE);
  print_array(test, SIZE);
}

/* -------------------------------------------------------------------------- */
/* Prints the statistics of an array */
void print_statistics(uchar* arr, size_t arr_size) {
  uchar median = find_median(arr, arr_size);
  uchar mean = find_mean(arr, arr_size);
  uchar maximum = find_maximum(arr, arr_size);
  uchar minimum = find_minimum(arr, arr_size);

  printf("------------------------------------------------------\n");
  printf("Statistics of array (rounded to the nearest integer): \n");
  printf("------------------------------------------------------\n");
  printf("  - median\t=\t%hhu\n", median);
  printf("  - mean \t=\t%hhu\n", mean);
  printf("  - maximum\t=\t%hhu\n", maximum);
  printf("  - minimum\t=\t%hhu\n", minimum);
  printf("\n");

  return;
}

/* -------------------------------------------------------------------------- */
/* Prints an array to the screen */
void print_array(uchar* arr, size_t arr_size) {
  printf("-----------------\n");
  printf("Array\n");
  printf("-----------------\n");
  if ( !arr ){
    printf("<null array>\n");
  } else if ( arr_size == 0 ){
    printf("<empty array>\n");
  } else {
    const size_t row_size = 10;
    const size_t col_size = arr_size / row_size + 1;
    for ( size_t i = 0; i < row_size; ++i ){
      for ( size_t j = 0; j < col_size; ++j ){
        size_t idx = i + j*row_size;
        if ( idx < arr_size ){
          printf("%2zu => %3hhu\t|\t", idx, arr[idx]);
        }
      }
      printf("\n");
    }
  }
  printf("\n");
}

/* -------------------------------------------------------------------------- */
/* Helper function to return the boundary of an arr given a comparator */
uchar find_boundary(uchar* arr, size_t arr_size, bool (comparator)(uchar, uchar)) {
  uchar res = 0;
  if ( arr && arr_size > 0 ){
    res = arr[0];
    for ( size_t i = 1; i < arr_size; ++i ){
      uchar current = arr[i];
      if ( comparator(current, res) ){
        res = current;
      }
    }
  }
  return res;
}

/* -------------------------------------------------------------------------- */
/* Helper function min */
bool min_comparator(uchar x, uchar y) {
  return (x < y);
}

/* -------------------------------------------------------------------------- */
/* Helper function max */
bool max_comparator(uchar x, uchar y) {
  return (x > y);
}

/* -------------------------------------------------------------------------- */
/* Returns the maximum of an arr */
uchar find_maximum(uchar* arr, size_t arr_size) {
  return find_boundary(arr, arr_size, max_comparator);
}

/* -------------------------------------------------------------------------- */
/* Returns the minimum of an arr */
uchar find_minimum(uchar* arr, size_t arr_size) {
  return find_boundary(arr, arr_size, min_comparator);
}
/* -------------------------------------------------------------------------- */

/* Sort an array from largest to smallest in place */
/* => Bubble sort : simplest algorithm */
void sort_array(uchar* arr, size_t arr_size) {
  if ( arr && arr_size > 0 ){
    for ( size_t end = arr_size; end >= 2; --end ){
      for ( size_t i = 1; i < end; ++i ){
        if ( arr[i-1] < arr[i] ){
          uchar tmp = arr[i-1];
          arr[i-1] = arr[i];
          arr[i] = tmp;
        }
      }
    }
  }
}

/* -------------------------------------------------------------------------- */
/* Helper round_nearest_uchar */
/* Not sure if it is authorized to use round() from math.h */
/* This implementation assumes : */
/*  - d is > 0, */
/*  - can be safely converted into a uchar */
uchar round_nearest_integer(double d) {
  return (uchar) (d + 0.5);
}

/* -------------------------------------------------------------------------- */
/* Returns the mean of an arr */
uchar find_mean(uchar* arr, size_t arr_size) {
  uchar res = 0;
  if ( arr && arr_size > 0 ){
    /* cannot use uchar to do the sum : may overflow => use double */
    double sum = (double) arr[0];
    for ( size_t i = 1; i < arr_size; ++i ){
      sum += (double) arr[i];
    }
    /* This is safe because the mean is lower than the maximum of the array */
    res = round_nearest_integer(sum/arr_size);
  }
  return res;
}

/* -------------------------------------------------------------------------- */
/* Returns the median value of an arr */
/* NB: arr must be not be modified by the calculation of a statistics */
/* NB: it is assumed that arr_size <= SIZE */
uchar find_median(const uchar* arr, size_t arr_size) {
  uchar res = 0;
  if ( arr && arr_size > 0 ){
    uchar arr_copy[SIZE];
    for ( size_t i = 0; i < arr_size; ++i ) {
      arr_copy[i] = arr[i];
    }

    sort_array(arr_copy, arr_size);
    size_t mid = arr_size / 2;
    if ( arr_size % 2 == 0 ){
      res = round_nearest_integer((arr_copy[mid-1] + arr_copy[mid]) / 2.0);
    } else {
      res = arr_copy[mid];
    }
  }
  return res;
}

/* -------------------------------------------------------------------------- */
/* Unit tests                                                                 */
/* -------------------------------------------------------------------------- */

#define TEST_SIZE (5)

/* -------------------------------------------------------------------------- */
bool test_find_boundary() {
  bool res = false;

  {
    /* ------------------------------------- */
    /* Case 1 : null array with arbitrary size */
    /* the size must be != 0 to make sure that the right branch is tested */
    uchar* null_arr = NULL;
    size_t arbitrary_size = 999;

    /* Should return 0 */
    res = ( find_maximum(null_arr, arbitrary_size) == 0 );
    if ( !res ){
      return res;
    }

    /* Should return 0 */
    res = ( find_minimum(null_arr, arbitrary_size) == 0 );
    if ( !res ){
      return res;
    }
  }

  {
    /* ------------------------------------- */
    /* Case 2 : normal array, but size is set to 0 */
    uchar test_arr[TEST_SIZE] = { 3, 1, 5, 2, 4 };
    size_t zero_size = 0;

    /* Should return 0 */
    res = ( find_maximum(test_arr, zero_size) == 0 );
    if ( !res ){
      return res;
    }

    /* Should return 0 */
    res = ( find_minimum(test_arr, zero_size) == 0 );
    if ( !res ){
      return res;
    }
  }

  {
    /* ------------------------------------- */
    /* Case 3 : normal case */
    /* Should return the maximum */
    uchar test_arr[TEST_SIZE] = { 3, 1, 5, 2, 4 };

    res = ( find_maximum(test_arr, TEST_SIZE) == 5 );
    if ( !res ){
      return res;
    }

    /* Should return the minimum */
    res = ( find_minimum(test_arr, TEST_SIZE) == 1 );
    if ( !res ){
      return res;
    }
  }

  return true;
}

/* -------------------------------------------------------------------------- */
/* Helper function to compare if 2 arrays are identical */
bool compare_array(uchar* arr1, uchar* arr2, size_t arr_size) {
  bool res = true;
  for ( size_t i = 0; i < arr_size; ++i ){
    if ( arr1[i] != arr2[i] ){
      res = false;
      break;
    }
  }
  return res;
}

/* -------------------------------------------------------------------------- */
bool test_compare_array() {
  bool res = false;

  uchar test_arr1[TEST_SIZE] = { 3, 1, 5, 2, 4 };
  uchar test_arr2[TEST_SIZE] = { 3, 1, 7, 2, 4 };

  /* should return true */
  res = compare_array(test_arr1, test_arr1, TEST_SIZE);
  if ( res == false ){
    return false;
  }

  /* should return false */
  res = compare_array(test_arr1, test_arr2, TEST_SIZE);
  if ( res == true ){
    return false;
  }

  return true;
}

/* -------------------------------------------------------------------------- */
bool test_sort_array() {
  bool res = false;

  {
    /* Case 1 : null array with arbitrary size */
    /* the size must be != 0 to make sure that the right branch is tested */
    uchar* null_arr = NULL;
    size_t arbitrary_size = 999;
    sort_array(null_arr, arbitrary_size);
    res = (null_arr == NULL);
    if ( !res ){
      return res;
    }
  }

  {
    /* Case 2 : normal array, but size is set to 0 */
    /* array should remain unchanged        */

    uchar test_arr[TEST_SIZE] = { 3, 1, 5, 2, 4 };
    uchar expected_arr[TEST_SIZE] = { 3, 1, 5, 2, 4 };

    size_t zero_size = 0;
    sort_array(test_arr, zero_size);
    res = compare_array(test_arr, expected_arr, TEST_SIZE);
    if ( !res ){
      return res;
    }
  }

  {
    /* Case 3 : sorted array */
    uchar test_arr[TEST_SIZE] =  { 5, 4, 3, 2, 1 };
    uchar expected_arr[TEST_SIZE] = { 5, 4, 3, 2, 1 };

    sort_array(test_arr, TEST_SIZE);
    res = compare_array(test_arr, expected_arr, TEST_SIZE);
    if ( !res ){
      return res;
    }
  }

  {
    /* Case 4 : normal case : unsorted array */
    uchar test_arr[TEST_SIZE] = { 3, 1, 5, 2, 4 };
    uchar expected_arr[TEST_SIZE] =  { 5, 4, 3, 2, 1 };

    sort_array(test_arr, TEST_SIZE);
    res = compare_array(test_arr, expected_arr, TEST_SIZE);
    if ( !res ){
      return res;
    }
  }

  return true;
}

/* -------------------------------------------------------------------------- */
bool test_round_nearest_integer() {
  bool res = false;

  {
    res = ( round_nearest_integer(0) == 0 );
    if ( !res ){
      return res;
    }
  }

  {
    res = ( round_nearest_integer(1) == 1 );
    if ( !res ){
       return res;
    }
  }

  {
    res = ( round_nearest_integer(4.0/3) == 1 );
    if ( !res ){
      return res;
    }
  }

  {
    res = ( round_nearest_integer(5.0/3) == 2 );
    if ( !res ){
      return res;
    }
  }

  return true;
}
/* -------------------------------------------------------------------------- */
bool test_find_mean() {
  bool res = false;

  {
    /* ------------------------------------- */
    /* Case 1 : null array with arbitrary size */
    /* the size must be != 0 to make sure that the right branch is tested */
    uchar* null_arr = NULL;
    size_t arbitrary_size = 999;

    /* Should return 0 */
    res = ( find_mean(null_arr, arbitrary_size) == 0 );
    if ( !res ){
      return res;
    }
  }

  {
    /* ------------------------------------- */
    /* Case 2 : normal array, but size is set to 0 */
    uchar test_arr[TEST_SIZE] = { 3, 1, 5, 2, 4 };
    size_t zero_size = 0;

    /* Should return 0 */
    res = ( find_mean(test_arr, zero_size) == 0 );
    if ( !res ){
      return res;
    }
  }

  {
    /* ------------------------------------- */
    /* Case 3 : normal case : sum is divisible by 5 */
    uchar test_arr[TEST_SIZE] = { 3, 1, 5, 2, 4 };

    res = ( find_mean(test_arr, TEST_SIZE) == 3 );
    if ( !res ){
      return res;
    }
  }

  {
    /* ------------------------------------- */
    /* Case 4 : normal case : rounded down */
    uchar test_arr[TEST_SIZE] = { 1, 10, 20, 30, 40 };

    res = ( find_mean(test_arr, TEST_SIZE) == 20 );
    if ( !res ){
      return res;
    }
  }

  {
    /* ------------------------------------- */
    /* Case 5 : normal case : rounded up */
    uchar test_arr[TEST_SIZE] = { 3, 10, 20, 30, 40 };

    res = ( find_mean(test_arr, TEST_SIZE) == 21 );
    if ( !res ){
      return res;
    }
  }

  return true;
}

/* -------------------------------------------------------------------------- */
bool test_find_median() {
  bool res = false;

  {
    /* ------------------------------------- */
    /* Case 1 : null array with arbitrary size */
    /* the size must be != 0 to make sure that the right branch is tested */
    uchar* null_arr = NULL;
    size_t arbitrary_size = 999;

    /* Should return 0 */
    res = ( find_median(null_arr, arbitrary_size) == 0 );
    if ( !res ){
      return res;
    }
  }

  {
     /* ------------------------------------- */
    /* Case 2 : normal array, but size is set to 0 */
    uchar test_arr[TEST_SIZE] = { 3, 1, 5, 2, 4 };
    size_t zero_size = 0;

    /* Should return 0 */
    res = ( find_median(test_arr, zero_size) == 0 );
    if ( !res ){
      return res;
    }
  }

  {
     /* ------------------------------------- */
    /* Case 3 : normal case : odd size  */
    uchar test_arr[TEST_SIZE] = { 3, 1, 5, 2, 4 };
    uchar expected_arr[TEST_SIZE] =  { 3, 1, 5, 2, 4 };

    res = ( find_median(test_arr, TEST_SIZE) == 3 );
    if ( !res ){
      return res;
    }

    /* test that the array has not been changed */
    res = compare_array(test_arr, expected_arr, TEST_SIZE);
    if ( !res ){
      return res;
    }
  }

  {
     /* ------------------------------------- */
    /* Case 4 : normal case : even size  */
    uchar test_arr[TEST_SIZE-1] = { 8, 6, 2, 4 };
    uchar expected_arr[TEST_SIZE-1] = { 8, 6, 2, 4 };

    res = ( find_median(test_arr, TEST_SIZE-1) == 5 );
    if ( !res ){
      return res;
    }

    /* test that the array has not been changed */
    res = compare_array(test_arr, expected_arr, TEST_SIZE-1);
    if ( !res ){
      return res;
    }
  }

  return true;
}

/* -------------------------------------------------------------------------- */
bool test_all() {
  printf("------------------------------------------------------\n");
  printf("test_all...\n");

  bool res = false;

  /* ----------------------------------------------------- */
  res = test_find_boundary();
  if ( !res ){
    printf("test_all...FAILED : test_find_boundary\n");
    return res;
  }

  /* ----------------------------------------------------- */
  res = test_compare_array();
  if ( !res ){
    printf("test_all...FAILED : test_compare_array\n");
    return res;
  }

  /* ----------------------------------------------------- */
  res = test_sort_array();
  if ( !res ){
    printf("test_all...FAILED : test_sort_array\n");
    return res;
  }

  /* ----------------------------------------------------- */
  res = test_round_nearest_integer();
  if ( !res ){
    printf("test_all...FAILED : test_round_nearest_integer\n");
    return res;
  }

  /* ----------------------------------------------------- */
  res = test_find_mean();
  if ( !res ){
    printf("test_all...FAILED : test_find_mean\n");
    return res;
  }

  /* ----------------------------------------------------- */
  res = test_find_median();
  if ( !res ){
    printf("test_all...FAILED : test_find_median\n");
    return res;
  }

  printf("test_all...OK\n");
  printf("------------------------------------------------------\n\n");
  return true;
}
