#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define N 1000
#define day_cnt 7

#define key_up 72
#define key_down 80
#define key_right 77
#define key_left 75
#define key_press 224
#define enter 13
#define _delete 46
int cnt_T = 0;
typedef struct seat {
	int idx;
}SEAT;
SEAT *_S;
typedef struct id_pw  //������ �����͸� ����
{
	char id[10];
	char pw[10];
	char arr_[10];
	char start_[10];
	char tim_[10];
	int  da_[2];
	struct seat seat_[40];
	char grade[3];
	int man_num;
	int flag_del;
	int nothing;
}node;
node *_id[20];


typedef struct start {				//����� ����ü
	char *start_name;
	int num;
	struct start *left;
	struct start *right;
	struct arrive *arr_struct;		//��������� �����ִ� �������� root ����Ŵ
}Start_N;
Start_N *s_root = 0;
typedef struct watch {   //�ð��� ����
	char grade[2]; //��޺� �¼�    1:�Ϲ�, 2:��� 3:�����̾�
	char time[6]; //�ð�
	int seat[42];  //�Ϲ� 28, ��� 40   
}Watch_N;
typedef struct Day {  //��¥�� (�� ��)
	int today[3];
	struct watch wat_struct[100];
}DAY_N;
typedef struct waypoint { //������ �����ϴ� ����ü
	char way_p[100];
}Way;
typedef struct arrive {							//������ ����ü
	struct Day day_struct[100];
	char *arrive_name; //������
	struct waypoint w_p[10]; //������
	struct arrive *left;
	struct arrive *right;
	int num;
	char price[6];  //����
}Arrive_N;
Arrive_N *a_root = 0;

int day_print[2] = { 0, };
char time_print[10];
int seat_print[10] = { 0, };
int man_num = 0;
int finish = 0;
void gotoxy(int y, int x)
{
	COORD CSP = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CSP);
}
void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
Start_N * s_makeNode(char* s_name)	//����� new node
{
	Start_N *new = (Start_N*)malloc(sizeof(Start_N));
	new->start_name = (char*)malloc(strlen(s_name));
	strcpy(new->start_name, s_name);
	new->left = new->right = 0;
	new->arr_struct = a_root;
	return new;
}
Arrive_N * a_makeNode(char* a_name)	//������ new node
{
	int i;
	Arrive_N *new = (Arrive_N*)malloc(sizeof(Arrive_N));
	new->arrive_name = (char*)malloc(strlen(a_name));
	strcpy(new->arrive_name, a_name);
	new->left = new->right = 0;
	return new;
}

Start_N *search_node = 0; // start�� ��带 ã�Ƽ� arrive�� root�� ����Ŵ
Start_N *search_node_1 = 0;
Arrive_N *search_a = 0;
Arrive_N *search_a_1 = 0;

void a_add(char *a_name)
{
	Arrive_N *a_new = a_makeNode(a_name);
	Arrive_N *cur = search_node->arr_struct;
	search_a = a_new;
	if (cur == 0)
	{
		search_node->arr_struct = a_new;	//start ��带 ã�Ƽ� �̵��� ��带 ��ȯ 
		return;								//�� ���� arrive root ��带 ���� Ű�� ����
	}
	else
	{
		while (1)
		{
			if (strcmp(cur->arrive_name, a_name) <0)
			{
				if (cur->right == 0)
				{
					cur->right = a_new;
					return;
				}
				cur = cur->right;
			}
			else if (strcmp(cur->arrive_name, a_name) > 0)
			{
				if (cur->left == 0)
				{
					cur->left = a_new;
					return;
				}
				cur = cur->left;
			}
		}
	}
}

void s_add(char *s_name)			//����� tree ����
{
	Start_N *s_new = s_makeNode(s_name);
	Start_N *cur = s_root;
	if (s_root == 0)
	{
		s_root = s_new;
		return;
	}
	else
	{
		while (1)
		{
			if (strcmp(cur->start_name, s_name) <0)
			{
				if (cur->right == 0)
				{
					cur->right = s_new;
					return;
				}
				cur = cur->right;
			}
			else if (strcmp(cur->start_name, s_name) > 0)
			{
				if (cur->left == 0)
				{
					cur->left = s_new;
					return;
				}
				cur = cur->left;
			}
		}
	}
}
int count = 1;
Start_N *s_inorder(Start_N *node, int cnt, int what)  //����� Ʈ�� ���  //what==0 ������������ ���� �Ҵ� �� ���, what==1 �Ҵ�� ���� ã�Ƽ� ��尡 ����Ű�� ��
{
	textcolor(15);
	Start_N *cur = node;
	if (cur == 0)
	{
		return;
	}
	s_inorder(cur->left, cnt, what);
	if (what == 0)//���
	{
		cur->num = count;
		count++;
		printf("                %s\n\n", cur->start_name);
	}
	else if (what == 1) //ã��
	{
		if (cur->num == cnt) {
			search_node = cur;
			count = 1;
		}
	}
	s_inorder(cur->right, cnt, what);
}
int goto_X = 8;
Arrive_N *a_inorder(Arrive_N *node, int cnt, int what)  //������ Ʈ�� ���
{
	textcolor(15);
	Arrive_N *cur = node;
	if (cur == 0)
	{
		return;
	}

	a_inorder(cur->left, cnt, what);

	if (what == 0) {
		gotoxy(goto_X, 65);
		goto_X = goto_X + 2;
		cur->num = count;
		count++;
		printf("%s\n\n", cur->arrive_name);
	}
	else if (what == 1) //ã��
	{
		if (cur->num == cnt) {
			search_a = cur;
		}
	}
	a_inorder(cur->right, cnt, what);
}

int search(char *name, int flag)  //����� ã��
{
	Start_N *cur = s_root;
	if (s_root == 0)
	{
		search_node = s_root;
		return;
	}
	else
	{
		while (1)
		{
			if (cur == 0)
			{
				gotoxy(40, 5);
				//printf("�Է��Ͻ� ������ �����ϴ�. �ٽ� �ѹ� �Է��� �ֽñ� �ٶ��ϴ�.\n");
				return 1;
			}
			if (strcmp(cur->start_name, name) < 0)
			{
				cur = cur->right;
			}
			else if (strcmp(cur->start_name, name) > 0)
			{
				cur = cur->left;
			}
			else
			{
				search_node = cur;  //ã�� ����� ��带 ����Ŵ
				if (flag != 0)
				{
					textcolor(12);
					gotoxy(4, 65);
					printf("**����� [%s]�� ���� �����Դϴ�.**", search_node->start_name);
					a_inorder(search_node->arr_struct, 0, 0);
				}
				return 0;
			}
		}

	}
}
int search_arrive(char *name)  //������ ã��
{
	Arrive_N *cur = search_node->arr_struct;  //����� ��尡 ����Ű�� ����������� root�� ����Ŵ
	while (1)
	{
		if (cur == 0)
		{
			//printf("�Է��Ͻ� ������ �����ϴ�. �ٽ� �ѹ� �Է��� �ֽñ� �ٶ��ϴ�.\n");
			return 1;
		}
		if (strcmp(cur->arrive_name, name) < 0)
		{
			cur = cur->right;
		}
		else if (strcmp(cur->arrive_name, name) > 0)
		{
			cur = cur->left;
		}
		else
		{
			search_a = cur;  //ã�� ������ ��带 ����Ŵ
			return 0;
		}
	}
}
void cur_time(void)
{
	time_t timer;
	struct tm *ti;
	timer = time(NULL);
	ti = localtime(&timer);
	//����ð� ���
	textcolor(15);
	gotoxy(9, 95);
	printf("���� �ð� : %d�� %d��\n", ti->tm_hour, ti->tm_min);
}
int Not_Seat = 0;
int Not_Seat_F = 0;
int d_point = 0;
void search_data(int mon_i, int day_i, int fa)  //�ð�ǥ�� �¼������ ����
{
	Not_Seat = 0;
	cur_time();
	count = 1;
	time_t timer;
	struct tm *ti;
	char watch[6] = { 0, };
	int buffer = 0, bufferH_Q = 0, bufferH_R = 0, bufferM_Q = 0, bufferM_R = 0;
	timer = time(NULL) + (30 * 60);  //����ð����� +30��
	ti = localtime(&timer);
	buffer = ti->tm_hour;

	bufferH_Q = buffer / 10;  // hour�� ���������� �ٲٱ�
	bufferH_R = buffer % 10;
	bufferH_Q = bufferH_Q + '0';
	bufferH_R = bufferH_R + '0';

	buffer = ti->tm_min;
	bufferM_Q = buffer / 10;  //minute�� ���������� �ٲٱ�
	bufferM_R = buffer % 10;
	bufferM_Q = bufferM_Q + '0';
	bufferM_R = bufferM_R + '0';

	watch[0] = (char)bufferH_Q;
	watch[1] = (char)bufferH_R;
	watch[2] = ':';
	watch[3] = (char)bufferM_Q;
	watch[4] = (char)bufferM_R;
	watch[5] = 0;
	int flag = 0, flag2 = 0;
	int i = 0, j = 0;
	if ((mon_i == ti->tm_mon + 1) && (day_i == ti->tm_mday)) //���� ž���� ���� ������ ���� ���� ��� �ð��� üũ �ؾ���
	{
		Not_Seat_F = 1;
		flag = 1;
	}
	int r = 3, c = 75;
	if (fa != 1)
	{
		textcolor(12);
		gotoxy(r, c);
		printf("**ž�� �ð� 30�� ������ ���� �� �� ������ �����ϼ���.** ");
		r = r + 4;
		gotoxy(r, c);
		textcolor(14);
		printf("<<��� �ð��� �����ϼ���>> ");
	}

	while (i != day_cnt)
	{
		if (search_a->day_struct[i].today[0] == mon_i)
		{
			if (search_a->day_struct[i].today[1] == day_i)
			{
				d_point = i; //������ ��¥�� �ε����� ����Ŵ
				if (fa != 1) {
					while (strcmp(search_a->day_struct[i].wat_struct[j].time, "end") != 0)
					{
						if (flag == 1)
						{
							if (strcmp(watch, search_a->day_struct[i].wat_struct[j].time) == -1)  //���� ���Ͽ� ������ Ż�Ÿ� ž�°����� �ð� üũ
							{
								r = r + 2;
								gotoxy(r, c);
								textcolor(15);
								printf("%s", search_a->day_struct[i].wat_struct[j].time);  //�ð�ǥ ���
								if (strcmp(search_a->day_struct[i].wat_struct[j].grade, "1") == 0) { printf(" �Ϲ�\n"); }
								else if (strcmp(search_a->day_struct[i].wat_struct[j].grade, "2") == 0) { printf(" ���\n"); }
								flag2 = 1;
							}
							else
							{
								textcolor(8);
								r = r + 2;
								gotoxy(r, c);

								printf("%s", search_a->day_struct[i].wat_struct[j].time);  //�ð�ǥ ���
								Not_Seat++;

								if (strcmp(search_a->day_struct[i].wat_struct[j].grade, "1") == 0) { printf(" �Ϲ�\n"); }
								else if (strcmp(search_a->day_struct[i].wat_struct[j].grade, "2") == 0) { printf(" ���\n"); }
								flag2 = 1;
							}
							count++;
						}
						else {
							r = r + 2;
							gotoxy(r, c);
							textcolor(15);
							printf("%s", search_a->day_struct[i].wat_struct[j].time);
							if (strcmp(search_a->day_struct[i].wat_struct[j].grade, "1") == 0) { printf(" �Ϲ�\n"); }
							else if (strcmp(search_a->day_struct[i].wat_struct[j].grade, "2") == 0) { printf(" ���\n"); }
							flag2 = 1;
							count++;
						}
						j++;
					}
				}
				if (flag2 == 0 && fa != 1) { printf("���� ž�� ������ ������ �����ϴ�. "); }
				return;
			}
		}
		i++;

	}
	r = r + 2;
	gotoxy(r, c);
	textcolor(12);
	printf("������� �����ϴ�. ");
}


int t_point = 0;
int grade_cnt;
int find_sel_seat(int cnt)
{
	int i = 0, j = 0, index = 0;
	if (Not_Seat == count - 1) { return 999; }

	if (Not_Seat >= cnt && Not_Seat_F == 1)
	{
		gotoxy(11, 95);
		textcolor(12);
		printf("!!������ �� ���� �ð��Դϴ�.!!");
		gotoxy(6, 70);
		for (i = 0; i < 2; i++)
		{
			textcolor(0);
			printf("%c%c", _delete, _delete);
		}
		gotoxy(6, 72);
		textcolor(14);
		return 1;
	}
	while (strcmp(search_a->day_struct[d_point].wat_struct[i].time, "end") != 0)
	{
		if (i == cnt - 1)
		{
			t_point = i;
			if (strcmp(search_a->day_struct[d_point].wat_struct[i].grade, "1") == 0) { grade_cnt = 40; }
			else if (strcmp(search_a->day_struct[d_point].wat_struct[i].grade, "2") == 0) { grade_cnt = 28; }
			strcpy(time_print, search_a->day_struct[d_point].wat_struct[i].time);
			return 0;
		}
		i++;

	}
}

int seat_save(int seat_idx, int fa)  //�¼��� �����ϰ� ������ �¼� ó���� ����
{
	char s[6] = { 0, };
	Start_N *sta_node = search_node;
	Arrive_N *arr_node = search_a;
	strcpy(s, search_a->day_struct[d_point].wat_struct[t_point].time);
	seat_idx--;
	if (arr_node->day_struct[d_point].wat_struct[t_point].seat[seat_idx] == 1 && fa == 0)  //�̹� ���ŵ� ǥ���
	{
		return 1;
	}
	else {
		arr_node->day_struct[d_point].wat_struct[t_point].seat[seat_idx] = 1;
	}
	if (fa == 1)
	{
		arr_node->day_struct[d_point].wat_struct[t_point].seat[seat_idx] = 0;
	}
	int i = 0, j = 0;
	if (strcmp(arr_node->w_p[i].way_p, "empty") == 0)
	{
		//printf("�������� �����ϴ�.");
	}
	else
	{
		while (strcmp(arr_node->w_p[i].way_p, search_a->arrive_name))//�������� �������� ����������
		{ //�������� �տ��� ���� �о� ������ ã�� �¼� �ٲ�
			search(arr_node->w_p[i].way_p, 0);  //����� ã��
			j = i + 1;
			while (strcmp(arr_node->w_p[j].way_p, "end"))//������
			{
				search_arrive(arr_node->w_p[j].way_p);  //�������� ����
				int k = 0;
				while (strcmp(search_a->day_struct[d_point].wat_struct[k].time, "end"))
				{
					if (strcmp(search_a->day_struct[d_point].wat_struct[k].time, s) > 0&& strcmp(search_node, sta_node) != 0) {
						if (fa == 0)
						{
							search_a->day_struct[d_point].wat_struct[k].seat[seat_idx] = 1;
						}
						else if (fa == 1)
						{
							search_a->day_struct[d_point].wat_struct[k].seat[seat_idx] = 0;
						}
						break;
					}
					if (strcmp(s, search_a->day_struct[d_point].wat_struct[k].time) == 0)
					{
						if (fa == 0)
						{
							search_a->day_struct[d_point].wat_struct[k].seat[seat_idx] = 1;
						}
						else if (fa == 1)
						{
							search_a->day_struct[d_point].wat_struct[k].seat[seat_idx] = 0;
						}
						break;
					}
					k++;
				}
				j++;
			}
			i++;
		}
	}
	search_a = arr_node;
	return 0;
}
int bon_price_sum = 0;
void pricing(int man_number, int man_class_)   //�ݾ��� ������
{
	int grade_price = 0;
	float class_price = 0.0;
	int bon_price = atoi(search_a->price);  //���ڿ��� ���ڷ� �ٲٱ�
	if (strcmp(search_a->day_struct[d_point].wat_struct[t_point].grade, "2") == 0) { grade_price = 5200; }  //��� ��� ����
	else { grade_price = 0; }  //�Ϲ� ��� ����
	if (man_class_ == 1) { class_price = 1; } //û�ҳ� 20%, �Ƶ� 50% ����
	else if (man_class_ == 2) { class_price = 0.2; }
	else { class_price = 0.5; }
	bon_price = (bon_price + grade_price)*class_price*man_number;//������ ����ϱ�
	bon_price_sum = bon_price_sum + bon_price;
	gotoxy(40, 60);
	printf("���� �ݾ� : %d��\n", bon_price_sum);
}
void print_seat(int grade_cnt)  //��޿� ���� �����¼� ǥ�� ������
{
	system("cls");
	textcolor(15);
	int i = 0, j = 0;
	if (grade_cnt == 28)
	{
		int r = 2, c = 9;
		for (i = 0; i < 9 * 4; i++)
		{
			gotoxy(r, c + 1);
			if ((i % 4) == 0)
			{
				if (i == 28 + 4)
				{
					printf("����������������������������������������������������������������������������������������");
				}
				else {
					printf("��������������������������������                     ����������");
				}
			}
			r = r + 1;
			gotoxy(r, c);
			if (i < 36 - 4)
			{

				printf("��        ��        ��                 ��        ��  ");

			}
			else {
				printf("��          ��           ��          ��          ��  ");

			}
		}
		r = r + 1;
		gotoxy(r, c);
		printf("�������������������������������������������������������������������������������������������� ");
		gotoxy(2, 9);
		printf("�������������������������������������������������������������������������������������������� ");

		r = 4, c = 7;
		j = 1;
		for (i = 1; i <= grade_cnt - 4; i++)
		{
			if (i % 3 == 0)
			{
				c = c + 18;
			}
			if (i % 3 == 1 && i != 1)
			{
				j = j + 4;
				r = 3 + j;
				c = 7 + 8;
			}
			else {

				c = c + 8;

			}
			gotoxy(r, c);
			if (search_a->day_struct[d_point].wat_struct[t_point].seat[i - 1] == 1) { textcolor(8); }
			printf("%d", i);
			textcolor(15);
		}
		c = 3;
		r = r + 4;
		for (j = i; j <= grade_cnt; j++)
		{
			c = c + 11;
			gotoxy(r, c);
			if (search_a->day_struct[d_point].wat_struct[t_point].seat[j - 1] == 1) { textcolor(8); }
			printf("%d", j);
			textcolor(15);
		}
	}
	i = 0, j = 0;
	if (grade_cnt == 40)
	{
		int r, c;
		for (i = 0; i < 9 * 4; i++)
		{
			r = 2, c = 7;
			j = 1;
			for (i = 1; i <= grade_cnt - 4; i++)
			{
				if (i % 2 == 1)
				{
					c = c + 8;
				}
				if (i % 4 == 1)
				{
					j = j + 4;
					r = 3 + j;
					c = 7 + 8;
				}
				else {

					c = c + 8;

				}
				gotoxy(r, c);
				if (search_a->day_struct[d_point].wat_struct[t_point].seat[i - 1] == 1) { textcolor(8); }
				printf("%d", i);
				textcolor(15);
			}
			c = 3;
			r = r + 4;
			for (j = i; j <= grade_cnt; j++)
			{
				c = c + 11;
				gotoxy(r, c);
				if (search_a->day_struct[d_point].wat_struct[t_point].seat[j - 1] == 1) { textcolor(8); }
				printf("%d", j);
				textcolor(15);
			}
		}
	}

}
int seat_idx;

int point_print(int r, int c, int what)  //what =1 ������� ���� 2=> �������� ���� ���
{
	int cnt_ = 1, key_p = 0;

	textcolor(14);
	gotoxy(r, c);
	printf("��");
	while (key_p != enter)     //�����͸� ����Ű �������� �ޱ�
	{
		key_p = getch();
		if (key_p == 48) { return; }
		if (key_p == key_up) {
			if (cnt_ <= 1) { cnt_ = 1; }
			else
			{
				gotoxy(r, c - 1);
				textcolor(0);
				printf("%c%c", _delete, _delete);
				textcolor(14);
				r = r - 2;
				gotoxy(r, c - 1);
				printf("��");
				cnt_--;
			}
		}
		else if (key_p == key_down)
		{
			if (cnt_ >= (count - 1)) { cnt_ = (count - 1); }
			else
			{
				gotoxy(r, c - 1);
				textcolor(0);
				printf("%c%c", _delete, _delete);
				textcolor(14);
				r = r + 2;
				gotoxy(r, c - 1);
				printf("��");
				cnt_++;
			}
		}
	}
	if (what == 1)  //������� ���Ѱ�
	{
		s_inorder(s_root, cnt_, 1);
		gotoxy(6, 65);
		textcolor(14);
		printf("<<�������� �����Ͻÿ�>> ");
		textcolor(15);
		search(search_node->start_name, 1);
		//strcpy(_ID[cnt_T-1].start_ , search_node->start_name);
		return;
	}
	else if (what == 2)  //�������� ���Ѱ�
	{
		a_inorder(search_node->arr_struct, cnt_, 1);
		return;
	}
	else if (what == 3)  //��¥�� ���Ѱ�
	{
		cnt_ = cnt_ - 1;
		time_t timer;
		struct tm *ti;
		timer = time(NULL) + (24 * 60 * 60 * cnt_);
		ti = localtime(&timer);
		day_print[0] = ti->tm_mon + 1;
		day_print[1] = ti->tm_mday;
		search_data(ti->tm_mon + 1, ti->tm_mday, 0);

	}
	else if (what == 4)  //�ð��� ���Ѱ�
	{
		int re = 0;
		re = find_sel_seat(cnt_);
		if (re == 999) { return 999; }
		if (re == 1)
		{
			gotoxy(r, c - 1);
			textcolor(0);
			printf("%c%c", _delete, _delete);
			textcolor(14);
			cnt_ = 1;
			point_print(9, 69, 4);
		}
	}
	else if (what == 5)  //����
	{
		gotoxy(r, c - 1);
		textcolor(0);
		printf("%c%c", _delete, _delete);
		return cnt_;
	}
}


void id_print(char *id, char *pw)  //����� �����͸� ��������
{
	int i, re, j = 0, n = 0, k = 0;
	system("cls");
	textcolor(15);
	int r = 5, c = 30;
	for (n = 0; n < finish; n++)
	{
		gotoxy(r, c - 7);
		textcolor(14);
		printf("%d", _id[n]->nothing);
		textcolor(15);
		k++;
		gotoxy(r, c);
		printf("[%s] --> [%s]", _id[n]->arr_, _id[n]->start_);
		r = r + 2;
		gotoxy(r, c);
		printf("%d�� %d��, �ð� [%s]", _id[n]->da_[0], _id[n]->da_[1], _id[n]->tim_);
		r = r + 2;
		gotoxy(r, c);
		printf("���� �ο� �� : %d��", _id[n]->man_num);
		r = r + 2;
		gotoxy(r, c);
		printf("�¼� ��ȣ : ");
		for (i = 0; i < _id[n]->man_num; i++)
		{
			printf("%d ", _id[n]->seat_[i].idx);
		}
		r = r + 3;
	}
	gotoxy(r, c);
	textcolor(14);
	printf("<<���Ÿ� ��� �Ϸ��� ��ȣ�� ������ �ּ���>>");
	r = r + 3;
	gotoxy(r, c);
	textcolor(0);
	scanf("%d", &re);

	textcolor(14);
	if (re > 0) {
		search(_id[n-1]->arr_, 1);
		search_arrive(_id[n-1]->start_);
		search_data(_id[n-1]->da_[0], _id[n-1]->da_[1], 1);
		find_sel_seat(_id[n-1]->tim_);
		i = 0;
		while (strcmp(search_a->day_struct[d_point].wat_struct[i].time, _id[n-1]->tim_) != 0)
		{
			++i;
		}
		t_point =i;
		for (i = 0; i < man_num; i++)
		{
			seat_save(_id[n-1]->seat_[i].idx, 1);
		}
		finish--;
		system("cls");
		gotoxy(5, 50);
		if (re - 1 > finish)                     //�����͸� ���� �ٲٱ�
		{
			re = re - 1;
			strcpy(_id[re]->arr_, _id[finish]->arr_);
			strcpy(_id[re]->start_, _id[finish]->start_);
			strcpy(_id[re]->tim_, _id[finish]->tim_);
			_id[re]->da_[0] = _id[finish]->da_[0];
			_id[re]->da_[1] = _id[finish]->da_[1];
			_id[re]->man_num = _id[finish]->man_num;
		}
		textcolor(14);
		printf("***��Ұ� �Ϸ�Ǿ����ϴ�, ����ȭ������ ���ư��ϴ�***");
		return;
	}
	else {
		system("cls");
		textcolor(14);
		gotoxy(5, 50);
		printf("����ȭ������ ���ư��ϴ�");
		return;
	}

}
void delete_Ticketing()  //���� ���
{
	int  r ,c;
	char id[10] = { 0, }, pw[10] = { 0, };
	system("cls");
	r = 6, c = 60;
	gotoxy(c, r);
	textcolor(14);
	printf("***���� ��Ҹ� ���Ͻø� �α����� ���ּ���.***");
	r = r + 1;
	gotoxy(r, c);
	printf("ID : ");
	r = r + 1;
	gotoxy(r, c);
	printf("P/W : ");
	r = 6 + 1;
	c = c + 5;
	gotoxy(r, c);
	scanf("%s", id);
	r = r + 1;
	gotoxy(r, c);
	scanf("%s", pw);
	if (strcmp(_id[0]->id, id) == 0)
	{
		if (strcmp(_id[0]->pw, pw) == 0)
		{
			id_print(id, pw);
		}
		else
		{
			gotoxy(13, 28);
			textcolor(12);
			printf("***���̵� Ȥ�� ��й�ȣ�� Ʋ�Ƚ��ϴ�.***");
			gotoxy(15, 28);
			printf("***����ȭ������ ���ư��ϴ�.***");
			textcolor(14);
			return;
		}
	}
	else
	{
		gotoxy(13, 28);
		textcolor(12);
		printf("***���̵� Ȥ�� ��й�ȣ�� Ʋ�Ƚ��ϴ�.***");
		gotoxy(15, 28);
		printf("***����ȭ������ ���ư��ϴ�.***");
		textcolor(14);
		return;
	}
}
int start_Ticketing(void)   //�����ϱ� �Լ�
{
	system("cls");   //�ܼ� â clear

	char s_data[10] = { 0, }, a_data[10] = { 0, };
	char time_i[6] = { 0, };
	int mon_i = 0, day_i = 0;
	int re = 0;
	int key_p = 0, r, c, cnt_ = 1;
	int man_number, man_class_;
	gotoxy(2, 15);
	textcolor(12);
	printf("***����Ű�� ���͸� ����Ͽ� �����Ͻʽÿ�.*** ");
	gotoxy(6, 10);
	textcolor(14);
	printf("<<������� �����Ͻÿ�.>>\n\n");
	textcolor(15);
	s_inorder(s_root, 0, 0);
	key_p = getch();
	if (key_p == key_press)
	{
		point_print(8, 11, 1);
	}
	if (key_p == key_press)
	{
		textcolor(14);
		r = 8, c = 62;
		gotoxy(r, c);
		point_print(r, c, 2);
	}

	search_a_1 = search_a;
	//-----------------------------------------(�����, ������ �Ϸ�)
	system("cls");
	textcolor(14);
	gotoxy(3, 20);
	printf("[%s] ---> [%s] �� �����ϼ̽��ϴ�. ", search_node->start_name, search_a->arrive_name);
	gotoxy(5, 20);
	int i = 0;
	if (strcmp(search_a->w_p[i].way_p, "empty") == 0) { printf("(����)"); }
	else {
		gotoxy(5, 20+7);
		while (strcmp(search_a->w_p[i].way_p, search_a->arrive_name) != 0)
		{
			printf("%s -> ", search_a->w_p[i].way_p);
			i++;
		}
		printf("%s", search_a->w_p[i].way_p);

	}

	textcolor(14);
	gotoxy(7, 15);
	printf("<<����� ��¥�� �Է��ϼ���>> "); //���� ��¥���� 3�ϱ��� �˻�����
	textcolor(15);
	i = 0;
	time_t timer;
	struct tm *ti;
	for (i = 0; i < day_cnt; i++)                    //���Ϻ��� 7�ϰ��� ��¥�� ������
	{
		timer = time(NULL) + (24 * 60 * 60 * i);
		ti = localtime(&timer);
		gotoxy(9 + i * 2, 20);
		printf("%d / %d / %d", ti->tm_year + 1900, ti->tm_mon + 1, ti->tm_mday);
	}

	if (key_p == key_press)
	{
		textcolor(14);
		r = 9, c = 16;
		gotoxy(r, c);
		count = 7 + 1;
		point_print(r, c, 3);
	}
	search_node_1 = search_node;
	//--------------------------------------------

	//�ð� �Է� ����
	if (key_p == key_press)
	{
		int re;
		r = 9, c = 69;
		re = point_print(r, c, 4);
		if (re == 999) { return 999; }
	}
	//---------------------------------------------------------------------------------
	system("cls");                              //�ο���, �з�(����, û�ҳ�, �Ƶ�)
	gotoxy(3, 6);
	printf("<<�ο����� �Է��ϼ���.>>");
	gotoxy(5, 10);
	textcolor(15);
	printf("�ο� �� : ");
	textcolor(14);
	scanf("%d", &man_number);
	man_num = man_number;
	gotoxy(3, 60);
	printf("<<������ �����ϼ���.>>");
	count = 4;
	bon_price_sum = 0;
	for (i = 0; i < man_number; i++)
	{
		textcolor(15);
		gotoxy(5, 60);
		printf("����");
		gotoxy(7, 60);
		printf("û�ҳ�");
		gotoxy(9, 60);
		printf("�Ƶ�");
		textcolor(14);
		man_class_ = point_print(5, 60 - 3, 5);
		textcolor(14);
		pricing(1, man_class_); //���� å��   //man_class_ 1:���� 2:û�ҳ� 3:�Ƶ�
	}
	system("cls");
	textcolor(14);
	//_ID[cnt_T - 1].man_num = man_number;
	for (i = 0; i < man_number; i++)
	{
		//������ �¼��� �Է� ����
		textcolor(14);
		print_seat(grade_cnt);
		gotoxy(40, 60);
		textcolor(14);
		printf("���� �ݾ� : %d��\n", bon_price_sum);
		gotoxy(4, 65);
		textcolor(15);
		printf("<< �¼��� �����ϼ���. >>");
		gotoxy(6, 62);
		textcolor(14);
		printf("[�¼��� ������ �ּ���:        ]");
		gotoxy(6, 62 + 13 * 2);
		scanf("%d", &seat_idx);  //�Է¹��� ���� �ε��� ��
		seat_print[i] = seat_idx;
		//_ID[cnt_T - 1].seat_[i] = seat_idx;
		int retu;
		while ((retu = seat_save(seat_idx, 0)) != 0)  //�¼� ���� (�������� �����ؾ� ��)
		{
			textcolor(12);
			gotoxy(8, 70);
			printf("!!�̹� ���Ű� �Ϸ� �� �¼��Դϴ�. �� �¼��� ������ �� �����ϴ�.!!");
			gotoxy(6, 62 + 13 * 2);
			textcolor(0);
			for (i = 0; i < 2; i++)
			{
				printf("%c%c", _delete, _delete);
			}
			textcolor(14);
			gotoxy(6, 62 + 13 * 2);
			scanf("%d", &seat_idx);
		}
		//print_seat(grade_cnt);

	}
	return 0;
}

int main(void)	
{
	system("mode con cols=150 lines=60"); //����, ���� �ܼ� â ũ��


	char bus_start[10] = { 0, };
	FILE *start_data = fopen("start_data.txt", "r");		//������� tree�� ����
	while (1)
	{
		fscanf(start_data, "%s", bus_start);
		if (strcmp(bus_start, "end") == 0) { break; }
		s_add(bus_start);
	}
	fclose(start_data);

	char bus_arrive[20] = { 0, };
	FILE *arrive_data = fopen("arrive_data.txt", "r");		//�������� ������� �����ϴ� tree�� ����

	int flag = 0, i = 0;
	while (1)
	{
		fscanf(arrive_data, "%s", bus_arrive);
		if (strcmp(bus_arrive, "finish") == 0) { break; }
		if (strcmp(bus_arrive, "start") == 0)
		{
			flag = 1;
		}
		if (flag == 1)
		{
			fscanf(arrive_data, "%s", bus_arrive);
			search(bus_arrive, 0);
			flag = 0;
		}
		while (1)
		{
			fscanf(arrive_data, "%s", bus_arrive);
			if (strcmp(bus_arrive, "end") == 0)
			{
				break;
			}
			if (strcmp(bus_arrive, "wps") == 0)			//�������� arrive��忡 ����
			{
				while (1)
				{
					fscanf(arrive_data, "%s", bus_arrive);
					if ((strcmp(bus_arrive, "wpe") == 0)) {
						strcpy(search_a->w_p[i].way_p, "end");
						i = 0;
						break;
					}
					strcpy(search_a->w_p[i].way_p, bus_arrive);
					i++;
				}
			}
			else
			{
				a_add(bus_arrive);
				strcpy(search_a->w_p[i].way_p, "empty");
				i = 0;
				fscanf(arrive_data, "%s", bus_arrive);
				strcpy(search_a->price, bus_arrive); //�ش� ���������� ���� ����
			}
		}
	}
	fclose(arrive_data);

	//schedule ���� (��¥ �ð� �¼����)
	time_t timer;
	struct tm *ti;
	timer = time(NULL);
	ti = localtime(&timer);
	char sche[10] = { 0, };
	i = 0;
	int k = 0; //3�ϱ��� ���� ����
	int cnt, t = 0;
	FILE *schedule_data = fopen("schedule.txt", "r");		//������� tree�� ����
	while (1)
	{
		fscanf(schedule_data, "%s", sche);  //�����
		if (strcmp(sche, "finish") == 0) {

			break;
		}
		search(sche, 0);
		fscanf(schedule_data, "%s", sche);  //������
		search_arrive(sche);

		while (1)
		{
			fscanf(schedule_data, "%s", sche);
			if (strcmp(sche, "end") == 0) {
				//k = 0;
				i = 0;
				break;
			}
			strcpy(search_a->day_struct[k].wat_struct[i].time, sche);  //�ð� ����
			fscanf(schedule_data, "%s", sche);
			strcpy(search_a->day_struct[k].wat_struct[i].grade, sche);  //�¼� ��� ����
			cnt = 0;
			while (cnt != day_cnt)  //��¥���� �¼��� �ð�ǥ ����(��¥�� ���� ���� day_cnt���� ������)
			{
				timer = time(NULL) + (24 * 60 * 60 * cnt); // ���� �ð��� �� ������ ���
				ti = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

				search_a->day_struct[cnt].today[0] = ti->tm_mon + 1;    //��¥����
				search_a->day_struct[cnt].today[1] = ti->tm_mday;

				strcpy(search_a->day_struct[cnt].wat_struct[i].time, search_a->day_struct[k].wat_struct[i].time);
				strcpy(search_a->day_struct[cnt].wat_struct[i].grade, search_a->day_struct[k].wat_struct[i].grade);
				i++;
				strcpy(search_a->day_struct[cnt].wat_struct[i].time, "end");
				i--;
				int j;
				for (j = 0; j <= 40; j++)
				{
					search_a->day_struct[cnt].wat_struct[i].seat[j] = 0;
				}
				cnt++;
			}
			i++;
		}


	}

	while (1)
	{
		system("cls");
		unsigned char a = 0xa1;
		int p, p2, r, c;
		textcolor(14);  //8ȸ��

		gotoxy(2, 11);
		printf("�������������������������������������������������� ");

		//Sleep(2000);
		//system("cls");

		for (p = 3; p < 17; p++)
		{
			gotoxy(p, 11);
			printf("�� ");
			gotoxy(p, 107);
			printf("�� ");
		}
		gotoxy(p, 11);
		printf("�������������������������������������������������� ");
		gotoxy(5, 13); printf("��      ��  �� ");
		gotoxy(6, 13); printf("��      ��  �� ");
		gotoxy(7, 13); printf("��      ��  �� ");
		gotoxy(8, 13); printf("���������������� ���� ");
		gotoxy(9, 13); printf("��      ��  �� ");
		gotoxy(10, 13); printf("����������������  ��  ");

		gotoxy(5, 26); printf("���� ");
		gotoxy(6, 26); printf("��  �� ");
		gotoxy(7, 26); printf("��    �� ");
		gotoxy(8, 26); printf("��      �� ");
		gotoxy(9, 26); printf("��        �� ");
		gotoxy(10, 26); printf("��������������������  ");

		gotoxy(5, 38); printf("��������������  �� ");
		gotoxy(6, 38); printf("��        �� ");
		gotoxy(7, 38); printf("��        �� ");
		gotoxy(8, 38); printf("��������������  ���� ");
		gotoxy(9, 38); printf("��        �� ");
		gotoxy(10, 38); printf("��������������  ��  ");

		gotoxy(5, 51); printf("���������������� �� ");
		gotoxy(6, 51); printf("  ��      �� ");
		gotoxy(7, 51); printf("  ��      �� ");
		gotoxy(8, 51); printf("  ����    ����  ");
		gotoxy(9, 51); printf("  ��  ��  �� ");
		gotoxy(10, 51); printf("  ��    ���� ");

		gotoxy(5 + 3, 68); printf("��������������  ");
		gotoxy(6 + 3, 68); printf("��        ");
		gotoxy(7 + 3, 68); printf("��        ");
		gotoxy(8 + 3, 68); printf("��     ����   ");
		gotoxy(9 + 3, 68); printf("��      �� ");
		gotoxy(10 + 3, 68); printf("���������������� ");

		gotoxy(5 + 3, 77); printf("����������������   ");
		gotoxy(6 + 3, 77); printf("��      ��  ");
		gotoxy(7 + 3, 77); printf("��      �� ");
		gotoxy(8 + 3, 77); printf("��      ��   ");
		gotoxy(9 + 3, 77); printf("��      �� ");
		gotoxy(10 + 3, 77); printf("���������������� ");

		gotoxy(5 + 3, 87); printf("��������������  ");
		gotoxy(6 + 3, 87); printf("��        ");
		gotoxy(7 + 3, 87); printf("��        ");
		gotoxy(8 + 3, 87); printf("��     ����   ");
		gotoxy(9 + 3, 87); printf("��      �� ");
		gotoxy(10 + 3, 87); printf("���������������� ");

		gotoxy(5 + 3, 96); printf("����������������   ");
		gotoxy(6 + 3, 96); printf("��      ��  ");
		gotoxy(7 + 3, 96); printf("��      �� ");
		gotoxy(8 + 3, 96); printf("��      ��   ");
		gotoxy(9 + 3, 96); printf("��      �� ");
		gotoxy(10 + 3, 96); printf("���������������� ");

		gotoxy(9 + 3, 110); printf("      ���  ");
		gotoxy(10 + 3, 110); printf("����    ���  ");
		gotoxy(11 + 3, 110); printf("             ��  ");
		gotoxy(12 + 3, 110); printf("����    ���  ");
		gotoxy(13 + 3, 110); printf("      ���  ");

		textcolor(15);

		gotoxy(15, 20); printf("       �� �� �� ");
		gotoxy(16, 20); printf("    ��          �� ");
		gotoxy(17, 20); printf("  ��              �� ");
		gotoxy(18, 20); printf(" ��                �� ");
		gotoxy(19, 20); printf(" ��                �� ");
		gotoxy(20, 20); printf("  ��              �� ");
		gotoxy(21, 20); printf("    ��          �� ");
		gotoxy(22, 20); printf("       �� �� �� ");

		gotoxy(15, 20 * 4); printf("       �� �� �� ");
		gotoxy(16, 20 * 4); printf("    ��          �� ");
		gotoxy(17, 20 * 4); printf("  ��              �� ");
		gotoxy(18, 20 * 4); printf(" ��                �� ");
		gotoxy(19, 20 * 4); printf(" ��                �� ");
		gotoxy(20, 20 * 4); printf("  ��              �� ");
		gotoxy(21, 20 * 4); printf("    ��          �� ");
		gotoxy(22, 20 * 4); printf("       �� �� �� ");


		gotoxy(20 + 5, 20); printf("����������������������������������������������   ");
		gotoxy(21 + 5, 20); printf("��                     ��  ");
		gotoxy(22 + 5, 20); printf("��                     �� ");
		gotoxy(23 + 5, 20); printf("��                     �� ");
		gotoxy(24 + 5, 20); printf("���������������������������������������������� ");

		gotoxy(20 + 5, 20 * 4); printf("����������������������������������������������������   ");
		gotoxy(21 + 5, 20 * 4); printf("��                        ��  ");
		gotoxy(22 + 5, 20 * 4); printf("��                        �� ");
		gotoxy(23 + 5, 20 * 4); printf("��                        �� ");
		gotoxy(24 + 5, 20 * 4); printf("���������������������������������������������������� ");

		gotoxy(27, 23); printf("���� ���� GO GO~~ ");
		gotoxy(27, 82); printf("���� ���� ��� GO GO~~ ");

		textcolor(15);
		gotoxy(34, 50); printf("����Ű�� ����Ű�� ����Ͽ� ���� �ϼ���.");
		int key_p;
		key_p = getch();
		textcolor(14);
		if (key_p == key_press) //Ȯ��Ű���� Ȯ��
		{
			key_p = getch();
			while (key_p != enter)
			{
				if (key_p == key_right) { r = 22 + 5; c = 20 * 4 - 2; }
				else if (key_p == key_left) { r = 22 + 5; c = 20 - 2; }
				gotoxy(r, c);
				printf("��");
				key_p = getch();
				gotoxy(r, c - 1);
				printf("%c%c", _delete, _delete);
			}
		}
		goto_X = 8;
		char id_[10], pw_[10];
		if (c == 20 - 2)  //���Ű� ������ ���
		{
			textcolor(6);
			gotoxy(27, 23); printf("���� ���� GO GO~~ ");
			textcolor(15);
			count = 1;

			int r;
			r = start_Ticketing();
			while (r == 999)
			{
				count = 1;
				goto_X = 8;
				r = start_Ticketing();
				bon_price_sum = 0;
			}
			system("cls");
			textcolor(15);
			int re;
			r = 5, c = 30;     //���Ű� ���� �� ������ �����͸� ������
			gotoxy(r, c);
			printf("[%s] --> [%s]", search_node_1->start_name, search_a->arrive_name);
			r = r + 2;
			gotoxy(r, c);
			printf("%d�� %d��, �ð� [%s]", day_print[0], day_print[1], time_print);
			r = r + 2;
			gotoxy(r, c);
			printf("���� �ο� �� : %d��", man_num);
			r = r + 2;
			gotoxy(r, c);
			printf("�¼� ��ȣ : ");
			for (i = 0; i < man_num; i++)
			{
				printf("%d ", seat_print[i]);
			}
			r = r + 3;
			gotoxy(r, c);
			printf("���� �ݾ� : %d��", bon_price_sum);
			r = r + 5;
			gotoxy(r, c);
			textcolor(14);
			printf("<<���Ű� �Ϸ�Ǿ����ϴ�.>>");

			_S = (SEAT*)malloc(sizeof(SEAT));        
			_id[finish] = (node*)malloc(sizeof(node));
			strcpy(_id[0]->id, "���̵�1");
			strcpy(_id[0]->pw , "��й�ȣ1");
			for (i = 0; i < man_num; i++)
			{
				_id[finish]->seat_[i].idx = seat_print[i];
			}
			strcpy(_id[finish]->arr_, search_node_1->start_name);
			strcpy(_id[finish]->start_, search_a->arrive_name);
			strcpy(_id[finish]->tim_, time_print);
			_id[finish]->da_[0] = day_print[0];
			_id[finish]->da_[1] = day_print[1];
			_id[finish]->man_num = man_num;
			_id[finish]->nothing = finish+1;
			finish++;	

		}
		else  //���� ��Ұ� ������ ���
		{
			delete_Ticketing();
		}

		Sleep(5000);
	}
}
