#include<stdio.h>
#include<string.h>

typedef char* string;  //模拟字符串

string _strcpy(string str1,string str2)  //字符串拷贝函数实现
{
	while(*str1++=*str2++){
	;}
	return str1;
}

/*
string _strcpy(string str1,  string str2) 
{
	while(*str2 != '\0'){
		*str1++ = *str2++;
	}
	*str1 = '\0';
	return str1;
}
*/

int _strlen(string str)  //获取字符串长度
{
	int i=1;
	while(*str++){
		i++;
	}
	return i;
}

string _strcat(const string str1, string str2)  //字符串连接函数实现
{
	string _str1 = str1;

	if(*str2 == '\0'){
		return str1;
	}

	_str1 += (_strlen(_str1) - 1);
	//while(*_str1++ != '\0'){
	//;}
	while(*_str1++=*str2++){
	;}
	return str1;	
}

int _strcmp(string str1, string str2)  //字符串比较函数实现
{
	while(*str1++ == *str2++){
		;
	}
	return *(str1-1)-*(str2-1);
}

int _strstr(string str1,const string str2) //判断子字符串
{
	while(*str1){
		string _str2 = str2;
		while(*str1++ == *_str2++){
			if(*_str2 == '\0') return 0;
		}
	}	
	return -1;
}

int _strtok(string str1,const string str2)  //字符串切割函数实现
{
	while(*str1){
		string _str2 = str2;
		while(*str1 != *_str2 && *_str2++ != '\0'){
			printf("%c",*str1);
		}
		str1++;
		_str2 = str2;
		while(*str1 == *_str2++){
			printf("\n");
			break;
		}
	}
	return 0;
}

int main()
{
	string s1="sadja",s2="aj";
	//_strcpy(s2,s1);
	printf("%s %s\n",s1,s2);
	//printf("%d\n",_strcmp(s2,s1));
	//printf("%d\n",_strstr(s1,s2));
	//printf("%s\n",_strcat(s2,s1));
	_strtok(s1,s2);
	return 0;
}
