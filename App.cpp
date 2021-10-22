#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct newTugas {
    string name;
    tm dl;
    bool selesai;
};

//konversi angka ke nama hari
string weekday(int d){
    switch (d){
    case 1: return "Senin"; case 2: return "Selasa"; case 3: return "Rabu" ;
    case 4: return "Kamis"; case 5: return "Jumat" ; case 6: return "Sabtu";
    case 7: return "Minggu"; case 0: return "Minggu";
    }
}

//konversi angka ke nama bulan
string month(int m){
    switch (m){
    case 1: return "Jan"; case 2: return "Feb"; case 3: return "Mar" ; case 4: return "April"; 
    case 5: return "Mei" ; case 6: return "Jun"; case 7: return "Jul"; case 8: return "Ags";
    case 9: return "Sep" ; case 10: return "Okt"; case 11: return "Nov"; case 12: return "Des";
    }
}

//mengambil input deadline 
tm inputDL(){
    string dl;
    tm DL;
    cout<< "tambahkan deadline (dd/mm/yy hh:mm): ";
    getline(cin, dl);
    DL.tm_mday   = stoi(dl.substr(0,2));
    DL.tm_mon = stoi(dl.substr(3,2));
    DL.tm_year  = stoi(dl.substr(6,2));
    DL.tm_hour    = stoi(dl.substr(9,2));
    DL.tm_min   = stoi(dl.substr(12,2));
    
    return DL;
}

//Fungsi mengambil waktu sekarang
tm getTimeNow(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    tm Now;
    Now.tm_mday = ltm->tm_mday;
    Now.tm_wday = ltm->tm_wday;
    Now.tm_mon = 1 + ltm->tm_mon;
    Now.tm_year = ltm->tm_year - 100;
    Now.tm_hour = ltm->tm_hour;
    Now.tm_min = ltm->tm_min;
    cout<<weekday(Now.tm_wday)<<", "<<Now.tm_mday<<" "<<month(Now.tm_mon)<<" "<<Now.tm_year<<"  "<<Now.tm_hour<<":"<<Now.tm_min<<"\n\n";
    return Now;
}

//Menampilkan deadline tugas
string displayDL(tm dl, tm Now){
    
    if(dl.tm_year==Now.tm_year){
        if((dl.tm_mon==Now.tm_mon)&&((dl.tm_mday-Now.tm_mday)<7)){
            int wday = (Now.tm_wday+dl.tm_mday-Now.tm_mday)%7;
             return weekday(wday) + " " + to_string(dl.tm_hour) + ":" + to_string(dl.tm_min);
        } else {
            return to_string(dl.tm_mday) + " " + month(dl.tm_mon) + " " + to_string(dl.tm_hour) + ":" + to_string(dl.tm_min);
        }       
    } else {
        return to_string(dl.tm_mday) + " " + month(dl.tm_mon) + " 20" + to_string(dl.tm_year);
    }
}

//Menampilkan seluruh tugas
void display(vector <newTugas> Tugas){
    tm Now;
    Now = getTimeNow();
    if (Tugas.size()==0){
        cout<<"belum ada tugas silahkan tambahkan tugas baru \n";
    }
    else { 
    cout<<"id\ttugas\t\tdeadline\tselesai\n";
        for(int i=0; i < Tugas.size(); i++){
            cout<<i+1<<"\t";
            cout<<Tugas[i].name<<"\t";
            cout<< displayDL(Tugas[i].dl,Now) <<"\t[";
            if(Tugas[i].selesai) cout<<"V";
            cout<<"]\n";
        }
    }
}
// Membandingkan waktu 
bool compare(tm a, tm b){
    if(a.tm_year > b.tm_year) return true;
    if(a.tm_year == b.tm_year && a.tm_mon > b.tm_mon) return true;
    if(a.tm_year == b.tm_year && a.tm_mon == b.tm_mon && a.tm_mday > b.tm_mday) return true;
    if(a.tm_year == b.tm_year && a.tm_mon == b.tm_mon && a.tm_mday == b.tm_mday && a.tm_hour > b.tm_hour) return true;
    if(a.tm_year == b.tm_year && a.tm_mon == b.tm_mon && a.tm_mday == b.tm_mday && a.tm_hour == b.tm_hour && a.tm_min > b.tm_min) return true;
    return false;
}
// Menukar data
void swap(struct newTugas &a, struct newTugas &b){
    struct newTugas temp = a;
    a = b;
    b = temp;
}
// Fungsi mengurutkan data berdasarkan waktu deadline
void shortbyDate(vector <newTugas> &T){
    for(int i = T.size()-1; i > 0; i--){
        for(int k = 0; k < i; k++){
            if(compare(T[k].dl,T[k+1].dl)) swap(T[k],T[k+1]);
        }
    }
}

// Fungsi Utama
int main(){
    vector <newTugas> Tugas; 
    int perintah;
    bool exit = false;
    
    while(exit==0){
        system("clear"); system("cls");     //clearscrean
        cout<<"\tAplikasi Manajemen Tugas\n\n"; 
        display(Tugas); //Tampilkan seluruh tugas
        cout<<"\npilih perintah :1. Tambah tugas\n\t\t2. edit tugas\n\t\t3. centang tugas\n\t\t4. hapus tugas\n\t\t5. Urutkan tugas berdasarkan deadline\n\t\t0. exit";
        cout<<"\npilih id perintah : ";
        cin >>perintah; 
        cin.ignore(1, '\n');
        struct newTugas input; 
        int id;
        switch (perintah)
        {
        case 1: //menambah tugas baru
            cout<<"tambah tugas baru \n";
            cout<<"input nama tugas : ";
            getline(cin, input.name);
            input.dl = inputDL();
            input.selesai=false;

            Tugas.push_back(input);
            break;
        case 2: //edit tugas
            cout<<"pilih id tugas yang akan diedit : ";
            cin >> id;
            cin.ignore(1, '\n');
            cout<< "edit nama tugas : ";
            getline(cin, input.name);
            input.dl = inputDL();

            Tugas[id-1]=input;
            break;
        case 3: //centang tugas
            cout<<"centang tugas yang sudah selesai (id) : ";
            cin >> id; 
            
            Tugas[id-1].selesai=true;
            break;
        case 4: //hapus tugas
            cout<<"pilih id tugas yang akan di hapus : ";
            cin >> id;

            Tugas.erase(Tugas.begin()+id-1);
            break;
        case 5: 
            shortbyDate(Tugas);
            break;
        case 0: //keluar 
            exit=true;
            break;
        default: 
            cout<<"invalid input";
        }
                
    }

    return 0;
}
