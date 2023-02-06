#include<iostream>
#include<algorithm>
using namespace std;

const int maxx = 200 ;
const int maxx_users = 200 ;
int added = 0 ;
int added_users = 0 ;

struct book {
    int id ;
    int quantity ; 
    int total_borrowed = 0 ;
    string name ;
    void set_book_data(){
        cout << "Enter book info id & name & total quantity : " << flush ;
        cin >> id >> name >> quantity ;
    }
} ;

struct user {
    string name ;
    int id ;
    int count = 0 ;
    int arre[200] ;
    void ser_user_data(){
        cout << "Enter user name & nathional ID : " << flush ;
        cin >> name >> id ;
    }
    void user_borrow(int a){
        arre[count++] = a ;
    }
    void user_return(int a){
        for ( int i = 0 ; i < count ; i++ ){
            if ( arre[i] == a ){
                arre[i] = arre[--count] ;
                break ;
            }
        }
    }
} ;

book arr[maxx] ;
user users[maxx_users] ;

void menu(){
    cout << "1) add_book " << endl ;
    cout << "2) search books by prefix " << endl ;
    cout << "3) print who borrowed books " << endl ;
    cout << "4) print library by id " << endl ;
    cout << "5) print library by name " << endl ;
    cout << "6) add user " << endl ;
    cout << "7) user_borrow book " << endl ;
    cout << "8) user_return book " << endl ;
    cout << "9) print users " << endl ;
    cout << "10) Exit " << endl ;
}

bool name_compare( book a , book b ){
    if ( a.name > b.name ){
        return false ;
    }
    return true ;
}

bool id_compare( book a , book b ){
    if ( a.id > b.id ){
        return false ;
    } else if ( a.id == b.id ){
        name_compare( a , b ) ;
    }
    return true ;
}

bool is_prefix( string items , string search ){
    if ( items.length() >= search.length() ){
        bool state = true ;
        for ( int j = 0 ; j < search.length() ; j++ ){
            if ( items[j] != search[j] ){
                state = false ;
                break ;
            }
        }
        return state ;
    } else {
        return false ;
    }
}

void add_book(){
    arr[added++].set_book_data() ;
}

void add_user(){
    users[added_users++].ser_user_data() ;
}

void search_book(){
    cout << "Enter book name prefix : " << flush ;
    string search ;
    cin >> search ;
    bool check = true ;
    for ( int i = 0 ; i < added ; i++ ){
        if ( is_prefix(arr[i].name , search )){
            cout << arr[i].name << endl ;
            check = false ;
        }
    }
    if ( check ){
        cout << "invalid book name" << endl ;
    }
}

void print_who_borrowed(){
    string _name_ ;
    int temp_id ;
    cin >> _name_ ;
    for ( int i = 0 ; i < added ; i++ ){
        if ( _name_ == arr[i].name ){
            temp_id = arr[i].id ;
            break ;
        }
    }
    for ( int i = 0 ; i < added_users ; i++ ){
        for ( int j = 0 ; j < users[i].count ; j++ ){
            if ( users[i].arre[j] == temp_id ){
                cout << users[i].name << endl ;
                break ;
            }
        }
    }
}

void print_library_byname(){
    sort(arr , arr + added , name_compare ) ;
    for ( int i = 0 ; i < added ; i++ ){
        cout << "ID : " << arr[i].id << " name : " << arr[i].name << "total quantity : " << arr[i].quantity << " total quantity borrowed : " << arr[i].total_borrowed << endl ;
    }
}

void print_library_byid(){
    sort(arr , arr + added , id_compare ) ;
    for ( int i = 0 ; i < added ; i++ ){
        cout << "ID : " << arr[i].id << " name : " << arr[i].name << "total quantity : " << arr[i].quantity << " total quantity borrowed : " << arr[i].total_borrowed << endl ;
    }
}

void print_users() {
    for ( int i = 0 ; i < added_users ; i++ ){
        cout << "user : " << users[i].name << " ID : " << users[i].id << "borowed books ids : " << flush ;
        for ( int j = 0 ; j < users[i].count ; i++) {
            cout << users[i].arre[j] << " " << flush ;
        }
        cout << endl ;
    }
}

void user_borrow(){
    string _name_ , _book_ ;
    int temp_id ;
    cout << "Enter user name and book name : " << flush ;
    cin >> _name_ >> _book_ ;
    for ( int i = 0 ; i < added ; i++ ){
        if ( _book_ == arr[i].name ){
            temp_id = arr[i].id ;
            arr[i].total_borrowed++ ;
            break ;
        }
    }
    for ( int i = 0 ; i < added_users ; i++ ){
        if ( _name_ == users[i].name ){
            users[i].user_borrow(temp_id) ;
            break ;
        }
    }
}

void user_return(){
    string _name_ , _book_ ;
    int temp_id ;
    cout << "Enter user name and book name : " << flush ;
    cin >> _name_ >> _book_ ;
    for ( int i = 0 ; i < added ; i++ ){
        if ( _book_ == arr[i].name ){
            temp_id = arr[i].id ;
            arr[i].total_borrowed-- ;
            break ;
        }
    }
    for ( int i = 0 ; i < added_users ; i++ ){
        if ( _name_ == users[i].name ){
            users[i].user_return(temp_id) ;
            break ;
        }
    }
}

void library_system(){
    menu();
    int choice ;
    while ( true ){
        cout << "Enter your menu choice [ 1 - 10 ] : " << flush ;
        cin >> choice ;
        if ( choice == 1 ){
            add_book();
        } else if ( choice == 2 ){
            search_book();
        } else if ( choice == 3 ){
            print_who_borrowed() ;
        } else if ( choice == 4 ){
            print_library_byid() ;
        } else if ( choice == 5 ){
            print_library_byname() ;
        } else if ( choice == 6 ){
            add_user() ;
        } else if ( choice == 7 ){
            user_borrow() ;
        } else if ( choice == 8 ){
            user_return() ;
        } else if ( choice == 9 ){
            print_users() ;
        } else if ( choice == 10 ){
            cout << "Exit System..." << endl ;
            break ;
        } else {
            cout << "invalid input !" << endl ;
        }
    }
}
int main(){
    library_system() ;
    return 0 ;
}