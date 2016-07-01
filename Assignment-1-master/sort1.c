/*
 * sort1.c
 *
 *  Created on: Jul 1, 2016
 *      Author: Tim
 */
#include <sort1.h>

void sort1(int *a, int n) {
    int i=1, j=2, t;
# define swap(i, j) { t = a[i]; a[i] = a[j]; a[j] = t; }
    while(i < n) {
        if (a[i - 1] > a[i]) {
            swap(i - 1, i);
            if (--i) continue;
        }
        i = j++;
    }
# undef swap
}


