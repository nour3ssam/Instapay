#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cmath>
#include<string>
#include<map>
#include <set>
#include <deque>
#include <stack>
#include <queue>
#include <fstream>
#define ceil(x,y) (x+y-1)/y
#define endl "\n"
#define IOS ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL)
using namespace std;
class Icard;
class User;
vector<User> Userslist;
vector<Icard*>card;
class User {
public:
    string Username;
    string Password;
    string Address;
    string Phone;
public:
    friend class System;
    User() {}
    User(string Username, string Password, string Address, string Phone) {
        this->Username = Username;
        this->Password = Password;
        this->Address = Address;
        this->Phone = Phone;
    }
    void setname(string name) {
        Username = name;
    }
    string getname() {
        return Username;
    }
    void setpass(string pass) {
        Password = pass;
    }
    string getpass() {
        return Password;
    }
    void setadd(string add) {
        Address = add;
    }
    string getadd() {
        return Address;
    }
    void setphone(string phone) {
        Phone = phone;
    }
    string getphone() {
        return Phone;
    }
};
class Icard {
public:
    string username;
    string password;
    string numberphone;
    int amount;
    int type;
    virtual void sendmoney(int money, string username) = 0;
    virtual void sendmoney(string phone, int money) = 0;
    virtual void addmoney() = 0;
};
class mastercard :public Icard {
    void sendmoney( string username,int money) {
        bool flag = 0;
        if (amount < money) {
            cout << "not have this money " << endl;
        }
        else {
            for (int i = 0; i < Userslist.size(); i++) {
                if (username == Userslist[i].Username) {
                    flag = 1; break;
                }
            }
            if (flag) {
                amount -= money;
                for (int i = 0; i < card.size(); i++) {
                    if (card[i]->username == username) {
                        card[i]->amount += money; break;
                    }
                }
                cout << "Successful operation " << endl;
            }
            else {
                cout << "not found the user " << endl;
            }
        }
    }
    void sendmoney(int money,string phone) {
        bool flag = 0;
        if (amount < money) {
            cout << "not have this money ";
        }
        else {
            for (int i = 0; i < Userslist.size(); i++) {
                if (Userslist[i].Phone == phone) {
                    flag = 1; break;
                }
            }
            if (flag) {
                amount -= money;
                for (int i = 0; i < card.size(); i++) {
                    if (card[i]->numberphone == phone) {
                        card[i]->amount += money; break;
                    }
                }
                cout << "Successful operation " << endl;
            }
            else {
                cout << "not found the user " << endl;
            }
        }
    }
    void addmoney() {
        cout << "Enter the money nour  :";
        int mn; cin >> mn;
        if (mn > 10000) {
            cout << "Exceeded the maximum" << endl;
            addmoney();
        }
        amount += mn;
    }
};
class vesacard :public Icard {
    void sendmoney(string username, int money) {
        bool flag = 0;
        if (amount < money) {
            cout << "not have this money " << endl;
        }
        else {
            for (int i = 0; i < Userslist.size(); i++) {
                if (username == Userslist[i].Username) {
                    flag = 1; break;
                }
            }
            if (flag) {
                amount -= money;
                for (int i = 0; i < card.size(); i++) {
                    if (card[i]->username == username) {
                        card[i]->amount += money; break;
                    }
                }
                cout << "Successful operation " << endl;
            }
            else {
                cout << "not found the user " << endl;
            }
        }
    }
    void sendmoney(int money, string phone) {
        bool flag = 0;
        if (amount < money) {
            cout << "not have this money ";
        }
        else {
            for (int i = 0; i < Userslist.size(); i++) {
                if (Userslist[i].Phone == phone) {
                    flag = 1; break;
                }
            }
            if (flag) {
                amount -= money;
                for (int i = 0; i < card.size(); i++) {
                    if (card[i]->numberphone == phone) {
                        card[i]->amount += money; break;
                    }
                }
                cout << "Successful operation " << endl;
            }
            else {
                cout << "not found the user " << endl;
            }
        }
    }
    void addmoney() {
        cout << "Enter the money " << endl;
        int mn; cin >> mn;
        if (mn > 10000) {
            cout << "Exceed limit " << endl;
            addmoney();
        }
        amount += mn;
    }
};
class System {
public:
    System() {
        Userslist.clear();
        ifstream User_file("users.txt", ios::in);
        if (User_file.is_open()) {
            User fuser;
            while (User_file >> fuser.Username >> fuser.Password >> fuser.Phone >> fuser.Address) {
                Userslist.push_back(fuser);
            }
            User_file.close();
        }
        card.clear();
        ifstream card_file("cards.txt", ios::in);
        if (card_file.is_open()) {
            Icard* fcard=new mastercard;
            while (card_file >> fcard->username >> fcard->password >> fcard->amount >> fcard->type) {
                card.push_back(fcard);
            }
            card_file.close();
        } 
    }
    User login() {
        bool ck = 0;
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        for (int i = 0; i < Userslist.size(); i++) {
            if (Userslist[i].Username == username and Userslist[i].Password == password) {
                ck = 1;
                cout << "Your login is successfull. Thanks for logging in! " << endl;
                return Userslist[i];
            }
        }
        if (!ck) {
            cout << "Wrong password or no user as name : try again " << endl;
            return login();
        }
    }
    User sign_up() {
        bool ch = 0;
        string ruser, rpassword, ph;
        cout << "Enter the username : ";
        cin >> ruser;
        cout << "Enter the password : ";
        cin >> rpassword;
        cout << "Enter the phone : ";
        cin >> ph;
        for (int i = 0; i < Userslist.size(); i++) {
            if (Userslist[i].Username == ruser) {
                ch = 1; break;
            }
        }
        if (ch) {
            cout << "Username already taken. Try another." << endl;
            return sign_up();
        }
        string add = ruser + "insta.com";
        User New_User(ruser, rpassword, ph, add);
        Userslist.push_back(New_User);
        Add_User_To_System(New_User);
        cout << "your address " << add << endl;
        return New_User;
    }
    void Add_User_To_System(User New_User) {
        ofstream Ufile("users.txt", ios::out | ios::app);
        Ufile << New_User.Username << " " << New_User.Password << " " << New_User.Phone << " " << New_User.Address << endl;
        cout << "Registration is successfully! " << endl;
        Ufile.close();
    }
    void add_visa_to_system(Icard* ptr) {
        ofstream ccard("cards.txt", ios::out | ios::app);
        ccard << ptr->username << " " << ptr->password << " " << ptr->amount << " " << ptr->type << endl;
        cout << "Added visa is successfully! " << endl;
        ccard.close();
    }
    void add_visa(User nour) {
        cout << "1- visacard " << endl;
        cout << "2- mastarcard " << endl;
        int num; cin >> num;
        if (num != 1 and num != 2) {
            cout << "Invalid selection" << endl;
            return;
        }
        if (num == 1) {
            bool flag = 0;
            for (const auto& c : card) {
                if (nour.getname() == c->username and c->type == 1) {
                    cout << "you have already this visa  " << endl;
                    flag = 1;
                }
            }
            if (!flag) {
                Icard* ptr = new vesacard;
                ptr->amount = 0;
                ptr->username = nour.getname();
                ptr->password = nour.getpass();
                ptr->numberphone = nour.getphone();
                ptr->type = 1;
                card.push_back(ptr);
                add_visa_to_system(ptr);
            }
        }
        else {
            bool flag = 0;
            for (const auto& c : card) {
                if (nour.getname() == c->username and c->type == 2) {
                    cout << "you have already this visa " << endl;
                    flag = 1;
                }
            }
            if (!flag) {
                Icard* ptr = new mastercard;
                ptr->amount = 0;
                ptr->username = nour.getname();
                ptr->password = nour.getpass();
                ptr->numberphone = nour.getphone();
                ptr->type = 2;
                card.push_back(ptr);
                 add_visa_to_system(ptr);
            }
        }
    }

    int menu1() {
        cout << " menu " << endl;
        cout << "1 : login " << endl;
        cout << "2 : sign up  " << endl;
        cout << "3 :  Exit " << endl;
        cout << "Enter number in range 1 - 3 " << endl;
        int op; cin >> op;
        if (op < 1 or op > 3) {
            cout << "invalid number try again " << endl;
            return menu1();
        }
        return op;
    }



    int menu2() {
        cout << " menu : " << endl;
        cout << "1 : Send money " << endl;
        cout << "2 : Show money  " << endl;
        cout << "3 : Add visa " << endl;
        cout << "4 : Add money  " << endl;
        cout << "5 : main " << endl;
        cout << "6 : Exit " << endl;
        cout << "Enter number in range 1 - 6 " << endl;
        int op; cin >> op;
        if (op < 1 or op > 6) {
            cout << "invalid number ";
            return menu2();
        }
        return op;
    }
};


int main() {
    System s;
    for (const auto& c : card) {
        cout << c->username << " " << c->password << " " << c->amount << " " << c->type << endl;
    }
    User user;
    int op;
start:
    op = s.menu1();
    if (op == 1) {
        user = s.login();
    }
    if (op == 2) {
        user = s.sign_up();
    }
    if (op == 3) {
        return 0;
    }
    cout << "Hello " << user.getname() << endl;
second:
    op = s.menu2();

    if (op == 1) {
        string name, phone_num;
        cout << "1: send by username " << endl;
        cout << "2: send by phone number " << endl;
        cin >> op;
        if (op == 1) {
            cout << "Enter username " << endl;
            cin >> name;
        }
        else if (op == 2) {
            cout << "Enter Phone number " << endl;
            cin >> phone_num;

        }
        else {
            cout << "invalid number : try again " << endl;
            goto second;
        }
        cout << "Enter the value " << endl;
        int val; cin >> val;

        int count = 0;
        for (int i = 0; i < card.size(); i++) {
            if (user.getname() == card[i]->username) {
                count++;
            }
        }
        if (count == 0) {
            cout << "you not have any visa yet" << endl;
            goto second;
        }
        else if (count == 1) {
            for (int i = 0; i < card.size(); i++) {
                if (card[i]->username == user.getname() and op == 1) {
                    card[i]->sendmoney(name, val);
                }
                else if (card[i]->numberphone == user.getphone() and op == 2) {
                    card[i]->sendmoney(val, phone_num);
                }
            }
        }
        else if (count == 2) {
            cout << "please choise to send money by " << endl;
            cout << "1 visacard " << endl;
            cout << "2 mastarcard " << endl;
            int num; cin >> num;
            if (num == 1) {
                for (int i = 0; i < card.size(); i++) {
                    if (user.getname() == card[i]->username and card[i]->type == 1 and op == 1) {
                        card[i]->sendmoney(name, val);
                    }
                }
                for (int i = 0; i < card.size(); i++) {
                    if (user.getphone() == card[i]->numberphone and card[i]->type == 1 and op == 2) {
                        card[i]->sendmoney(val, phone_num);
                    }
                }
            }
            else if (num == 2) {
                for (int i = 0; i < card.size(); i++) {
                    if (user.getname() == card[i]->username and card[i]->type == 2 and op == 1) {
                        card[i]->sendmoney(name, val);
                    }
                }
                for (int i = 0; i < card.size(); i++) {
                    if (user.getphone() == card[i]->numberphone and card[i]->type == 2 and op == 2) {
                        card[i]->sendmoney(val, phone_num);
                    }
                }
            }
        }
        else if (count == 3) {
            cout << "Project is Expired" << endl;
            cout << "please call me 01015111214 " << endl;
        }
        goto second;
    }
    else if (op == 2) {
        int count = 0;
        for (int i = 0; i < card.size(); i++) {
            if (user.getname() == card[i]->username) {
                count++;
            }
        }
        if (count == 0) {
            cout << "you not have visa yet " << endl;
            goto second;
        }
        if (count == 1) {
            for (int i = 0; i < card.size(); i++) {
                if (user.getname() == card[i]->username) {
                    cout << "your balance is " << card[i]->amount << endl;
                }
            }
        }
        else if (count == 2) {
            cout << "1- visacart " << endl;
            cout << "2- mastercart" << endl;
            int num; cin >> num;
            if (num == 1) {
                for (int i = 0; i < card.size(); i++) {
                    if (user.getname() == card[i]->username and card[i]->type == 1) {
                        cout << "your money is " << card[i]->amount << endl;
                    }
                }
            }
            if (num == 2) {
                for (int i = 0; i < card.size(); i++) {
                    if (user.getname() == card[i]->username and card[i]->type == 2) {
                        cout << "your money is " << card[i]->amount;
                    }
                }
            }
        }
        else if (count == 3) {
            cout << "Project is Expired" << endl;
            cout << "please call me 01015111214 " << endl;
        }
        goto second;
    }
    else if (op == 3) {
        s.add_visa(user);
        goto second;
    }
    else if (op == 4) {
        int count = 0;
        for (int i = 0; i < card.size(); i++) {
            if (user.getname() == card[i]->username) {
                count++;
            }
        }
        if (count == 0) {
            cout << "you not have visa yet " << endl;
            goto second;
        }
       else if (count == 1) {
            for (int i = 0; i < card.size(); i++) {
                if (user.getname() == card[i]->username) {
                    card[i]->addmoney();
                }
            }
        }
        else if (count==2) {
            cout << "1- visacart" << endl;  
            cout << "2- mastercart" <<endl;
            int num; cin >> num;
            if (num == 1) {
                for (int i = 0; i < card.size(); i++) {
                    if (user.getname() == card[i]->username and card[i]->type == 1) {
                        card[i]->addmoney(); 
                    }
                }
            }
            else {
                for (int i = 0; i < card.size(); i++) {
                    if (user.getname() == card[i]->username  and  card[i]->type == 2) {
                        card[i]->addmoney();
                    }
                }
            }
        }
        else if (count == 3) {
            cout << "Project is Expired" << endl;
            cout << "please call me 01015111214 " << endl;
        }
        goto second;
    }
    else if (op == 5) {
        goto start;
    }
    else {
        return 0;
    }
}