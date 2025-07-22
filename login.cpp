#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void registeruser(){
    string username,password,u,p;
    bool exists=false;

    //Username input
    cout << "Enter username: ";
    cin  >> username;

    ifstream infile("user.txt");

    //Checking if username already exists
    while(infile >> u >> p){
        if(u==username){
            exists = true;
            break;
        }
    }
    
    infile.close();

    if(exists){
        cout << "Username already exists"<< endl;
        return;
    }

    //password input
    cout<<"Enter password :";
    cin>>password;

    ofstream outfile("user.txt",ios::app);
    outfile << username << " "<<password<<endl;

    outfile.close();

    cout << "User registered successfully!"<<endl;

}

void loginIn(){
    string username,password,u,p;
    bool found = false;

    //Input for username and password
    cout << "Enter username : ";
    cin >> username;
    cout << "Enter password : ";
    cin >> password;

    //Checking if username and password matches

    ifstream infile("user.txt");
    while(infile >> u >> p){
        if(u==username && p == password){
            found = true;
            break;
        }
    }
    infile.close();

    if(found){
        cout << "Login successful!\nWelcome back "<<username<< endl;
    } else {
        cout << "Invalid username or password."<< endl;
    }

}

int main(){
    int choice;
    while(true){
        cout << "Welcome to the System!" << endl;
        cout << "----------------------------------" << endl;
        cout << "Please choose an option:" << endl;
        cout << "[1] Register \n[2] Login \n[3] Exit" << endl;
        cin >> choice;

        switch(choice){
            case 1:
                registeruser();
                break;
            case 2:
                loginIn();
                break;
            case 3:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }
   return 0;

}


