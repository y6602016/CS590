#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "sort.h"

/*
 * HW 2 part
 */
int string_compare(char *s1, char *s2)
{
  /*
   * We assume that s1 and s2 are non-null pointers
   */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
  {
    return 0;
  }
  else
  {
    if (s1[i] < s2[i])
    {
      return -1;
    }
    else
    {
      return 1;
    }
  }
} /*>>>*/

void insertion_sort(char **A, int l, int r)
{
  int i;
  char *key;

  for (int j = l + 1; j <= r; j++)
  {
    key = A[j];
    i = j - 1;

    while ((i >= l) && (string_compare(A[i], key) > 0))
    {
      A[i + 1] = A[i];
      i = i - 1;
    }

    A[i + 1] = key;
  }
}

void insertion_sort_digit(char **A, int *A_len, int l, int r, int d)
{
  // sort the strings in A array according to the chat at position d
  // ex: A["ayc", "def", "dag"], d = 1 => sorted: A["dag", "def", "ayc"]
  // if d doesn't exist in a string, then string[d] = 0
  int i;
  char *key_string;
  char key_char;
  char compared;
  int string_len;
  int string_len2;

  for (int j = l + 1; j <= r; j++)
  {
    // get key_string
    key_string = A[j];

    // get the key string len
    string_len = A_len[j];

    // check d position exists or not
    if (d >= string_len)
    {
      // if not exist, key_char = 0
      key_char = 0;
    }
    else
    {
      // if exists, key_char = A[j] + d pointer
      key_char = A[j][d];
    }

    // initialize i
    i = j - 1;

    // get the conmpared string length
    string_len2 = A_len[i];

    // // check d position exists or not
    if (d >= string_len2)
    {
      compared = 0;
    }
    else
    {
      compared = A[i][d];
    }

    while ((i >= l) && (compared > key_char))
    {
      // move A[i] right
      A[i + 1] = A[i];

      // update A_len as well
      A_len[i + 1] = A_len[i];

      i = i - 1;

      // if i>= l, check length and update compared
      if (i >= l)
      {
        string_len2 = A_len[i];
        if (d >= string_len2)
        {
          compared = 0;
        }
        else
        {
          compared = A[i][d];
        }
      }
    }

    // set A[i + 1] as key string and update A_len[i + 1] as well
    A[i + 1] = key_string;
    A_len[i + 1] = string_len;
  }
}

void counting_sort_digit(char **A, int *A_len, char **B, int *B_len, int n, int d)
{
  int c[256];

  // initialize the c array
  for (int i = 0; i < 256; i++)
  {
    c[i] = 0;
  }

  int key_char;
  int string_len;

  // populate the c array
  for (int i = 0; i <= n; i++)
  {
    string_len = A_len[i];
    if (d >= string_len)
    {
      // if not exist, key_char = 0
      key_char = 0;
    }
    else
    {
      // if exists, key_char = A[j] + d pointer
      key_char = A[i][d];
    }
    c[key_char] += 1;
  }

  // accumulate the index, c[i] means the last i value in B array at c[i] - 1 index
  for (int i = 1; i < 256; i++)
  {
    c[i] += c[i - 1];
  }

  for (int i = n; i >= 0; i--)
  {
    string_len = A_len[i];
    if (d >= string_len)
    {
      // if not exist, key_char = 0
      key_char = 0;
    }
    else
    {
      key_char = A[i][d];
    }

    B[c[key_char] - 1] = A[i];
    B_len[c[key_char] - 1] = string_len;
    c[key_char] -= 1;
  }
}

void radix_sort_is(char **A, int *A_len, int n, int m)
{
  // for debugging
  // for (int i = 0; i < n; i++)
  // {
  //   cout << A[i] << " " << A_len[i] << endl;
  // }
  // cout << "---------" << endl;

  // do insertion sort from the rightmost digit to leftmost digit
  // index [m - 1] is 0, start from m - 2 to 0 to sort
  for (int d = m - 2; d >= 0; d--)
  {
    insertion_sort_digit(A, A_len, 0, n - 1, d);
  }

  // for debugging
  // for (int i = 0; i < n; i++)
  // {
  //   cout << A[i] << " " << A_len[i] << endl;
  // }
  // cout << "---------" << endl;
}

void radix_sort_cs(char **A, int *A_len, int n, int m)
{
  // for debugging
  // for (int i = 0; i < n; i++)
  // {
  //   cout << A[i] << " " << A_len[i] << endl;
  // }
  // cout << "---------" << endl;

  char **B = new char *[n];
  int *B_len = new int[n];

  // do counting sort from the rightmost digit to leftmost digit
  // index [m - 1] is 0, start from m - 2 to 0 to sort
  for (int d = m - 2; d >= 0; d--)
  {
    counting_sort_digit(A, A_len, B, B_len, n - 1, d);

    // copy B to A
    for (int x = 0; x < n; x++)
    {
      A[x] = B[x];
      A_len[x] = B_len[x];
    }
  }

  // for debugging
  // for (int i = 0; i < n; i++)
  // {
  //   cout << A[i] << " " << A_len[i] << endl;
  // }
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is
 *    greater than the i-th element.
 */
bool check_sorted(char **A, int l, int r)
{
  for (int i = l + 1; i < r; i++)
    if (string_compare(A[i - 1], A[i]) > 0)
      return false;
  return true;
}
