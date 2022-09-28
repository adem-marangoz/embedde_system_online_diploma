## **Write the output of this Program**

```C
#include <stdio.h>
union job
{
    char name[32];
    float salary;
    int worker_no;
}u;

stuct job1
{
    char name[32];
    float salary;
    int worker_no;
}s;

int main()
{
    printf("size of union = %d",sizeof(u));
    printf("size of structure = %d",sizeof(s));
}

```

---
