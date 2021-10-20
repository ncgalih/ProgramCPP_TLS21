#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct waktu {
    int day;
    int month;
    int year;
    int hh;
    int mm;
    int wday;
};

struct newTugas {
    string name;
    struct waktu dl;
    bool selesai;
};

string weekday(int d){
    switch (d){
    case 1: return "Senin"; case 2: return "Selasa"; case 3: return "Rabu" ;
    case 4: return "Kamis"; case 5: return "Jumat" ; case 6: return "Sabtu";
    case 7: return "Minggu";
    }
}

string month(int m){
    switch (m){
    case 1: return "Jan"; case 2: return "Feb"; case 3: return "Mar" ; case 4: return "April"; 
    case 5: return "Mei" ; case 6: return "Jun"; case 7: return "Jul"; case 8: return "Ags";
    case 9: return "Sep" ; case 10: return "Okt"; case 11: return "Nov"; case 12: return "Des";
    }
}

waktu inputDL(){
    string dl;
    struct waktu DL;
    cout<< "tambahkan deadline (dd/mm/yy hh:mm): ";
    getline(cin, dl);
    DL.day   = stoi(dl.substr(0,2));
    DL.month = stoi(dl.substr(3,2));
    DL.year  = stoi(dl.substr(6,2));
    DL.hh    = stoi(dl.substr(9,2));
    DL.mm   = stoi(dl.substr(12,2));
    
    return DL;
}

waktu getTimeNow(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    struct waktu Now;
    Now.day = ltm->tm_mday;
    Now.wday = ltm->tm_wday;
    Now.month = 1 + ltm->tm_mon;
    Now.year = ltm->tm_year - 100;
    Now.hh = ltm->tm_hour;
    Now.mm = ltm->tm_min;
    cout<<weekday(Now.wday)<<", "<<Now.day<<" "<<month(Now.month)<<" "<<Now.year<<"  "<<Now.hh<<":"<<Now.mm<<"\n\n";
    return Now;
}

string displayDL(struct waktu dl, struct waktu Now){
    struct waktu dl, Now;
    
    if(dl.year==Now.year){
        if((dl.month==Now.month)&&((dl.day-Now.day)<7)){
            int wday = Now.wday+dl.day-Now.day;
             return weekday(wday) + " " + to_string(dl.hh) + ":" + to_string(dl.mm);
        } else {
            return to_string(dl.day) + " " + month(dl.month) + " " + to_string(dl.hh) + ":" + to_string(dl.mm);
        }       
    } else {
        return to_string(dl.day) + " " + month(dl.month) + " 20" + to_string(dl.year);
    }
}

void display(vector <newTugas> Tugas){
    struct waktu Now;
    Now = getTimeNow();
    if (Tugas.size()==0){
        cout<<"belum ada tugas silahkan tambahkan tugas baru \n";
    }
    else { 
    cout<<"id\ttugas\t\tdeadline\tselesai\n";
        for(int i=0; i < Tugas.size(); i++){
            cout<<i+1<<"\t";
            cout<<Tugas[i].name<<"\t\t";
            cout<< displayDL(Tugas[i].dl,Now) <<"\t\t[";
            if(Tugas[i].selesai) cout<<"V";
            cout<<"]\n";
        }
    }
}

int main(){
    vector <newTugas> Tugas;
    int perintah;
    bool exit = false;
    
    while(exit==0){
        cout<<"\tAplikasi Manajemen Tugas\n\n";
        display(Tugas);
        cout<<"\npilih perintah :1. Tambah tugas\n\t\t2. edit tugas\n\t\t3. centang tugas\n\t\t4. hapus tugas";
        cout<<"\npilih id perintah : ";
        cin >>perintah;
        cin.ignore(1, '\n');
        struct newTugas input;
        int id;
        switch (perintah)
        {
        case 1:
            cout<<"tambah tugas baru \n";
            cout<<"input nama tugas : ";
            getline(cin, input.name);
            input.dl = inputDL();
            input.selesai=false;

            Tugas.push_back(input);
            break;
        case 2:
            cout<<"pilih id tugas yang akan diedit : ";
            cin >> id;
            cin.ignore(1, '\n');
            cout<< "edit nama tugas : ";
            getline(cin, input.name);
            input.dl = inputDL();

            Tugas[id-1]=input;
            break;
        case 3:
            cout<<"centang tugas yang sudah selesai (id) : ";
            cin >> id; 
            
            Tugas[id-1].selesai=true;
            break;
        case 4:
            cout<<"pilih id tugas yang akan di hapus : ";
            cin >> id;

            Tugas.erase(Tugas.begin()+id-1);
        }
        system("clear"); system("cls");
        
    }

    return 0;
}
