#include <cstring>
#include <iostream>
#include <limits.h>

#include "dynprog.h"

using namespace std;

/*
 * Bottom up implementation of Smith-Waterman algorithm
 */
void SW_bottomUp(char *X, char *Y, char **P, int **H, int n, int m)
{
  for (int i = 0; i <= n; i++)
  {
    H[i][0] = 0;
    P[i][0] = 0;
  }

  for (int i = 0; i <= m; i++)
  {
    H[0][m] = 0;
    P[0][m] = 0;
  }

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
    {
      char xi = X[i - 1];
      char yj = Y[j - 1];
      int p1, p2, p3;

      if (xi == yj)
      { // same char
        p1 = H[i - 1][j - 1] + 2;
      }
      else
      { // not same char
        p1 = H[i - 1][j - 1] - 1;
      }

      p2 = H[i - 1][j] - 1;
      p3 = H[i][j - 1] - 1;

      H[i][j] = max(p1, p2);
      H[i][j] = max(H[i][j], p3);

      if (H[i][j] == p1)
      {
        P[i][j] = 'd';
      }
      else
      {
        if (H[i][j] == p2)
        {
          P[i][j] = 'u';
        }
        else
        {
          P[i][j] = 'l';
        }
      }
    }
  }

  return;
}

/*
 * Top-down with memoization implementation of Smith-Waterman algorithm
 */
void memoized_SW(char *X, char *Y, char **P, int **H, int n, int m)
{
  // the smallest negative value = -min(n, m)
  // so we can initialize P tables value as -min(n, m) - 1 (except first row and first column)
  // if the P[x][y] value > -min(n, m) - 1, means it has been visited, return value

  int smallest = min(n, m) * -1;
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
    {
      H[i][j] = smallest - 1;
    }
  }

  for (int i = 0; i <= n; i++)
  {
    H[i][0] = 0;
    P[i][0] = 0;
  }

  for (int i = 0; i <= m; i++)
  {
    H[0][m] = 0;
    P[0][m] = 0;
  }

  memoized_SW_AUX(X, Y, P, H, n, m, smallest);

  return;
}

/*
 * Auxilary recursive function of top-down with memoization implementation of Smith-Waterman algorithm
 */
void memoized_SW_AUX(char *X, char *Y, char **P, int **H, int n, int m, int smallest)
{
  // base case
  if (n < 1 || m < 1)
  {
    return;
  }

  // int smallest = min(n, m) * -1;
  char xi = X[n - 1];
  char yj = Y[m - 1];
  int p1, p2, p3;

  // if (H[n - 1][m - 1] == smallest - 1), means not visited yest, call recursion to visit it
  if (xi == yj)
  {
    if (H[n - 1][m - 1] == smallest - 1)
    {
      memoized_SW_AUX(X, Y, P, H, n - 1, m - 1, smallest);
    }
    p1 = H[n - 1][m - 1] + 2;
  }
  else
  {
    if (H[n - 1][m - 1] == smallest - 1)
    {
      memoized_SW_AUX(X, Y, P, H, n - 1, m - 1, smallest);
    }
    p1 = H[n - 1][m - 1] - 1;
  }

  if (H[n - 1][m] == smallest - 1)
  {
    memoized_SW_AUX(X, Y, P, H, n - 1, m, smallest);
  }
  p2 = H[n - 1][m] - 1;

  if (H[n][m - 1] == smallest - 1)
  {
    memoized_SW_AUX(X, Y, P, H, n, m - 1, smallest);
  }
  p3 = H[n][m - 1] - 1;

  H[n][m] = max(p1, p2);
  H[n][m] = max(H[n][m], p3);

  if (H[n][m] == p1)
  {
    P[n][m] = 'd';
  }
  else
  {
    if (H[n][m] == p2)
    {
      P[n][m] = 'u';
    }
    else
    {
      P[n][m] = 'l';
    }
  }
}

/*
 * Print X'
 */
void print_Seq_Align_X(char *X, char **P, int n, int m)
{
  if (n < 1 || m < 1)
  {
    return;
  }

  char p = P[n][m];
  char x = X[n - 1];
  if (p == 'd')
  {
    print_Seq_Align_X(X, P, n - 1, m - 1);
    cout << x;
  }
  else
  {
    if (p == 'l')
    {
      print_Seq_Align_X(X, P, n, m - 1);
      cout << '-';
    }
    else
    {
      print_Seq_Align_X(X, P, n - 1, m);
      cout << x;
    }
  }
}

/*
 * Print Y'
 */
void print_Seq_Align_Y(char *Y, char **P, int n, int m)
{
  if (n < 1 || m < 1)
  {
    return;
  }
  char p = P[n][m];
  char y = Y[m - 1];

  if (p == 'd')
  {
    print_Seq_Align_Y(Y, P, n - 1, m - 1);
    cout << y;
  }
  else
  {
    if (p == 'u')
    {
      print_Seq_Align_Y(Y, P, n - 1, m);
      cout << '-';
    }
    else
    {
      print_Seq_Align_Y(Y, P, n, m - 1);
      cout << y;
    }
  }
}
