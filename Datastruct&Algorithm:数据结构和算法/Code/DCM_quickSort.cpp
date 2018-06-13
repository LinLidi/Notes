int Partition(int r[ ], int first, int end)
{
  int i = first;
  int j = end;
  while (i < j)//1-从下标开始
  {
    while (i<j && r[i]<=r[j])//1-2 从右向左移动下标
    j--;
    if (i < j)//1-2-1交换，左边下标向右移
    {
      int temp = r[i];r[i] = r[j];r[j] = temp;
      i++;
    }
    while (i<j && r[i]<=r[j])
    i++;
    if (i < j)
    {
      int temp = r[i];r[i] = r[j];r[j] = temp;
      j--;
    }
  }
  return i;
}
void quickSort(int r[ ], int first, int end)
{
  int pivot;
  if (first < end)
  {
    pivot = Partition(r, first, end);
    quickSort(r, first, pivot-1);
    quickSort(r, pivot+1, end);
  }
}
