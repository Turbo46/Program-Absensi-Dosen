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
struct Date{
	char date[3];
	char mo[3];
	char yr[3];
};
struct Time{
	char hr[3];
	char min[3];
};

void clear_screen(){
	system("cls");
	return;
}

char *separ(){
	return "----------------------------------------------";
}

void err_txt(){
	printf("Input yang dimasukkan salah. Silahkan coba kembali\n%s\n",separ());
	return;
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

int hasLen(char *str,int len){
	if(strlen(str)==len) return 1;
	return 0;
}

int parse_day(char day[]){
	char list_of_day[][3]={"Min","Sen","Sel","Rab","Kam","Jum","Sab"};
	int len=sizeof(list_of_day)/sizeof(list_of_day[0]);
	for(int i=0;i<len;i++){
		if(*list_of_day[i]==*day) return i;
	}
	return -1;
}

int isTruePeriod(char *period){
	int len,cnt,date,mo,yr,
		day_in_a_month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	struct Date start,end;
	len=strlen(period);
	if(len!=19) return 0;
	cnt=sscanf(period,"%s %s %s - %s %s %s",
		&start.date,&start.mo,&start.yr,&end.date,&end.mo,&end.yr
	);
	if(cnt!=6) return 0;
	if(isNum(start.date)&&hasLen(start.date,2)) date=parse(start.date);
	else return 0;
	if(isNum(start.mo)&&hasLen(start.mo,2)) mo=parse(start.mo);
	else return 0;
	if(isNum(start.yr)&&hasLen(start.yr,2)) yr=parse(start.yr);
	else return 0;
	if(date<1||date>((yr%4==0&&mo==2)?29:day_in_a_month[mo])) return 0;
	if(mo<1||mo>12) return 0;
	if(isNum(end.date)&&hasLen(end.date,2)) date=parse(end.date);
	else return 0;
	if(isNum(end.mo)&&hasLen(end.mo,2)) mo=parse(end.mo);
	else return 0;
	if(isNum(end.yr)&&hasLen(end.yr,2)) yr=parse(end.yr);
	else return 0;
	if(date<1||date>((yr%4==0&&mo==2)?29:day_in_a_month[mo])) return 0;
	if(mo<1||mo>12) return 0;
	return 1;
}

int isTrueTime(char *time){
	int len,cnt,hr,min;
	char day[4];
	struct Time start,end;
	len=strlen(time);
	if(len!=15) return 0;
	cnt=sscanf(time,"%s %[^:]:%[^-]-%[^:]:%s",
		day,&start.hr,&start.min,&end.hr,&end.min);
	if(cnt!=5) return 0;
	if(parse_day(day)==-1) return 0;
	if(isNum(start.hr)&&hasLen(start.hr,2)) hr=parse(start.hr);
	else return 0;
	if(isNum(start.min)&&hasLen(start.min,2)) min=parse(start.min);
	else return 0;
	if(hr<0||hr>23) return 0;
	if(min<0||min>59) return 0;
	if(isNum(end.hr)&&hasLen(end.hr,2)) hr=parse(end.hr);
	else return 0;
	if(isNum(end.min)&&hasLen(end.min,2)) min=parse(end.min);
	else return 0;
	if(hr<0||hr>23) return 0;
	if(min<0||min>59) return 0;
	return 1;
}

int about_to_back(char resp[]){
	if(strlen(resp)==1&&(int)resp[0]=='\\') return 1;
	return 0;
}

void back_txt(){
	printf("(Untuk kembali, masukkan tanda \"\\\")\n");
	return;
}

char *matkul_info(){
	int error=0;
	static char mk[MAX];
	char periode[MAX],waktu[MAX],sks[MAX],temp[MAX];
	clear_screen();
	back_txt();
	printf("Masukkan nama mata kuliah: ");
	scanf(" %[^\n]",&temp);
	if(about_to_back(temp)) return "\b";
	strcpy(mk,temp);
	while(1){
		clear_screen();
		if(error==1){
			err_txt();
			error=0;
		}
		printf("Jumlah SKS: ");
		scanf("\n%s",&temp);
		if(about_to_back(temp)) return "\b";
		strcpy(sks,temp);
		if(isNum(sks)) break;
		error=1;
	}
	while(1){
		clear_screen();
		if(error==1){
			err_txt();
			error=0;
		}
		set_txt(3,
			"Masukkan periode perkuliahan...",
			"Format: (Tanggal mulai) - (Tanggal selesai)",
			"Format tanggal: \"dd mm yy\""
		);
		scanf(" %[^\n]",&temp);
		if(about_to_back(temp)) return "\b";
		strcpy(periode,temp);
		if(isTruePeriod(periode)) break;
		error=1;
	}
	while(1){
		clear_screen();
		if(error==1){
			err_txt();
			error=0;
		}
		set_txt(2,
			"Masukkan waktu perkuliahan...",
			"Format: (3 huruf pertama hari) (jam mulai):(menit mulai)-(jam selesai):(menit selesai)"
		);
		scanf(" %[^\n]",&temp);
		if(about_to_back(temp)) return "\b";
		strcpy(waktu,temp);
		if(isTrueTime(waktu)) break;
		error=1;
	}
	fp=fopen("matkul.csv","a");
	fprintf(fp,"%s;%d;%s;%s\n",mk,parse(sks),periode,waktu);
	fclose(fp);
	return mk;
}

void input_student(struct Student *x,int *n){
	clear_screen();
	int error=0;
	char temp[MAX];
	back_txt();
	printf("Masukkan nama mahasiswa: ");
	scanf(" %[^\n]",&temp);
	if(about_to_back(temp)) return;
	strcpy(x->name,temp);
	while(1){
		clear_screen();
		if(error==1){
			err_txt();
			error=0;
		}
		printf("Masukkan NPM: ");
		scanf(" %[^\n]",&temp);
		if(about_to_back(temp)) return;
		if(isNum(temp)&&hasLen(temp,10)) break;
		error=1;
	}
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
	int n=0,exit=0,error=0;
	char resp;
	struct Student student[MAX];
	while(!exit){
		clear_screen();
		if(error==1){
			err_txt();
			error=0;
		}
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
			default:error=1;
		}
	}
	write_class(mk,student,n);
	return;
}

void add_matkul(){
	char *mk=matkul_info();
	if(mk=="\b") return;
	matkul_students(mk);
	return;
}

int in_range_time(int mk,time_t t){
	struct tm *curr=localtime(&t);
	struct Time start,end;
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
	struct Date s_info,e_info;
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

char start_presence(int mk,time_t t){
	int i=1,error=0,exit=0;
	char fname[MAX],temp_mhs[MAX],temp_npm[MAX],resp;
	struct tm *curr=localtime(&t);
	FILE* fq;
	set_txt(3,
		"Lakukan presensi untuk setiap mahasiswa dengan menekan salah satu:",
		"\"h\" apabila mahasiswa tersebut hadir, sebaliknya \"t\"",
		separ()
	);
	back_txt();
	printf("%s",separ());
	strcpy(fname,_mk[mk]);
	strcat(fname," (Presensi).csv");
	fp=fopen(fname,"a");
	fprintf(fp,"%d;%d;%d",curr->tm_mday,curr->tm_mon+1,curr->tm_year+1900);
	strcpy(fname,_mk[mk]);
	strcat(fname," (Mahasiswa).csv");
	fq=fopen(fname,"r");
	while(fscanf(fq,"%[^;];%[^\n]\n",&temp_mhs,&temp_npm)!=EOF){
		while(1){
			if(error==1){
				err_txt();
				error=0;
			}
			printf("\n%d. %s %s (Hadir/tidak hadir) ",i,temp_mhs,temp_npm);
			fetch_char(&resp);
			switch(resp){
				case 'h':case 'H':
					fprintf(fp,";1");
					i++;
					exit=1;
				break;
				case 't':case 'T':
					fprintf(fp,";0");
					i++;
					exit=1;
				break;
				case '\\':return '\b';break;
				default:
					clear_screen();
					error=1;
			}
			if(exit==1) break;
		}
	}
	fprintf(fp,"\n");
	fclose(fq);
	fclose(fp);
	clear_screen();
	printf("Presensi selesai\n");
	return '\0';
}

void presence_check(int mk){
	char resp;
	time_t curr_time;
	clear_screen();
	time(&curr_time);
	if(in_range_time(mk,curr_time)&&in_range_period(mk,curr_time))
		resp=start_presence(mk,curr_time);
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
	if(resp=='\b') return;
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

int confirm_delete(int mk){
	char resp;
	int error=0;
	while(1){
		clear_screen();
		if(error==1){
			err_txt();
			error=0;
		}
		printf("Anda yakin ingin menghapus mata kuliah \"%s\"? (y/t) ",_mk[mk]);
		fetch_char(&resp);
		switch(resp){
			case 'y':case 'Y':return 1;break;
			case 't':case 'T':return 0;break;
			default:error=1;
		}
	}
}

void delete_matkul(int mk){
	FILE *fq;
	char temp[512],filename[512],resp,
		suff[2][32]={" (Mahasiswa).csv"," (Presensi).csv"};
	int i=0,ln;
	if(!confirm_delete(mk)) return;
	fp=fopen("matkul.csv","r");
	fq=fopen("t","w+");
	ln=mk+1;
	while(fscanf(fp,"%[^\n]\n",temp)!=EOF){
		i++;
		if(i!=ln) fprintf(fq,"%s\n",temp);
	}
	fclose(fp);
	fclose(fq);
	remove("matkul.csv");
	rename("t","matkul.csv");
	for(i=0;i<2;i++){
		strcpy(filename,_mk[mk]);
		strcat(filename,suff[i]);
		remove(filename);
	}
	clear_screen();
	printf("Mata kuliah \"%s\" sudah terhapus\n",_mk[mk]);
	printf("Tekan apa saja untuk melanjutkan\n");
	fetch_char(&resp);
	return;
}

void expand_matkul(int mk){
	int i,error=0;
	char resp,temp1[MAX],temp2[11],fname[MAX];
	mk--;
	while(1){
		clear_screen();
		if(error==1){
			err_txt();
			error=0;
		}
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
		set_txt(5,
			separ(),
			"A. Mulai presensi (Harus dilakukan pada jam perkuliahan)",
			"B. Lihat presensi",
			"X. Hapus mata kuliah ini",
			"Y. Kembali"
		);
		fetch_char(&resp);
		switch(resp){
			case 'A':case 'a':presence_check(mk);break;
			case 'B':case 'b':view_presence(mk);break;
			case 'X':case 'x':
				delete_matkul(mk);
				return;
			break;
			case 'Y':case 'y':return;break;
			default:error=1;
		}
	}
}

void main_menu(){
	int count_mk,len,error=0;
	while(1){
		clear_screen();
		if(error==1){
			err_txt();
			error=0;
		}
		fp=fopen("matkul.csv","r");
		set_txt(3,
			"Berikut mata kuliah yang Anda ampu:",
			separ(),
			"No | Mata kuliah | SKS"
		);
		count_mk=0;
		char resp[MAX];
		input_file(&count_mk);
		fclose(fp);
		disp_mem(count_mk);
		set_txt(3,separ(),"A. Tambah mata kuliah baru","B. Keluar");
		scanf("%s",&resp);
		len=strlen(resp);
		if(len==1){
			switch(resp[0]){
				case 'A':case 'a':add_matkul();break;
				case 'B':case 'b':return;break;
				default:
					if(isNum(resp)&&parse(resp)<=count_mk)
						expand_matkul(parse(resp));
					else error=1;
				break;
			}
		}
		else error=1;
	}
}

void banner(){
	set_txt(36,
		"\t\t                        ***                       ",
		"\t\t                      *******                     ",
		"\t\t                 ****************                 ",
		"\t\t           **** ****** ***** ****** ***           ",
		"\t\t          **** *****   *****  ****** ****         ",
		"\t\t         ****  *****  ******   ***** *****        ",
		"\t\t     **  ***** ******  *****  *****  ***** **     ",
		"\t\t     **  ******  ***** ***** *****  ******  **    ",
		"\t\t     ***  *******   ***** ****    *******  ***    ",
		"\t\t  ** *****   ********  ** **  ********   ***** ** ",
		"\t\t  ***  ****         *** *** ***         ****  *** ",
		"\t\t  *****************    *****    ***************** ",
		"\t\t** **********     ***   ***   ***     ********** *",
		"\t\t **    *            **  ***  **                ***",
		"\t\t* ******   ********  ** *** *   ********   ****** ",
		"\t\t**      *****      ** ******* **      *****      *",
		"\t\t *********     **** *********** ****     *********",
		"\t\t  *****        * **  *********  ** *        ****  ",
		"\t\t ******          **  ***   **   **          ***** ",
		"\t\t  ****          ***  *** * ***  ***         ****  ",
		"\t\t   ****         ******************          ****  ",
		"\t\t     ****    ******** **  *** ********    ****    ",
		"\t\t      *   ******   **** *** ****   ******   *     ",
		"\t\t            * *    *************    * * *         ",
		"\t\t      ***************************************     ",
		"\t\t         **********   *******   **********        ",
		"\t\t          ********   ***   ***  ********          ",
		"\t\t            ****************** ********           ",
		"\t\t                  *   **   **  **                 ",
		"\t\t_____________________________________________",
		"\t\t||\tSelamat datang di Program Presensi  ||",
		"\t\t||\t	A Mini-Project by:          ||",
		"\t\t||\t   Gilbert Parluhutan Siagian       ||",
		"\t\t||\t	Alvin Audinata              ||",
		"\t\t||__________________________________________||",
		"Press Any Key To Continue"
	);
	return;
}

void main_page(){
	char resp;
	clear_screen();
	banner();
	system("color 1E");
	fetch_char(&resp);
	main_menu();
	return;
}

int main(){
	main_page();
	clear_screen();
	printf("Program selesai");
	return 0;
}
