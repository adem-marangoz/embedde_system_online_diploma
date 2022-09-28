## **Write C Program to Find prime number between two intervals by making user-defined function**

<br>Consol_Output</br>

---
<br>Enter two number(intervals) : 10
<br>30
<br>Prime numbers between 10 and 30 are : 11 13 17 19 23 29

----

<br>**Solution Key**

---
```C
int main()
{
	int num1,num2;
	printf("Enter two numbers(intervals) :");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&num1,&num2);
	if(num1>num2)
	{
		int temp;
		temp=num1;
		num1=num2;
		num2=temp;
	}
	printf("Prime numbers between 10 and 30 are : ");
	prime_fun(num1,num2);
	return 0;
}


void prime_fun(int _num1, int _num2)
{
	int p;
	for(int i=_num1;i<=_num2;i++)
	{
		for(int j=1;j<=i;j++)
		{
			if(i%j==0)
			{
				p++;
			}
		}
		if(p==2)
			printf("%d ",i);
		else
			p=0;
	}
}
```