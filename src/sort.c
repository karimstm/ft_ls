#include "../inc/ft_ls.h"

void merge(char **a, int low, int mid, int high)
{
	char **b = (char **)malloc(sizeof(char *) * (high-low+1));
	int i;
	int	j;
	int	k;

	i = low;
	j = mid + 1;
	k = 0;
	while (i <= mid && j <= high)
   	{
		if (ft_strcmp(a[i], a[j]))
			b[k++] = ft_strdup(a[i++]);
		else
			b[k++] = ft_strdup(a[j++]);
	}
	while (i <= mid)
		b[k++] = ft_strdup(a[i++]);
	while (j <= high)
		b[k++] = ft_strdup(a[j++]);
	k--;
	while (k >= 0) {
		a[low + k] = ft_strdup(b[k]);
		k--;
	}
}

void Mergesort(char **a, int low, int high)
{
	int m;

	if (low < high) {
		m = (high + low)/2;
		Mergesort(a, low, m);
		Mergesort(a, m + 1, high);
		merge(a, low, m, high);
	}
}
