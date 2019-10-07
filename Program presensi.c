#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdarg.h>
#include<time.h>
#include<windows.h>
#include<math.h>

#define MAX_MATKUL 16
#define MAX 256

FILE *fp;
int _no[MAX_MATKUL],_sks[MAX_MATKUL];
char _mk[MAX_MATKUL][MAX],_periode[MAX_MATKUL][MAX],
	_waktu[MAX_MATKUL][MAX];
struct Student{
	char name[MAX];
	char number[11];
};

void clear_screen(){
	system("cls");
	return;
}

char *separ(){
	return "----------------------------------------------";
}

void fetch_char(char *target){
	*target=getch();
	return;
}

int isNum(char str[]){
	int t=0;
	char ch;
	while(1){
		ch=*str;
		if(ch=='\0') break;
		if((int)ch>=48&&(int)ch<=57){
			t=1;
			break;
		}
		str++;
	}
	return t;
}

int parse(char str[]){
	int len=strlen(str),t=0;
	while(len>0){
		t+=((int)(*str)-48)*pow(10,len-1);
		str++;
		len--;
	}
	return t;
}

void set_txt(int n,...){
	va_list arg;
	va_start(arg,n);
	for(int i=1;i<=n;i++){
		printf("%s\n",va_arg(arg,char[]));
	}
	va_end(arg);
	return;
}

void input_file(int *i){
	int val;
	while(1){
		val=*i;
		_no[val]=val+1;
		if(fscanf(fp,"%[^;];%d;%[^;];%[^\n]\n",
			_mk[val],&_sks[val],_periode[val],_waktu[val]
		)==EOF) break;
		(*i)++;
	}
	return;
}

void disp_mem(int n){
	for(int i=0;i<n;i++){
		printf("%d. %s | %d\n",_no[i],_mk[i],_sks[i]);
	}
	if(n==0) printf("Tidak ada mata kuliah terdaftar\n");
	return;
}

char *matkul_info(){
	int sks;
	static char mk[MAX];
	char periode[MAX],waktu[MAX];
	clear_screen();
	printf("Masukkan nama mata kuliah: ");
	scanf(" %[^\n]",&mk);
	printf("Jumlah SKS: ");
	scanf("\n%d",&sks);
	set_txt(3,
		"Masukkan periode perkuliahan...",
		"Format: (Tanggal mulai) - (Tanggal selesai)",
		"Format tanggal: \"dd mm yy\""
	);
	scanf(" %[^\n]",&periode);
	set_txt(2,
		"Masukkan waktu perkuliahan...",
		"Format: (3 huruf pertama hari) (jam mulai):(menit mulai)-(jam selesai):(menit selesai)"
	);
	scanf(" %[^\n]",&waktu);
	fp=fopen("matkul.csv","a");
	fprintf(fp,"%s;%d;%s;%s\n",mk,sks,periode,waktu);
	fclose(fp);
	return mk;
}

void input_student(struct Student *x,int *n){
	clear_screen();
	char temp[MAX];
	printf("Masukkan nama mahasiswa: ");
	scanf(" %[^\n]",&temp);
	strcpy(x->name,temp);
	printf("Masukkan NPM: ");
	scanf(" %[^\n]",&temp);
	strcpy(x->number,temp);
	(*n)++;
	return;
}

void write_class(char mk[],struct Student student[],int n){
	fp=fopen(strcat(mk," (Mahasiswa).csv"),"a");
	for(int i=0;i<n;i++){
		fprintf(fp,"%s;%s\n",student[i].name,student[i].number);
	}
	fclose(fp);
	return;
}

void matkul_students(char mk[]){
	int n=0,exit=0;
	char resp;
	struct Student student[MAX];
	while(!exit){
		clear_screen();
		printf("Daftar mahasiswa di kelas %s:\n",mk);
		if(n==0) printf("--- Tidak ada mahasiswa terdaftar ---\n");
		else{
			printf("No Nama NPM\n");
			for(int i=0;i<n;i++){
				printf("%d. %s %s\n",i+1,student[i].name,student[i].number);
			}
		}
		set_txt(3,
			separ(),
			"a. Tambah mahasiswa",
			"b. Selesai"
		);
		fetch_char(&resp);
		switch(resp){
			case 'A':case 'a':input_student(&student[n],&n);break;
			case 'B':case 'b':exit=1;break;
		}
	}
	write_class(mk,student,n);
	return;
}

void add_matkul(){
	char *mk=matkul_info();
	matkul_students(mk);
	return;
}

int parse_day(char day[]){
	char list_of_day[][3]={"Min","Sen","Sel","Rab","Kam","Jum","Sab"};
	int len=sizeof(list_of_day)/sizeof(list_of_day[0]);
	for(int i=0;i<len;i++){
		if(*list_of_day[i]==*day) return i;
	}
}

int in_range_time(int mk,time_t t){
	struct tm *curr=localtime(&t);
	struct Time{
		char hr[3];
		char min[3];
	} start,end;
	char day[4];
	int curr_min=(curr->tm_hour)*60+curr->tm_min,start_min,end_min;
	sscanf(_waktu[mk],"%s %[^:]:%[^-]-%[^:]:%[^\0]",
		&day,&start.hr,&start.min,&end.hr,&end.min
	);
	start_min=parse(start.hr)*60+parse(start.min);
	end_min=parse(end.hr)*60+parse(end.min);
	if(curr->tm_wday!=parse_day(day)) return 0;
	if(curr_min<start_min||curr_min>end_min) return 0;
	return 1;
}

int in_range_period(int mk,time_t curr_secs){
	struct A{
		char date[3];
		char mo[3];
		char yr[3];
	} s_info,e_info;
	time_t start_secs,end_secs;
	sscanf(_periode[mk],"%s %s %s - %s %s %s",
		&s_info.date,&s_info.mo,&s_info.yr,&e_info.date,&e_info.mo,&e_info.yr
	);
	struct tm
		start={0,0,0,parse(s_info.date),parse(s_info.mo)-1,parse(s_info.yr)+100},
		end={23,59,59,parse(e_info.date),parse(e_info.mo)-1,parse(e_info.yr)+100};
	start_secs=mktime(&start);
	end_secs=mktime(&end);
	if((int)difftime(curr_secs,start_secs)>(int)difftime(end_secs,start_secs))
		return 0;
	return 1;
}

void start_presence(int mk,time_t t){
	int i=1;
	char fname[MAX],temp_mhs[MAX],temp_npm[MAX],resp;
	struct tm *curr=localtime(&t);
	FILE* fq;
	set_txt(3,
		"Lakukan presensi untuk setiap mahasiswa dengan menekan salah satu:",
		"\"h\" apabila mahasiswa tersebut hadir, sebaliknya \"t\"",
		separ()
	);
	strcpy(fname,_mk[mk]);
	strcat(fname," (Presensi).csv");
	fp=fopen(fname,"a");
	fprintf(fp,"%d;%d;%d",curr->tm_mday,curr->tm_mon+1,curr->tm_year+1900);
	strcpy(fname,_mk[mk]);
	strcat(fname," (Mahasiswa).csv");
	fq=fopen(fname,"r");
	while(fscanf(fq,"%[^;];%[^\n]\n",&temp_mhs,&temp_npm)!=EOF){
		printf("\n%d. %s %s (Hadir/tidak hadir) ",i,temp_mhs,temp_npm);
		fetch_char(&resp);
		switch(resp){
			case 'h':case 'H':
				fprintf(fp,";1");
				i++;
			break;
			case 't':case 'T':
				fprintf(fp,";0");
				i++;
			break;
		}
	}
	fprintf(fp,"\n");
	fclose(fq);
	fclose(fp);
	clear_screen();
	printf("Presensi selesai\n");
	return;
}

void presence_check(int mk){
	char resp;
	time_t curr_time;
	clear_screen();
	time(&curr_time);
	if(in_range_time(mk,curr_time)&&in_range_period(mk,curr_time))
		start_presence(mk,curr_time);
	else{
		set_txt(7,
			"Tidak dapat melakukan presensi",
			"Waktu kuliah belum dimulai atau sudah berakhir",
			separ(),
			"Solusi:",
			"1. Jika masih periode kuliah, tunggu hingga kuliah dimulai kembali",
			"2. Jika sudah di luar periode, silahkan buat mata kuliah baru",
			separ()
		);
	}
	printf("Tekan apa saja untuk melanjutkan");
	fetch_char(&resp);
	return;
}

char *parse_month(int mo){
	static char* arr[]={
		"Januari","Februari","Maret","April","Mei","Juni",
		"Juli","Agustus","September","Oktober","November","Desember"
	};
	return arr[mo];
}

void detail_presence(FILE *p,int mk){
	struct Student list[MAX];
	struct info{
		int date;
		int mo;
		int yr;
	} class_date[MAX];
	char fname[MAX];
	int data[MAX][MAX],n=0,tot=0,jum_masuk,cnt;
	float persen_hadir;
	strcpy(fname,_mk[mk]);
	strcat(fname," (Mahasiswa).csv");
	FILE *q=fopen(fname,"r");
	while(fscanf(q,"%[^;];%[^\n]\n",&list[n].name,&list[n].number)!=EOF) n++;
	fclose(q);
	while(fscanf(p,"%d;%d;%d",
		&class_date[tot].date,&class_date[tot].mo,&class_date[tot].yr
	)!=EOF){
		for(int i=0;i<n;i++) fscanf(p,";%d",&data[i][tot]);
		fscanf(p,"\n");
		tot++;
	}
	for(int i=0;i<n;i++){
		jum_masuk=0;
		for(int j=0;j<tot;j++) jum_masuk+=data[i][j];
		printf("%d. %s %s\n",i+1,list[i].name,list[i].number);
		printf("  %d kali masuk\n",jum_masuk);
		printf("  %d kali absen\n",tot-jum_masuk);
		cnt=0;
		for(int j=0;j<tot;j++){
			if(data[i][j]==0){
				if(cnt==0) printf("  Absen di tanggal:\n");
				cnt++;
				printf("  %d. %d %s %d\n",
					cnt,class_date[j].date,
					parse_month(class_date[j].mo),class_date[j].yr
				);
			}
		}
		persen_hadir=(float)(jum_masuk*100);
		persen_hadir/=(float)tot;
		printf("  Persentase kehadiran: %.2f%%\n",persen_hadir);
		if(persen_hadir<75)
			printf("  Peserta ini tidak diperbolehkan mengikuti ujian\n");
		else printf("  Peserta ini dapat mengikuti ujian\n");
	}
	return;
}

void view_presence(int idx_mk){
	char resp,mk[MAX];
	clear_screen();
	strcpy(mk,_mk[idx_mk]);
	strcat(mk," (Presensi).csv");
	fp=fopen(mk,"r");
	if(fp==NULL){
		printf("Presensi tidak ditemukan atau belum dilakukan\n");
	}
	else detail_presence(fp,idx_mk);
	fclose(fp);
	set_txt(2,
		separ(),
		"Tekan tombol apa saja untuk melanjutkan"
	);
	fetch_char(&resp);
	return;
}

int expand_matkul(int mk){
	int i;
	char resp,temp1[MAX],temp2[11],fname[MAX];
	mk--;
	while(1){
		clear_screen();
		printf("Nama mata kuliah: %s\n",_mk[mk]);
		printf("Jumlah SKS: %d\n",_sks[mk]);
		printf("Periode perkuliahan: %s\n",_periode[mk]);
		printf("Waktu perkuliahan: %s\n",_waktu[mk]);
		printf("%s\n",separ());
		printf("Peserta kelas:\n");
		printf("No. Nama NPM\n");
		strcpy(fname,_mk[mk]);
		i=0;
		fp=fopen(strcat(fname," (Mahasiswa).csv"),"r");
		while(1){
			i++;
			if(fscanf(fp,"%[^;];%s\n",&temp1,&temp2)==EOF) break;
			printf("%d. %s %s\n",i,temp1,temp2);
		}
		fclose(fp);
		set_txt(4,
			separ(),
			"A. Mulai presensi (Harus dilakukan pada jam perkuliahan)",
			"B. Lihat presensi",
			"C. Kembali"
		);
		fetch_char(&resp);
		switch(resp){
			case 'A':case 'a':presence_check(mk);break;
			case 'B':case 'b':view_presence(mk);break;
			case 'C':case 'c':return 0;break;
		}
	}
}

int main_menu(){
	clear_screen();
	fp=fopen("matkul.csv","r");
	set_txt(3,
		"Berikut mata kuliah yang Anda ampu:",
		separ(),
		"No | Mata kuliah | SKS"
	);
	int count_mk=0,len;
	char resp[MAX];
	input_file(&count_mk);
	fclose(fp);
	disp_mem(count_mk);
	set_txt(3,separ(),"A. Tambah mata kuliah baru","B. Keluar");
	scanf("%s",&resp);
	len=strlen(resp);
	if(len==1&&(resp[0]=='A'||resp[0]=='B')){
		if(resp[0]=='A') add_matkul();
		else if(resp[0]=='B') return 1;
	}
	else if(isNum(resp)&&parse(resp)<=count_mk){
		return expand_matkul(parse(resp));
	}
	else return 0;
}

void main_page(){
	char resp;
	clear_screen();
	printf("\t\t                        707                       \n");
	printf("\t\t                      7772777                     \n");
	printf("\t\t                 7488888808888885                 \n");
	printf("\t\t           7487 888887 50087 588885 285           \n");
	printf("\t\t          8882 88008   80488  780082 8885         \n");
	printf("\t\t         8888  88098  780408   89088 78884        \n");
	printf("\t\t     78  88982 788884  80488  88888  08488 78     \n");
	printf("\t\t     88  880082  70888 28887 88847  080888  88    \n");
	printf("\t\t     885  4888887   79881 8882    4888882  888    \n");
	printf("\t\t  87 28887   77488827  97 87  74888177   78887 80 \n");
	printf("\t\t  887  7727         797 074 447         7277  288 \n");
	printf("\t\t  88885272240809557    88884    25408880522508885 \n");
	printf("\t\t77 7088880577     780   880   887     7750888047 7\n");
	printf("\t\t 58    7            28  882  87                787\n");
	printf("\t\t7 488807   78847727  72 082 8   27774887   788882 \n");
	printf("\t\t87      78887      87 2748777 41      78887      5\n");
	printf("\t\t 288908882     8887 89788888787 2888     488808887\n");
	printf("\t\t  77227        7 88  888777882  81 7        7227  \n");
	printf("\t\t 782772          88  788   88   84          27728 \n");
	printf("\t\t  7277          884  787 8 787  882         7772  \n");
	printf("\t\t   7772         788274898889847588          2777  \n");
	printf("\t\t     7757    77272777 58  787 77777777    7277    \n");
	printf("\t\t      7   477782   4527 787 7245   547771   7     \n");
	printf("\t\t            7 8    7777404817777    0 7 7         \n");
	printf("\t\t      887882727545227727222227224445777288788     \n");
	printf("\t\t         4452777777   8827488   7777772541        \n");
	printf("\t\t          72225557   888   884  77451222          \n");
	printf("\t\t            777777877887777288 08777777           \n");
	printf("\t\t                  7   57   75  77                 \n");
	printf("\t\t_____________________________________________\n");
	printf("\t\t||\tSelamat datang di Program Presensi  ||\n");
	printf("\t\t||\t	A Mini-Project by:          ||\n");
	printf("\t\t||\t   Gilbert Parluhutan Siagian       ||\n");
	printf("\t\t||\t	Alvin Audinata              ||\n");
	printf("\t\t||__________________________________________||\n");
	printf("Press Any Key To Continue");
	system("color 1E");
	fetch_char(&resp);
	while(1){
		if(main_menu()) break;
	}
	return;
}

int main(){
	main_page();
	clear_screen();
	return 0;
}
