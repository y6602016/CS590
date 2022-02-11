#include <cstdio>
#include <cstdlib>
#include <iostream>
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
