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
//����ͷ�ļ���ÿһ�����Ǳ���ģ�û�ж���ģ���������ɾ�����Ѱ����ֳ�������

//����ǰ��Ҫ�޸������Ӧ���ļ���ַ��Ŀ¼��ַ
//��ַ��ʽ��\\��˫б�ߣ�����/����б�ߣ�
//names_address -- �洢�����б�
//data_address -- �洢��������ʱ������
//file_address -- �洢�����õ���Data�ļ���Ŀ¼
//����ַ����Ϊ�ַ����������ַ����飬���ñ���������޸Ļ���

char *data_address = "*\\Data";
char *names_address = "*\\names.txt";
char *file_address = "*\\FILES";

//char *data_address = "E:\\Git\\Code\\CLion\\FILES\\Data";
//char *names_address = "E:\\Git\\Code\\CLion\\FILES1\\names3.txt";
//char *file_address = "E:\\Git\\Code\\CLion\\FILES";

//��Ȩ���У�δ����������ת��
//���˱���һ��׷���������ε�Ȩ��
//��ϵ��ʽ��651608356@qq.com
//https://github.com/danielduyixin/ScoreSystem

//�ṹ�嶨�����
typedef struct node Node;

//��������ڵ�����ݸ�ʽ
struct node
{
	char NAME[10];
	char ID[10];
	float SCORE;
	struct node *next;
} NODE;//����ṹ������

//�����Ǳ����������еĺ�������

Node *Read(); //���ļ���ȡ����

Node *Creat(Node *head); //��������

int Len(Node *head); //����������

void Menu(); //��ʾ���˵�

void menu(); //��ʾ���˵�

void Password(); //ģ����������

void New_Data(); //�������������

void Restore_default(); //�ָ�Ĭ������

void Add(Node *head); //������ӽڵ�

void Print(Node *head); //�������

void Write(Node *head); //������д���ļ�

void Sort_by_ID(Node *head); //����ID����

void Sort_by_NAME(Node *head); //����NAME��ĸ˳������

void Sort_by_SCORE(Node *head); //���ݷ����Ӹߵ���˳������

void Average_SCORE(Node *head); //������߷֣���ͷ֣�ȥ�������͵�ƽ����

Node *Del_by_ID(Node *head, char del_id[10]); //����IDɾ������

Node *Del_by_NAME(Node *head, char del_name[20]); //����NAMEɾ������

void Find_by_ID(Node *head, char find_id[10]); //����ID��������

void Find_by_NAME(Node *head, char find_name[20]); //����NAME��������

void Find_by_SCORE(Node *head, float find_score); //���ݷ�����������

void Modify_by_name(Node *head, char md_name[20]); //����NAME�޸�����

int main() //������
{
	Menu(); //ֱ�ӽ������˵�
	return 0;
}

//�������ڵ����
//��Ϊû����ȫ���գ���֪����ô��������ʹ�ã�����û��д����
//void Swap(Node *pr, Node *n1, Node *n2, Node *nt)
//{
//  //�����ڵ㣺 n1 �� n2
//  //�ο������� https://www.jianshu.com/p/bd4dc088e97a
//	Node *temp = (Node *) malloc(sizeof(Node));
//	temp->next = nt;
//	n1->next = nt;
//	n2->next = pr->next;
//	pr->next = n1;
//	pr->next = n2;
//	temp = NULL;
//	free(temp);
//}

int Len(Node *head) //����������
{
	Node *p = head; //head��Ϊ��������־����������pѭ������ͬ
	int count = 1;  //��head��ʼ����һ���Ѿ����ڣ����Դ�1��ʼ�������Ǵ�0
	while (1) {
		if (p->next != NULL) { //ֱ�����һ���ڵ㣬��nextΪNULL
			count++;
			p = p->next;
		}
		else {
			break;
		}
	}
	return count;
}

void Restore_default() //�ָ�Ĭ������
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
					"AbaDh       106      67.62"};//���һ�в�д����
	lines = 0;
	for (i = 0; i < 30; i++) {
		for (t = 0; t < 30; t++) {
			if (file_content[i][t] == '\n') {
				lines++;
				//ƥ�䵽ÿ�еĻ��з���������һ�����������һ��
				break;
			}
		}
	}
	lines = lines + 1; //�������������һ�У�����Ҫ��1
	
	mkdir(file_address);
	fp = fopen(data_address, "w+");
	printf("�������������ݻָ�Ĭ�ϣ�\n");
	system("cls");
	printf("\n��Ĭ������д���ļ�...\n");
	//	for (i = 0; i < 6; i++) {
	//		printf("*");
	//		Sleep(500);
	//	}
	i = 0;
	do {
		fputs(file_content[i++], fp);
	} while (i < lines);
	fclose(fp);
	printf("\n����ɣ�����\n\n");
	printf("\n");
	system("pause");
	system("cls");
	Menu();
}

void menu() //��ʾ���˵�
{
	Node *head;
	//�������ѡ���õ���ѡ�����
	int choice_2 = 998; //��Ϊ��һ������ʱ�ͻ��жϣ����Ա���ǿ�Ƴ�ʼ��
	int choice_3;
	int choice_4;
	int choice_5;
	if (choice_2 == 9) {
		goto begin; //��ת��ɾ�����ݺ�
	}
begin:
	printf("0:�˳�����\n");
	printf("1:��ʾ��������\n");
	printf("2:�������\n");
	printf("3:ɾ������\n");
	printf("4:�޸�����\n");
	printf("5:��ѯ����\n");
	printf("6:��������\n");
	printf("7:ƽ���ּ���\n");
	printf("8:�������������\n");
	printf("9:ɾ����������\n");
	printf("11:�������˵�\n");
	printf("\n��ѡ��");
	scanf("%d", &choice_2); //ѡ����Ҫ�Ĳ���
	switch (choice_2) {
		case 11: //�������˵�
			system("cls");
			getchar();
			Menu(); //��BUG�ѽ��
			//�ο���https://blog.csdn.net/mealu00/article/details/75019813
		case 0:     //�˳�����
			exit(0);
		case 1: //��ӡ����
			//ÿ���õ�head�ĺ�������������ļ���ȡ
			// ��֪���˴��Ƿ����д��ѭ����
			head = Read();
			system("cls");
			Print(head);
			system("cLs");
			printf("\n");
			goto begin;
			break;
		case 2: //�������
			head = Read();
			system("pause");
			system("cls");
			int i = 0;
			int x[20];
			int length = Len(head);
			Node *p;
			p = head;
			//��ʹ�ù���ѧ������
			while (p != NULL) { //��ѧ�Ŷ���x
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
			printf("����ʹ�ù���ID���£�\n");
			while (i < length) { //��������Ѿ�ʹ�ù���ѧ�ţ������ظ�
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
		case 3: //ɾ������
			head = Read();
			char del_id[10];
			char del_name[10];
			system("cls");
			printf("\n�г��������ݣ�\n");
			while (head != NULL) { //�ȴ�ӡ���������ݣ��ù۲���Ҫɾ����һ��
				printf("%-12s%-6s%-5.2f\n", head->NAME, head->ID, head->SCORE);
				head = head->next;
			}
			printf("\n");
			printf("��ӭ����ɾ�����ݽ��棡\n");
			printf("1.����ID��ɾ������\n");
			printf("2.����NAME��ɾ������\n");
			printf("\n��������Ҫ�Ĳ�����");
			scanf("%d", &choice_3);
			switch (choice_3) {
				case 1:
					head = Read();
					printf("��������Ҫɾ�����ݵ�ID��");
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
					printf("��������Ҫɾ�����ݵ�NAME��");
					scanf("%9s", del_name);
					head = Del_by_NAME(head, del_name);
					Write(head);
					printf("\n");
					Print(head);
					system("cls");
					goto begin;
					break;
			}
		case 4: //�޸�����
			head = Read();
			system("cls");
			char md_name[10];
			printf("\n�г��������ݣ�\n");
			while (head != NULL) { //�ȴ�ӡ���������ݣ��ù۲���Ҫ�޸���һ��
				printf("%-12s%-6s%-5.2f\n", head->NAME, head->ID, head->SCORE);
				head = head->next;
			}
			head = Read();
			printf("\n");
			printf("��������Ҫ�޸����ݵ��˵����֣�");
			scanf("%s", md_name);
			Modify_by_name(head, md_name);
			Write(head);
			printf("\n");
			Print(head);
			system("cLs");
			goto begin;
			break;
		case 5: //��ѯ����
			head = Read();
			system("cls");
			char find_id[10];
			char find_name[10];
			float find_score;
			system("cls");
			printf("\n�г��������ݣ�\n");
			while (head != NULL) {
				printf("%-12s%-6s%-5.2f\n", head->NAME, head->ID, head->SCORE);
				head = head->next;
			}
			printf("\n");
			printf("��ӭ�������ݲ�ѯ���棡\n");
			printf("1.����ID����ѯ����\n");
			printf("2.����NAME����ѯ����\n");
			printf("3.����SCORE����ѯ����\n");
			printf("\n��������Ҫ�Ĳ�����");
			scanf("%d", &choice_4);
			switch (choice_4) {
				case 1:
					head = Read();
					printf("��������Ҫ��ѯ��ID��");
					scanf("%s", find_id);
					Find_by_ID(head, find_id);
					printf("\n");
					system("pause");
					system("cls");
					goto begin;
					break;
				case 2:
					head = Read();
					printf("��������Ҫ��ѯ��NAME��");
					scanf("%s", find_name);
					Find_by_NAME(head, find_name);
					printf("\n");
					system("pause");
					system("cls");
					goto begin;
					break;
				case 3:
					head = Read();
					printf("��������Ҫ��ѯ��SCORE��");
					scanf("%f", &find_score);
					Find_by_SCORE(head, find_score);
					printf("\n");
					system("pause");
					system("cls");
					goto begin;
					break;
			}
		case 6: //��������
			head = Read();
			system("cls");
			printf("\n��ӭ��������������棡\n");
			printf("1:����������ĸ˳������\n");
			printf("2:����ID����\n");
			printf("3:���շ����Ӹߵ�������\n");
			printf("\n��������Ҫ�Ĳ�����");
			scanf("%d", &choice_5);
			switch (choice_5) {
				case 1:
					Sort_by_NAME(head);
					Write(head);
					printf("\n�����������д���ļ���\n\n");
					system("pause");
					Print(head);
					system("cLs");
					break;
				case 2:
					Sort_by_ID(head);
					Write(head);
					printf("\n�����������д���ļ���\n\n");
					system("pause");
					Print(head);
					system("cLs");
					break;
				case 3:
					Sort_by_SCORE(head);
					Write(head);
					printf("\n�����������д���ļ���\n\n");
					system("pause");
					Print(head);
					system("cLs");
					break;
			}
			printf("\n");
			goto begin;
			break;
		case 7: //����ƽ��
			head = Read();
			system("cls");
			Average_SCORE(head);
			printf("\n");
			system("pause");
			system("cls");
			goto begin;
			break;
		case 8: //�������������
			system("cls");
			New_Data();       //��ʱ������д���ļ�������ҪWrite����
			head = Read();    //�ٴ��ļ����������ݣ���Ȼû��Print
			Print(head);
			system("cLs");
			printf("\n");
			goto begin;
			break;
		case 9: //�������
			system("cls");
			printf("���������������\n");
			printf("����ɾ���������ݣ�����\n");
			printf("���볬��10λĬ���������\n");
			printf("Ĭ������123\n");
			printf("�����˸���������������һ���ַ�\n");
			printf("\n���������Լ�����");
			Password(); //ģ���������뺯��
	}
}

void Password() //ģ���������뺯��
{
	char *password = "123"; //����Ĭ������
	// �ַ���ָ�����ͣ��޷��޸ģ���֤��ȫ
	char ch, input[10]; //ch������ַ���input������ַ���
	int i = 0;
	
	//�ο���http://www.voidcn.com/article/p-ojbjkige-bpp.html
	while (i < 10) {
		ch = getch();
		if (ch == '\r') { //�س���������
			printf("\n");
			break;
		}
		if (ch == '\b' && i > 0) { //����ɾ���������˸�
			i--;
			printf("\b \b"); //���ﲻ�Ǻܶ�Ϊʲô��ôд
		}
		else if (isprint(ch)) { //���������ǿɴ�ӡ���ַ�
			input[i] = ch;
			printf("*");
			i++;
		}
	}
	input[i] = 0; //����Ҳ���Ǻܶ�������ճ����
	
	if (!strcmp(password, input)) { //�Ƚ�����������Ƿ�ƥ��Ĭ������
		printf("\n������ȷ��\n");
		printf("\n��ʼɾ�����ݣ�\n");
		//		for (i = 0; i < 10; i++) {
		//			printf("*");
		//			Sleep(500);
		//		}
		
		//����ļ����ݣ�����ɾ���ļ�
		//�ο���https://blog.csdn.net/u010889616/article/details/47670555
		int fp = open(data_address, O_RDWR);   //���ﲻ��fopen
		ftruncate(fp, 0);                      //����ļ����ݣ��ļ���δ��ɾ��
		lseek(fp, 0, SEEK_SET);                //���������ļ�ָ��ƫ����
		close(fp);                             //���ﲻ��fclose
		
		//����ĺ������Ч����ͬ�����Ǹ��бƸ�
		//		FILE *fp = fopen(data_address,"w");
		//		fclose(fp);
		
		printf("\n\n������������ȫɾ��������\n\n");
		system("pause");
		system("cls");
		menu();
	}
	else {
		printf("\n\n�������\n");
		printf("�����������˵���\n");
		printf("\n");
		system("pause");
		//		for (i = 0; i < 6; i++) {
		//			printf("%d...", i);
		//			Sleep(800);
		//			printf("\b\b\b\b");//��������ӡ�����ݣ�׼�����´�ӡ
		//		}
		system("cls");
		menu();
	}
}

void Menu() //���˵�
{
	char choice;       //���������ѡ��
	Node *head = NULL; //Ĭ�ϳ��Ի�ΪNULL
start:
	printf("              ");
	printf("**************************************\n");
	printf("              ");
	printf("******");
	printf("��ӭ������ѧ���ɼ�����ϵͳ");
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
	printf("�˵���\n");
	printf("\n");
	printf("                     ");
	printf("��ѡ���������ģʽ��\n");
	printf("                     ");
	printf("1���Լ�������������\n");
	printf("                     ");
	printf("2����ȡԭʼ��������\n");
	printf("                     ");
	printf("  ");
	printf("3��д��Ĭ������\n");
	printf("                     ");
	printf("    ");
	printf("4���˳�����\n");
	printf("                     ");
	printf("      ");
	printf("��ѡ��");
	choice = getchar();
	if (choice == '1' || choice == '2' || choice == '3') {
		goto out; //��������ȷ�ļȶ�ѡ����������
	}
	else {
		printf("\n\n�����������������!!!\n");
		system("pause");
		system("cls");
		goto start;
		//BUG:���볬��һ���ַ��󣬾ͻ�ѭ���ж�Ϊ����֪������ж�������ַ�����
	}
out:
	switch (choice) {
		case '1': //�Լ�������������
			printf("\n");
			printf("                ");
			printf("�˲�����������Ѵ洢���κ����ݣ�\n");
			printf("                ");
			printf("           ");
			printf("���½��ļ���\n\n");
			system("pause");
			head = Creat(head);
			Write(head);
			Print(head);
			system("cLs");
			printf("\n����ɣ�\n\n");
			menu(); //���ظ��˵�
			break;
		case '2': //��ȡԭʼ��������
			system("cls");
			Read();
			int i;
			//			for (i = 0; i < 6; i++) {
			//				printf("*");
			//				Sleep(500);
			//			}
			printf("\n");
			printf("ԭʼ��������ɶ�ȡ��\n\n");
			system("pause");
			system("cls");
			printf("\n��ѡ��������Ĳ���:\n");
			menu();
			break;
		case '3':
			Restore_default();
		case '4': //�˳�����
			exit(0);
	}
}

void Average_SCORE(Node *head) //ͳ����߷֣���ͷ֣�����ƽ����
{
	Node *p = head;
	int i;                                 //ѭ������
	float sum = 0;                         //�ܷ�
	float max_SCORE, min_SCORE, average; //��߷֣���ͷ֣�ƽ����
	int numbers = Len(head);             //����ƽ���֣���Ҫͳ���м�������¼��
	char max_ID[10];                     //��߷ֵ�ID
	char max_NAME[10];                     //��߷ֵ�NAME
	char min_ID[10];                     //��ͷֵ�ID
	char min_NAME[10];                     //��ͷֵ�NAME
	max_SCORE = head->SCORE;             //�ȳ�ʼ��Ϊ��һ������ͬ
	min_SCORE = head->SCORE;
	while (p->next != NULL) {
		if (p->SCORE > max_SCORE) { //�б����Ļ��󣬾����������ͬ
			max_SCORE = p->SCORE;
			strcpy(max_NAME, p->NAME);
			strcpy(max_ID, p->ID);
		}
		p = p->next;
	}
	p = head; //��ָ��λ�ûع�����ͷ
	while (p->next != NULL) {
		if (p->SCORE < min_SCORE) {
			min_SCORE = p->SCORE;
			strcpy(min_NAME, p->NAME);
			strcpy(min_ID, p->ID);
		}
		p = p->next;
	}
	p = head; //��ָ��λ�ûع�����ͷ
	while (p->next != NULL) {
		if (p->SCORE == min_SCORE || p->SCORE == max_SCORE) {
			p = p->next;
			continue;
		}
		sum = sum + p->SCORE;
		p = p->next;
	}
	average = sum / (numbers - 2); //ȥ���������ͣ�������Ŀ��2
	printf("\n\n");
	printf("��߷֣�%g\n", max_SCORE);
	printf("ѧ�ţ�%s\n", max_ID);
	printf("������%s \n", max_NAME);
	printf("\n");
	printf("��ͷ֣�%g\n", min_SCORE);
	printf("ѧ�ţ�%s\n", min_ID);
	printf("������%s \n", min_NAME);
	printf("\n");
	printf("ȥ��һ����߷�");
	//	for (i = 0; i < 5; i++) {
	//		printf("*");
	//		Sleep(500);
	//	}
	printf("\n");
	printf("ȥ��һ����ͷ�");
	//	for (i = 0; i < 5; i++) {
	//		printf("*");
	//		Sleep(500);
	//	}
	printf("\n");
	printf("\n����ƽ����Ϊ��%.2f��\n", average);
}

void New_Data() //�������������
{
	int i, t;                 //ѭ������
	char file_names[30][30]; //�洢���ļ��ж��������
	char names[30][30];         //�洢����õ�ÿ������
	i = 0;
	FILE *fp = fopen(names_address, "r");
	while (!feof(fp)) {
		fscanf(fp, "%s", file_names[i]); //���ļ��������ݴ�������
		i++;
	}
	fclose(fp);
	
	//����ѡȡNAME�����������
	srand((unsigned) time(NULL)); //��ʱ�����֣�ÿ�β����������һ��
	int NAMES_index[30];
	for (i = 0; i < 11; i++) {                                      //��Ϊ�����б�Ĭ��11�������Դ�С��Ϊ11
		NAMES_index[i] = rand() % 11 + 0; //��Χ��0��10,������11
		t = 0;
		while (t < i) {
			if (NAMES_index[t++] == NAMES_index[i]) {
				//����Ƿ�����ͬ��������У����±��һ����ȥ��������
				i--;
				break;
			}
		}
	}
	
	//��ȡ�����������������ѡȡ���ִ��뵽names
	int index; //�������������ո��������������б�ѡȡ����
	for (i = 0; i < 11; i++) {
		index = NAMES_index[i];
		strcpy(names[i], file_names[index]);
	}
	//����ÿ�����ɵ����ݣ����ִ��ϵ��µ�˳�򶼲�һ��
	
	//�������ID
	int ID[11]; //���ID
	for (i = 0; i < 11; i++) {
		ID[i] = rand() % 21 + 100; //��Χ��100��120��������121
		t = 0;
		while (t < i) {
			if (ID[t++] == ID[i]) {
				//����Ƿ�����ͬ��������У����±��һ����ȥ��������
				i--;
				break;
			}
		}
	}
	
	//�������SCORE
	float scores[11]; //���SCORES
	for (i = 0; i < 11; i++) {
		scores[i] = (float) (rand() % 700 + 300) / 10;
		//�����������300��999���ٳ���10 -- 30��99.9
		t = 0;
		while (t < i) {
			if (scores[t++] == scores[i]) {
				//����Ƿ�����ͬ��������У����±��һ����ȥ��������
				i--;
				break;
			}
		}
	}
	
	fp = fopen(data_address, "w+");
	for (i = 0; i < 11; i++) { //����ֱ�Ӱ���ʽд�룬�����ֶ��ӿո�
		fprintf(fp, "%-12s", names[i]);
		fprintf(fp, "%-9d", ID[i]);
		fprintf(fp, "%-5.2f", scores[i]);
		if (i == 10) {
			break; //�������һ�еĺ��滹�п��У�Ĭ��11�����ļ���Ҳ��11������
		}
		fputc('\n', fp);
	}
	fclose(fp);
}

Node *Del_by_NAME(Node *head, char del_name[10]) //��������ɾ������
{
	int i;                         //ѭ������
	Node *p = head, *pre = NULL; //����head��Զ���ǵ�һ���������
	Node *new_head;
	
	while (1) { //pΪNULLʱ������ѭ��
		if (!strcmp(p->NAME, del_name)) { //���ƥ�䵽Ҫɾ�������˳�
			break;
		}
		p = p->next;
		if (p == NULL) {
			printf("\nû�ҵ�NAME��Ӧ�����ݣ�����\n");
			printf("Ҫɾ�������ݲ����ڣ�����\n\n");
			system("pause");
			return head;
		}
	}
	if (!strcmp(head->NAME, del_name)) { //ɾ����һ���ڵ������
		new_head = head->next;
		free(p);
		printf("\nƥ�䵽��Ҫɾ�������ݣ�\n");
		printf("\n���ڴ������Ժ�...\n");
		//		for (i = 0; i < 6; i++) {
		//			printf("*");
		//			Sleep(500);
		//		}
		printf("\n\n����ɣ�\n\n");
		system("pause");
		return new_head;
	}
	p = head; //����ָ��λ��
	while (p->next != NULL) {
		pre = p;
		p = p->next;
		if (!strcmp(p->NAME, del_name)) {
			printf("\nƥ�䵽��Ҫɾ�������ݣ�\n");
			printf("\n���ڴ������Ժ�...\n");
			//			for (i = 0; i < 6; i++) {
			//				printf("*");
			//				Sleep(500);
			//			}
			printf("\n\n����ɣ�\n\n");
			system("pause");
			break;
		}
	}
	pre->next = p->next;
	return head;
}

Node *Del_by_ID(Node *head, char del_id[10]) //����IDɾ������
{
	int i;
	Node *p = head, *pre = NULL; //����head��Զ���ǵ�һ���������
	Node *new_head;
	
	while (1) { //pΪNULLʱ������ѭ��
		if (!strcmp(p->ID, del_id)) { //���ƥ�䵽Ҫɾ�������˳�
			break;
		}
		p = p->next;
		if (p == NULL) {
			printf("\nû�ҵ�ID��Ӧ�����ݣ�����\n");
			printf("Ҫɾ�������ݲ����ڣ�����\n\n");
			system("pause");
			return head;
		}
	}
	if (!strcmp(head->ID, del_id)) { //ɾ����һ���ڵ������
		new_head = head->next;
		free(p);
		//		for (i = 0; i < 6; i++) {
		//			printf("*");
		//			Sleep(500);
		//		}
		printf("\n\n����ɣ�\n\n");
		system("pause");
		return new_head;
	}
	p = head;
	while (p->next != NULL) {
		pre = p;
		p = p->next;
		if (!strcmp(p->ID, del_id)) {
			printf("\nƥ�䵽��Ҫɾ�������ݣ�\n");
			printf("\n���ڴ������Ժ�...\n");
			for (i = 0; i < 6; i++) {
				printf("*");
				Sleep(500);
			}
			printf("\n\n����ɣ�\n\n");
			system("pause");
			break;
		}
	}
	pre->next = p->next;
	return head;
}

void Find_by_SCORE(Node *head, float find_score) //���ݷ�����ѯ����
{
	int count = 0;
	Node *p = head;
	while (p != NULL) {
		if (find_score == p->SCORE) {
			printf("\n�ҵ��ˣ�\n");
			printf("%-12s%-9s%-5.2f\n", p->NAME, p->ID, p->SCORE);
			count++;
		}
		p = p->next;
	}
	printf("\n����%d���˵ķ�����\"%g\"\n", count, find_score);
}

void Find_by_ID(Node *head, char find_id[10]) //����ID��ѯ����
{
	int flag = 0;
	Node *p = head;
	while (p != NULL) {
		if (!(strcmp(find_id, p->ID))) {
			flag = 1;
			printf("\n�ҵ��ˣ�\n");
			printf("%-12s%-9s%-5.2f\n", p->NAME, p->ID, p->SCORE);
			break;
		}
		p = p->next;
	}
	if (flag != 1) {
		printf("\nû�в�ѯ��������ݣ�\n");
		printf("�����������˵���\n\n");
		//		system("pause");
		system("cls");
		return;
	}
}

void Find_by_NAME(Node *head, char find_name[10]) //����NAME��ѯ����
{
	Node *p = head;
	while (p != NULL) {
		if (!(strcmp(find_name, p->NAME))) {
			printf("\n�ҵ��ˣ�\n");
			printf("%-12s%-9s%-5.2f\n", p->NAME, p->ID, p->SCORE);
			break;
		}
		p = p->next;
	}
}

void Sort_by_ID(Node *head) //����ID����
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

void Sort_by_NAME(Node *head) //����NAME��ĸ˳������
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
				//q�ǣ�p����һ���ڵ�
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

void Sort_by_SCORE(Node *head) //���ݷ����Ӹߵ�������
{
	//	Node *pr, *nt;
	//	Node *n1, *n2;
	//	Node *j;
	//	pr = head;
	//���� �ڵ� �� ����̫���ˡ�ʵ�ڲ��ᡣ����������
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
	
	// �����ǣ�����ֵ �������㷨��ð�������������ɣ������ȶ�
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

Node *Read() //���ļ���ȡ����
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
	
	//����ÿ��ʵ�ʳ��ȣ�������'\n'����֪����ʱΪʲôҪд���
	//	for (i = 0; i < 30; i++) {
	//		if (file_content[0][i] == '\n') {
	//			break;//����ʵ��ÿ�г��ȣ�������'\n'
	//		}
	//	}
	//	line_size = i + 1;
	
	lines = 0;
	for (i = 0; i < 30; i++) {
		for (t = 0; t < 30; t++) {
			if (file_content[i][t] == '\n') {
				lines++;
				//ƥ�䵽ÿ�еĻ��з���������һ�����˲������������һ��
				break;
			}
		}
	}
	lines = lines + 1; //�������������һ�У�����Ҫ��1
	
	fp = fopen(data_address, "r+");
	//�ж��ļ��Ƿ����
	if (fp == NULL) {
		fclose(fp);
		printf("\n�����ļ������ڣ����ڴ���...\n");
		//		for (i = 0; i < 6; i++) {
		//			printf("*");
		//			Sleep(500);
		//		}
		mkdir("E:\\Git\\Code\\CLion\\FILES");
		fp = fopen(data_address, "w+");
		printf("\n����ɣ�����\n\n");
		printf("��Ĭ������д���ļ�...\n");
		//		for (i = 0; i < 6; i++) {
		//			printf("*");
		//			Sleep(500);
		//		}
		i = 0;
		do {
			fputs(file_content[i++], fp);
		} while (i < lines);
		printf("\n����ɣ�����\n\n");
		printf("\n");
		system("pause");
		system("cls");
		goto next; //�ļ������������ж������Ƿ�Ϊ��
	}
	
	//�ж��ļ������Ƿ�Ϊ��
	//�ο���https://blog.csdn.net/lwpping/article/details/7441950
	char ch = fgetc(fp);
	if (ch == EOF) {
		printf("\n�ļ�����Ϊ�գ�\n");
		printf("\n�����������˵���\n\n");
		printf("\n");
		system("pause");
		system("cls");
		Menu();
	}

next:
	rewind(fp); //��ͷ��ʼ���ļ�
	printf("\n��ʼ���ļ���������...\n");
	//	for (i = 0; i < 6; i++) {
	//		printf("*");
	//		Sleep(500);
	//	}
	printf("\n����ɣ�����\n\n");
	while (!feof(fp)) {
		fscanf(fp, "%s", NODE.NAME);
		fscanf(fp, "%s", NODE.ID);
		fscanf(fp, "%g", &NODE.SCORE);
		//		if (feof(fp)) {
		//			break;
		//		}//�������һ�п���
		//ǰ������޸Ĺ��Ժ�����Ͳ���Ҫ������
		//�������һ�о������ݣ�û�п�����
		//�������������������Ǹ�С���
		
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
			printf("���ݲ����ڣ����в��Ϸ������ݱ����룬�������������\n");
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
	while (1) { //pΪNULLʱ������ѭ��
		if (!strcmp(p->NAME, md_name)) { //���ƥ�䵽Ҫɾ�������˳�
			break;
		}
		p = p->next;
		if (p == NULL) {
			printf("\nû�ҵ�NAME��Ӧ�����ݣ�����\n");
			printf("Ҫ�޸ĵ����ݲ����ڣ�����\n\n");
			system("pause");
			return;
		}
	}
	if (p == NULL) //û��ƥ�䵽
	{
		printf("û��ƥ������ݣ�\n");
		system("pause");
		return;
	}
back:
	printf("�������޸ĺ�ĳɼ���");
	scanf("%f", &new_SCORE);
	if (new_SCORE == 0) {
		printf("�޸ĵĳɼ����Ϸ����������0��\n");
		printf("���������룡\n");
		goto back;
	}
	p->SCORE = new_SCORE;
	//	for (t = 0; t < 5; t++) {
	//		Sleep(100);
	//		printf("*");
	//		Sleep(200);
	//	}
	printf("\n�޸ĳɹ�������\n");
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
	printf("\n��ʼ��������:\n");
	printf("\n¼������ע�����\n");
	printf("1�������������0\n");
	printf("2��ѧ�����ʹ��101,102���ָ�ʽ\n");
	printf("\n");
	printf("����0 0 0���˳�����\n");
	do {
		new = (Node *) malloc(sizeof(Node));
		printf("������������ID���������Կո��������\n");
		scanf("%s%s%f", NAME, ID, &SCORE);
		if (SCORE < 0) {
			printf("\n��������ݲ��Ϸ��������ԣ�\n");
			system("pause");
			system("cls");
			goto begin;
		} //�ж�SCORE�ǲ��Ǹ���
		if (atoi(ID) < 0) {
			printf("\n��������ݲ��Ϸ��������ԣ�\n");
			system("pause");
			system("cls");
			goto begin;
		} //�ж�ID�ǲ��Ǹ���
		if (SCORE == 0) {
			system("cls");
			goto end;
		} //����0 0 0���˳�
		q = head;
		while (q != NULL) {
			if (!strcmp(q->ID, ID)) {
				printf("\n�����ظ���ID�������ԣ�\n\n");
				system("pause");
				system("cls");
				goto begin;
			}
			q = q->next;
		} //�ж��Ƿ�����ظ�ID
		q = head;
		while (q != NULL) {
			if (!strcmp(q->NAME, NAME)) {
				printf("\n�����ظ���NAME�������ԣ�\n\n");
				system("pause");
				system("cls");
				goto begin;
			}
			q = q->next;
		} //�ж��Ƿ�����ظ�NAME
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
	printf("�������뿪ʼ:\n");
	printf("\n¼������ע�����\n");
	printf("1�������������0\n");
	printf("2��ѧ�����ʹ��101,102���ָ�ʽ\n");
	printf("\n����0 0 0���˳�����\n\n");
	while (1) {
start:
		printf("\n������������ID���������Կո��������\n");
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
			printf("��������ݲ��Ϸ������������룡\n\n");
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
		printf("���ݲ��Ϸ��򲻴��ڣ������������\n");
		goto end;
	}
	printf("\n����������ݣ�\n");
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
	printf("\n��ʼ������д���ļ������Ժ�......\n");
	//	Sleep(3);
	printf("\n");
	FILE *fp;
	fp = fopen(data_address, "w+");
	while (p != NULL) {
		fprintf(fp, "%-12s", p->NAME);
		fprintf(fp, "%-9s", p->ID);
		fprintf(fp, "%-5.2f", p->SCORE);
		if (p->next == NULL) { //���һ���������һ������
			break;
		}
		fputc('\n', fp);
		p = p->next;
	}
	fclose(fp);
	printf("����ɣ�����\n\n");
	system("pause");
	system("cls");
}