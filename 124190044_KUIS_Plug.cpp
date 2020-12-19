#include "iostream"
#include "string.h"
#include "malloc.h"

#define max 50
using namespace std;

struct datadarah{
	int jumlah;
	char id[20];
};

struct typestack{
	int top;
	datadarah darah[max];
};
 typestack stack;

struct typeinfo{//Ini typeinfo saya bikin struct untuk menampung banyak data
	char nama[100];
	char id[20];
	int umur;
	char golongan[3];
};

typedef struct typenode * typeptr;
struct typenode{//ini typenode untuk membuat node
	typeinfo info;
	typeptr next;
};
typeptr awal, akhir;

bool valid = false;

void buatstack();
void cetakstack();
void push(datadarah IB);
void pop();
int stackkosong();
int stackpenuh();
void cekdata(typeinfo shark);//buat cek data yang mau di donor
bool cek(char a[], char b[]);//membandingkan kesamaan dua char array
void buatlistbaru();//bikin list baru
void sisipnode(typeinfo IB);//masukin node
void hapusnode(typeinfo IH);//hapus node
void bacamaju();//baca node iya masih pake fungsi yang dulu pas bikin pr, iya mendaur ulang sehat.
int listkosong();//cek list kosong atau nggak
void cekdarah(typeinfo tako);
void detailreserve(typestack chicken);
bool cekid(char a[]);

int main(){
	bool ulang=true;//buat mengulang setiap reset.
	typeinfo temp;//bikin info namanya temp.
	datadarah temp2;//bikin info temp2 buat nampung data darah.
	int pilih;
	cout << "Program Listing dsb."<<endl;
	while(ulang==true){
		system("CLS");
		cout<<"Pilih: \n";
		cout<<"1. Liat Data Pendonor\n";
		cout<<"2. Input Data Pendonor\n";//TAMPILAN
		cout<<"3. Hapus Data Pendonor\n";
		cout<<"4. Pendonoran Langsung\n";
		cout<<"5. Pendonoran Tidak Langsung\n";
		cout<<"6. Donor\n";
		cin>>pilih;cin.ignore();//buat pilih
		switch(pilih){
			case 1: 
				bacamaju();//eksekusi fungsi bacamaju
				cin.ignore();//biar gak langsung close
				break;
			case 2:
				cout<<"Masukan Nama: ";cin.getline(temp.nama,100);//cin.getline karena char array
				cout<<"Masukan ID: ";cin.getline(temp.id,20);//sama
				cout<<"Masukan Umur: ";cin>>temp.umur;cin.ignore();
				cout<<"Masukan Golongan Darah: ";cin.getline(temp.golongan,3);//karena AB dua digit jadi dibikin char array
				sisipnode(temp);//masukin temp
				break;
			case 3:
				cout<<"Masukan ID yang ingin di hapus: ";cin.getline(temp.id,20);//id yang mau dihapus
				hapusnode(temp);//hapus id yang udah diisi
				break;
			case 4:
				cout<<"Masukan Data orang ingin di Donor: \n\n";
				cout<<"Masukan Nama: ";cin.getline(temp.nama,100);
				cout<<"Masukan ID: ";cin.getline(temp.id,100);
				cout<<"Masukan Umur: ";cin>>temp.umur;cin.ignore();
				cout<<"Masukan Golongan Darah: ";cin.getline(temp.golongan,3);
				cekdata(temp);//kayak bacamaju tapi khusus cekdata
				cin.ignore();
				break;
			case 5:
				cout<<"Masukan Data orang ingin di Donor: \n\n";
				cout<<"Masukan Nama: ";cin.getline(temp.nama,100);
				cout<<"Masukan ID: ";cin.getline(temp.id,20);
				cout<<"Masukan Umur: ";cin>>temp.umur;cin.ignore();
				cout<<"Masukan Golongan Darah: ";cin.getline(temp.golongan,3);
				cekdarah(temp);
				cin.ignore();
				cin.ignore();
				break;
			case 6:
				cout<<"\n\nMasukan id: ";cin.getline(temp2.id,20);
				valid=cekid(temp2.id);
				if(valid==false){
					cout<<"id belum terdaftar!\n";
					cin.ignore();
				}
				else{
					cout<<"Masukan jumlah yang di donor darah (liter): ";cin>>temp2.jumlah;cin.ignore();

					push(temp2);
					cout<<"Input Berhasil: ";
					cout<<"ID: "<<stack.darah[stack.top].id<<endl;
					cout<<"Jumlah: "<<stack.darah[stack.top].jumlah<<endl;
					cin.ignore();
				}
				break;
			default:
				cout<<"Salah"<<endl;
		}
		
	}
	return 0;
}





void bacamaju(){
	typeptr bantu;//pointer bantu
	bantu=awal;//taro di awal
	while(bantu!=NULL){//OUTPUT
		cout <<"Nama     : "<< bantu->info.nama<<endl;
		cout <<"ID		 : "<<bantu->info.id<<endl;
		cout <<"Golongan : "<< bantu->info.golongan<<endl;
		cout <<"Umur     : "<<bantu->info.umur<<endl;
		cout <<"Status   : ";if(bantu->info.umur>=17&&bantu->info.umur<=60) cout<<"Bisa Donor"<<endl<<endl;
						else cout<<"Gak bisa Donor"<<endl<<endl;
		
		bantu=bantu->next;//tiap selesai pointer nunjuk ke node berikutnya
	}
}

bool cekgolongan(char pendonor[], char penerima[]){//fungsi untuk membandingkan golongan darah.
	char golA[3]={'A'};
	char golB[3]={'B'};
	char golO[3]={'O'};
	char golAB[3]={'A','B'};
	if(cek(pendonor,penerima))return true;//menggunakan fungsi cek() karena char array
	else if(cek(pendonor,golO))return true;//kalo pendonornya O berarti semuanya bisa (iyakan?)
	else if(penerima==golAB)return true;//kalo penerimanya AB berarti semuanya bisa (iyakan?)
	else return false;
}

void cekdata(typeinfo shark){//ini menampilkan tapi sambil di bandingkan
	typeptr bantu;
	bantu=awal;
	while(bantu!=NULL){
		if(cekgolongan(bantu->info.golongan,shark.golongan)/*pake fungsi cekgolongan*/&&(bantu->info.umur>=17&&bantu->info.umur<=60)){
			cout <<"Nama     : "<< bantu->info.nama<<endl;
			cout <<"ID		 : "<< bantu->info.id<<endl;
			cout <<"Golongan : "<< bantu->info.golongan<<endl;
			cout <<"Umur     : "<<bantu->info.umur<<endl;
			cout <<"Status   : ";
			if(bantu->info.umur>=17&&bantu->info.umur<=60) cout<<"Bisa Donor"<<endl<<endl;
			else cout<<"Gak bisa Donor"<<endl<<endl;
		}
		bantu=bantu->next;
	}
}

void cekdarah(typeinfo tako){
	typeptr bantu;
	bantu=awal;
	char temp3[max][20];
	int total=0;
	int i=0,pilih;
	while(bantu!=NULL){
		if(cekgolongan(bantu->info.golongan,tako.golongan)&&(bantu->info.umur>=17&&bantu->info.umur<=60)){
			strcpy(temp3[i], bantu->info.id);
			cout<<endl<<temp3<<endl;
			i++;
		}
		bantu=bantu->next;
	}
	bantu=awal;
	while(bantu!=NULL){
		i=0;
		if(temp3[i]==bantu->info.id){
			cout<<stack.darah[i].jumlah;
			total+=stack.darah[i].jumlah;
			i++;
		} 
		bantu=bantu->next;
	}
	bool salah=false;
	while(salah==false){
		cout<<"Total: "<<total<<endl<<endl;
		cout<<"1. Detail: \n";
		cout<<"2. Ambil: \n";
		cout<<"Pilih: ";cin>>pilih;
		if(pilih==1){
			salah=true;
			detailreserve(stack);
		} 
		else if(pilih==2){
			salah = true;
			pop();	
		}
		else cout<<"Error, coba lagi.";
	}
	
	
}

void detailreserve(typestack chicken){
	typeptr bantu;
	bantu=awal;
	int i=0;
	while(bantu!=NULL){
		if(cekgolongan(bantu->info.id,chicken.darah[i].id)&&(bantu->info.umur>=17&&bantu->info.umur<=60)){
			cout<<"Nama: "<<bantu->info.nama<<endl;
			cout<<"Umur: "<<bantu->info.umur<<endl;
			cout<<"Golongan: "<<bantu->info.golongan<<endl;
			cout<<"Jumlah: "<<chicken.darah[i].jumlah<<" liter."<<endl;
			i++;
		}
		bantu=bantu->next;
	}
}

void buatlistbaru(){//buat list baru tapi kosong
	typeptr list;
	list = NULL;
	awal = list;
	akhir = list;
}

int listkosong(){//cek list kosong nggak
	if(awal==NULL) return(true);
	else return(false);
}

void sisipnode(typeinfo IB){
	
	typeptr NB, bantu;
	NB = (typenode *) malloc(sizeof(typenode));
	NB -> info = IB;
	NB -> next = NULL;
	//Gunakan fungsi malloc untuk menyediakan tempat buat typenode baru "malloc(sizeof(typenode)). 
	//Nah, typenode itu dibuatkan pointer (typenode *) dan pointer itu dimasukan ke NB.
	//Sehingga NB adalah pointer yang menunjuk ke typenode baru!

	if (listkosong()){//kalo kosong node ditaru di awal
		awal = NB;
		akhir = NB;
	}
	else if (IB.umur <= awal ->info.umur){//kalo lebih kecil dari awal maka ditaruh di awal
		NB->next=awal;
		awal=NB;
	}
	else {//kalo ditengah maka dia akan nyari satu satu sampe lebih kecil. Dalam kasus ini aku urutin berdasarkan umur
		bantu=awal;
		while(bantu->next!=NULL and IB.umur > bantu->next->info.umur)bantu=bantu->next;
		NB->next=bantu->next;
		bantu->next=NB;
		if(IB.umur>akhir->info.umur)akhir=NB;
	}
}

bool cek(char a[], char b[]){//ini fungsi buat cek char array
	if(strlen(a)==strlen(b)){//pertama bandingin ukurannya dulu sama gak?
		for(int i=0; i<strlen(a);i++){//kalo sama tiap elemen array di bandingin satu satu
			if(a[i]!=b[i]) return false;
		}
	}
	
}

void hapusnode(typeinfo IH){//hapus node
	typeptr hapus, bantu;
	if (listkosong()){//cek kosong gak
		cout << "List masih kosong\n";
	}
	
	else if (cek(awal->info.id,IH.id)){//bandingin sama gak nama yang mau dihapus sama awal
		hapus=awal;
		awal=hapus->next;
		free(hapus);
	}
	else{//yang ini intinya roll sampe nemu 
		bantu=awal;//mulai dari awal
		while(bantu->next->next!=NULL and !cek(IH.id,bantu->next->info.id))bantu=bantu->next;
		if(cek(IH.id,bantu->next->info.id)){ 
			hapus=bantu->next;
			if(hapus==akhir){//cek akhir gak. Kalo ahir berarti node terakhir nunjuk ke NULL
				akhir=bantu;
				akhir->next=NULL;
			}
			else bantu->next = hapus->next;//node yang sebelumnya ditunjuk ke node setelah yang mau dihapus
			//lalu yang mau dihapus dihapus
			free(hapus);//free memory
		}
		else cout<< "Tidak ditemukan! \n";//kalo udah muter muter gak nemu
	}
}

void buatstack(){ 
	stack.top=-1; 
}

int stackkosong(){ 
	if (stack.top==-1)return(true);
 else
return(false); }

int stackpenuh(){ 
	if (stack.top==max) return(true);
	else return(false); 
}

void push(datadarah IB){ 
	if(stackpenuh()) cout << "stack overflow\n";
	else{
		stack.top++;
		stack.darah[stack.top]=IB;
	};
}

void pop(){ 
	datadarah IP;
	if(stackkosong()) cout << "stack underflow\n";
	else{
	IP=stack.darah[stack.top];
	stack.top--;
	}; 
}

void cetakstack(){
	int i=0;
	while (i<=stack.top){
		cout << " " << stack.darah[i].id << endl;
		i++;
	}
}

bool cekid(char a[]){
	typeptr bantu;
	bantu=awal;
	bool hasil=false;
	while(bantu!=NULL){
		if(cek(bantu->info.id,a)) hasil=true;
		bantu=bantu->next;
	}
	if(hasil==true){
		return true;
	}
	else return false;
}

