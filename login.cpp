#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void registeruser(){
    string username,password,u,p;
    bool exists=false;

    cout << "Enter username: ";
    cin  >> username;

    ifstream infile("user.txt");

    while(infile >> u >> p){
        if(u==username){
            exists = true;
            break;
        }
    }
    
    infile.close();

    if(exists){
        cout << "Username already exists" << endl;
        return;
    }

    do{
        cout<<"Enter password (at least 3 characters): ";
        cin >> password;
        if(password.length() < 3){
            cout << "Password must be at least 3 characters long." << endl;
        }
    } while(password.length() < 3);

    ofstream outfile("user.txt", ios::app);
    outfile << username << " " << password << endl;
    outfile.close();

    cout << "User registered successfully!" << endl;
}

void updateuser(string oldusername, string oldpassword, string newusername, string newpassword){
    ifstream infile("user.txt");
    ofstream outfile("temp.txt");
    string u, p;

    while(infile >> u >> p){
        if(u == oldusername && p == oldpassword){
            outfile << newusername << " " << newpassword << endl;
            // Rename their personal file
            rename((oldusername + ".txt").c_str(), (newusername + ".txt").c_str());
        } else {
            outfile << u << " " << p << endl;
        }
    }

    infile.close();
    outfile.close();

    remove("user.txt");
    rename("temp.txt", "user.txt");
}

void userStorage(const string& username){
    int choice;
    string data, line;

    cout << "[1] Write to your personal file\n[2] View your stored text\n[3] Go back\n";
    cin >> choice;

    if(choice == 1){
        cout << "Enter your text (type 'END' on a new line to finish):\n";
        ofstream userfile(username + ".txt", ios::app);
        cin.ignore(); // Flush newline
        while (getline(cin, data)) {
            if(data == "END") break;
            userfile << data << endl;
        }
        userfile.close();
        cout << "Your text has been saved.\n";
    }
    else if(choice == 2){
        ifstream userfile(username + ".txt");
        if(userfile){
            cout << "----- Your Saved Text -----\n";
            while(getline(userfile, line)){
                cout << line << endl;
            }
            cout << "---------------------------\n";
        } else {
            cout << "No data found yet.\n";
        }
        userfile.close();
    }
}

void loginIn(){
    string username,password,u,p,newusername,newpassword;
    bool found = false;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream infile("user.txt");
    while(infile >> u >> p){
        if(u == username && p == password){
            found = true;
            break;
        }
    }
    infile.close();

    if(found){
        cout << "Login successful!\nWelcome back, " << username << "!" << endl;
        int choice;

        while(true){
            cout << "\n[1] Update Username\n[2] Update Password\n[3] Access Personal Text\n[4] Logout" << endl;
            cin >> choice;

            if(choice == 1){
                cout << "Enter new username: ";
                cin >> newusername;
                updateuser(username, password, newusername, password);
                cout << "Username updated successfully!" << endl;
                username = newusername;
            }
            else if(choice == 2){
                do {
                    cout << "Enter new password (at least 3 characters): ";
                    cin >> newpassword;
                    if(newpassword.length() < 3)
                        cout << "Password must be at least 3 characters long." << endl;
                } while(newpassword.length() < 3);
                updateuser(username, password, username, newpassword);
                cout << "Password updated successfully!" << endl;
                password = newpassword;
            }
            else if(choice == 3){
                userStorage(username);
            }
            else if(choice == 4){
                cout << "Logging out...\nGoodbye " << username << "!\n----------------------------------" << endl;
                break;
            }
            else {
                cout << "Invalid choice." << endl;
            }
        }
    } else {
        cout << "Invalid username or password." << endl;
    }
}

int main(){
    int choice;
    while(true){
        cout << "\n----------------------------------" << endl;
        cout << "Please choose an option:" << endl;
        cout << "[1] Register\n[2] Login\n[3] Exit" << endl;
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
