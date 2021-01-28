int binary_search(int const values[], size_t const n, int const x)
{
	int l(0);
	int r(n - 1);
	while (l <= r)
	{
		int m((l + r) / 2);
		if (values[m] < x)
		{
			l = m + 1;
		}
		else if (values[m] > x)
		{
			r = m - 1;
		}
		else
		{
			return m;
		}
		
	}
}