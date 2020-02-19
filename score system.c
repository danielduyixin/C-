#include <io.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
//上述头文件，每一个都是必须的，没有多余的，不可随意删除，已按名字长度排序

//运行前需要修改下面对应的文件地址和目录地址
//地址格式：\\（双斜线），或/（单斜线）
//names_address -- 存储名字列表
//data_address -- 存储程序运行时的数据
//file_address -- 存储程序用到的Data文件的目录
//将地址定义为字符串而不是字符数组，放置被不经意的修改或损坏

char *data_address = "*\\Data";
char *names_address = "*\\names.txt";
char *file_address = "*\\FILES";

//char *data_address = "E:\\Git\\Code\\CLion\\FILES\\Data";
//char *names_address = "E:\\Git\\Code\\CLion\\FILES1\\names3.txt";
//char *file_address = "E:\\Git\\Code\\CLion\\FILES";

//版权所有，未经允许，不能转载
//本人保留一切追究法律责任的权利
//联系方式：651608356@qq.com
//https://github.com/danielduyixin/ScoreSystem

//结构体定义别名
typedef struct node Node;

//定义链表节点的数据格式
struct node
{
	char NAME[10];
	char ID[10];
	float SCORE;
	struct node *next;
} NODE;//定义结构体数组

//下面是本程序中所有的函数声明

Node *Read(); //从文件读取数据

Node *Creat(Node *head); //创建链表

int Len(Node *head); //计算链表长度

void Menu(); //显示主菜单

void menu(); //显示副菜单

void Password(); //模拟密码输入

void New_Data(); //随机生成新数据

void Restore_default(); //恢复默认数据

void Add(Node *head); //链表添加节点

void Print(Node *head); //输出链表

void Write(Node *head); //把数据写入文件

void Sort_by_ID(Node *head); //根据ID排序

void Sort_by_NAME(Node *head); //根据NAME字母顺序排序

void Sort_by_SCORE(Node *head); //根据分数从高到低顺序排序

void Average_SCORE(Node *head); //计算最高分，最低分，去掉最高最低的平均分

Node *Del_by_ID(Node *head, char del_id[10]); //根据ID删除数据

Node *Del_by_NAME(Node *head, char del_name[20]); //根据NAME删除数据

void Find_by_ID(Node *head, char find_id[10]); //根据ID查找数据

void Find_by_NAME(Node *head, char find_name[20]); //根据NAME查找数据

void Find_by_SCORE(Node *head, float find_score); //根据分数查找数据

void Modify_by_name(Node *head, char md_name[20]); //根据NAME修改数据

int main() //主函数
{
	Menu(); //直接进入主菜单
	return 0;
}

//链表交换节点代码
//因为没有完全掌握，不知道怎么在排序中使用，所以没有写进来
//void Swap(Node *pr, Node *n1, Node *n2, Node *nt)
//{
//  //交换节点： n1 和 n2
//  //参考出处： https://www.jianshu.com/p/bd4dc088e97a
//	Node *temp = (Node *) malloc(sizeof(Node));
//	temp->next = nt;
//	n1->next = nt;
//	n2->next = pr->next;
//	pr->next = n1;
//	pr->next = n2;
//	temp = NULL;
//	free(temp);
//}

int Len(Node *head) //计算链表长度
{
	Node *p = head; //head作为链表起点标志，函数中用p循环，下同
	int count = 1;  //从head开始，第一个已经存在，所以从1开始，而不是从0
	while (1) {
		if (p->next != NULL) { //直到最后一个节点，其next为NULL
			count++;
			p = p->next;
		}
		else {
			break;
		}
	}
	return count;
}

void Restore_default() //恢复默认数据
{
	FILE *fp;
	int i, t, lines;
	char file_content[30][30] =
			{
					"Jacob       102      86.40\n",
					"Archie      107      57.50\n",
					"Katherine   109      93.10\n",
					"ABech       111      99.50\n",
					"Megan       112      92.90\n",
					"Abdfh       105      84.50\n",
					"William     113      63.60\n",
					"Veronica    115      57.40\n",
					"Abech       114      57.50\n",
					"Tina        103      30.30\n",
					"Fred        110      60.77\n",
					"Alice       101      77.80\n",
					"Betty       108      58.10\n",
					"Cheryl      104      63.60\n",
					"AbaDh       106      67.62"};//最后一行不写换行
	lines = 0;
	for (i = 0; i < 30; i++) {
		for (t = 0; t < 30; t++) {
			if (file_content[i][t] == '\n') {
				lines++;
				//匹配到每行的换行符，就算作一个，跳过最后一行
				break;
			}
		}
	}
	lines = lines + 1; //上面跳过了最后一行，所以要加1
	
	mkdir(file_address);
	fp = fopen(data_address, "w+");
	printf("即将把所有数据恢复默认！\n");
	system("cls");
	printf("\n将默认数据写入文件...\n");
	//	for (i = 0; i < 6; i++) {
	//		printf("*");
	//		Sleep(500);
	//	}
	i = 0;
	do {
		fputs(file_content[i++], fp);
	} while (i < lines);
	fclose(fp);
	printf("\n已完成！！！\n\n");
	printf("\n");
	system("pause");
	system("cls");
	Menu();
}

void menu() //显示副菜单
{
	Node *head;
	//定义各个选项用到的选择变量
	int choice_2 = 998; //因为第一次运行时就会判断，所以必须强制初始化
	int choice_3;
	int choice_4;
	int choice_5;
	if (choice_2 == 9) {
		goto begin; //跳转到删除数据后
	}
begin:
	printf("0:退出程序\n");
	printf("1:显示所有数据\n");
	printf("2:添加数据\n");
	printf("3:删除数据\n");
	printf("4:修改数据\n");
	printf("5:查询数据\n");
	printf("6:数据排序\n");
	printf("7:平均分计算\n");
	printf("8:随机生成新数据\n");
	printf("9:删除所有数据\n");
	printf("11:返回主菜单\n");
	printf("\n请选择：");
	scanf("%d", &choice_2); //选择需要的操作
	switch (choice_2) {
		case 11: //返回主菜单
			system("cls");
			getchar();
			Menu(); //此BUG已解决
			//参考：https://blog.csdn.net/mealu00/article/details/75019813
		case 0:     //退出程序
			exit(0);
		case 1: //打印数据
			//每次用到head的函数，都必须从文件读取
			// 不知道此处是否可以写在循环外
			head = Read();
			system("cls");
			Print(head);
			system("cLs");
			printf("\n");
			goto begin;
			break;
		case 2: //添加数据
			head = Read();
			system("pause");
			system("cls");
			int i = 0;
			int x[20];
			int length = Len(head);
			Node *p;
			p = head;
			//对使用过的学号排序
			while (p != NULL) { //把学号读入x
				x[i++] = atoi(p->ID);
				p = p->next;
			}
			int t, temp;
			for (i = 0; i < length; i++) {
				for (t = 0; t < length - i - 1; t++) {
					if (x[t] > x[t + 1]) {
						temp = x[t];
						x[t] = x[t + 1];
						x[t + 1] = temp;
					}
				}
			}
			i = 0;
			system("cls");
			printf("所有使用过的ID如下：\n");
			while (i < length) { //输出所有已经使用过的学号，避免重复
				printf("%-5d", x[i++]);
				if (i % 4 == 0) {
					printf("\n");
				}
			}
			Add(head);
			Write(head);
			head = Read();
			Print(head);
			system("cls");
			printf("\n");
			goto begin;
			break;
		case 3: //删除数据
			head = Read();
			char del_id[10];
			char del_name[10];
			system("cls");
			printf("\n列出所有数据：\n");
			while (head != NULL) { //先打印出所有数据，好观察需要删除哪一个
				printf("%-12s%-6s%-5.2f\n", head->NAME, head->ID, head->SCORE);
				head = head->next;
			}
			printf("\n");
			printf("欢迎来到删除数据界面！\n");
			printf("1.输入ID，删除数据\n");
			printf("2.输入NAME，删除数据\n");
			printf("\n请输入需要的操作：");
			scanf("%d", &choice_3);
			switch (choice_3) {
				case 1:
					head = Read();
					printf("请输入需要删除数据的ID：");
					scanf("%9s", del_id);
					head = Del_by_ID(head, del_id);
					Write(head);
					printf("\n");
					Print(head);
					system("cls");
					goto begin;
					break;
				case 2:
					head = Read();
					printf("请输入需要删除数据的NAME：");
					scanf("%9s", del_name);
					head = Del_by_NAME(head, del_name);
					Write(head);
					printf("\n");
					Print(head);
					system("cls");
					goto begin;
					break;
			}
		case 4: //修改数据
			head = Read();
			system("cls");
			char md_name[10];
			printf("\n列出所有数据：\n");
			while (head != NULL) { //先打印出所有数据，好观察需要修改哪一个
				printf("%-12s%-6s%-5.2f\n", head->NAME, head->ID, head->SCORE);
				head = head->next;
			}
			head = Read();
			printf("\n");
			printf("请输入需要修改数据的人的名字：");
			scanf("%s", md_name);
			Modify_by_name(head, md_name);
			Write(head);
			printf("\n");
			Print(head);
			system("cLs");
			goto begin;
			break;
		case 5: //查询数据
			head = Read();
			system("cls");
			char find_id[10];
			char find_name[10];
			float find_score;
			system("cls");
			printf("\n列出所有数据：\n");
			while (head != NULL) {
				printf("%-12s%-6s%-5.2f\n", head->NAME, head->ID, head->SCORE);
				head = head->next;
			}
			printf("\n");
			printf("欢迎来到数据查询界面！\n");
			printf("1.输入ID，查询数据\n");
			printf("2.输入NAME，查询数据\n");
			printf("3.输入SCORE，查询数据\n");
			printf("\n请输入需要的操作：");
			scanf("%d", &choice_4);
			switch (choice_4) {
				case 1:
					head = Read();
					printf("请输入需要查询的ID：");
					scanf("%s", find_id);
					Find_by_ID(head, find_id);
					printf("\n");
					system("pause");
					system("cls");
					goto begin;
					break;
				case 2:
					head = Read();
					printf("请输入需要查询的NAME：");
					scanf("%s", find_name);
					Find_by_NAME(head, find_name);
					printf("\n");
					system("pause");
					system("cls");
					goto begin;
					break;
				case 3:
					head = Read();
					printf("请输入需要查询的SCORE：");
					scanf("%f", &find_score);
					Find_by_SCORE(head, find_score);
					printf("\n");
					system("pause");
					system("cls");
					goto begin;
					break;
			}
		case 6: //数据排序
			head = Read();
			system("cls");
			printf("\n欢迎来到数据排序界面！\n");
			printf("1:按照姓名字母顺序排序\n");
			printf("2:按照ID排序\n");
			printf("3:按照分数从高到低排序\n");
			printf("\n请输入需要的操作：");
			scanf("%d", &choice_5);
			switch (choice_5) {
				case 1:
					Sort_by_NAME(head);
					Write(head);
					printf("\n排序后数据已写入文件！\n\n");
					system("pause");
					Print(head);
					system("cLs");
					break;
				case 2:
					Sort_by_ID(head);
					Write(head);
					printf("\n排序后数据已写入文件！\n\n");
					system("pause");
					Print(head);
					system("cLs");
					break;
				case 3:
					Sort_by_SCORE(head);
					Write(head);
					printf("\n排序后数据已写入文件！\n\n");
					system("pause");
					Print(head);
					system("cLs");
					break;
			}
			printf("\n");
			goto begin;
			break;
		case 7: //计算平均
			head = Read();
			system("cls");
			Average_SCORE(head);
			printf("\n");
			system("pause");
			system("cls");
			goto begin;
			break;
		case 8: //随机生成新数据
			system("cls");
			New_Data();       //此时数据已写入文件，不需要Write函数
			head = Read();    //再从文件读入新数据，不然没法Print
			Print(head);
			system("cLs");
			printf("\n");
			goto begin;
			break;
		case 9: //数据清除
			system("cls");
			printf("请谨慎操作！！！\n");
			printf("即将删除所有数据！！！\n");
			printf("输入超过10位默认输入错误！\n");
			printf("默认密码123\n");
			printf("按下退格键，可以已输入的一个字符\n");
			printf("\n输入密码以继续：");
			Password(); //模拟密码输入函数
	}
}

void Password() //模拟密码输入函数
{
	char *password = "123"; //定义默认密码
	// 字符串指针类型，无法修改，保证安全
	char ch, input[10]; //ch输入的字符，input输入的字符串
	int i = 0;
	
	//参考：http://www.voidcn.com/article/p-ojbjkige-bpp.html
	while (i < 10) {
		ch = getch();
		if (ch == '\r') { //回车结束输入
			printf("\n");
			break;
		}
		if (ch == '\b' && i > 0) { //按下删除键，则退格
			i--;
			printf("\b \b"); //这里不是很懂为什么这么写
		}
		else if (isprint(ch)) { //如果输入的是可打印的字符
			input[i] = ch;
			printf("*");
			i++;
		}
	}
	input[i] = 0; //这里也不是很懂，复制粘贴的
	
	if (!strcmp(password, input)) { //比较输入的内容是否匹配默认密码
		printf("\n密码正确！\n");
		printf("\n开始删除数据！\n");
		//		for (i = 0; i < 10; i++) {
		//			printf("*");
		//			Sleep(500);
		//		}
		
		//清空文件内容，而不删除文件
		//参考：https://blog.csdn.net/u010889616/article/details/47670555
		int fp = open(data_address, O_RDWR);   //这里不是fopen
		ftruncate(fp, 0);                      //清空文件内容，文件并未被删除
		lseek(fp, 0, SEEK_SET);                //重新设置文件指针偏移量
		close(fp);                             //这里不是fclose
		
		//上面的和下面的效果相同，但是更有逼格
		//		FILE *fp = fopen(data_address,"w");
		//		fclose(fp);
		
		printf("\n\n所有数据已完全删除！！！\n\n");
		system("pause");
		system("cls");
		menu();
	}
	else {
		printf("\n\n密码错误！\n");
		printf("即将返回主菜单！\n");
		printf("\n");
		system("pause");
		//		for (i = 0; i < 6; i++) {
		//			printf("%d...", i);
		//			Sleep(800);
		//			printf("\b\b\b\b");//清除上面打印的内容，准备重新打印
		//		}
		system("cls");
		menu();
	}
}

void Menu() //主菜单
{
	char choice;       //定义下面的选择
	Node *head = NULL; //默认初试化为NULL
start:
	printf("              ");
	printf("**************************************\n");
	printf("              ");
	printf("******");
	printf("欢迎来到大学生成绩管理系统");
	printf("******\n");
	printf("              ");
	printf("**************************************\n");
	printf("              ");
	printf("        ");
	printf("Write By Daniel Du\n");
	printf("              ");
	printf("       ");
	printf("All Rights Reserved\n");
	printf("              ");
	printf("\n");
	printf("              ");
	printf("               ");
	printf("菜单：\n");
	printf("\n");
	printf("                     ");
	printf("请选择程序运行模式：\n");
	printf("                     ");
	printf("1：自己输入数据运行\n");
	printf("                     ");
	printf("2：读取原始数据运行\n");
	printf("                     ");
	printf("  ");
	printf("3：写入默认数据\n");
	printf("                     ");
	printf("    ");
	printf("4：退出程序\n");
	printf("                     ");
	printf("      ");
	printf("请选择：");
	choice = getchar();
	if (choice == '1' || choice == '2' || choice == '3') {
		goto out; //若输入正确的既定选项，则继续运行
	}
	else {
		printf("\n\n输入错误，请重新输入!!!\n");
		system("pause");
		system("cls");
		goto start;
		//BUG:输入超过一个字符后，就会循环判断为错，不知道如何判断输入的字符个数
	}
out:
	switch (choice) {
		case '1': //自己输入数据运行
			printf("\n");
			printf("                ");
			printf("此操作将会清除已存储的任何数据，\n");
			printf("                ");
			printf("           ");
			printf("并新建文件！\n\n");
			system("pause");
			head = Creat(head);
			Write(head);
			Print(head);
			system("cLs");
			printf("\n已完成！\n\n");
			menu(); //返回副菜单
			break;
		case '2': //读取原始数据运行
			system("cls");
			Read();
			int i;
			//			for (i = 0; i < 6; i++) {
			//				printf("*");
			//				Sleep(500);
			//			}
			printf("\n");
			printf("原始数据已完成读取！\n\n");
			system("pause");
			system("cls");
			printf("\n请选择接下来的操作:\n");
			menu();
			break;
		case '3':
			Restore_default();
		case '4': //退出程序
			exit(0);
	}
}

void Average_SCORE(Node *head) //统计最高分，最低分，计算平均分
{
	Node *p = head;
	int i;                                 //循环变量
	float sum = 0;                         //总分
	float max_SCORE, min_SCORE, average; //最高分，最低分，平均分
	int numbers = Len(head);             //计算平均分，需要统计有几个数据录入
	char max_ID[10];                     //最高分的ID
	char max_NAME[10];                     //最高分的NAME
	char min_ID[10];                     //最低分的ID
	char min_NAME[10];                     //最低分的NAME
	max_SCORE = head->SCORE;             //先初始化为第一个，下同
	min_SCORE = head->SCORE;
	while (p->next != NULL) {
		if (p->SCORE > max_SCORE) { //有比最大的还大，就重置最大，下同
			max_SCORE = p->SCORE;
			strcpy(max_NAME, p->NAME);
			strcpy(max_ID, p->ID);
		}
		p = p->next;
	}
	p = head; //将指针位置回归链表开头
	while (p->next != NULL) {
		if (p->SCORE < min_SCORE) {
			min_SCORE = p->SCORE;
			strcpy(min_NAME, p->NAME);
			strcpy(min_ID, p->ID);
		}
		p = p->next;
	}
	p = head; //将指针位置回归链表开头
	while (p->next != NULL) {
		if (p->SCORE == min_SCORE || p->SCORE == max_SCORE) {
			p = p->next;
			continue;
		}
		sum = sum + p->SCORE;
		p = p->next;
	}
	average = sum / (numbers - 2); //去掉了最高最低，所以数目减2
	printf("\n\n");
	printf("最高分：%g\n", max_SCORE);
	printf("学号：%s\n", max_ID);
	printf("姓名：%s \n", max_NAME);
	printf("\n");
	printf("最低分：%g\n", min_SCORE);
	printf("学号：%s\n", min_ID);
	printf("姓名：%s \n", min_NAME);
	printf("\n");
	printf("去掉一个最高分");
	//	for (i = 0; i < 5; i++) {
	//		printf("*");
	//		Sleep(500);
	//	}
	printf("\n");
	printf("去掉一个最低分");
	//	for (i = 0; i < 5; i++) {
	//		printf("*");
	//		Sleep(500);
	//	}
	printf("\n");
	printf("\n最后的平均分为：%.2f分\n", average);
}

void New_Data() //随机生成新数据
{
	int i, t;                 //循环变量
	char file_names[30][30]; //存储从文件中读入的名字
	char names[30][30];         //存储处理好的每行数据
	i = 0;
	FILE *fp = fopen(names_address, "r");
	while (!feof(fp)) {
		fscanf(fp, "%s", file_names[i]); //把文件名字数据存入数组
		i++;
	}
	fclose(fp);
	
	//生成选取NAME函数的随机数
	srand((unsigned) time(NULL)); //用时间做种，每次产生随机数不一样
	int NAMES_index[30];
	for (i = 0; i < 11; i++) {                                      //因为名字列表默认11个，所以大小定为11
		NAMES_index[i] = rand() % 11 + 0; //范围：0到10,不包含11
		t = 0;
		while (t < i) {
			if (NAMES_index[t++] == NAMES_index[i]) {
				//检测是否有相同数，如果有，则下标减一，回去重新生成
				i--;
				break;
			}
		}
	}
	
	//读取随机数，按随机数随机选取名字存入到names
	int index; //定义索引，按照该索引，从名字列表选取名字
	for (i = 0; i < 11; i++) {
		index = NAMES_index[i];
		strcpy(names[i], file_names[index]);
	}
	//这样每次生成的数据，名字从上到下的顺序都不一样
	
	//生成随机ID
	int ID[11]; //随机ID
	for (i = 0; i < 11; i++) {
		ID[i] = rand() % 21 + 100; //范围：100到120，不包含121
		t = 0;
		while (t < i) {
			if (ID[t++] == ID[i]) {
				//检测是否有相同数，如果有，则下标减一，回去重新生成
				i--;
				break;
			}
		}
	}
	
	//生成随机SCORE
	float scores[11]; //随机SCORES
	for (i = 0; i < 11; i++) {
		scores[i] = (float) (rand() % 700 + 300) / 10;
		//生成随机数：300到999，再除以10 -- 30到99.9
		t = 0;
		while (t < i) {
			if (scores[t++] == scores[i]) {
				//检测是否有相同数，如果有，则下标减一，回去重新生成
				i--;
				break;
			}
		}
	}
	
	fp = fopen(data_address, "w+");
	for (i = 0; i < 11; i++) { //可以直接按格式写入，不用手动加空格
		fprintf(fp, "%-12s", names[i]);
		fprintf(fp, "%-9d", ID[i]);
		fprintf(fp, "%-5.2f", scores[i]);
		if (i == 10) {
			break; //避免最后一行的后面还有空行，默认11个，文件内也是11个数据
		}
		fputc('\n', fp);
	}
	fclose(fp);
}

Node *Del_by_NAME(Node *head, char del_name[10]) //根据名字删除数据
{
	int i;                         //循环变量
	Node *p = head, *pre = NULL; //保持head永远都是第一个，不会变
	Node *new_head;
	
	while (1) { //p为NULL时，结束循环
		if (!strcmp(p->NAME, del_name)) { //如果匹配到要删除的则退出
			break;
		}
		p = p->next;
		if (p == NULL) {
			printf("\n没找到NAME对应的数据！！！\n");
			printf("要删除的数据不存在！！！\n\n");
			system("pause");
			return head;
		}
	}
	if (!strcmp(head->NAME, del_name)) { //删除第一个节点的数据
		new_head = head->next;
		free(p);
		printf("\n匹配到需要删除的数据！\n");
		printf("\n正在处理，请稍后...\n");
		//		for (i = 0; i < 6; i++) {
		//			printf("*");
		//			Sleep(500);
		//		}
		printf("\n\n已完成！\n\n");
		system("pause");
		return new_head;
	}
	p = head; //重置指针位置
	while (p->next != NULL) {
		pre = p;
		p = p->next;
		if (!strcmp(p->NAME, del_name)) {
			printf("\n匹配到需要删除的数据！\n");
			printf("\n正在处理，请稍后...\n");
			//			for (i = 0; i < 6; i++) {
			//				printf("*");
			//				Sleep(500);
			//			}
			printf("\n\n已完成！\n\n");
			system("pause");
			break;
		}
	}
	pre->next = p->next;
	return head;
}

Node *Del_by_ID(Node *head, char del_id[10]) //根据ID删除数据
{
	int i;
	Node *p = head, *pre = NULL; //保持head永远都是第一个，不会变
	Node *new_head;
	
	while (1) { //p为NULL时，结束循环
		if (!strcmp(p->ID, del_id)) { //如果匹配到要删除的则退出
			break;
		}
		p = p->next;
		if (p == NULL) {
			printf("\n没找到ID对应的数据！！！\n");
			printf("要删除的数据不存在！！！\n\n");
			system("pause");
			return head;
		}
	}
	if (!strcmp(head->ID, del_id)) { //删除第一个节点的数据
		new_head = head->next;
		free(p);
		//		for (i = 0; i < 6; i++) {
		//			printf("*");
		//			Sleep(500);
		//		}
		printf("\n\n已完成！\n\n");
		system("pause");
		return new_head;
	}
	p = head;
	while (p->next != NULL) {
		pre = p;
		p = p->next;
		if (!strcmp(p->ID, del_id)) {
			printf("\n匹配到需要删除的数据！\n");
			printf("\n正在处理，请稍后...\n");
			for (i = 0; i < 6; i++) {
				printf("*");
				Sleep(500);
			}
			printf("\n\n已完成！\n\n");
			system("pause");
			break;
		}
	}
	pre->next = p->next;
	return head;
}

void Find_by_SCORE(Node *head, float find_score) //根据分数查询数据
{
	int count = 0;
	Node *p = head;
	while (p != NULL) {
		if (find_score == p->SCORE) {
			printf("\n找到了！\n");
			printf("%-12s%-9s%-5.2f\n", p->NAME, p->ID, p->SCORE);
			count++;
		}
		p = p->next;
	}
	printf("\n共有%d个人的分数是\"%g\"\n", count, find_score);
}

void Find_by_ID(Node *head, char find_id[10]) //根据ID查询数据
{
	int flag = 0;
	Node *p = head;
	while (p != NULL) {
		if (!(strcmp(find_id, p->ID))) {
			flag = 1;
			printf("\n找到了！\n");
			printf("%-12s%-9s%-5.2f\n", p->NAME, p->ID, p->SCORE);
			break;
		}
		p = p->next;
	}
	if (flag != 1) {
		printf("\n没有查询到相关数据！\n");
		printf("即将返回主菜单！\n\n");
		//		system("pause");
		system("cls");
		return;
	}
}

void Find_by_NAME(Node *head, char find_name[10]) //根据NAME查询数据
{
	Node *p = head;
	while (p != NULL) {
		if (!(strcmp(find_name, p->NAME))) {
			printf("\n找到了！\n");
			printf("%-12s%-9s%-5.2f\n", p->NAME, p->ID, p->SCORE);
			break;
		}
		p = p->next;
	}
}

void Sort_by_ID(Node *head) //根据ID排序
{
	int len;
	int i, t;
	len = Len(head);
	Node *p = head, *q;
	float temp_SCORE;
	char temp_ID[10];
	char temp_NAME[10];
	
	for (i = 0; i < len; i++, p = p->next) {
		for (t = 0, q = p->next; t < len - 1 - i; t++, q = q->next) {
			if (atoi(q->ID) < atoi(p->ID)) {
				
				temp_SCORE = q->SCORE;
				q->SCORE = p->SCORE;
				p->SCORE = temp_SCORE;
				
				strcpy(temp_ID, q->ID);
				strcpy(q->ID, p->ID);
				strcpy(p->ID, temp_ID);
				
				strcpy(temp_NAME, q->NAME);
				strcpy(q->NAME, p->NAME);
				strcpy(p->NAME, temp_NAME);
			}
		}
	}
}

void Sort_by_NAME(Node *head) //根据NAME字母顺序排序
{
	int i, t;
	int len;
	len = Len(head);
	Node *p = head, *q;
	float temp_SCORE;
	char temp_ID[10];
	char temp_NAME[10];
	char a[10], b[10];
	for (i = 0; i < len; i++, p = p->next) {
		for (t = 0, q = p->next; t < len - 1 - i; t++, q = q->next) {
			strcpy(a, p->NAME);
			strcpy(b, q->NAME);
			if (strcmp(a, b) > 0) {
				//q是：p的下一个节点
				temp_SCORE = q->SCORE;
				q->SCORE = p->SCORE;
				p->SCORE = temp_SCORE;
				
				strcpy(temp_ID, q->ID);
				strcpy(q->ID, p->ID);
				strcpy(p->ID, temp_ID);
				
				strcpy(temp_NAME, q->NAME);
				strcpy(q->NAME, p->NAME);
				strcpy(p->NAME, temp_NAME);
			}
		}
	}
}

void Sort_by_SCORE(Node *head) //根据分数从高到低排序
{
	//	Node *pr, *nt;
	//	Node *n1, *n2;
	//	Node *j;
	//	pr = head;
	//交换 节点 来 排序，太难了。实在不会。。。。。。
	//	n1 = pr->next;
	//	n2 = n1->next;
	//	nt = n2->next;
	//	for (pr = head; pr->next != NULL; pr = pr->next) {
	//		for (j = head; j->next != NULL; j = j->next) {
	//			if (j->SCORE > j->next->SCORE) {
	//				Swap(pr,n1,n2,nt);
	//			}
	//		}
	//	}
	
	// 下面是：交换值 来排序，算法：冒泡排序，慢就慢吧，好在稳定
	int i, t;
	int len;
	len = Len(head);
	Node *p = head, *q;
	float temp_SCORE;
	char temp_ID[10];
	char temp_NAME[10];
	
	for (i = 0; i < len; i++, p = p->next) {
		for (t = 0, q = p->next; t < len - 1 - i; t++, q = q->next) {
			if (q->SCORE > p->SCORE) {
				
				temp_SCORE = q->SCORE;
				q->SCORE = p->SCORE;
				p->SCORE = temp_SCORE;
				
				strcpy(temp_ID, q->ID);
				strcpy(q->ID, p->ID);
				strcpy(p->ID, temp_ID);
				
				strcpy(temp_NAME, q->NAME);
				strcpy(q->NAME, p->NAME);
				strcpy(p->NAME, temp_NAME);
			}
		}
	}
}

Node *Read() //从文件读取数据
{
	int i, t, lines;
	FILE *fp;
	Node *head = NULL;
	Node *p, *q = NULL;
	char file_content[30][30] =
			{
					"Jacob       102      86.40\n",
					"Archie      107      57.50\n",
					"Katherine   109      93.10\n",
					"ABech       111      99.50\n",
					"Megan       112      92.90\n",
					"Abdfh       105      84.50\n",
					"William     113      63.60\n",
					"Veronica    115      57.40\n",
					"Abech       114      57.50\n",
					"Tina        103      30.30\n",
					"Fred        110      60.77\n",
					"Alice       101      77.80\n",
					"Betty       108      58.10\n",
					"Cheryl      104      63.60\n",
					"AbaDh       106      67.62"};
	
	//计算每行实际长度，不算入'\n'，不知道当时为什么要写这个
	//	for (i = 0; i < 30; i++) {
	//		if (file_content[0][i] == '\n') {
	//			break;//计算实际每行长度，不算入'\n'
	//		}
	//	}
	//	line_size = i + 1;
	
	lines = 0;
	for (i = 0; i < 30; i++) {
		for (t = 0; t < 30; t++) {
			if (file_content[i][t] == '\n') {
				lines++;
				//匹配到每行的换行符，就算作一个，此操作跳过了最后一行
				break;
			}
		}
	}
	lines = lines + 1; //上面跳过了最后一行，所以要加1
	
	fp = fopen(data_address, "r+");
	//判断文件是否存在
	if (fp == NULL) {
		fclose(fp);
		printf("\n数据文件不存在，正在创建...\n");
		//		for (i = 0; i < 6; i++) {
		//			printf("*");
		//			Sleep(500);
		//		}
		mkdir("E:\\Git\\Code\\CLion\\FILES");
		fp = fopen(data_address, "w+");
		printf("\n已完成！！！\n\n");
		printf("将默认数据写入文件...\n");
		//		for (i = 0; i < 6; i++) {
		//			printf("*");
		//			Sleep(500);
		//		}
		i = 0;
		do {
			fputs(file_content[i++], fp);
		} while (i < lines);
		printf("\n已完成！！！\n\n");
		printf("\n");
		system("pause");
		system("cls");
		goto next; //文件不存在跳过判断内容是否为空
	}
	
	//判断文件内容是否为空
	//参考：https://blog.csdn.net/lwpping/article/details/7441950
	char ch = fgetc(fp);
	if (ch == EOF) {
		printf("\n文件内容为空！\n");
		printf("\n即将返回主菜单！\n\n");
		printf("\n");
		system("pause");
		system("cls");
		Menu();
	}

next:
	rewind(fp); //从头开始读文件
	printf("\n开始从文件读入数据...\n");
	//	for (i = 0; i < 6; i++) {
	//		printf("*");
	//		Sleep(500);
	//	}
	printf("\n已完成！！！\n\n");
	while (!feof(fp)) {
		fscanf(fp, "%s", NODE.NAME);
		fscanf(fp, "%s", NODE.ID);
		fscanf(fp, "%g", &NODE.SCORE);
		//		if (feof(fp)) {
		//			break;
		//		}//跳过最后一行空行
		//前面代码修改过以后，这里就不需要跳过了
		//现在最后一行就是数据，没有空行了
		//哈哈哈哈哈哈，我真是个小天才
		
		if (NODE.SCORE <= 0) {
			goto illegal;
		}
		p = (Node *) malloc(sizeof(Node));
		strcpy(p->NAME, NODE.NAME);
		strcpy(p->ID, NODE.ID);
		p->SCORE = NODE.SCORE;
		p->next = NULL;
		if (NODE.SCORE > 0) {
			if (head != NULL) {
				q->next = p;
			}
			else {
				head = p;
			}
		}
		else {
illegal:
			printf("数据不存在，或有不合法的数据被读入，程序结束！！！\n");
			goto end;
		}
		q = p;
		p = NULL;
		q->next = NULL;
		free(p);
	}
	fclose(fp);
end:
	fclose(fp);
	return head;
}

void Modify_by_name(Node *head, char md_name[10])
{
	Node *p = head;
	float new_SCORE;
	while (1) { //p为NULL时，结束循环
		if (!strcmp(p->NAME, md_name)) { //如果匹配到要删除的则退出
			break;
		}
		p = p->next;
		if (p == NULL) {
			printf("\n没找到NAME对应的数据！！！\n");
			printf("要修改的数据不存在！！！\n\n");
			system("pause");
			return;
		}
	}
	if (p == NULL) //没有匹配到
	{
		printf("没有匹配的数据！\n");
		system("pause");
		return;
	}
back:
	printf("请输入修改后的成绩：");
	scanf("%f", &new_SCORE);
	if (new_SCORE == 0) {
		printf("修改的成绩不合法，必须大于0！\n");
		printf("请重新输入！\n");
		goto back;
	}
	p->SCORE = new_SCORE;
	//	for (t = 0; t < 5; t++) {
	//		Sleep(100);
	//		printf("*");
	//		Sleep(200);
	//	}
	printf("\n修改成功！！！\n");
}

void Add(Node *head)
{
	Node *p = head;
	Node *q;
	Node *new = NULL;
	char NAME[10];
	char ID[10];
	float SCORE = 0;
	while (p->next != NULL) {
		p = p->next;
	}
begin:
	printf("\n开始增加数据:\n");
	printf("\n录入数据注意事项：\n");
	printf("1：分数必须大于0\n");
	printf("2：学号最好使用101,102这种格式\n");
	printf("\n");
	printf("输入0 0 0来退出程序\n");
	do {
		new = (Node *) malloc(sizeof(Node));
		printf("请输入姓名，ID，分数（以空格隔开）：\n");
		scanf("%s%s%f", NAME, ID, &SCORE);
		if (SCORE < 0) {
			printf("\n输入的数据不合法，请重试！\n");
			system("pause");
			system("cls");
			goto begin;
		} //判断SCORE是不是负数
		if (atoi(ID) < 0) {
			printf("\n输入的数据不合法，请重试！\n");
			system("pause");
			system("cls");
			goto begin;
		} //判断ID是不是负数
		if (SCORE == 0) {
			system("cls");
			goto end;
		} //输入0 0 0，退出
		q = head;
		while (q != NULL) {
			if (!strcmp(q->ID, ID)) {
				printf("\n存在重复的ID，请重试！\n\n");
				system("pause");
				system("cls");
				goto begin;
			}
			q = q->next;
		} //判断是否存在重复ID
		q = head;
		while (q != NULL) {
			if (!strcmp(q->NAME, NAME)) {
				printf("\n存在重复的NAME，请重试！\n\n");
				system("pause");
				system("cls");
				goto begin;
			}
			q = q->next;
		} //判断是否存在重复NAME
		strcpy(new->NAME, NAME);
		strcpy(new->ID, ID);
		new->SCORE = SCORE;
		new->next = NULL;
		p->next = new;
		p = new;
	} while (SCORE != 0);
end:
	free(new);
	return;
}

Node *Creat(Node *head)
{
	char NAME[10];
	char ID[10];
	float SCORE;
	Node *p, *q = NULL;
	system("cls");
	printf("数据输入开始:\n");
	printf("\n录入数据注意事项：\n");
	printf("1：分数必须大于0\n");
	printf("2：学号最好使用101,102这种格式\n");
	printf("\n输入0 0 0来退出程序\n\n");
	while (1) {
start:
		printf("\n请输入姓名，ID，分数（以空格隔开）：\n");
		scanf("%s%s%f", NAME, ID, &SCORE);
		if (SCORE == 0) {
			goto end;
		}
		p = (Node *) malloc(sizeof(Node));
		strcpy(p->NAME, NAME);
		strcpy(p->ID, ID);
		p->SCORE = SCORE;
		p->next = NULL;
		if (SCORE > 0) {
			if (head != NULL) {
				q->next = p;
			}
			else {
				head = p;
			}
		}
		else {
			printf("输入的数据不合法，请重新输入！\n\n");
			goto start;
		}
		q = p;
	}
	p = NULL;
	q->next = NULL;
	free(p);
end:
	return head;
}

void Print(Node *head)
{
	Node *p = head;
	int i = 01;
	if (head == NULL) {
		printf("数据不合法或不存在，无输出！！！\n");
		goto end;
	}
	printf("\n输出所有数据：\n");
	while (p != NULL) {
		if (i <= 9) {
			printf("0%d. ", i++);
		}
		else {
			printf("%d. ", i++);
		}
		printf("%-12s%-9s%-5.2f\n", p->NAME, p->ID, p->SCORE);
		p = p->next;
	}
	printf("\n");
	system("pause");
end:
	return;
}

void Write(Node *head)
{
	Node *p = head;
	printf("\n开始将数据写入文件，请稍后......\n");
	//	Sleep(3);
	printf("\n");
	FILE *fp;
	fp = fopen(data_address, "w+");
	while (p != NULL) {
		fprintf(fp, "%-12s", p->NAME);
		fprintf(fp, "%-9s", p->ID);
		fprintf(fp, "%-5.2f", p->SCORE);
		if (p->next == NULL) { //最后一个不输出下一个空行
			break;
		}
		fputc('\n', fp);
		p = p->next;
	}
	fclose(fp);
	printf("已完成！！！\n\n");
	system("pause");
	system("cls");
}