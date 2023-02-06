#include<iostream>
#include<string>
using namespace std;

const int specializations_max = 20 ;
const int queue_max = 5 ;
string name_list[specializations_max][queue_max] ;
int specialize[specializations_max] = {0} ;
int urgent_count[specializations_max] = {0} ; 

int menu(){
    cout << "1) add a patient " << endl ;
    cout << "2) print all patients " << endl ;
    cout << "3) get next patient " << endl ;
    cout << "4) Exit " << endl ;
    int choice ;
    cin >> choice ; 
    return choice ;
}
void add_patient(){
    int specialization ;
    string name ;
    char state ;
    cout << "Enter specialization , name , state : " << flush ;
    cin >> specialization >> name >> state ;
    specialization-- ;
    int &temp = specialize[specialization ] ;
    if ( specialize[specialization] < queue_max ){
        if ( state == '0'){
            name_list[specialization ][temp] = name ;
            temp++ ;
        } else if ( state == '1'){
            for ( int i = temp  ; i > 0 ; i-- ){
                name_list[specialization][i] = name_list[specialization][i - 1] ;
            }
            name_list[specialization][0] = name ;
            urgent_count[specialization]++ ;
            temp++ ;
        }
    } else {
        cout << "Sorry we cant accept any more patients in this specialization " << endl ;
    }
}

void list_patients(){
    for ( int i = 0 ; i < specializations_max ; i++ ){
        if (specialize[i] != 0 ){
            cout << "-----------------------" << endl ;
            cout << "there are " << specialize[i] << " patients in " << i + 1 << endl ;
            int &temp = specialize[i];
            for ( int j = 0 ; j < temp ; j++ ){
                cout << name_list[i][j] << " " << flush ;
                if ( urgent_count[i] > j ){
                    cout << "urgent" << endl ;
                } else {
                    cout << "regular" << endl ;
                }
            }
        }
    }
}

void Next_patient(){
    int specialization ;
    cout << "Enter specialization : " << flush ;
    cin >> specialization ;
    specialization-- ;
    if ( specialize[specialization] == 0 ){
        cout << "there are no patients you can rest doctor " << endl ;
    } else {
        cout << name_list[specialization][0] << ", you can see the doctor now" << endl ;
        for ( int i = 0 ; i < specialize[specialization] ; i++ ){
            name_list[specialization][i] = name_list[specialization][i+1] ;
        }
        specialize[specialization]-- ;
        if ( urgent_count[specialization] > 0 ){
            urgent_count[specialization]-- ;
        }
    }
}

void temp_listing (){
    for ( int i = 0 ; i < specializations_max ; i++ ){
        for ( int j = 0 ; j < specialize[i] ; j++ ){
            cout << name_list[i][j] << " " << flush ;
        }
        cout << endl ;
    }
}

void hospital_System(){
    while(true){
        int choice = menu() ;
        if ( choice == 1){
            add_patient();
        } else if ( choice == 2 ){
            list_patients();
        } else if ( choice == 3 ){
            Next_patient();
        } else {
            break ;
        }
    }
}

int main(){ 
    hospital_System();
    return 0 ;
}
