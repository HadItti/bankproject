
#include <iostream>
#include <string>
#include <fstream>
#include<iomanip>
#include<vector>
#include <functional>
using namespace std;
struct StusersData{
    string userName;
    string password;
    string permission;
    string currentUser;
    struct permissions {
        short showList;
        short addNewClient;
        short deleteClient;
        short updateClient;
        short findClient;
        short transaction;
    };
    permissions p;
};
struct stClientsData{
    string accountNumbr;
    string pinCode;
    string userName;
    string phoneNumber;
    string accountBalance;
};
static string currentUser;
void runTheApp();
void login();
//Print users data 
void fromFileToVector(string fileName,vector<string> &getData){
    //The task of this function is to copy data from file to vector 
    // and remove each symbole before add the data to the vector
    fstream myFile;
    string word;
    myFile.open(fileName, ios::in);
    if(myFile.is_open()){
        string line;
        while (getline(myFile,line))
        {
        char letter ='-';
        for(int x=0; x<line.length();x++){
            if(line[x] != letter){
                word+=line[x];
            }else{
                if(!word.empty()){
                    getData.push_back(word);
                word.clear();
                }
            }
        }
         if (word.length()==1) {
                getData.push_back("-"+word);
                word.clear();
            }
    }
}
    myFile.close();
}
void fromVectorToStruct(vector<string> getData, vector<stClientsData> &totalOfClients){
         short item=0;
         for(int i=1; i<=(getData.size()/5);i++){
            totalOfClients.push_back({getData[item+0],getData[item+1],getData[item+2],getData[item+3],getData[item+4]});
            item+=5;
         }
    }
void printStruct(vector<stClientsData> totalOfClients){
        cout<<setw(10)<<"===============================================================\n";
        cout<<setw(10)<<"Account Number"<<setw(15)<<"User Name"<<setw(15)<<"Pin Code"<<setw(20)<<"Account Balance";
        cout<<setw(10)<<"\n===============================================================\n";
        for(int i=0; i<totalOfClients.size();i++){
            cout<<setw(10)<<totalOfClients[i].accountNumbr<<setw(5)<<"|"<<setw(15)<<totalOfClients[i].userName<<setw(5)<<"|"<<setw(15)<<totalOfClients[i].pinCode<<setw(5)<<"|"<<setw(8)<<totalOfClients[i].accountBalance<<endl;
         }
    }
//End of print users data 

//Add new users 
int readUserDate(){
    //Te task of this function is to take a user date and save it in a vectore
    int findThisAccountNumber=0;
   // cout<<"Search for account number: ";
    cin>>findThisAccountNumber;
    return findThisAccountNumber;
}
void searchInVector(int searchFor,vector<stClientsData> searchIn,bool &found,int &index){
    // this function searching in vector, looking for user ID
    stClientsData number;
    number.accountNumbr=to_string(searchFor);
     for(int i=0; i<searchIn.size();i++){
            if(number.accountNumbr == searchIn[i].accountNumbr){
                found=true;
                index=i;
                break;
            }else{
                found=false;
            }
         }
}
void addNewClient(stClientsData &info,vector<string> &getData){
    //THe task of this function is to take a user date and save it in a vectore
    cout<<"Enter client's account number: ";
    cin>>info.accountNumbr;
    getData.push_back(info.accountNumbr);
    cout<<"Enter client's pin code: ";
    cin>>info.pinCode;
    getData.push_back(info.pinCode);
    cout<<"Enter client's name: ";
    getline(cin>>ws,info.userName);
    getData.push_back(info.userName);
    cout<<"Enter client's phone number: ";
    cin>>info.phoneNumber;
    getData.push_back(info.phoneNumber);
    cout<<"Enter client's account balance: ";
    cin>>info.accountBalance;
    getData.push_back(info.accountBalance);
}
void appendClientToFile(string fileName,vector<string> vectorName){
    fstream myfile;
    myfile.open(fileName,ios::out|ios::app);
    if(myfile.is_open()){
    for(string &info:vectorName){
        myfile<<info<<"-";
     }
     myfile.close();
    }
      vectorName.clear();
}
void clintDataBase(string fileName,vector<string> &getData,stClientsData info){
   // The task of this function is taking client data from vector
    cout<<"Add New Clint:\n"<<endl;
    bool switchar =true;
    char answer;
    while(switchar){
        getData.clear();
        addNewClient(info,getData);
        appendClientToFile(fileName,getData);
        cout<<"y or n for adding more clients:";
        cin>>answer;
        if(tolower(answer) == 'y'){
            continue;
        }else{
            runTheApp();
            switchar = false;
        }
    }
}
//End of add new users data 

// Search for user data on order to delete from database
void searchForUser(int searchFor,vector<string> searchIn,vector <string> &newVector,int &index){
    // this function searching in vector, looking for user ID
    bool found =0;
    string number;
    for(int x=0;x<searchIn.size();x++){
        index++; 
        number+= searchIn[x];
        if(number !=to_string(searchFor)){
            newVector.push_back(number);
        }
    if(number ==to_string(searchFor)){
        found =1;
        break;
    }
    number.clear();
}
}
void addFoundUserDataToVector(int index, bool found,vector<stClientsData> totalOfClients,vector<string> &foundData){
    //     if(found == false){
    //     cout<<"User Not Found";
    // }else{
    //     foundData.push_back(totalOfClients[index].accountNumbr);
    //     foundData.push_back(totalOfClients[index].pinCode);
    //     foundData.push_back(totalOfClients[index].userName);
    //     foundData.push_back(totalOfClients[index].phoneNumber);
    //     foundData.push_back(totalOfClients[index].accountBalance);
    // }
    if(found == false){
        cout<<"User Not Found";
    }else{
        foundData.push_back(totalOfClients[index].accountNumbr);
        foundData.push_back(totalOfClients[index].pinCode);
        foundData.push_back(totalOfClients[index].userName);
        foundData.push_back(totalOfClients[index].phoneNumber);
        foundData.push_back(totalOfClients[index].accountBalance);
    }
}
void deleteUserData(vector<string> &foundUserData, bool found){
    char updateData;
    if(found) {  
        cout<<setw(5)<<"===============================================================\n";
        cout<<setw(5)<<"Account Number"<<setw(15)<<"User Name"<<setw(15)<<"Pin Code"<<setw(20)<<"Account Balance";
        cout<<setw(5)<<"\n===============================================================\n";
        cout<<setw(10)<<foundUserData[0]<<setw(5)<<"|"<<setw(15)<<foundUserData[2]<<setw(5)<<"|"<<setw(15)<<foundUserData[1]<<setw(5)<<"|"<<setw(8)<<foundUserData[4]<<endl;
    cout<<"\n Do you want to delete this client data? Yes or No: ";
    cin>>updateData;
    if(updateData =='y'){
        for(int i=1;i<=4;i++){
           foundUserData[i].clear();
        }
        cout<<"The user has been deleted";
    }else{
        runTheApp();
    }
    }

}
void sendUpdatedData(vector<stClientsData> sourceVector,vector<string> &targetVector,int startIndex){
     for(int i=0;i<sourceVector.size();i++){
        if(i != startIndex)
       {
        targetVector.push_back(sourceVector[i].accountNumbr);
        targetVector.push_back(sourceVector[i].pinCode);
        targetVector.push_back(sourceVector[i].userName);
        targetVector.push_back(sourceVector[i].phoneNumber);
        targetVector.push_back(sourceVector[i].accountBalance);
    }; }
}
void overwriteAllClients(string fileName,vector<string> vectorName){
    fstream myfile;
    myfile.open(fileName,ios::out);
    if(myfile.is_open()){
    for(string &info:vectorName){
        myfile<<info<<"-";
     }
     myfile.close();
    }
      vectorName.clear();
}
// End fo search for user data on order to delete from database

// Search and edit user data then save it in a file
void getUserDate(stClientsData
 &info,vector<string> &foundUserData){
    //The task of this function is to take a user date and save it in a vectore
    cout<<"Enter pin code: ";
    cin>>info.pinCode;
    foundUserData.push_back(info.pinCode);
    cout<<"Enter the name: ";
    getline(cin>>ws,info.userName);
    foundUserData.push_back(info.userName);
    cout<<"Enter phone number: ";
    cin>>info.phoneNumber;
    foundUserData.push_back(info.phoneNumber);
    cout<<"Enter account balance: ";
    cin>>info.accountBalance;
    foundUserData.push_back(info.accountBalance);
}
void updateUserData(stClientsData
 &info,vector<string> &foundUserData){
    char updateData;
    cout<<"Do you want to update this client data? Yes or No: ";
    cin>>updateData;
    if(updateData =='y'){
        for(int i=1;i<=4;i++){
           foundUserData[i].clear();
        }
        getUserDate(info,foundUserData);
    }else{
        cout<<"Wrong selection, Try again later";
    }
    cout<<"Data has been updated"<<endl;
}
void copyFromEditedVectorToAnotherVector(vector<string> &source, vector<string> &target, int startIndex) {
    for (int i = 1; i < source.size(); ++i) {
        if (startIndex + i < target.size() && !source[i].empty()) {
            target[startIndex + i] = source[i];
        } else {
           if(!source[i].empty()){
            target.push_back(source[i]);
           }
        }
    }
}
//  End of search and edit user data then save it in a file

//Search users data on order to find client
void printClientData(vector<stClientsData> totalOfClients, int index){
        cout<<setw(10)<<"===============================================================\n";
        cout<<setw(10)<<"Account Number"<<setw(15)<<"User Name"<<setw(15)<<"Pin Code"<<setw(20)<<"Account Balance";
        cout<<setw(10)<<"\n===============================================================\n";
        cout<<setw(10)<<totalOfClients[index].accountNumbr<<setw(5)<<"|"<<setw(15)<<totalOfClients[index].userName<<setw(5)<<"|"<<setw(15)<<totalOfClients[index].pinCode<<setw(5)<<"|"<<setw(8)<<totalOfClients[index].accountBalance<<endl;
    }
//End of Search users data on order to find client

// Transaction operations
void transactionOperations(vector<string> &foundUserData,vector<string> &getData, vector<string> &newData,int index,
    bool found,vector<stClientsData> totalOfClients){
    //This block of codes updates client's balance
    double newbalance =50.1;
    vector<string> updatedTansaction;
    auto updateTransactionsData = [&](vector<string> &newData,vector<stClientsData> totalOfClients){
 
        for(int i=0;i<totalOfClients.size();i++){
        newData.push_back(totalOfClients[i].accountNumbr);
        newData.push_back(totalOfClients[i].pinCode);
        newData.push_back(totalOfClients[i].userName);
        newData.push_back(totalOfClients[i].phoneNumber);
        newData.push_back(totalOfClients[i].accountBalance);
     }
    };
    auto deposit = [&](double &newbalance, vector<stClientsData> &totalOfClients){
        //The task of thid function is adding balance to user's account, the function is local works inside it's perent function
        short moneyAmount=0;
        char response;
        cout<<"Enter deposit amount: ";
        cin>>moneyAmount;
        cout<<"\n Are you sure you want to deposit this amount? y/r ";
        cin>>response;
        if(response =='y'){
            newbalance = moneyAmount+stoi(totalOfClients[index].accountBalance);
        }
        totalOfClients[index].accountBalance = to_string(newbalance);
    }; 
    auto withdraw = [&](double &newbalance,vector<stClientsData> &totalOfClients){
        //The task of this function is withdraw balance from user's account, the function is local works inside it's perent function
        double moneyAmount=0;
        char response;
        bool balanceValidation =false;
        cout<<"Enter withdraw amount: ";
        cin>>moneyAmount;
        cout<<"\n Are you sure you want to withdraw this amount? y/r";
        cin>>response;
        if(response =='y'){
           while(balanceValidation == false){
            if((stoi(totalOfClients[index].accountBalance) - moneyAmount)<0){
                cout<<"Amount Exceeds the balance, you can withdraw up to :"<< stoi(totalOfClients[index].accountBalance)<<endl;
                cout<<"Plaese enter anthoer amount:";
                cin>>moneyAmount;
            }else 
            {
                newbalance = (stoi(totalOfClients[index].accountBalance) - moneyAmount);
                break;
            } 
           }
        }
        totalOfClients[index].accountBalance = to_string(newbalance);
    }; 
    auto totalBalances =[&](vector<string> getData){
        // This function search in accounts file for index of account balance, and add
        // it value to result on order to count the totale
        double result=0;
        for (int i=4; i<=getData.size();i++){
            result+=stod(getData[i]);
            cout<<getData[i]<<endl;
            i+=4;
       }
        cout<<"The total of accounts balance is: "<<result<<endl;
    };
    system("clear");
    cout<<"=========================\n";
    cout<<setw(20)<<"Transactions Menu Screen \n";
    cout<<"=========================\n";
    printf(
        "[1] Deposit.\n"
        "[2] Withdraw.\n"
        "[3] Total Balances.\n"
        "[4] Main menu. \n");
        cout<<"=========================\n";
        int response=0;
        cout<<"Select what do you want to do 1 to 4: ";
        cin>>response;
        switch (response)
        {
        case 1:
        {system("clear");
        cout<<"=========================\n";
        cout<<setw(20)<<"Deposit Screen \n";
        cout<<"=========================\n";
            cout<<"\nSearch for account number:" ;
            int findThisAccountNumber =readUserDate();
            fromFileToVector("clients.txt",getData);
            fromVectorToStruct(getData,totalOfClients);
            searchInVector(findThisAccountNumber,totalOfClients,found,index);
            addFoundUserDataToVector(index,found, totalOfClients,foundUserData);
            if (found == true) {
                printClientData(totalOfClients, index);
                deposit(newbalance,totalOfClients);
                updateTransactionsData(newData,totalOfClients);
                overwriteAllClients("clients.txt",newData); 
            }
        break;
    }
    case 2:{
            system("clear");
            cout<<"=========================\n";
            cout<<setw(20)<<"Withdraw Screen \n";
            cout<<"=========================\n";
            cout<<"\nSearch for account number:" ;
            int findThisAccountNumber =readUserDate();
            fromFileToVector("clients.txt",getData);
            fromVectorToStruct(getData,totalOfClients);
            searchInVector(findThisAccountNumber,totalOfClients,found,index);
            addFoundUserDataToVector(index,found, totalOfClients,foundUserData);
            if (found == true) {
                printClientData(totalOfClients, index);
                withdraw(newbalance,totalOfClients);
                updateTransactionsData(newData,totalOfClients);
            }
                overwriteAllClients("clients.txt",newData); 
       break;
     }
    case 3:{
        system("clear");
        cout<<"=========================\n";
        cout<<setw(20)<<"Total Balance Screen \n";
        cout<<"=========================\n";
        fromFileToVector("clients.txt",getData);
        totalBalances(getData);
        break;
    }
    case 4:
        runTheApp();
     break;
   };
    }
 //End of transaction operations

void backToMainMenu() {
    char key;
    cout<<"\n Press any key key to back to the main menu...";
    cin>>key;
    runTheApp();
}
// maneging users
void manageUsers() {
    vector<string> getData;
    vector<string> newData;
    vector<string> words;
    vector<StusersData> totalOfUsers;
    vector<string> getPermission;
    int index=0;
    bool found =0;
    StusersData user;
    auto backToManageUserScreen = [&]{
        char key;
        cout<<"\n Press any key key to back to previous menu...";
        cin>>key;
        manageUsers();
    };
    auto fromVectorToStruct = [&](vector <string>getData, vector<StusersData> &totalOfUsers){
        short item=0;
        for(int i=1; i<=(getData.size()/3);i++){
            totalOfUsers.push_back({getData[item+0],getData[item+1],getData[item+2]});
            item+=3;
        }
    };
    auto printUsers  = [&] (vector<StusersData> totalOfUsers){
        system("clear");
        cout<<setw(30)<<"Users List ("<<totalOfUsers.size()<<") user"<<endl;
        cout<<setw(10)<<"===============================================================\n";
        cout<<setw(10)<<"User Name"<<setw(15)<<"Password"<<setw(20)<<"Permission";
        cout<<setw(10)<<"\n===============================================================\n";
        for(int i=0; i<totalOfUsers.size();i++){
            cout<<setw(10)<<totalOfUsers[i].userName<<setw(5)<<"|"<<setw(15)<<totalOfUsers[i].password<<setw(5)<<"|"<<setw(15)<<totalOfUsers[i].permission<<endl;
        }
        backToManageUserScreen();
    };

    //Add new user
    auto setPermission=[&](StusersData &user , vector<string> &getPermission){
        char response;
        short totalOfpermission;
        cout<<"Do you want to give access: \n";
        cout<<"Show client list (y/n)? ";
        cin>>response;
        user.p.showList=(response==tolower('y'))?0b0001:0b0000;
        getPermission.push_back(to_string(user.p.showList));
        cout<<"Add new client (y/n)? ";
        cin>>response;
        user.p.addNewClient=(response==tolower('y'))?0b0010:0b0000;
        getPermission.push_back(to_string(user.p.addNewClient));
        cout<<"Delete client (y/n)? ";
        cin>>response;
        user.p.deleteClient=(response==tolower('y'))?0b0100:0b0000;
        getPermission.push_back(to_string(user.p.deleteClient));
        cout<<"Update client (y/n)? ";
        cin>>response;
        user.p.updateClient=(response==tolower('y'))?0b1000:0b0000;
        getPermission.push_back(to_string(user.p.updateClient));
        cout<<"Find client (y/n)? ";
        cin>>response;
        user.p.findClient=(response==tolower('y'))?0b10000:0b0000;
        getPermission.push_back(to_string(user.p.findClient));
        cout<<"Show transactions (y/n)? ";
        cin>>response;
        user.p.transaction=(response==tolower('y'))?0b100000:0b0000;
        getPermission.push_back(to_string(user.p.transaction));
        totalOfpermission = user.p.showList +user.p.addNewClient + user.p.updateClient + user.p.findClient + user.p.deleteClient + user.p.transaction;
        user.permission = to_string(totalOfpermission);
        return user.permission;
    };
    auto searchByUserName=[&](vector<StusersData> searchIn,bool found,int index){
        // this function searching in vector, looking for username
        StusersData user;
        string username;
        cout<<"Search by username before adding the new user: ";
        getline(cin>>ws,username);
        short attempt=1;
        while(attempt <=3){
            for(int i=0; i<searchIn.size();i++){
                if(username == searchIn[i].userName){
                    found=true;
                    index=i;
                    cout << "client with [" << username << "] already exists, please try again." << endl;
                    getline(cin>>ws,username);
                    attempt++;
                }else{
                    cout << "client with [" << username << "] not exists, you can add him/her." << endl;
                    return username;
                }
            }}
    };
    auto savePermissionsToFile=[&](string fileName, vector<string> vectorOfPermissions) {
            fstream myfile;
            myfile.open(fileName,ios::out|ios::app);
            if(myfile.is_open()){
                for(int i=0; i<vectorOfPermissions.size();i++){
                    myfile<<vectorOfPermissions[i]<<"-";
                }
                myfile.close();
            }
    };
    auto addNewUser= [&] (StusersData &user, vector<StusersData> &totalOfUsers, vector<string> &getPermission){
        //The task of this function is to take a user date and save it in a vectore
        char permission;
        char addMore;
        cout<<"Add new user: "<<endl;
        cout<<"Enter userName: ";
        getline(cin>>ws,user.userName);
        getPermission.push_back(user.userName);
        cout<<"Enter password: ";
        cin>>user.password;
        cout<<"Do you want to give full access?(y/n) ";
        cin>>permission;
        if(permission==tolower('y')){
            user.permission = "-1";
            cout<<"User added successfully,";
        }else{
            setPermission(user,getPermission);
        }
        totalOfUsers.push_back(user);
    };
    auto sendUpdatedData=[&](vector<StusersData> sourceVector){
        fstream myfile;
        myfile.open("users.txt",ios::out);
        if(myfile.is_open()){
            for(int i=0; i<totalOfUsers.size();i++){
                myfile<<totalOfUsers[i].userName<<"-";
                myfile<<totalOfUsers[i].password<<"-";
                (totalOfUsers[i].permission=="1")?myfile<<"-1-":myfile<<totalOfUsers[i].permission<<"-";
            }
            myfile.close();
        }
    };

    //Delete user
    auto printOneUserData=[&](vector<StusersData> sourceVector, int index) {
        cout<<setw(10)<<"===============================================================\n";
        cout<<setw(10)<<"User Name"<<setw(15)<<"Password"<<setw(20)<<"Permission";
        cout<<setw(10)<<"\n===============================================================\n";
        cout<<setw(10)<<sourceVector[index].userName<<setw(5)<<"|"<<setw(15)<<sourceVector[index].password<<setw(5)<<"|"<<setw(15)<<sourceVector[index].permission<<endl;
    };
    auto findUserIndexByName=[&](vector<StusersData> &searchIn){
        // this function searching in vector, looking for username
        StusersData user;
        string username;
        getline(cin>>ws,username);
        for(int i=0; i<searchIn.size();i++) {
            if(username == searchIn[i].userName){
                found=true;
                index=i;
                break;
            }
        }
        return found;
    };
    auto saveUpdatedUsersDataToFile=[&] (vector <StusersData>vectorName,string fileName) {
        fstream myfile;
        myfile.open(fileName,ios::out);
        if(myfile.is_open()){
            for(int i=0; i<vectorName.size();i++){
                myfile<<vectorName[i].userName<<"-";
                myfile<<vectorName[i].password<<"-";
                (vectorName[i].permission=="1")?myfile<<"-1-":myfile<<vectorName[i].permission<<"-";
            }
            myfile.close();
        }
    };
    auto deleteUser=[&](vector<StusersData> sourceVector) {
        char answer;
        system("clear");
        cout<<"=========================\n";
        cout<<setw(20)<<"Delete Users Screen \n";
        cout<<"=========================\n";
        cout<<"\nSearch by username before delete the user: ";
        findUserIndexByName(sourceVector);
        if (found) {
            if (sourceVector[index].userName == "admin") {
                cout<<"You can't delete this user"<<endl;
                backToManageUserScreen();
            }
            cout<<"The following are the client details \n";
            printOneUserData(sourceVector,index);
            cout<<"Are you sure you want delete this client? (Y/N): ";
            cin>>answer;
            if (answer== tolower('y')) {
                sourceVector.erase(sourceVector.begin() + index);
                saveUpdatedUsersDataToFile(sourceVector,"users.txt");
                cout<<"User deleted successfully"<<endl;
                backToManageUserScreen();
            }else
            {manageUsers();}
        }else {
            cout<<"User not found"<<endl;
            backToManageUserScreen();
        }
    };

    //Update user
    auto editUser=[&](vector<StusersData> &sourceVector) {
        char answer;
        string newPassword,newPermission;
        system("clear");
        cout<<"=========================\n";
        cout<<setw(20)<<"Update Users Screen \n";
        cout<<"=========================\n";
        cout<<"\nSearch by username before update the user: ";
        findUserIndexByName(sourceVector);
        if (found) {
            cout<<"The following are the client details \n";
            printOneUserData(sourceVector,index);
            cout<<"Are you sure you want update this client? (Y/N): ";
            cin>>answer;
            if (answer== tolower('y')) {
                cout<<"Enter the password: \n";
                cin>>newPassword;
                sourceVector[index].password=newPassword;
              //  getPermission.push_back(sourceVector[index].userName);
                cout<<"Do you want to give full access>(Y/N)? ";
                cin>>answer;
                if (answer==tolower('y')){
                    sourceVector[index].permission="-1";
                    //getPermission.push_back(sourceVector[index].permission);
                }else {
                    getPermission.push_back(sourceVector[index].userName);
                    newPermission = setPermission(user,getPermission);
                    sourceVector[index].permission=newPermission;
                }
                cout<<"User updated successfully"<<endl;
            }
            saveUpdatedUsersDataToFile(sourceVector,"users.txt");
            savePermissionsToFile("userPermission.txt", getPermission);
            manageUsers();
        }
    };

    //Find user
    auto findUser=[&](vector<StusersData> &sourceVector) {
        system("clear");
        cout<<"=========================\n";
        cout<<setw(20)<<"Find Users Screen \n";
        cout<<"=========================\n";
        cout<<"\nEnter user name: ";
        findUserIndexByName(sourceVector);
        if (found) {
            cout<<"The following are the client details \n";
            printOneUserData(sourceVector,index);
            backToManageUserScreen();
        }
    };
        system("clear");
        cout<<"=========================\n";
        cout<<setw(20)<<"Maneging Users Main Screen \n";
        cout<<"=========================\n";
        printf("[1] List User. \n"
        "[2] Add New User.\n"
        "[3] Delete User.\n"
        "[4] Update User.\n"
        "[5] Find User. \n"
        "[6] Main Menu. \n"
        );
        cout<<"=========================\n";
        int response=0;
        cout<<"Select what you want from 1 to 6: ";
        cin>>response;
        switch (response)
        {
            case 1:
                // print users data
            {
                fromFileToVector("users.txt",getData);
                fromVectorToStruct(getData,totalOfUsers);
                printUsers(totalOfUsers);
                break;
            }
            case 2:
                //add new user
            {
                char addMore;
                fromFileToVector("users.txt",getData);
                fromVectorToStruct(getData,totalOfUsers);
                addNewUser(user,totalOfUsers,getPermission);
                sendUpdatedData(totalOfUsers);
                savePermissionsToFile("userPermission.txt", getPermission);
                cout<<"do you want to add more users? Y/N?";
                cin>>addMore;
                if(addMore==tolower('y')){
                    searchByUserName(totalOfUsers,found,index);
                    if (!found) {
                        addNewUser(user,totalOfUsers,getData);
                        sendUpdatedData(totalOfUsers);
                        backToManageUserScreen();
                    }
                }else {
                    manageUsers();
                }
                break;
            }
            case 3: {
                //Delete user
                fromFileToVector("users.txt",getData);
                fromVectorToStruct(getData,totalOfUsers);
                deleteUser(totalOfUsers);
                break;
            }
            case 4: {
                //Edit user
                fromFileToVector("users.txt",getData);
                fromVectorToStruct(getData,totalOfUsers);
                editUser(totalOfUsers);
                break;
            }
            case 5: {
                //Search and find user
                fromFileToVector("users.txt",getData);
                fromVectorToStruct(getData,totalOfUsers);
                findUser(totalOfUsers);
                break;
            }
            case 6:{
                runTheApp();
            }
        }
    };

// End of maneging users
void controlAccessibility(short optionNumber) {
    vector<string> getData;
    vector<string> words;
    vector<string> getPermission;
    short index=0;
    bool found=false, allow=false;
    auto backToMineMenu = [&]{
        char key;
        cout<<"Access Denied,\n";
        cout<<"You Don't Have Permission To Access\n";
        cout<<"Please contact your admin \n";
        cout<<"\n Press any key key to back to previous menu...";
        cin>>key;
        runTheApp();
    };
    auto findUserIndexByName=[&](vector<string> searchIn,bool &found){
        for(int i=0; i<searchIn.size();i++) {
            if(currentUser == searchIn[i]){
                found=true;
                index=i;
               break;
            }
            i+=6;
        }
    };
    fromFileToVector("userPermission.txt",getData);
    findUserIndexByName(getData,found);
    if (found == true && getData[index+optionNumber] =="0" ) {
        backToMineMenu();
    }
}

void runTheApp() {
    vector<string> getData;
    vector<string> newData;
    vector<string> words;
    vector<string> foundUserData;
    vector<stClientsData> totalOfClients;
    int index=0;
    bool found =0;
    stClientsData info;
    StusersData user;
    StusersData data;
    system("clear");
    cout<<"=========================\n";
    cout<<setw(20)<<"Main Menu Screen \n";
    cout<<"=========================\n";
    printf("[1] Show clients list. \n"
    "[2] Add new client.\n"
    "[3] Delete client.\n"
    "[4] Update client.\n"
    "[5] Find client. \n"
    "[6] Transactions. \n"
    "[7] Manage Users.\n"
    "[8] Logout.\n");
    cout<<"=========================\n";
    int response=0;
    cout<<"Select what you want from 1 to 8: ";
    cin>>response;
    switch (response)
    {
    case 1:
    // print clients data
    controlAccessibility(1);
    fromFileToVector("clients.txt",getData);
    fromVectorToStruct(getData,totalOfClients);
    printStruct(totalOfClients);
            backToMainMenu();
        break;
    case 2:
    // Add new client
        {   
        do{
            controlAccessibility(2);
            char response;
            cout<<"\nSearch for account number:" ;
           int findThisAccountNumber =readUserDate();
            fromFileToVector("clients.txt",getData);
            fromVectorToStruct(getData,totalOfClients);
            searchInVector(findThisAccountNumber,totalOfClients,found,index);
            if (found) {
                cout << "client with [" << findThisAccountNumber << "] already exists, please try again. or enter x to back to main menu:";
                cin>>response;
                if(response == tolower('x')) { runTheApp(); }
            } else if (!found) {
                cout << "client with [" << findThisAccountNumber << "] not exists, you can add him/her." << endl;
                clintDataBase("clients.txt",getData,info);
                break;
            }
        }while(found);
         backToMainMenu();
        break;
        }
    case 3:{
        //search than delete user data
        controlAccessibility(3);
        cout<<"\nSearch for account number:" ;
        do {
            char response;
             int findThisAccountNumber =readUserDate();
            fromFileToVector("clients.txt", getData);
            fromVectorToStruct(getData, totalOfClients);
            searchInVector(findThisAccountNumber, totalOfClients, found, index);
            if (!found) {
                cout << "This account number is not exists, please try again: ";
            } else if (found) {
                addFoundUserDataToVector(index, found, totalOfClients, foundUserData);
                deleteUserData(foundUserData, found);
                sendUpdatedData(totalOfClients, newData, index);
                overwriteAllClients("clients.txt", newData);
                break;
            }
        } while (!found);
        backToMainMenu();
        break;
    }
    case 4:{
         //search than edit user data
        controlAccessibility(4);
        cout<<"\nSearch for account number:" ;
         int findThisAccountNumber =readUserDate();
            fromFileToVector("clients.txt",getData);
            fromVectorToStruct(getData,totalOfClients);
            searchInVector(findThisAccountNumber,totalOfClients,found,index);
            addFoundUserDataToVector(index,found, totalOfClients,foundUserData);
            updateUserData(info, foundUserData);
            copyFromEditedVectorToAnotherVector(foundUserData,newData,index);
            sendUpdatedData(totalOfClients,newData,index);
            overwriteAllClients("clients.txt",newData);
            backToMainMenu();
                break;
    }
    case 5:
        {
            controlAccessibility(5);
            cout<<"\nSearch for account number:" ;
            int findThisAccountNumber =readUserDate();
            fromFileToVector("clients.txt",getData);
            fromVectorToStruct(getData,totalOfClients);
            searchInVector(findThisAccountNumber,totalOfClients,found,index);
            addFoundUserDataToVector(index,found, totalOfClients,foundUserData);
            if (found == true) {
                printClientData(totalOfClients, index);
            }
             backToMainMenu();
            break;
        }
    case 6:
            {
             controlAccessibility(6);
            transactionOperations(foundUserData,getData,newData, index,
                 found,totalOfClients);
        backToMainMenu();
        break;
            }
    case 7:
            {
            manageUsers();
            break;
            }
    case 8:
            {
            login();
            }        
    default:
        cout<<"Please select from 1 to 6";
            break;
        };


}
// The next functions for login to the app and validate credentials
void loginScreen(StusersData &data){
    cout<<"-------------------------\n";
    cout<<setw(20)<<"Login Screen\n";
    cout<<"-------------------------\n";
    cout<<"Enter username: ";
    getline(cin>>ws,data.userName);
    currentUser = data.userName;
    cout<<"Enter your password: ";
    getline(cin>>ws,data.password);
}
bool validate_admin_credentials(StusersData &data, vector<string> searchIn){
    // this function searching in vector, looking for admins username and its correct password
    // counter must equals 2 to run the app, 1 for correct username and 1 for correct password
    bool found =0;
    short counter=0;
    for(int x=0;x<searchIn.size();x++){
     (((searchIn[x] == data.userName) || (searchIn[x]==data.password))?counter++:counter);
    }
    return ((counter == 2)?found=true:false);
}
void isCredentialsCorrect(StusersData &data, vector<string> searchIn){
    bool isCorrect=validate_admin_credentials(data, searchIn);
    int attempt=3;
    if (!isCorrect){
        while(attempt >=1){
        cout<<"Wrong password or username, please try again\n";
        cout<<setw(20)<<attempt<<" Attempt Left"<<endl;
            attempt--;
            loginScreen(data);
            if(validate_admin_credentials(data, searchIn) == true){
                runTheApp();
                break;
                }else{
                    continue;
                }
    }
    }
    else{
       runTheApp();
    }
}
// The ends of the functions of login to the app and validate credentials

void login(){
    system("clear");
    vector<string> getUsersData;
    StusersData data;
    loginScreen(data);
    fromFileToVector("users.txt", getUsersData);
    validate_admin_credentials(data,getUsersData);
    isCredentialsCorrect(data,getUsersData);
}
int main() {
    login();
    return 0;
}