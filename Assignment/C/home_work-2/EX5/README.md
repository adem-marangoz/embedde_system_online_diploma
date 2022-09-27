## **Write C Program Check Whether a Character is an Alphabet or not**

**This program takes a character from user and checks whether that character is an alphabet or not**

<br>Consol_Output</br>

---
Enter a character : *
<br>* is not an alphabet</br>

---
Enter a character : K
<br>K is an alphabet</br>

---
Solution Key
```C
	char num;
	scanf("%c",&num);
	if((num>=65 && num<=90)||(num>=97 && num<=122))
		printf("%c is an alphabet",num);
	else
		printf("%c is not an alphabet",num);
```