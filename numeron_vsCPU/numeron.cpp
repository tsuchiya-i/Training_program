#include<stdio.h>
#include<time.h>
#include<stdlib.h>

struct numeron
{
	int num1;
	int num2;
	int num3;
};

numeron n0 = {0,0,0};

int error(numeron n)
{
	if(n.num1==n.num2 || n.num2==n.num3 || n.num3==n.num1) return 0;
	if(n.num1>=10 || n.num2>=10 || n.num3>=10) return 0;
	else return 1;
}

int inputnum(numeron &n) // n1n2n3 return 1(NO) or 0(OK)
{
	printf("���Ȃ��̗\�z:");
	int a;
	scanf("%d", &a);
	if(a>=1000 || a<=10){
		printf("�G���[: �������O���ł͂���܂���B\n");
		return 1;
	}
	n.num1 = a/100;
	n.num2 = (a-n.num1*100)/10;
	n.num3 = a-n.num1*100-n.num2*10;
	if(n.num1==n.num2 || n.num2==n.num3 || n.num1==n.num3){
		printf("�G���[: �����������g���Ă��܂��B\n");
		return 1;
	}
	return 0;
}

numeron numtonumeron(int num) // error�̎�000��Ԃ�
{
	numeron n;
	if(num>=1000 || num<=10){
		return n0;
	}
	n.num1 = num/100;
	n.num2 = (num-n.num1*100)/10;
	n.num3 = num-n.num1*100-n.num2*10;
	if(n.num1==n.num2 || n.num2==n.num3 || n.num1==n.num3){
		return n0;
	}
	return n;
}

int numerontonum(numeron a)
{
	return a.num1*100+a.num2*10+a.num3;
}

void printnum(numeron n)
{
	printf("%d%d%d\n", n.num1,n.num2,n.num3);
}

void judge(numeron ans,numeron gss,int &e,int &b) //���� or �s����
{
	e=0;
	b=0;
	if(ans.num1 == gss.num1){
		e++;
	}
	if(ans.num2 == gss.num2){
		e++;
	}
	if(ans.num3 == gss.num3){
		e++;
	}
	
	if(ans.num1 == gss.num2 || ans.num1 == gss.num3){
		b++;
	}
	if(ans.num2 == gss.num1 || ans.num2 == gss.num3){
		b++;
	}
	if(ans.num3 == gss.num1 || ans.num3 == gss.num2){
		b++;
	}
}

void random(numeron &a,int s)
{
	a=n0;
	int ss=s;
	if(ss == 0) ss=rand();
	srand((unsigned int)time(NULL)-ss*9);
	while(a.num1==n0.num1 && a.num2==n0.num2 && a.num3==n0.num3){
		a=numtonumeron(rand()%1000);
	}
}

void random1(numeron &a,int s)
{
	a=n0;
	int ss=s;
	if(ss == 0) ss=rand();
	srand((unsigned int)time(NULL)+ss);
	while(a.num1==n0.num1 && a.num2==n0.num2 && a.num3==n0.num3){
		a=numtonumeron(rand()%1000);
	}
}


void seeder(numeron seeds[1000])
{
	for(int i=0;i<1000;i++){
		seeds[i]=numtonumeron(i);
	}
}

void printcpu(numeron ai,int &e,int &b)
{
	e=0;
	b=0;
	printf("CPU�̗\�z:");
	printnum(ai);
	while(1){
		printf("EAT:");
		scanf("%d",&e);
		printf("BITE:");
		scanf("%d",&b);
		if(e+b<4) break;
		else printf("�G���[: �s����EAT��BITE���ł��B\n");
	}
}

int equal(numeron a,numeron b)
{
	if(a.num1 == b.num1 && a.num2 == b.num2 && a.num3 == b.num3) return 1;
	else return 0;
}

int equal000(numeron seeds[1000])
{
	for(int i=0;i<1000;i++){
		if(!equal(seeds[i],n0)) return 0;
	}
	return 1;
}


void AI(numeron seeds[1000],numeron &ai,int e,int b) //�Ō�Ɏ��ɕ�������ai�ɑ��
{
	int i;
	seeds[numerontonum(ai)]=n0;
	int ee,bb;
	for(int i=0;i<1000;i++){
		judge(seeds[i],ai,ee,bb);
		if(ee!=e || bb!=b) seeds[i]=n0;
	}
	
	
	srand((unsigned int)time(NULL));
	i=rand()%1000;
	
		
	while(1){
		if(equal000(seeds)){
			printf("�G���[: EAT��BITE���ɊԈႢ������܂��B\n");
			break;
		}
		ai=seeds[i];
		if(!equal(seeds[numerontonum(ai)],n0)) break;
		else i++;
		if(i==1000) i=0;
	}
}

void test(numeron a[1000])
{
	for(int i=0;i<1000;i++){
		printnum(a[i]);
	}
}


int main(void)
{
	numeron seeds[1000];
	numeron n,ai,ans;
	//numeron ans={1,2,3};
	
	int e,b,cpe,cpb,turn,turncount;
	
	while(1){
		seeder(seeds);
		srand((unsigned int)time(NULL));
		turn = rand()%2;
		turncount = 0;
		random(ans,1);
		random1(ai,1);
		
		if(turn) printf("���Ȃ��͐�U�ł��B\n");
		else printf("���Ȃ��͌�U�ł��B\n");
		
		if(turn){
			while(1){
				turncount++;
				printf("\n�^�[�� %d\n",turncount);
				while(inputnum(n));
				judge(ans,n,e,b);
				printf("EAT  : %d\nBITE : %d\n", e, b);
			if(e==3){
					printf("\n\n      ���Ȃ��̏����ł��B\n");
					break;
				}
				printcpu(ai,cpe,cpb);
				if(cpe==3){
					printf("\n\n      CPU�̏����ł��B\n      (����:%d)\n",numerontonum(ans));
					break;
				}
				AI(seeds,ai,cpe,cpb);
			}
		}
		
		else{
			while(1){
				turncount++;
				printf("\n�^�[�� %d\n",turncount);
				printcpu(ai,cpe,cpb);
				if(cpe==3){
					printf("\n\n      CPU�̏����ł��B\n      (����:%03d)\n",numerontonum(ans));
					break;
				}
			AI(seeds,ai,cpe,cpb);
				while(inputnum(n));
				judge(ans,n,e,b);
				printf("EAT  : %d\nBITE : %d\n", e, b);
				if(e==3){
					printf("\n\n      ���Ȃ��̏����ł��B\n");
					break;
				}
			}
		}
		
		char s;
		printf("\n    F:�I��\n    R:�Đ�\n    ");
		while(1){
			scanf("%s",&s);
			if(s == 'F' || s == 'f') return 0;
			else if(s == 'R' || s == 'r') break;
			else printf("�G���[:F�܂���R�ȊO�̕����B\n");
		}
		printf("\n\n");
	}
}