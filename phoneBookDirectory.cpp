#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <chrono>
#define ll long long
#define vec vector<ll>
#define pb push_back
#define mk make_pair
using namespace std;

template <class T>
T max(T a, T b, T c)
{
    return max(a, max(b, c));
}
ll fact(ll n)
{
    if (n == 0 || n == 1)
        return 1;
    else
        return n * fact(n - 1);
}
// comb = fact(n) / (fact(r) * fact(n-r));
// per = fact(n) / fact(n-r);

class Dnode
{ // doubly linked list class for creating node
private:
    Dnode *prev;
    Dnode *next;
    string name;
    string number;
    string gmail;

public:
    Dnode(string name, string number, string gmail);
    friend class PhoneBook;
};
Dnode::Dnode(string name, string number, string gmail)
{
    this->name = name;
    this->number = number;
    this->gmail = gmail;
    prev = NULL;
    next = NULL;
}
class PhoneBook
{ // ADT class which uses doubly linked list
private:
    Dnode *head;
    Dnode *temp;
    Dnode *last;
    Dnode *ptr;

public:
    PhoneBook();
    void insert();                // inserting in list
    void display();               // displaying list
    void deleteContact(string n); // deleting contact
    // void sort_phonebook(); //bubble sort algo
    void merge_sort(); // merge sort algo time complexity O(nlogn)
    void searchby_name(string n);
    void searchby_phone(string num);
    void searchby_email(string mail);
    void update(string n);

    // Split a doubly linked list (DLL) into 2 DLLs of
    // half size
    Dnode *split(Dnode *head)
    {
        Dnode *fast = head;
        Dnode *slow = head;
        while (fast->next != NULL && fast->next->next != NULL)
        { // tortise and hare method
            fast = fast->next->next;
            slow = slow->next;
        }
        Dnode *tem = slow->next;
        slow->next = NULL;
        return tem;
    }
    Dnode *merge(Dnode *first, Dnode *second)
    { // merging two splitted linked lists
        if (!first)
            return second;
        if (!second)
            return first;

        if (first->name.compare(second->name) < 0)
        {
            first->next = merge(first->next, second);
            first->next->prev = first;
            first->prev = NULL;
            return first;
        }
        else
        {
            second->next = merge(first, second->next);
            second->next->prev = second;
            second->prev = NULL;
            return second;
        }
    }
    Dnode *mergeSort(Dnode *head)
    {
        if (!head || !head->next)
            return head;
        Dnode *second = split(head);
        // Recur for left and right halves
        head = mergeSort(head);
        second = mergeSort(second);
        // Merge the two sorted halves
        return merge(head, second);
    }
};
PhoneBook::PhoneBook()
{
    head = NULL;
    temp = NULL;
    last = NULL;
    ptr = NULL;
}
void PhoneBook::insert()
{
    char c;
    string name;
    string number;
    string gmail;
    do
    {
        cout << "Enter name : ";
        cin >> name;

        cout << "Enter phone number : ";
        cin >> number;
        while (number.length() != 10)
        {
            cout << "Enter valid phone number : ";
            cin >> number;
        }
        cout << "Enter gmail address (only gmail.com is accepted) : ";
        cin >> gmail;
        string s;
        s = gmail;
        int pos = gmail.find('@');
        while (gmail.substr(pos + 1, gmail.length()) != "gmail.com")
        {
            cout << "Enter valid gmail : ";
            cin >> gmail;
            int pos = gmail.find('@');
        }
        temp = new Dnode(name, number, gmail);

        if (head == NULL)
        {
            head = temp;
            last = head;
        }
        else
        {
            last->next = temp;
            temp->next = NULL;
            temp->prev = last;
            last = temp;
        }
        cout << "DO YOU WANT TO ENTER MORE CONTACTS ???? \n"
             << endl;
        cout << "ENTER y OR Y TO CONTINUE : ";
        cin >> c;
    } while (c == 'y' || c == 'Y');
}
void PhoneBook::display()
{
    ptr = head;
    if (ptr == NULL)
    {
        cout << "PHONEBOOK IS EMPTY!!!! \n";
    }
    while (ptr != NULL)
    {
        cout << "Name : " << ptr->name << endl;
        cout << "Phone Number : " << ptr->number << endl;
        cout << "Gmail Address : " << ptr->gmail << endl;
        ptr = ptr->next;
    }
}
void PhoneBook::deleteContact(string n)
{
    ptr = head;
    int res = n.compare(ptr->name);
    if (ptr == head && head->next == NULL && res == 0)
    {
        delete (ptr);
        head = NULL;
        cout << " \n CONTACT DELETED SUCCESSFULLY !!!" << endl;
    }
    else if (ptr == head && res == 0)
    {
        head = head->next;
        head->prev = NULL;
        delete (ptr);
        cout << " \n CONTACT DELETED SUCCESSFULLY !!!" << endl;
    }
    else
    {
        while (ptr != NULL)
        {
            res = n.compare(ptr->name);
            if (res == 0)
            {
                temp = ptr->prev;
                temp->next = ptr->next;
                ptr->next->prev = temp;
                delete (ptr);
                cout << "\n CONTACT DELETED SUCCESSFULLY !!!" << endl;
                break;
            }
            else if (ptr->next == NULL)
            {
                cout << "\n CONTACT NOT PRESENT IN THE LIST !!!!! \n";
                break;
            }
            else
            {
                ptr = ptr->next;
            }
        }
    }
}
// void PhoneBook::sort_phonebook(){
//     Dnode *i,*j;
//     int temp;
//     string n;
//     for(i=head;i->next!=NULL;i=i->next)
//     {
//         for(j=i->next;j!=NULL;j=j->next)
//         {
//             temp=i->name.compare(j->name);
//             if(temp>0)
//             {
//                 n = i->name;
//                 i->name = j->name;
//                 j->name = n;
//             }
//         }
//     }
// }
void PhoneBook::searchby_name(string n)
{
    ptr = head;
    int res;
    bool flag = true;
    while (ptr != NULL)
    {
        res = n.compare(ptr->name);
        if (res == 0)
        {
            cout << "\n CONTACT FOUND !!! \n"
                 << endl;
            cout << "Name : " << ptr->name << endl;
            cout << "PhoneNo : " << ptr->number << endl;
            cout << "EmailId : " << ptr->gmail << endl;
            ptr = ptr->next;
            flag = false;
        }
        ptr = ptr->next;
    }
    if (flag == true)
    {
        cout << "\n CONTACT DOES NOT EXSIST !!!!!\n"
             << endl;
    }
}
void PhoneBook::searchby_phone(string num)
{
    ptr = head;
    int res;
    bool flag = true;
    while (ptr != NULL)
    {
        res = num.compare(ptr->number);
        if (res == 0)
        {
            cout << "\n CONTACT FOUND !!! \n"
                 << endl;
            cout << "Name : " << ptr->name << endl;
            cout << "PhoneNo : " << ptr->number << endl;
            cout << "EmailId : " << ptr->gmail << endl;
            ptr = ptr->next;
            flag = false;
        }
        ptr = ptr->next;
    }
    if (flag == true)
    {
        cout << "\n CONTACT DOES NOT EXSIST !!!!!\n"
             << endl;
    }
}
void PhoneBook::searchby_email(string mail)
{
    ptr = head;
    int res;
    bool flag = true;
    while (ptr != NULL)
    {
        res = mail.compare(ptr->gmail);
        if (res == 0)
        {
            cout << "\n CONTACT FOUND !!! \n"
                 << endl;
            cout << "Name : " << ptr->name << endl;
            cout << "PhoneNo : " << ptr->number << endl;
            cout << "EmailId : " << ptr->gmail << endl;
            ptr = ptr->next;
            flag = false;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    if (flag == true)
    {
        cout << "\n CONTACT DOES NOT EXSIST !!!!!\n"
             << endl;
    }
}
void PhoneBook::update(string n)
{
    ptr = head;
    int res;
    char ans;
    while (ptr != NULL)
    {
        res = n.compare(ptr->name);
        if (res == 0)
        {
            do
            {
                int c;
                cout << "WHAT DO YOU WANT TO UPDATE" << endl;
                cout << "1. FOR NAME  " << endl;
                cout << "2. FOR NUMBER  " << endl;
                cout << "3. FOR GMAIL  " << endl;
                cin >> c;
                switch (c)
                {
                case 1:
                    cout << "Enter new name : ";
                    cin >> ptr->name;
                    break;
                case 2:
                    cout << "Enter new phone number : ";
                    cin >> ptr->number;
                    while (ptr->number.length() != 10)
                    {
                        cout << "Enter valid phone number : ";
                        cin >> ptr->number;
                    }
                    break;
                case 3:
                    cout << "Enter gmail address (only gmail.com is accepted) : ";
                    cin >> ptr->gmail;
                    string s;
                    s = ptr->gmail;
                    int pos = ptr->gmail.find('@');
                    while (ptr->gmail.substr(pos + 1, ptr->gmail.length()) != "gmail.com")
                    {
                        cout << "Enter valid gmail : ";
                        cin >> ptr->gmail;
                        int pos = ptr->gmail.find('@');
                    }
                    break;
                }
                cout << "\n DO YOU WANT TO CONTINUE UPDATING CONTACTS ????? \n";
                cout << "ENTER y OR Y TO CONTINUE : ";
                cin >> ans;
            } while (ans == 'y' || ans == 'Y');
            ptr = ptr->next;
        }
        else
        {
            ptr = ptr->next;
        }
    }
}
void PhoneBook::merge_sort()
{
    head = mergeSort(head);
}

int main()
{
    string name;
    string updat;
    string del;
    string search_name;
    string num;
    string gmail;
    char a, b;
    int switc;
    int searc;
    PhoneBook pb;
    cout << "****************** PHONE BOOK DIRECTORY ******************";
    cout << "\n WHAT'S YOUR NAME \n";
    cin >> name;
    cout << "\n\n!!!!!!!!!! WELCOME " << name << " !!!!!!!!!!!!";
    cout << "\n\n LET'S CREATE YOUR PHONEBOOK " << name << " \n\n";
    pb.insert();

    do
    {
        cout << "\n 1)DISPLAY YOUR PHONEBOOK ";
        cout << "\n 2)INSERT NEW CONTACT ";
        cout << "\n 3)UPDATE YOUR EXSISTING CONTACT ";
        cout << "\n 4)DELETE CONTACT";
        cout << "\n 5)SORT YOUR CONTACTS ";
        cout << "\n 6)SEARCH CONTACT \n";
        cin >> switc;
        switch (switc)
        {
        case 1:
            pb.display();
            break;

        case 2:
            pb.insert();
            break;

        case 3:
            cout << "\n\n ENTER NAME OF PERSON WHOSE DETAILS YOU WANT TO  UPDATE \n";
            cin >> updat;
            pb.update(updat);
            break;

        case 4:
            cout << "\n\n ENTER NAME OF PERSON WHOSE CONTACT YOU WANT TO DELETE \n";
            cin >> del;
            pb.deleteContact(del);
            break;

        case 5:
            pb.merge_sort();
            break;

        case 6:
            do
            {
                cout << "\n 1.SEARCH BY NAME ";
                cout << "\n 2.SEARCH BY NUMBER";
                cout << "\n 3.SEARCH BY GMAIL \n";
                cin >> searc;
                switch (searc)
                {
                case 1:
                    cout << "\n ENTER NAME TO BE SEARCHED \n";
                    cin >> search_name;
                    pb.searchby_name(search_name);
                    break;

                case 2:
                    cout << "\n ENTER PHONE TO BE SEARCHED \n";
                    cin >> num;
                    pb.searchby_phone(num);
                    break;

                case 3:
                    cout << "\n ENTER EMAIL ADDRESS TO BE SEARCHED \n";
                    cin >> gmail;
                    pb.searchby_email(gmail);
                    break;

                default:
                    cout << "\nENTER A VALID INPUT\n";
                }
                cout << "\n DO YOU WANT TO CONTINUE SEARCHING FOR MORE CONTACTS ???? \n";
                cout << "ENTER y OR Y TO CONTINUE : ";
                cin >> a;
            } while (a == 'y' || a == 'Y');
            break;
        default:
            cout << "\n\n NO PROPER INPUT GIVEN\n\n";
        }
        cout << "\n DO YOU WANT TO CONTINUE OPERATIONS ON PHONEBOOK ???? \n";
        cout << "ENTER y OR Y TO CONTINUE : ";
        cin >> b;
    } while (b == 'y' || b == 'Y');
    cout << " \n\n THANKS FOR USING OUR PHONE DIRECTORY !!!!!!! \n\n";
}