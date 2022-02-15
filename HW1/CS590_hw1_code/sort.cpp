#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include "sort.h"
using namespace std;

int ivector_length(int *v, int n)
{
  int sum;

  sum = 0;
  for (int i = 0; i < n; i++)
    sum += (v[i] < 0) ? -v[i] : v[i];

  return sum;
}

/*
 * insertion sort
 */
void insertion_sort(int **A, int n, int l, int r)
{
  int i;
  int *key;

  for (int j = l + 1; j <= r; j++)
  {
    key = A[j];
    i = j - 1;

    while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n)))
    {
      A[i + 1] = A[i];
      i = i - 1;
    }

    A[i + 1] = key;
  }
}

/*
 *   TO IMPLEMENT: Improved Insertion Sort for problem 1.
 */
void insertion_sort_im(int **A, int n, int l, int r)
{
  // precompute the vector's length and store their length in an array
  int vector_length[r + 1]; // declare an array to store all vector's length

  for (int i = l; i <= r; i++)
  {
    vector_length[i] = ivector_length(A[i], n); // call ivector_length() to calaculate A[i]'s length
  }

  // now vector_length[] stores all vector's length of A, we can access it by an index in insertion sort
  int i;
  int *key;
  int key_length;

  for (int j = l + 1; j <= r; j++)
  {
    key = A[j];

    // use the key_length variable to store the length of the key
    key_length = vector_length[j];

    i = j - 1;

    while ((i >= l) && (vector_length[i] > key_length)) // get the vector's length via accessing the vector_length array
    {
      A[i + 1] = A[i];

      // update vector_length[i + 1] as well
      vector_length[i + 1] = vector_length[i];

      i = i - 1;
    }

    // update vector_length[i + 1] with key_length
    vector_length[i + 1] = key_length;

    A[i + 1] = key;
  }
}

/*
 *   TO IMPLEMENT: Improved Merge Sort for problem 2.
 */
void merge_sort(int **A, int n, int p, int r)
{
  // precompute the vector's length and store their length in an array
  int vector_length[r + 1]; // declare an array to store all vector's length

  for (int i = p; i <= r; i++)
  {
    vector_length[i] = ivector_length(A[i], n); // call ivector_length() to calaculate A[i]'s length
  }

  // call _merge_sort() to implement the merge sort algorithm with vector_length
  _merge_sort(A, vector_length, p, r);
}

/*
 *   _merge_sort() function
 */
void _merge_sort(int **A, int *vector_length, int p, int r)
{
  if (p < r)
  {
    int q = int(floor((p + r) / 2));
    _merge_sort(A, vector_length, p, q);
    _merge_sort(A, vector_length, q + 1, r);

    // // optimized to achieve O(m) for best case
    // if (A[q] > A[q + 1])
    // {
    //   merge(A, vector_length, p, q, r);
    // }
    // // optimized for best case to achieve O(m)

    merge(A, vector_length, p, q, r);
  }
}

/*
 *   merge() fuinction
 */
void merge(int **A, int *vector_lengh, int p, int q, int r)
{
  // mid point(q) is included in the left side
  int n1 = q - p + 1;
  int n2 = r - q;

  // L stores left side of vector_lenth, A_L stores left side of A
  int L[n1 + 1];
  int *A_L[n1 + 1];

  // R stores right side of vector_lenth, A_R stores right side of A
  int R[n2 + 1];
  int *A_R[n2 + 1];

  // left side index = p + i
  for (int i = 0; i < n1; i++)
  {
    L[i] = vector_lengh[p + i];
    A_L[i] = A[p + i];
  }

  // right side start from q + 1, mid point is included in left side, not in right side
  for (int i = 0; i < n2; i++)
  {
    R[i] = vector_lengh[q + 1 + i];
    A_R[i] = A[q + 1 + i];
  }

  L[n1] = INT32_MAX;
  R[n2] = INT32_MAX;

  int i = 0;
  int j = 0;
  for (int k = p; k <= r; k++)
  {
    if (L[i] <= R[j])
    { // update vector_length and A
      vector_lengh[k] = L[i];
      A[k] = A_L[i];
      i += 1;
    }
    else
    { // update vector_length and A
      vector_lengh[k] = R[j];
      A[k] = A_R[j];
      j += 1;
    }
  }
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is
 *    greater than the i-th element.
 */
bool check_sorted(int **A, int n, int l, int r)
{
  for (int i = l + 1; i <= r; i++)
    if (ivector_length(A[i - 1], n) > ivector_length(A[i], n))
      return false;
  return true;
}

/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int **create_ivector(int n, int m)
{
  int **iv_array; // declare a 2d array

  iv_array = new int *[m];    // initialize an array of pointer with m size (how many arrays)
  for (int i = 0; i < m; i++) // initialize an array of int with n size (how many elements in an array)
    iv_array[i] = new int[n];

  return iv_array;
}

void remove_ivector(int **iv_array, int m)
{
  for (int i = 0; i < m; i++)
    delete[] iv_array[i];
  delete[] iv_array;
}

int **create_sorted_ivector(int n, int m)
{
  int **iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = (i + j) / n;

  return iv_array;
}

int **create_reverse_sorted_ivector(int n, int m)
{
  int **iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = ((m - i) + j) / n;

  return iv_array;
}

int **create_random_ivector(int n, int m, bool small)
{
  random_generator rg;
  int **iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
    {
      rg >> iv_array[i][j];
      if (small)
        iv_array[i][j] %= 100;
      else
        iv_array[i][j] %= 65536;
    }

  return iv_array;
}
