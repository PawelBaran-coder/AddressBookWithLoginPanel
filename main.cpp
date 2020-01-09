#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Person
{
    int id, userId;
    string name, lastName, phoneNumber, emailAddress, address;
};

struct User
{
    int id;
    string login, password;
};

void displayVectorPeople(vector <Person> people, vector <Person>::iterator itr)
{
    cout << itr->id << endl;
    cout << itr->name << endl;
    cout << itr->lastName << endl;
    cout << itr->phoneNumber << endl;
    cout << itr->emailAddress << endl;
    cout << itr->address << endl;
}

string convwertIntToString(int number)
{
    ostringstream ss;
    ss << number;
    string str = ss.str();

    return str;
}

vector <string> split(string&dataLine)
{
    vector <string> result;
    const char separator = '|';
    stringstream ss(dataLine);
    string data;

    while (getline(ss, data, separator))
    {
        result.push_back(data);
    }
    return result;
}

void fromVectorToFile(vector <Person> &people, int memberId)
{
    const char separator = '|';
    string line;
    string id, userId, name, lastName, phoneNumber, emailAddress, address;
    int idInt, userIdInt;

    fstream file;
    fstream fileTemp;
    fileTemp.open("KsiazkaAdresowaTymczas.txt",ios::out);
    file.open("KsiazkaAdresowa.txt",ios::in);

    while (getline(file,line))
    {
        vector <string> splited = split(line);

        idInt = atoi(splited[0].c_str());
        id = splited[0];
        userIdInt = atoi(splited[1].c_str());
        userId = splited[1];
        name = splited[2];
        lastName = splited[3];
        phoneNumber = splited[4];
        emailAddress = splited[5];
        address = splited[6];

        if (idInt == memberId)
        {
            for ( vector<Person>::iterator itr = people.begin(), finish = people.end(); itr != finish; ++itr )
            {
                if(itr->id == idInt)
                {
                    fileTemp << itr->id << separator << itr->userId << separator << itr->name << separator << itr->lastName << separator << itr->phoneNumber << separator << itr->emailAddress << separator << itr->address << separator << endl;
                }
            }
        }
        else
        {
            fileTemp << id << separator << userId << separator << name << separator << lastName << separator << phoneNumber << separator << emailAddress << separator << address << separator << endl;
        }

    }
    fileTemp.close();
    file.close();

    remove ("KsiazkaAdresowa.txt");
    rename ("KsiazkaAdresowaTymczas.txt", "KsiazkaAdresowa.txt");
}

int fromFileToVector(vector <Person> &people, int userId)
{
    Person member;
    string line;
    int lastOneMemberId = 0;

    fstream file;
    file.open("KsiazkaAdresowa.txt",ios::in | ios::app);

    if (file.good()==false)
    {
        cout<< "Nie udalo sie otworzyc pliku: KsiazkaAdresowa.txt!";
        exit(0);
    }
    while (getline(file,line))
    {
        vector <string> splited = split(line);

        member.id = atoi(splited[0].c_str());
        member.userId = atoi(splited[1].c_str());
        member.name = splited[2];
        member.lastName = splited[3];
        member.phoneNumber = splited[4];
        member.emailAddress = splited[5];
        member.address = splited[6];

        lastOneMemberId = member.id;

        if(member.userId == userId)
        {
            people.push_back(member);
        }
    }
    file.close();

    return lastOneMemberId;
}

void fromVectorToFileUsers(vector <User> &users)
{
    const char separator = '|';
    fstream fileUsers;

    fileUsers.open("Uzytkownicy.txt", ios::out);
    if (fileUsers.good())
    {
        for ( vector<User>::iterator itr = users.begin(), finish = users.end(); itr != finish; ++itr )
        {
            fileUsers << itr->id << separator << itr->login << separator << itr->password << separator << endl;
        }
        fileUsers.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: Uzytkownicy.txt" << endl;
    }
}

int fromFileToVectorUsers(vector <User> &users, int numberOfUsers)
{
    User member;
    string line;

    fstream fileUsers;
    fileUsers.open("Uzytkownicy.txt",ios::in | ios::app);

    if (fileUsers.good()==false)
    {
        cout<< "Nie udalo sie otworzyc pliku: Uzytkownicy.txt!";
        exit(0);
    }
    while (getline(fileUsers,line))
    {
        vector <string> splited = split(line);

        member.id = atoi(splited[0].c_str());
        member.login = splited[1];
        member.password = splited[2];

        numberOfUsers++;
        users.push_back(member);
    }
    fileUsers.close();

    return numberOfUsers;
}

int registration(vector <User> &users,int numberOfUsers)
{
    User member;
    string login, password;
    string fullData;
    const char separator = '|';

    cout<<"Podaj nazwe uzytkownika:";
    cin>>login;

    int i=0;
    while (i<numberOfUsers)
    {
        if(users[i].login==login)
        {
            cout<<"Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika:";
            cin>>login;
            i=0;
        }
        else
        {
            i++;
        }
    }
    cout<<"Podaj haslo:";
    cin>>password;

    int personalNumber = numberOfUsers+1;

    member.login=login;
    member.password=password;
    member.id=personalNumber;

    users.push_back(member);
    fullData = convwertIntToString(personalNumber) + separator + login + separator + password + separator;

    fstream fileUsers;
    fileUsers.open("Uzytkownicy.txt", ios::out | ios::app);

    if (fileUsers.good())
    {
        fileUsers << fullData << endl;
        fileUsers.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: Uzytkownicy.txt" << endl;
    }
    cout<<"Konto zalozone"<<endl;
    Sleep(1000);
    return numberOfUsers+1;
}

void changePassword(vector <User> &users, int numberOfUsers, int userId)
{
    string password;
    cout<<"Podaj nowe haslo: ";
    cin>>password;

    for(int i=0; i<numberOfUsers; i++)
    {
        if (users[i].id==userId)
        {
            users[i].password=password;
            cout<<"Haslo zostalo zmienione"<<endl;
            Sleep(1500);
        }
    }
}

int loggingIn(vector <User> &users,int numberOfUsers)
{
    string login, password;
    cout<<"Podaj nazwe: ";
    cin>>login;
    int i=0;

    while (i<numberOfUsers)
    {
        if(users[i].login==login)
        {
            for (int attempt=0; attempt<3; attempt++)
            {
                cout<<"Podaj haslo. Pozostalo prob "<<3-attempt<<": ";
                cin>>password;

                if (users[i].password==password)
                {
                    cout<<"Zalogowales sie."<<endl;
                    Sleep(1000);
                    return users[i].id;
                }
            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba"<<endl;
            Sleep(3000);

            return 0;
        }
        i++;
    }
    cout<<"Nie ma uzytkownika z takim loginem"<<endl;
    Sleep(1500);

    return 0;
}

int addPerson(vector <Person> &people, int lastOneMemberId, int userId)
{
    Person member;
    string name, lastName, phoneNumber, emailAddress, address;
    string fullData;
    const char separator = '|';
    int personalNumber = 0;

    system("cls");
    cout << "Dodawanie osoby" << endl;
    cout << "Podaj imie osoby : ";
    cin >> name;
    cout << "Podaj nazwisko osoby: ";
    cin >> lastName;
    cout << "Podaj numer telefonu osoby: ";
    cin.sync();
    getline(cin, phoneNumber);
    cout << "Podaj email osoby: ";
    cin >> emailAddress;
    cout << "Podaj adres osoby: ";
    cin.sync();
    getline(cin, address);

    personalNumber = lastOneMemberId+1;

    member.id = personalNumber;
    member.userId = userId;
    member.name = name;
    member.lastName = lastName;
    member.phoneNumber = phoneNumber;
    member.emailAddress = emailAddress;
    member.address = address;

    people.push_back(member);
    fullData = convwertIntToString(personalNumber) + separator + convwertIntToString(userId) + separator + name + separator + lastName + separator + phoneNumber + separator + emailAddress + separator + address + separator;

    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (file.good())
    {
        file << fullData << endl;

        file.close();

        cout << "Osoba zostala dodana." << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }

    return personalNumber;
}

void nameDisplay(vector <Person> people)
{
    string nameForSearch;
    int howManyNames = 0;

    cout << "Podaj imie: ";
    cin >> nameForSearch;
    system("cls");

    for ( vector<Person>::iterator itr = people.begin(), finish = people.end(); itr != finish; ++itr )
    {
        if(nameForSearch == itr->name)
        {
           displayVectorPeople(people, itr);
            howManyNames += 1;
        }
        else
        {
            howManyNames += 0;
        }
    }
    if(howManyNames == 0)
    {
        cout << "Nie ma takiej osoby!" << endl;
    }
    system("pause");
}

void lastNameDisplay(vector <Person> people)
{
    string lastNameForSearch;
    int howManyNames = 0;

    cout << "Podaj Nazwisko: ";
    cin >> lastNameForSearch;
    system("cls");

    for ( vector<Person>::iterator itr = people.begin(), finish = people.end(); itr != finish; ++itr )
    {
        if(lastNameForSearch == itr->lastName)
        {
            displayVectorPeople(people, itr);
            howManyNames += 1;
        }
        else
        {
            howManyNames += 0;
        }
    }
    if(howManyNames == 0)
    {
        cout << "Nie ma takiej osoby!" << endl;
    }
    system("pause");
}

void everyoneDisplay(vector <Person> people)
{
    system("cls");
    for ( vector<Person>::iterator itr = people.begin(), finish = people.end(); itr != finish; ++itr )
    {
        displayVectorPeople(people, itr);
    }
    system("pause");
}

int deleteMember(vector <Person> &people)
{
    system("cls");
    int numberToDelete;

    char choice;

    cout << "Podaj nr id osoby do usuniecia: ";
    cin >> numberToDelete;

    for ( vector<Person>::iterator itr = people.begin(), finish = people.end(); itr != finish; ++itr )
    {
        if(itr -> id == numberToDelete)
        {
            cout << "Czy napewno chcesz usunac osobe: " << itr -> name << " " << itr -> lastName << " " << "z ksiazki adresowej (t/n)? ";
            cin >> choice;
            if (choice == 't')
            {
                people.erase(itr);

                cout << "Osoba zostala usunieta!";
                Sleep(1000);

                return numberToDelete;
            }
            if (choice == 'n')
            {
                numberToDelete = 0;
                return numberToDelete;
            }
        }
    }

    cout << "Nie ma takiej osoby" << endl;
    Sleep(1000);

    numberToDelete = 0;
    return numberToDelete;
}

int editData (vector<Person>&people)
{
    system("cls");
    int memberId;
    char choice;
    int vectorSize = people.size();
    string newData;

    cout <<"Podaj id osoby, ktorej dane chcesz zmienic: "<<endl;
    cin>>memberId;

    for(int i = 0; i < vectorSize; i++)
    {
        if (people[i].id==memberId)
        {
            cout << "Znaleziono taka osobe: "<< endl;
            cout << people[i].name << " " << people[i].lastName << endl;
            break;
        }
        if (i == vectorSize-1)
        {
            cout << "Nie ma osoby o takim nr id!" << endl;
            system("pause");
            memberId = 0;
            return memberId;
        }
    }
    while (true)
    {
        cout <<"Wybierz jaka dana chcesz zmienic:"<<endl;
        cout <<"1 - imie"<<endl;
        cout <<"2 - nazwisko"<<endl;
        cout <<"3 - nr telefonu"<<endl;
        cout <<"4 - e-mail"<<endl;
        cout <<"5 - adres"<<endl;
        cout <<endl;
        cout <<"6 - powrot do menu"<<endl;

        cin>>choice;
        system("cls");

        if (choice=='6')
        {
            break;
        }

        cout <<"Wprowadz nowa wartosc:"<<endl;
        cin>>newData;
        system("cls");

        for ( vector<Person>::iterator itr = people.begin(), finish = people.end(); itr != finish; ++itr )
        {
            if(itr->id == memberId)
            {
                if (choice == '1')
                {
                    itr->name = newData;
                    cout << "Imie zostalo zmienione" << endl;
                    Sleep(1000);
                }
                if (choice == '2')
                {
                    itr->lastName = newData;
                    cout << "Nazwisko zostalo zmienione" << endl;
                    Sleep(1000);
                }
                if (choice == '3')
                {
                    itr->phoneNumber = newData;
                    cout << "Nr telefonu zostal zmieniony" << endl;
                    Sleep(1000);
                }
                if (choice == '4')
                {
                    itr-> emailAddress = newData;
                    cout << "Adres e-mail zostal zmieniony" << endl;
                    Sleep(1000);
                }
                if (choice == '5')
                {
                    itr->address = newData;
                    cout << "Adres zostal zmieniony" << endl;
                    Sleep(1000);
                }
            }
        }
        system("cls");
    }
    return memberId;
}




int main()
{
    vector <Person> people;
    vector <User> users;

    int userId=0;
    int memberId=0;
    int numberOfUsers=0;
    int lastOneMemberId=0;

    char choice;

    fstream file;
    fstream fileUsers;

    numberOfUsers = fromFileToVectorUsers(users,numberOfUsers);

    while(1)
    {
        if (userId==0)
        {
            system("cls");
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"9. Zakoncz program"<<endl;
            cin>>choice;

            if (choice=='1')
            {
                numberOfUsers = registration(users,numberOfUsers);
            }
            else if (choice=='2')
            {
                userId=loggingIn(users,numberOfUsers);
            }
            else if (choice=='9')
            {
                exit(0) ;
            }
        }
        else
        {
            lastOneMemberId = fromFileToVector(people, userId);
            while(true)
            {
                system("cls");
                cout << "1. Dodaj osobe" << endl;
                cout << "2. Wyszukaj po imieniu" <<endl;
                cout << "3. Wyszukaj po nazwisku" <<endl;
                cout << "4. Wyswietl wszystkich" <<endl;
                cout << "5. Usun dana osobe" <<endl;
                cout << "6. Edytuj dane osoby" <<endl;
                cout << "7. Zmiana hasla"<<endl;
                cout << "8. Wylogowanie"<<endl;

                cin>>choice;
                if (choice == '1')
                {
                    people.clear();
                    lastOneMemberId = fromFileToVector(people, userId);
                    addPerson(people, lastOneMemberId, userId);
                }
                else if (choice == '2')
                {
                    nameDisplay(people);
                }
                else if (choice == '3')
                {
                    lastNameDisplay(people);
                }
                else if (choice == '4')
                {
                    everyoneDisplay(people);
                }
                else if (choice == '5')
                {
                    memberId = deleteMember(people);
                    fromVectorToFile(people, memberId);
                }
                else if (choice == '6')
                {
                    memberId = editData(people);
                    fromVectorToFile(people,memberId);
                }
                else if (choice=='7')
                {
                    changePassword(users, numberOfUsers, userId);
                    fromVectorToFileUsers(users);
                }
                else if (choice=='8')
                {
                    userId = 0;
                    people.clear();
                    break;
                }
            }
        }
    }

    return 0;
}
