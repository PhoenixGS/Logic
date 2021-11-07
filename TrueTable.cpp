#include <cstdio>
#include <cstring>

//0 ( 1 ) 2 ! 3 & 4 | 5 -> 6 <->
//0 + 7 ~ 25 + 7 A-Z

const int _n = 100000 + 10;
int n, now;
char s[_n];
int opn, prn;
int op[_n], pr[_n];
int knum;
int val[_n], oz[_n], ch[_n][2];
int ap[26 + 10];
int last, zz[26 + 10];

int get()
{
	int c = s[now];
	now++;
	if (c >= 'A' && c <= 'Z')
	{
		return c - 'A' + 7;
	}
	if (c == '(')
	{
		return 0;
	}
	if (c == ')')
	{
		return 1;
	}
	if (c == '!')
	{
		return 2;
	}
	if (c == '&')
	{
		return 3;
	}
	if (c == '|')
	{
		return 4;
	}
	if (c == '-')
	{
		c = s[now];
		now++;
		if (c == '>')
		{
			return 5;
		}
	}
	if (c == '<')
	{
		c = s[now];
		now++;
		if (c == '-')
		{
			c = s[now];
			now++;
			if (c == '>')
			{
				return 6;
			}
		}
	}
	return -1;
}

void maintain()
{
	knum++;
	oz[knum] = op[opn];
	opn--;
	if (oz[knum] == 2)
	{
		ch[knum][0] = pr[prn];
		prn--;
	}
	else
	{
		ch[knum][1] = pr[prn];
		prn--;
		ch[knum][0] = pr[prn];
		prn--;
	}
	prn++;
	pr[prn] = knum;
}

void init()
{
	n = strlen(s + 1);
	now = 1;
	while (now <= n)
	{
		int z = get();
		if (z < 7)
		{
			if (z == 0)
			{
				opn++;
				op[opn] = z;
			}
			if (z == 1)
			{
				while (opn && op[opn] != 0)
				{
					maintain();
				}
				opn--;
			}
			if (z > 1)
			{
				while (opn && op[opn] != 0 && op[opn] < z)
				{
					maintain();
				}
				opn++;
				op[opn] = z;
			}
		}
		else
		{
			int ch = z - 7;
			ap[ch] = true;
			prn++;
			pr[prn] = ch;
		}
	}
	while (opn)
	{
		maintain();
	}
}

int calc(int x, int y, int op)
{
	if (op == 2)
	{
		return x ^ 1;
	}
	if (op == 3)
	{
		return x & y;
	}
	if (op == 4)
	{
		return x | y;
	}
	if (op == 5)
	{
		return (! x) | y;
	}
	if (op == 6)
	{
		return x == y;
	}
	return -1;
}

void solve(int k)
{
	if (k < 26)
	{
		return;
	}
	solve(ch[k][0]);
	solve(ch[k][1]);
	val[k] = calc(val[ch[k][0]], val[ch[k][1]], oz[k]);
}

void dfs(int k)
{
	if (k > last)
	{
		solve(knum);
		for (int i = 1; i <= last; i++)
		{
			printf("%3d", val[zz[i]]);
		}
		printf("%3d\n", val[knum]);
		return;
	}
	val[zz[k]] = 0;
	dfs(k + 1);
	val[zz[k]] = 1;
	dfs(k + 1);
}

int main()
{
	scanf("%s", s + 1);
	knum = 25;
	init();
	for (int i = 0; i < 26; i++)
	{
		if (ap[i])
		{
			last++;
			zz[last] = i;
		}
	}
	for (int i = 1; i <= last; i++)
	{
		printf("  %c", zz[i] + 'A');
	}
	printf("  %s\n", s + 1);
	dfs(1);
	return 0;
}
