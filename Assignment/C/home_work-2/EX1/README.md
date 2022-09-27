## **Write C program to Check Whether a Number is Even or Odd**

### **The program idea :**
Numbers perfectly divisible by 2 are known even numbers and numbers which are not divisible by 2 are called odd numbers, This porgram takes an integer form user and checks whether that number is even or odd and displays the result

Console_output

---
Enter an integer you want to check : 25
<br>25 is odd

---
Enter an integer you want to check : 12
<br>12 is even

---
## solution key
```C
int num;
scanf("%d",&num);
if(num%2)
    printf("%d is odd",num);
else
    printf("%d is even",num);
```