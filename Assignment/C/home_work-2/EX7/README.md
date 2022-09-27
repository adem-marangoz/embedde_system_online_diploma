## **Write C Program to Find Factorial of a Number**

**For any positive number n, its factorial is given by: factorial = 1\*2\*3\*4\*...n
if a number is negative, factorial does not exist and factorial of 0 is 1
This program takes an integer from a user. if user enters negative integer, this program will display error message and if user enters non-negative integer, this program will display the factorial of thet number.**

Consol_Output

---
Enter an integer : -5

Error!!! Factorial of negative number doesn't exist

---

Enter an integer : 10

Factorial = 3628800

Solution Key
```C
int num,temp=1;
printf("enter a number: ");
scanf("%d",&num);
if(num==0)
    goto print_screen;
else if(num<0)
{
    printf("Error !!! Factorial of negative number doesn't exist");
    return 0;
}
for(;num;num--)
{
    temp*=num;
}
print_screen:
	printf("Factorial = %d",temp);
```