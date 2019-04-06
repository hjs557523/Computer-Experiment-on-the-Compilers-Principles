#include <stdio.h>
#include <string.h>

//定义全局变量和函数
char ch, prog[200], token[8];//ch为用户输入的每个字符,prog[]存放用户输入的程序句子,token[]存放从程序句子中划分出的单个单词字符串
int syn, p, m, n, num;//syn为单词种别码,p作为数组下标指针用于遍历prog[]数组给prog[]数组赋值
char* rwtab[6] = { "begin", "if", "then", "while", "do", "end"};//存放6个关键字单词的字符串指针数组rwtab,指向6个字符串
int scanner();//定义从左至右的扫描函数



int main()//主流程
{
	p = 0;//初始化指针
	printf("请输入正确格式的语句:\n");
	do {
		scanf("%c", &ch);
		prog[p++] = ch;//将用户输入的字符存放进程序句子里,包括结束符#
	} while (ch != '#');//遇到结束符#退出循环
	p = 0;
	do {//对prog里的程序句子进行单词切分并进行判断
		scanner();
		switch (syn)
		{
		case 11:printf("( %d , %d )\n", syn, num);
			break;
		case -1:printf("是一个非法的单词\n");
			break;
		default: printf("( %d , %s )\n", syn, token);
			break;
		}
	} while (syn != 0);
}


//扫描程序句子划分出单词
int scanner()
{
	memset(token,0,8);
	m = 0;//拼接单词字符串 	
	num = 0;//若为连续数字字符串，则先将数字字符串转化为数值，并赋初值0

	ch = prog[p++];//程序句子的第一个字符赋给ch
	while((ch == ' ')||(ch == '\n')) ch = prog[p++];//若扫描到的字符是空格或者是换行符,则进行跳过

	if(((ch <= 'z') && (ch >= 'a')) || ((ch <= 'Z') && (ch >= 'A')))//如果遇到的首字符是字母
	{
		while (((ch <= 'z') && (ch >= 'a')) || ((ch <= 'Z') && (ch >= 'A')) || ((ch >= '0') && (ch <= '9')))//接下来遇到的字符都是字母或数字
		{
			token[m++] = ch;//将连续遇到的所有字母和数字赋给token[]数组
			ch = prog[p++];
		}
         syn = 10;//假设token数组里存放的单词符号不为关键字,即对应种别码10
		p--;//指针回退一位
	
	    //接下来验证是否为关键字的情况
		for (n = 0; n <=5; n++) {//对字符串进行匹配
			if (strcmp(token, rwtab[n]) == 0)
			{
				syn = n + 1;//匹配成功则种别码为n+1
				break;//一旦匹配成功跳出for循环
			}
		}
		//没有匹配则证明为letter(letter|digit)，syn取为10
	}
		


	else if((ch>='0')&&(ch<='9'))//如果遇到首字符为数字
	{
		int p1=p;
	    while((ch>='0')&&(ch<='9'))
		{
			num = num * 10 + ch - '0';//将字符转化为数字并求累加和
			ch = prog[p++];
		}

		if (((ch <= 'z') && (ch >= 'a')) || ((ch <= 'Z') && (ch >= 'A'))) {//若输入以数字开头的单词内含有字母
			syn = -1;//则将syn=1表示错误,
			int p2 = p1-1;//p2指向第一个字符
			printf("%c",prog[p2]); 
			for(p1;p1<p;p1++)
			{
				printf("%c ",prog[p1]);//将错误字符串的数字部分打印出
			}
			
		}

		else {//为连续的数字字符

			p--;//最后一步指针回退一位
			syn = 11;//匹配成功,为digit digit*型,syn=11
		}

	}


/*对运算符等其他符号进行匹配:
  对于单个字符的运算符,直接匹配;
  对于多个字符的运算符,进行类似字符串匹配的过程*/

	else switch (ch){

	case '<': token[m++] = ch;//'<'字符需要往下一步再取一个字符进行判断
	 	      ch = prog[p++];//先将'<'写进token数组然后并p指针后移 

	 	      if (ch == '=') //'<='单词符号
			  {
			  syn = 22;
			  token[m++] = ch; //'='写进token数组
			  }
			  else if (ch == '>') { //'<>'单词符号
			  syn = 21;
			  token[m++] = ch; //'>'写进token数组
			  }
		      else//只有'<'字符
			  {
			  syn = 20;
			  p--;//往前判断的指针需要回退一位
			  }
			  break;

	case '>': token[m++] = ch;
		      ch = prog[p++];
		      if (ch == '=')//'>='单词符号
			  {
			  syn = 24;
			  token[m++] = ch;//'='写进token数组
			  }
		      else//只有'>'字符
			  {
		 	  syn = 23;
			  p--;//往前判断的指针需要回退一位
			  }
		      break;
	case '+': token[m++] = ch;
		      syn = 13;
		      break;
	case '-': token[m++] = ch;
		      syn = 14;
		      break;
	case ':': token[m++] = ch;//'='需要往下一步再取一个字符进行判断
		      ch = prog[p++];
		      if (ch == '=')//'=='单词符号
			  {
			  syn = 18;
			  token[m++] = ch;
			  }
		      else
			  {
			  syn = 17;
			  p--;
			  }
		      break;

	case '=': token[m++] = ch;
		      syn = 25;
		      break;
	case '*': syn = 15;
		      token[m++] = ch;
		      break;
	case '/': syn = 16;
		      token[m++] = ch;
		      break;
	case '(': syn = 27;
		      token[m++] = ch;
		      break;
	case ')': syn = 28;
		      token[m++] = ch;
		      break;
	case '{': syn = 5;
		      token[m++] = ch;
		      break;
	case '}': syn = 6;
		      token[m++] = ch;
		      break;
	case ';': syn = 26;
		      token[m++] = ch;
		      break;
	case '\"': syn = 30;
		       token[m++] = ch;
		       break;
	case '#': syn = 0;
		      token[m++] = ch;
		      break;
	default: syn = -1;//没有匹配到任何一种,返回错误
		printf(" %c ",ch);
		      break;
	}
	token[m++] = '\0';//置字符串结束标志
	return 0;
}
