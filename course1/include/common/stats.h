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
 * @file stat.h
 * @brief Function prototyped of the stats.c module
 *
 * Declares all the prototypes needed for the stats module
 * Redefines also unsigned types to shorter names
 *
 * @author Kevin Bourn
 * @date 10 Aug 2023
 *
 */
#ifndef __STATS_H__
#define __STATS_H__

/* Redefine unsigned types to shorter names */
typedef unsigned char uchar;

/**
 * @brief Prints the statistics of an array
 *
 * A function that prints the statistics of an array including
 * minimum, maximum, mean and median.
 *
 * @param arr array to process
 * @param arr_size size of arr
 *
 * @return nothing
 */
void print_statistics(uchar* arr, size_t arr_size);

/**
 * @brief Prints an array to the screen
 *
 * Given an array of data and a length, prints the array to the screen
 *
 * @param arr array to process
 * @param arr_size size of arr
 *
 * @return nothing
 */
void print_array(uchar* arr, size_t arr_size);

/**
 * @brief Returns the median value of an arr
 *
 * Given an array of data and a length, returns the median value
 * rounded to the nearest int
 *
 * @param arr array to process
 * @param arr_size size of arr
 *
 * @return the median value or 0 if the input are invalid or empty
 */
uchar find_median(const uchar* arr, size_t arr_size);

/**
 * @brief Returns the mean of an arr
 *
 * Given an array of data and a length, returns the mean
 * rounded to the nearest int
 *
 * @param arr array to process
 * @param arr_size size of arr
 *
 * @return the mean value or 0 if the input are invalid or empty
 */
uchar find_mean(uchar* arr, size_t arr_size);

/**
 * @brief Returns the maximum of an arr
 *
 * Given an array of data and a length, returns the maximum
 *
 * @param arr array to process
 * @param arr_size size of arr
 *
 * @return the maxmimun or 0 if the input are invalid or empty
 */
uchar find_maximum(uchar* arr, size_t arr_size);

/**
 * @brief Returns the minimum of an arr
 *
 * Given an array of data and a length, returns the minimum
 *
 * @param arr array to process
 * @param arr_size size of arr
 *
 * @return the minimum or 0 if the input are invalid or empty
 */
uchar find_minimum(uchar* arr, size_t arr_size);

/**
 * @brief Sort an array from largest to smallest in place
 *
 * Given an array of data and a length, sorts the array from largest to smallest
 * The zeroth Element should be the largest value, and the last element (n-1)
 * should be the smallest value.
 * The passed array is sorted in place.
 *
 * @param arr array to process
 * @param arr_size size of arr
 *
 * @return nothing [The passed array is sorted in place.]
 */
void sort_array(uchar* arr, size_t arr_size);

#endif /* __STATS_H__ */
