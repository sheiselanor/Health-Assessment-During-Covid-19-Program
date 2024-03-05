#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;


void newadmin() {

    string username, password, secretCode;
    cout << "Enter Your Username:";
    cin >> username;
    cout << "Enter Your Password:";
    cin >> password;
    cout << "Enter Your Security Code:";
    cin >> secretCode;

    // Check if admin username and password is in the txt file
    ifstream adminFile("admin.txt");
    if (adminFile.is_open()) {
            string input, fileUsername, filePassword, fileSecretCode;
            bool adminExists = false;
            while (getline(adminFile, input)) {
                // Split the line into username, password, and secretCode
                int pos = input.find(",");
                fileUsername = input.substr(0, pos);
                input.erase(0, pos + 1);
                pos = input.find(",");
                filePassword = input.substr(0, pos);
                input.erase(0, pos + 1);
                fileSecretCode = input;

                if (username == fileUsername && password == filePassword && secretCode == fileSecretCode) {
                        adminExists = true;
                        break;
                }
            }

            adminFile.close();
            if (adminExists) {
                cout << endl;
            } else {
                // Insert the new admin user info in the txt file
                cout << endl;
                cout << "               Admin doesn't exist! Create a new account." << endl;
                cout << "Enter new username:";
                cin >> username;
                cout << "Enter new password:";
                cin >> password;
                cout << "Enter new security code:";
                cin >> secretCode;

                ofstream adminFile("admin.txt", ios::app);
                if (adminFile.is_open()) {
                        cout << endl;
                        adminFile << username << "," << password << "," << secretCode << endl;
                        adminFile.close();
                        cout << "**Admin account created successfully.**" << endl;
                } else {
                        cout << "Error creating admin account." << endl;
                }
            }
        } else {
            cout << "Error opening admin file." << endl;
        }
}

void newclient() {
    string username, password, secretCode;
    cout << "Enter Your Username:";
    cin >> username;
    cout << "Enter Your Password:";
    cin >> password;

    // Check if admin username and password is in the txt file
    ifstream clientFile("client.txt");
    if (clientFile.is_open()) {
            string input, fileUsername, filePassword;
            bool clientExists = false;
            while (getline(clientFile, input)) {
                // Split the line into username, password
                int pos = input.find(",");
                fileUsername = input.substr(0, pos);
                input.erase(0, pos + 1);
                pos = input.find(",");
                filePassword = input;

                if (username == fileUsername && password == filePassword) {
                        clientExists = true;
                        break;
                }
            }
            clientFile.close();
            if (clientExists) {
                cout << endl;
            } else {
                cout << endl;
                cout << "               Client doesn't exist! Create a new account." << endl;
                cout << "Enter new username:";
                cin >> username;
                cout << "Enter new password:";
                cin >> password;
                // Insert the new client user info in the txt file
                ofstream clientFile("client.txt", ios::app);
                if (clientFile.is_open()) {
                        cout << endl;
                        clientFile << username << "," << password << endl;
                        clientFile.close();
                        cout << "**client account created successfully.**" << endl;
                } else {
                        cout << "Error creating client account." << endl;
                }
            }
        } else {
            cout << "Error opening client file." << endl;
        }
}

                                //function to search client data
void searchClientData(string clientName) {
    string line, clientData;
    ifstream file("clients.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find(clientName) != string::npos) {
                clientData += line + "\n"; // store the entire line
                for (int i = 0; i < 4; i++) { // store the next 4 lines
                    getline(file, line);
                    clientData += line + "\n";
                }
                break;
            }
        }
        if (clientData.empty()) {
            cout << "No data found for " << clientName << endl;
        } else {
            cout << "***Data for " << clientName << "***" << endl << clientData;
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

//function to delete client data
void deleteClientData(string clientName) {
    string line;
    ifstream file("clients.txt");
    ofstream newFile("temp.txt");
    if (file.is_open() && newFile.is_open()) {
        while (getline(file, line)) {
            if (line.find(clientName) != string::npos) {
                for (int i = 0; i < 4; i++) { // skip the next 4 lines
                    getline(file, line);
                }

            } else {
                newFile << line << endl; // write to new file
            }
        }
        file.close();
        newFile.close();
        remove("clients.txt");
        rename("temp.txt", "clients.txt");
        cout << "***Data for " << clientName << " has been deleted.***" << endl;

    } else {
        cout << "Unable to open file" << endl;
    }
}

                                                   //compare between every client data
                                                   //sorting by status
struct Client {
    string name;
    int age;
    string state;
    string nationality;
    string status;
};

//function to check comparison
bool compareStatus(Client a, Client b) {
    if (a.status == "high risk" && b.status == "low risk") {
        return true; //a should come before b in the sorted list
    }
    if (a.status == "low risk" && b.status == "high risk") {
        return false; //b should come before a in the sorted list
    }
    return a.name < b.name; //sorts the clients alphabetically by name
}

//function of sortByStatus
void sortByStatus() {
    vector<Client> clients; //declare a vector of struct-client
    string line;  // declare a string variable-line
    ifstream file("client_data.txt"); //open the txt file
    if (file.is_open()) {
        Client c;
        while (getline(file, line)) { //read each line in txt file and assign the value in line
            if (line.find("Name: ") != string::npos) {  //check line with Name. store it in struct c
                c.name = line.substr(6); //takes the current line and extracts the name by using the substr function and starting from the 6th character
                getline(file, line); //reads the next line of the text file and assigns the value to the string variable line

                c.age = stoi(line.substr(5)); //takes the current line and extracts the name by using the substr function and starting from the 5th character.
                getline(file, line);

                c.state = line.substr(7); //takes the current line and extracts the name by using the substr function and starting from the 7th character.
                getline(file, line);

                c.nationality = line.substr(12); //takes the current line and extracts the name by using the substr function and starting from the 12th character.
                getline(file, line);

                c.status = line.substr(8); //takes the current line and extracts the name by using the substr function and starting from the 8th character.
                clients.push_back(c); //the struct c is pushed into the vector of structs clients
            }
        }
        file.close();

        //sorts the clients' data stored in the vector of structs clients
        sort(clients.begin(), clients.end(), compareStatus); //using the sort() function and the comparator function compareStatus()
        cout << "***Sorted data by status***" << endl;
        cout << endl;
        for (int i = 0; i < clients.size(); i++) {
            cout << "Name: " << clients[i].name << endl;
            cout << "Age: " << clients[i].age << endl;
            cout << "State: " << clients[i].state << endl;
            cout << "Nationality: " << clients[i].nationality << endl;
            cout << "Status: " << clients[i].status << endl << endl;
        }
    } else {
        cout << "Unable to open file" << endl;
    }
}


                                              //compare between every client data
                                              //sorting by Age
bool compareAge(Client a, Client b) {
    if (a.age != b.age) {
        return a.age < b.age; //sorts the clients by age in ascending order
    }
    return a.name < b.name; //sorts the clients alphabetically by name
}

//function of sortByAge
void sortByAge() {
    vector<Client> clients;
    string line;
    ifstream file("client_data.txt");
    if (file.is_open()) {
        Client c;
        while (getline(file, line)) { //read each line in txt file and assign the value in line
            if (line.find("Name: ") != string::npos) { //check line with Name. store it in struct c
                c.name = line.substr(6);
                getline(file, line);
                c.age = stoi(line.substr(5));
                getline(file, line);
                c.state = line.substr(7);
                getline(file, line);
                c.nationality = line.substr(12);
                getline(file, line);
                c.status = line.substr(8);
                clients.push_back(c); //the struct c is pushed into the vector of structs clients
            }
        }
        file.close();

        //sorts the clients' data stored in the vector of structs clients
        sort(clients.begin(), clients.end(), compareAge); //using the sort() function and the comparator function compareStatus()
        cout << "***Sorted data by age***" << endl;
        cout << endl;
        for (int i = 0; i < clients.size(); i++) {
            cout << "Name: " << clients[i].name << endl;
            cout << "Age: " << clients[i].age << endl;
            cout << "State: " << clients[i].state << endl;
            cout << "Nationality: " << clients[i].nationality << endl;
            cout << "Status: " << clients[i].status << endl << endl;
        }
    } else {
        cout << "Unable to open file" << endl;
    }
}

std::string generateClientID() {
    time_t currentTime = time(nullptr);
    int randomNumber = rand();
    std::string clientID = std::to_string(currentTime) + std::to_string(randomNumber);
    return clientID;
}
string ADMIN_USERNAME, ADMIN_PASSWORD, ADMIN_SECRETCODE;

int main() {


  cout << "        =============================================================================================" << endl;
  cout << "        =============================================================================================" << endl;
  cout << "                                                 STOP THE SPREAD                     " << endl;
  cout << "        =============================================================================================" << endl;
  cout << "        =============================================================================================" << endl;
  cout << endl;

  cout << "                               >>>>>>>>Welcome to COVID-19 Health Assessment Page<<<<<<<<" << endl;
  cout << endl;
  int choice;
    string input, username, password, secretCode;
    cout << "        Are you a client or admin?" << endl;
    cout << "        1. Admin" << endl;
    cout << "        2. Client" << endl;
    cout << "       Please Enter Your Role:";
    cin >> choice;
    cout << "-------------------------------------------------" << endl;


    // call the function newadmin() when the user wants to create a new admin account
    if (choice == 1) {
    newadmin();
    //admin
  if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD && secretCode == ADMIN_SECRETCODE)
 {
    cout << "                                             Welcome, Admin!" << endl;

    cout << "        ---------------------------------------------------------------------------------------------" << endl;
    while (true){
    cout << "                            Please choose an option from the menu below:" << endl;
    cout << "                                    1. Display All Clients Data" << endl;
    cout << "                                    2. Delete Client's Data" << endl;
    cout << "                                    3. Search Client Data " << endl;
    cout << "                                    4. Update Information Disk" << endl;
    cout << "                                    5. Sort Client's Data By Status" << endl;
    cout << "                                    6. Sort Client's Data By Age" << endl;
    cout << "                                    7. Exit the Page" << endl <<endl;
    cout << "                            Enter your choice: ";

    int choice;
    cin >> choice;
    cout << "      ============================================================================================="<<endl;

    //choice=1 : display
    if (choice == 1) {

             cout << "                                 Displaying all client data:" << endl;
             cout << "      ---------------------------------------------------------------------------------------------" << endl;

             ifstream inputFile("clients.txt");
             string line;
             while (getline(inputFile, line)) {
                            cout << line << endl;
                     }
            cout << endl << endl;

    }

    //choice = 2 :delete
    else if (choice == 2) {
             string clientName;
    cout << "Enter client's name: ";
    cin >> clientName;
    deleteClientData(clientName); //call function deleteClientData
    }

    //choice = 3 : search
    else if (choice == 3) {
      // code to search data goes here
      string clientName;
    cout << "Enter client's name: ";
    cin >> clientName;
    cout << endl;
    searchClientData(clientName); //call function searchClientData
    }

    //choice = 4: update info
    else if (choice == 4) {
// code to update information goes here
      string question, answer;
    cout << "                        Enter the new question about COVID-19: ";
    cin.ignore();
    getline(cin, question);
    cout << "                        Enter the answer for the question: ";
    getline(cin, answer);

    // open the file in append mode
    ofstream outputFile("covid_info.txt", ios_base::app);
    cout << endl;
    outputFile << question << endl << answer << endl;
    outputFile.close();
    cout << endl;
    cout << "                Information has been updated. Updated information is::" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    // display all the information
    ifstream inputFile("covid_info.txt");
    string line;
    cout << endl;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }
    inputFile.close();
    }


    //choice = 5 : sort by status
    //call function sortByStatus
    else if (choice == 5) {
    	sortByStatus();
    }

    //choice =6 : sort by age
    //call function sortByAge
	else if (choice == 6) {
            sortByAge();
    }

    //choice =7 :exit
    else if (choice == 7) {
            cout << endl << endl;
            cout << "      **********************Thank you for using the COVID-19 Health Assessment.**********************" << endl;
          break; //exit the loop
    } else {
      cout << "                                               Invalid choice. Please try again." << endl;
      }
   }
 }
//client
    } else if (choice == 2) {
        newclient() ;
        cout << "                                             Welcome, Client!" << endl<<endl<<endl;

    while (true){
    cout << endl;
    cout << "                             Please choose an option from the menu below:" << endl;
    cout << "                              1. Assessment" << endl;
    cout << "                              2. Information" << endl;
    cout << "                              3. Exit" << endl<<endl;
    cout << "                              Enter your choice: ";

    int choice;
    cin >> choice;
    cout << "         ============================================================================================="<<endl;

    //choice=1
    if (choice == 1) {

            std::string username;
            int age;
            std::string state;
            std::string nationality;
            std::string riskStatus;

            std::string clientID = generateClientID();

            cout << "*Insert Your Personal Details First*" << endl;
            std::cout << "Your Fullname:";
            std::cin >> username;
            std::cout << "Your Age:";
            std::cin >> age;
            std::cout << "Your State:";
            std::cin >> state;
            std::cout << "Your Nationality:";
            std::cin >> nationality;


             // Ask the user about their symptoms
                int score = 0;
                char response;

             cout << "            1. Do you have a fever? (Y/N): ";
             cin >> response;
             cout << endl;

             if (response == 'Y') {
                        score += 3;
                }

             cout << "            2. Do you have following symptoms? " << endl;
             cout << "                 -cough"<<endl;
             cout << "                 -shortnessOfBreath" << endl;
             cout << "                 -fatigue" << endl;
             cout << "                 -bodyAches" <<endl;
             cout << "                 -headache" << endl;
             cout << "                 -lossOfTasteOrSmell" << endl;
             cout << "                 -soreThroat" << endl;
             cout << "                 -congestionOrRunnyNose" << endl;
             cout << "                 -nauseaOrVomiting" << endl;
             cout << "                 -diarrhea"<< endl;
             cout << "               (Y/N):";

             cin >> response;
             cout << endl;

             if (response == 'Y') {
                        score += 3;
                 }

             cout << "            3. Have you been in close contact with someone who has COVID-19? (Y/N):";
             cin >> response;
             cout << endl;

             if (response == 'Y') {
                       score += 3;
                 }

             cout << "            4. Have you traveled recently? (Y/N): ";
             cin >> response;
             cout << endl;

             if (response == 'Y') {
                       score += 1;
                 }
             if (score >= 3) {
                    riskStatus = "High Risk";
                       cout << "       -------------------------------------------------------------------------" << endl;
                       cout << "    Your risk level is high. Please take appropriate precautions." << endl;

                       string hospitals[] = {"   [1]Sunway Medical Centre", "   [2]MSU Medical Centre", "   [3]Poliklinik South City", "   [4]Klinik Hanita", "   [5]Subang Jaya Medical Centre(SJMC)", "   [6]Klinik Mediviron Puchong Avenue", "   [7]Sungai Long Medical Centre" };
                       cout << "    Here are a list of hospitals that offer swab testing:" << endl;

                       for (int i = 0; i < 7; i++) {
                                 cout << hospitals[i] << endl;
                              }

                       cout << "       -------------------------------------------------------------------------" << endl;

                       int hospital_number;
                       while (true) {
                                 cout << "    Please select a hospital by entering its number: ";
                                 cin >> hospital_number;
                                 cout << endl;

                                 if (hospital_number >= 1 && hospital_number <= 7) {
                                           cout << " >>> You have selected " << hospitals[hospital_number - 1] << "."<<endl;
                                           cout << " >>> We have contacted the hospital for your swab session. Please follow government's SOP. " << endl;
                                           cout << "       -------------------------------------------------------------------------" << endl;
                                           cout << "       -------------------------------------------------------------------------" << endl;
                                       break;
                                    } else {
                                           cout << "Invalid hospital number. Please try again." << endl;
                                    }
                                }
                             }
                else {
                        riskStatus = "Low Risk";
                       cout << "    Your risk level is low, but it is still important to follow guidelines from public health officials to prevent the spread of COVID-19." << endl;
                       cout << "       -------------------------------------------------------------------------" << endl;
                       cout << "       -------------------------------------------------------------------------" << endl;
                     }
    // Record client's information in text file
    std::ofstream outFile;
    outFile.open("clients.txt", std::ios_base::app);
    outFile << "Client ID: " << clientID << std::endl;
    outFile << "Name: " << username << std::endl;
    outFile << "Age: " << age << std::endl;
    outFile << "State: " << state << std::endl;
    outFile << "Nationality: " << nationality << std::endl;
    outFile << "Risk Status: " << riskStatus << std::endl;
    outFile << "---" << std::endl;
    outFile.close();
    }

    //choice=2
    else if (choice == 2) {
      cout << "Please select a question from the list below:" << endl;
      cout << "1. What is COVID-19?" << endl;
      cout << "2. when was the First Case of Covid-19 Detected in Malaysia?" << endl;
      cout << "3. How can I protect myself from COVID-19?" << endl;
      cout << "4. How many days a covid-19 patient has to be in quarantine?" << endl;
      cout << "5. How many waves of covid-19 has been in all over the world?" << endl << endl;
      cout << "Enter your choice: ";

      int questionChoice;
      cin >> questionChoice;
      cout << endl;

      string question;
      if (questionChoice == 1) {
             question = "What is COVID-19?";
         } else if (questionChoice == 2) {
                question = "when was the First Case of Covid-19 Detected in Malaysia?";
            } else if (questionChoice == 3) {
                   question = "How can I protect myself from COVID-19?";
              } else if (questionChoice == 4) {
                   question = "How many days a covid-19 patient has to be in quarantine?";
                }else if (questionChoice == 5) {
                   question = "How many waves of covid-19 has been in all over the world?";
                 }else {
                     cout << "Invalid choice. Please try again." << endl;
                     return 0;
                }
                  ifstream inputFile("covid_info.txt");
                  string line;
                  bool found = false;
                  while (getline(inputFile, line)) {
                        if (line.find(question) != string::npos) {
                               cout << line << endl;
                               found = true;
                             }
                        }
        if (!found) {
             cout << "Information not found." << endl;
        }

     }

     //choice=3
        else if (choice == 3) {
                cout << endl << endl;
                cout << "============================================================================================================" << endl;
                cout << "      **********************Thank you for using the COVID-19 Health Assessment.**********************" << endl;
                cout << "============================================================================================================" << endl;
                    break; //exit the loop
                } else {
                       cout << "                                                   Invalid choice. Please try again." << endl;
                   }
    }
    } else {

        cout << "                Invalid input! " << endl;


    }



  return 0;
}

