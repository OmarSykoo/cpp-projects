#include<iostream>
#include<algorithm>
using namespace std ;

const int max_books = 20 ;
const int max_users = 20 ;
const int max_borrow = 20 ;

struct book {
    string name ;
    int id ;
    int total_quantity ;
    int borrowed_books = 0 ;
    void enter_book_data (){
        cout << "Enter book name & ID & quantity : " << flush ;
        cin >> name >> id >> total_quantity;
    }
} ;

bool book_compare( book a , book b ){
    bool state = true ;
    if ( a.name != b.name || a.id != b.id ){
        state = false ;
    }
    return state ;
}

struct user {
    string name ;
    int id ;
    int borrowed_count = 0 ;
    book borrowed[max_borrow] ;
    void enter_user_date(){
        cout << "Enter username & ID : " << flush ;
        cin >> name >> id ;
    }
    void borrow_book( book &temp ){
        borrowed[borrowed_count++] = temp ;
        temp.borrowed_books++ ;
    } 
    void return_book( book &temp){
        for ( int i = 0 ; i < borrowed_count ; i++ ){
            if ( book_compare( borrowed[i] , temp ) ){
                borrowed[i] = borrowed[borrowed_count - 1 ] ;
                temp.borrowed_books-- ;
                borrowed_count-- ;
                break ;
            }
        }
    }
    void list_user_data(){
        cout << "user " << name << flush ;
        cout << " id " << id << flush ;
        cout << " borrowed book ids : " << flush ;
        for ( int i = 0 ; i < borrowed_count ; i++ ){
            cout << borrowed[i].id << " " << flush ;
        } 
        cout << endl ;
    }
} ;

int book_counter = 0 ;
int user_counter = 0 ;
book arr_books[max_books] ;
user arr_users[max_users] ;

bool compar_by_name( book a , book b ){
    if ( a.name > b.name ){
        return false ;
    }
    return true ;
}

bool compar_by_id( book a , book b  ){
    if ( a.id > b.id ){
        return false ;
    } else if ( a.id == b.id ) {
        return compar_by_name( a , b ) ;
    }
    return true ;
}

bool is_prefix ( string check , string search ){
    if ( search.length() > check.length() ){
        return false ;
    } else {
        bool state = true ;
        for ( int i = 0 ; i < search.length() ; i++ ){
            if ( check[i] != search[i] ){
                state = false ;
                break ;
            }
        }
        return state ;
    }
}

void add_book(){
    if ( book_counter < max_books) {
        book temp ; 
        temp.enter_book_data();
        arr_books[book_counter++] = temp ;
    } else {
        cout << "cant take in anymore books the library is full !" << endl ;
    }
}

void search_book_byname(){
    bool state = false ;
    string search ;
    cout << "Enter book name : " << flush ;
    cin >> search ;
    for ( int i = 0 ; i < book_counter ; i++ ){
        if ( is_prefix( arr_books[i].name , search ) ){ 
            state = true ;
            cout << arr_books[i].name << endl ;
        }
    }
    if ( !state ){
        cout << "invalid book name " << endl ;
    }
}

void add_user(){
    if ( user_counter < max_users ){
        user temp ;
        temp.enter_user_date() ;
        arr_users[user_counter++] = temp ;
    } else {
        cout << "cant take in any more users " << endl ;
    }
}

void print_library_by_id ( ){
    sort ( arr_books , arr_books + book_counter , compar_by_id ) ;
    for ( int i = 0 ; i < book_counter ; i++ ){
        cout << "name : " << arr_books[i].name << flush ;
        cout << " id : " << arr_books[i].id  << flush ;
        cout << " total quantity : " << arr_books[i].total_quantity << flush ;
        cout << " borrowed : " << arr_books[i].borrowed_books << endl ;
    }
}

void print_library_by_name ( ){
    sort ( arr_books , arr_books + book_counter , compar_by_name ) ;
    for ( int i = 0 ; i < book_counter ; i++ ){
        cout << "name : " << arr_books[i].name << flush ;
        cout << " id : " << arr_books[i].id  << flush ;
        cout << " total quantity : " << arr_books[i].total_quantity << flush ;
        cout << " borrowed : " << arr_books[i].borrowed_books << endl ;
    }
}

void user_borrow(){
    string user_name ;
    string book_name ;
    int a , b ;
    cout << "Enter user name and book name : " << flush ;
    cin >> user_name >> book_name ;
    for ( int i = 0 ; i < user_counter ; i++ ) {
        if ( arr_users[i].name == user_name ){
            a = i ;
            break ; 
        }
    }
    user &student = arr_users[a] ;
    for ( int i = 0 ; i < book_counter ; i++ ){
        if ( arr_books[i].name == book_name ){
            b = i ;
            break ;
        }
    }
    book &booky = arr_books[b] ;
    student.borrow_book(booky) ;
}

void user_return(){
    string user_name ;
    string book_name ;
    int a , b ;
    cout << "enter user_name and book name " << flush ;
    cin >> user_name >> book_name ;
    for ( int i = 0 ; i < user_counter ; i++ ) {
        if ( arr_users[i].name == user_name ){
            a = i ;
            break ; 
        }
    }
    user &student = arr_users[a] ;
    for ( int i = 0 ; i < book_counter ; i++ ){
        if ( arr_books[i].name == book_name ){
            b = i ;
            break ;
        }
    }
    book &booky = arr_books[b] ;
    student.return_book(booky) ;    
}

void print_users(){
    for ( int i = 0 ; i < user_counter ; i++ ){
        arr_users[i].list_user_data() ;
    }
}

void who_borrowed(){
    bool state = false ;
    string temp ;
    book loc ;
    cout << "Enter book name : " << flush ;
    cin >> temp ;
    for ( int i = 0 ; i < book_counter ; i++ ){
        if ( temp == arr_books[i].name ) {
            state = true ;
            loc = arr_books[i] ;
        }
    }
    if ( !state ){
        cout << "invalid book " << endl ;
        return ;
    }
    for ( int i = 0 ; i < user_counter ; i++ ){
        if ( arr_users[i].borrowed_count > 0 ){
            for ( int j = 0 ; j < arr_users[i].borrowed_count ; j++ ){
                if ( book_compare( loc , arr_users[i].borrowed[j] )) {
                    cout << arr_users[i].name << endl ;
                    break ;
                }
            }
        }
    }
}

int menu(){
    int choice ;
    cout << "1) add book " << endl ;
    cout << "2) search book by prefix " << endl ;
    cout << "3) add user" << endl ;
    cout << "4) print_library_by_id " << endl ;
    cout << "5) print_library_by_name " << endl ;
    cout << "6) user borrow book " << endl ;
    cout << "7) user return book " << endl ;
    cout << "8) list user data " << endl ;
    cout << "9) who borrowed " << endl ;
    cout << "10) Exit " << endl ;
    cout << "enter choice : " << flush;
    cin >> choice ; 
    return choice ;
}

void library_system(){
    while ( true ){
        int choice = menu() ;
        if ( choice == 1 ){
            add_book() ;
        } else if ( choice == 2 ) {
            search_book_byname() ;
        } else if ( choice == 3 ) {
            add_user() ;
        } else if ( choice == 4 ) {
            print_library_by_id() ;
        } else if ( choice == 5 ) {
            print_library_by_name() ;
        } else if ( choice == 6 ) {
            user_borrow() ;
        } else if ( choice == 7 ) {
            user_return() ;
        } else if ( choice == 8 ) {
            print_users() ;
        } else if ( choice == 9 ) {
            who_borrowed() ;
        } else if ( choice == 10 ) {
            break ;
        }
    }
}

int main(){
    library_system() ;
    return 0 ;
}
