
#include <stdio.h>
#include <stdlib.h>
void allocArray(int ***p, int m, int n)
{
    *p = (int **)malloc(m * sizeof(int *));
    int *data = (int *)malloc(m * n * sizeof(int));
    for (int i = 0; i < m; i++)
    {
        (*p)[i] = &data[i * n];
    }
}


int main()
{
  int **array, *a;
  int j, k;
  allocArray(&array, 2, 3);
  for(j = 0;j < 2;j ++)
    for(k = 0;k < 3;k ++)
      array[j][k] = j * 10 + k;
  for(j = 0;j < 2;j ++)
    for(k = 0;k < 3;k ++)
      printf("%p ", &(array[j][k]));
}
