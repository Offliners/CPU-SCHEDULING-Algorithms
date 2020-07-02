#include <stdio.h>

#define MAX_ARRAY_LENGTH (100000 + 7)

int tmp_array_for_sort[MAX_ARRAY_LENGTH];

void _sort(int lb, int rb, int id[], unsigned int R[]) 
{
    if (lb >= rb)
	   return;
	
    int mid = (lb + rb) >> 1;
	
    _sort(lb, mid, id, R);
    _sort(mid + 1, rb, id, R);

    int i1 = lb, i2 = mid + 1, p = lb;

    while(i1 <= mid || i2 <= rb)
    {
	    if(i1 <= mid && i2 <= rb)
        {
	        if(R[id[i1]] <= R[id[i2]])
		        tmp_array_for_sort[p++] = id[i1++];
    	    else
    		    tmp_array_for_sort[p++] = id[i2++];
    	}
    	else if(i1 <= mid) 
    	    tmp_array_for_sort[p++] = id[i1++];
    	else 
    	    tmp_array_for_sort[p++] = id[i2++];
    }

    for (int i = lb; i <= rb; i++)
	    id[i] = tmp_array_for_sort[i];
}

void sort(int n, int id[], unsigned int R[])
{
    _sort(0, n - 1, id, R);
}
