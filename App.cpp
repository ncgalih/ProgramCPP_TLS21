#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct waktu {
    int day;
    int month;
    int year;
    int hh;
    int mm;
};


struct newTugas {
    string name;
    struct waktu dl;
    bool selesai;
};

waktu inputDL(){
    string dl;
    struct waktu DL;
    cout<< "tambahkan deadline (dd/mm/yy hh:mm): ";
    getline(cin, dl);
    DL.day   = stoi(dl.substr(0,2));
    DL.month = stoi(dl.substr(3,2));
    DL.year  = stoi(dl.substr(6,2));
    DL.hh    = stoi(dl.substr(9,2));
    DL.dmm   = stoi(dl.substr(12,2));
    
    return DL;
}



void display(vector <newTugas> Tugas){
    
    if (Tugas.size()==0){
        cout<<"belum ada tugas silahkan tambahkan tugas baru \n";
    }
    else { 
    cout<<"id\ttugas\t\tdeadline\tselesai\n";
        for(int i=0; i < Tugas.size(); i++){
            cout<<i+1<<"\t";
            cout<<Tugas[i].name<<"\t\t";
            cout<<Tugas[i].dl.day<<"\t\t[";
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
