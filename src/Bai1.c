//kiểm tra file dấu ngoặc
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<malloc.h>
#define N 200
typedef struct {
	char a[N];
	int pos[N];
	int top;
}stack;
// khởi tạo stack
void initialize(stack *s) {
	s->top = -1;
	memset(s->pos, -1, sizeof(s->pos));
}
// kiểm tra stack đầy
int stack_full(stack *s) {
	if (s->top >= N) return 1;
	return 0;
}
//kiểm tra stack rỗng
int stack_empty(stack *s) {
	if (s->top == -1) return 1;
	return 0;
}
//lấy phần tử từ stack
int pop_stack(stack *s) {
	if (stack_empty(s) == 1) return 1;
	(s->top)--;
	return 0;
}
//thêm phần tử vào stack
int push_stack(stack *s, char b, int location) {
	if (stack_full(s) == 1) return 1;
	s->top++;
	s->a[s->top] = b;
	s->pos[s->top] = location;
	return 0;
}
//kiểm tra file tồn tại
int check_file(char *path) {
	FILE *file;
	file = fopen(path, "r");
	if (file) {
		fclose(file);
	}
	else {
		return 1;
	}
	return 0;
}
//đọc file
int read(char *path, char *buffer) {
	int i = 0;
	int c;
	FILE *file;
	file = fopen(path, "r");
	if (file) {
		while ((c = fgetc(file)) != EOF)
		{
			buffer[i] = (char)c;
			i++;
		}
		fclose(file);
	}
	return 0;
}
// kiểm tra dấu ngoặc đúng
int check_braket(char *a, stack *s1) {
	char b[N];
	int i, count[N], j = 0, wrong = 0, total = 0;
	memset(count, -1, sizeof(count));
	FILE *doc;
	for (i = 0; i<strlen(a); i++) {

		if ((a[i] == '(')) // nếu gặp dấu ngoặc mở
		{
			if (stack_full(s1) == 1) 
			{
				return 1;
			}
			if (a[i] == '(')
				push_stack(s1, a[i], i);// đẩy vào stack
		}
		else {
			if (a[i] == ')')// gặp dấu ngoặc đóng kiểm tra stack rỗng hoặc lấy phần tử trong stack
			{
				if (stack_empty(s1))
				{
					wrong = 1;
					count[j] = i;
					b[j] = '(';
					j++;
				}
				else pop_stack(s1);
			}
		}
	}
	if ((s1->top == -1) && (wrong == 0)) {
		doc = fopen("D:\\BRACKET.OUT.txt", "w");
		fprintf(doc, "0");
	}
	else {
		j = 0;
		while (count[j] != -1)
		{
			total++;
			j++;
		}
		if (stack_empty(s1) == 0) {
			total += s1->top;
			total++;
		}
		
		doc = fopen("F:\\BRACKET.OUT.txt", "w");
		fprintf(doc, "%d\n", total);
		i = 0;
		if (stack_empty(s1) == 0) {
			while (i <= s1->top) {
				fprintf(doc, ") %d\n", s1->pos[i] + 1);
				i++;
			}
			i = 0;
		}
		
		while (count[i] != -1) {
			if (b[i] == '(')
				fprintf(doc, "( %d\n", count[i]);
			i++;
		}
	}
	fclose(doc);
	getch();
	return 0;
}
int standardize(char *path, char *path2)
{
	int i, j = 0;
	for (i = 0; i<strlen(path); i++) {
		if (path[i] == '\\') {
			if ((path[i + 1] != '\\') && path[i - 1] != '\\') {
				path2[j] = '\\';
				j++;
			}
		}
		path2[j] = path[i];
		j++;
	}
}
int main() {
	stack *s1;
	s1 = (stack*)calloc(1, sizeof(stack));
	char a[N], path[30], path2[30];
	int i, j = 0;
	printf("Nhap file:");
	gets(path);
	standardize(path, path2);// chuẩn hóa tên file
	if (check_file(path2) == 1) {
		printf("file khong ton tai!");
		getch();
		return 1;
	}
	else {
		read(path2, a);//đọc file
		initialize(s1);
		check_braket(a, s1);
		free(s1);
		printf("\nThuc hien xong. Hay kiem tra file BRACKET.OUT trong o F:");
	}
	return 0;
}
