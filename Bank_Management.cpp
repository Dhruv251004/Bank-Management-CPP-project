//Author->Dhruv Verma
//Bank Managment System
//2 July 2023
//15 july 2023

#include <bits/stdc++.h>
#include<cstdio>
using namespace std;
typedef long long int ll;


//To check whether the account exist with help of file
bool file_exist(string path){
    ifstream inn(path);
    string s="";
    getline(inn,s);
    inn.close();
    if(s==""){
        return false;
    }
    return true;
}


class Bank
{
    public:
    string IFSC_Code="YMCA741235";
};


class customer:public Bank
{
    //User Details
    protected:
    string name;
    int age;
    string address;
};


//MAIN
class Account :protected customer 
{
    string Account_Number;
    ll balance;

    public:

    string file_name;
    string balance_file_name;
    friend void transfer_money(Account*user1,Account*user2,ll amount);

    //Constructor
    Account(string acc_no)
    {
        cout<<"Enter name : ";
        getline(cin,this->name);
        cout<<"Enter age : ";
        cin>>this->age;
        getchar();
        cout<<"Enter address : ";
        getline(cin,this->address);
        this->Account_Number=acc_no;
        this->balance=0;

        //Creating Account files
        this->file_name = "Transaction_history_" + this->Account_Number +".txt";
        this->balance_file_name="Balance_"+ this->Account_Number+".txt";

        //Transaction file
        ofstream out("Transaction_history_" + this->Account_Number +".txt");
        out<<acc_no<<endl<<name<<endl<<to_string(age)<<endl<<address<<endl;
        out.close();

        //Balance file
        ofstream out2("Balance_"+this->Account_Number+".txt");
        out<<to_string(balance);
        out2.close();

        //Account created
        cout<<endl<<endl<<"Your Account has been created successfully"<<endl;
    }

    //Constructor with file

    Account(string path,unordered_map<string,bool>&ALL_ACCOUNT_NO,unordered_map<string,Account*>&ALL_ACCOUNTS){

        //Accessing Account details from file
        ifstream in(path);
        getline(in,Account_Number);
        getline(in,name);
        string temp_age;
        getline(in,temp_age);
        if(temp_age!="")
        this->age=stoi(temp_age);
        getline(in,address);
        in.close();
        ALL_ACCOUNT_NO[this->Account_Number]=true;
        ALL_ACCOUNTS[this->Account_Number]=this;
        in.close();

        //Accessing balance from file
        ifstream in2("Balance_" + this->Account_Number+".txt");
        string temp_bal;
        getline(in2 ,temp_bal);
        if(temp_bal!="")
        this->balance=stoi(temp_bal);
        else
        this->balance=0;
        in2.close();
    }


    //To show all account details

    void show_details()
    {
        cout<<endl<<"*************************************************************"<<endl<<endl;
        cout<<"Name              : "<<this->name<<endl;
        cout<<"Age               : "<<this->age<<endl;
        cout<<"Address           : "<<this->address<<endl;
        cout<<"Account Number    : "<<this->Account_Number<<endl;
        cout<<"IFSC Code         : "<<this->IFSC_Code<<endl;
        cout<<"Balance           : "<<this->balance<<endl;
        cout<<endl<<"*************************************************************"<<endl<<endl;
    }


    //Deposit money in account

    ll deposit_money(ll amount)
    {
        this->balance+=amount;

        //Writing transaction in file
        ofstream out("Transaction_history_"+this->Account_Number+".txt",ios::app);   
        string deposit="Succesfully deposited Rs." + to_string(amount)+"_____"+__DATE__+" "+__TIME__;
        cout<<endl<<"*************************************************************"<<endl<<endl;
        cout<<deposit<<endl;
        cout<<"Current balance : Rs."<<balance;
        cout<<endl<<endl<<"*************************************************************"<<endl<<endl;
        out<<"Deposited Rs."<<to_string(amount)+"_____"+__DATE__+" "+__TIME__<<endl;
        out.close();

        //Updating balance file
        ofstream outy("Balance_"+this->Account_Number+".txt");
        outy<<balance;
        outy.close();
        return balance;
    }


    //Withdraw money from the account

    ll withdraw_money(ll amount)
    {
        ofstream out("Transaction_history_"+this->Account_Number+".txt",ios::app);   

        //Check for available balance
        if(balance<amount)
        {
            cout<<endl<<"******************************************************************************************"<<endl<<endl;
            cout<<"WARNING :: Not enough balance"<<endl<<endl;
            cout<<"******************************************************************************************"<<endl<<endl;
            out.close();
        }
        else
        {
            balance-=amount;

            //Writing transaction in file
            string transc="Withdrew Rs." + to_string(amount)+"_____"+__DATE__+" "+__TIME__;
            cout<<endl<<"*************************************************************"<<endl<<endl;
            cout<<transc<<endl;
            cout<<"Current balance : Rs."<<balance;
            cout<<endl<<endl<<"*************************************************************"<<endl<<endl;
            out<<transc<<endl;
            out.close();

            //Updating balance file
            ofstream outy("Balance_"+this->Account_Number+".txt");
            outy<<balance;
            outy.close();
            return balance;
        }
     }

     //Check for available balance

     ll available_balance()
    {
        cout<<endl<<"*************************************************************"<<endl<<endl;
        cout<<"Your account balance : Rs."<<this->balance;
        cout<<endl<<endl<<"*************************************************************"<<endl<<endl;
        return this->balance;
    }

     //View all transaction histor

     bool view_transaction_history(){
        string trs;
        stack<string>history;

        //Discarding first five lines which contains account details
        ifstream in("Transaction_history_"+this->Account_Number+".txt");
        for (int i = 0; i < 4; i++)
        {
            getline(in,trs);
        }
        
        //Pushing transaction details into stack
        while (in.eof()==0)
        {
            getline(in,trs);
            if(trs!="")
            history.push(trs);
        }

        //Accessinf details from stack
        cout<<endl<<endl<<"***********************************Transaction History***********************************"<<endl<<endl;
        if(history.empty())
        {
            cout<<"Nothing to show"<<endl<<endl;
        }
        while(!history.empty())
        {
            cout<<history.top()<<endl;
            history.pop();
        }
        cout<<endl<<endl<<"*****************************************************************************************"<<endl<<endl;
        in.close();
     }

     //Debit money to transfer

     ll debit_money(ll amount)
    {

        //Checking for available balance
        if(this->balance<amount){
            return -1;
        }

        //Deducting money
        this->balance=this->balance-amount;

        //Writing transaction in file
        ofstream out("Transaction_history_" + this->Account_Number +".txt",ios::app);   
        out<<"Debited Rs."+to_string(amount)+"_____"+__DATE__+" "+__TIME__<<endl<<endl;
        out.close();

        //Updating balance
        ofstream outy("Balance_"+this->Account_Number+".txt");
        outy<<balance;
        outy.close();

        //Printing on screen
        cout<<endl<<"***********************************************************************************************"<<endl<<endl;
        cout<<"Debited Rs."+to_string(amount)<<" from your account "<<endl;
        cout<<"Current balance Rs."<<this->balance<<endl<<endl;
        cout<<"***********************************************************************************************"<<endl<<endl;
        return this->balance;
     }

     //Credit money from another account

    ll credit_money(ll amount)
    {
        this->balance+=amount;

        //Writing transaction in file
        ofstream out("Transaction_history_" + this->Account_Number +".txt",ios::app);   
        out<<"Credited Rs."+to_string(amount)+"_____"+__DATE__+" "+__TIME__<<endl;
        out.close();

        //Updating Balance file
        ofstream out2("Balance_"+this->Account_Number+".txt");
        out2<<balance;
        out2.close();
        
        //Printing on screen
        cout<<endl<<"***********************************************************************************************"<<endl<<endl;
        cout<<"Credited Rs."<<amount<<" to account number "<<this->Account_Number<<endl<<endl;
        cout<<"***********************************************************************************************"<<endl<<endl;
        return this->balance;
     }

     //Destructor to delete account

     ~Account()
    {
        cout<<endl<<endl<<"Withdrew Rs."<<balance<<endl;
        cout<<endl<<endl<<"******************************ACCOUNT DELETED SUCCESSFULLY******************************"<<endl<<endl;  
    }

};

//Generating a random account number for the user

string generate_acc_no( unordered_map<string,bool>&ALL_ACCOUNT_NO,unordered_map<string,Account*>&ALL_ACCOUNTS){
    label:
    ll random_acc1=rand()%(99999999-1000 +1)+1991;
    ll random_acc2=rand()%(99999999-1000 +1)+1721;
    string ac_no=to_string(random_acc1*random_acc2);

    //If already an account exist with this number
    //In map
    if(ALL_ACCOUNT_NO[ac_no])
    {
        goto label;
    }

    //In file
    else if(file_exist("Transaction_history_"+ac_no+".txt"))
    {
            Account*existing_acc=new Account("Transaction_history_"+ac_no+".txt",ALL_ACCOUNT_NO,ALL_ACCOUNTS);
            goto label;
    }

    //If does not exist
    else
    {
        ALL_ACCOUNT_NO[ac_no]=true;
        return ac_no;
    }
};


//Transfer money from one account to another
void transfer_money(Account*user1,Account*user2,ll amount){
    ll debit=user1->debit_money(amount);

    //if available balance < transferring amount
    if(debit==-1)
    {
        cout<<"WARNING :: Insufficient balance"<<endl;
        cout<<endl<<"******************************************Cancelled******************************************"<<endl;
        return;
    }

    //if not
    user2->credit_money(amount);
}


//Finding user account
Account*find_acc(unordered_map<string,bool>&ALL_ACCOUNT_NO,unordered_map<string,Account*>&ALL_ACCOUNTS,int user=1)
{
        string accno;
        if(user==1){
            cout<<"Enter your Account Number : ";
        }
        else{
            cout<<"Enter the recipient Account number : ";
        }
        cin>>accno;

        //Finding in maps
        if(ALL_ACCOUNT_NO[accno]){
            return ALL_ACCOUNTS[accno];
        }

        //Finding in files
        else if(file_exist("Transaction_history_"+accno+".txt"))
        {
            Account*existing_acc=new Account("Transaction_history_"+accno+".txt",ALL_ACCOUNT_NO,ALL_ACCOUNTS);
            return ALL_ACCOUNTS[accno];
        }

        //If not found
        return NULL;
}


//Deleting an account
bool acc_termination(unordered_map<string,bool>&ALL_ACCOUNT_NO,unordered_map<string,Account*>&ALL_ACCOUNTS,Account*user){

    //Taking confirmation
    string confirm;
    cout<<"Are you sure you want to delete your account permanently [YES/NO] : ";
    confirmation:
    cin>>confirm;
    transform(confirm.begin(),confirm.end(),confirm.begin(),::toupper);


    if(confirm=="YES")
    {
            string user_acc_no;
            cout<<"Enter your account number again : ";
            cin>>user_acc_no;

            //Removing from saved accounts
            ALL_ACCOUNT_NO[user_acc_no]=false;
            ALL_ACCOUNTS[user_acc_no]=NULL;

            //Removing transaction file
            string f1="Transaction_history_"+user_acc_no + ".txt";
            int res1=remove(f1.c_str());
            if(res1==0 )
            {
                //Removing balance file    
                string f2="Balance_"+user_acc_no+".txt";
                int res2=remove(f2.c_str());
                if(res2==0)
                {
                    delete user;
                }
                else
                {
                    cout<<"couldn't delete the file"<<endl;
                }
            }
            else if(confirm=="NO")
            {
                cout<<endl<<endl<<"******************************STOPPED ACCOUNT DELETION******************************"<<endl<<endl;
            }
    else
    {
        cout<<"Enter a valid input : ";
        goto confirmation;
    }
    }   
}


//Check whether the account number is valid or not
bool validate_acc(Account*user){
    if(user!=NULL)
    {
            return true;
    }
    else
    {
        cout<<"WARNING :: No account exist with this account number"<<endl<<endl;
        return false;
    }
}


int main()
{

    //Main menu
    cout<<"*********************************************************************************************************************************************************************************"<<endl<<endl<<endl;
    cout<<setw(90)<<"WELCOME !"<<endl<<endl;
    cout<<setw(95)<<"ACC RC BANK SERVICES"<<endl;
    cout<<endl<<endl<<"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/";
    cout<<endl<<endl<<setw(5)<<":: Main Menu ::";
    cout<<endl<<"1. Open New Account";
    cout<<endl<<"2. Show All Account details";
    cout<<endl<<"3. View Balance";
    cout<<endl<<"4. Deposit Money";
    cout<<endl<<"5. Withdraw Money";
    cout<<endl<<"6. Transfer Money";
    cout<<endl<<"7. Show Transaction History";
    cout<<endl<<"8. Terminate Account";
    cout<<endl<<"9. Exit"<<endl;


    //Map to store all accounts
    unordered_map<string,bool>ALL_ACCOUNT_NO;
    unordered_map<string,Account*>ALL_ACCOUNTS;
    srand(time(NULL));


    //Program starts
    start:
    cout<<endl<<"Enter your choice : ";
    int choice;
    cin>>choice;
    getchar();

    //Open new Account
    if(choice==1)
    {

        string acc_no=generate_acc_no(ALL_ACCOUNT_NO,ALL_ACCOUNTS);

        Account*new_acc=new Account(acc_no);

        if(new_acc==NULL)
        {
            cout<<endl<<"***********************************************************"<<endl<<endl;
            cout<<"Error !"<<endl<<endl;
            cout<<"***********************************************************"<<endl<<endl;
        }
        ALL_ACCOUNTS[acc_no]=new_acc;
        new_acc->show_details();
       
    }

    //Show All Account details
    else if(choice==2)
    {

        Account*user=find_acc(ALL_ACCOUNT_NO,ALL_ACCOUNTS);

        //if Account exist
        if(validate_acc(user))
        {
            user->show_details();
        }
    }

    //View Available Balance
    else if(choice==3)
    {

        Account*user=find_acc(ALL_ACCOUNT_NO,ALL_ACCOUNTS);

         if(validate_acc(user))
        {
            user->available_balance();
        }

    }

    //Deposit money in account
    else if(choice==4)
    {

        Account*user=find_acc(ALL_ACCOUNT_NO,ALL_ACCOUNTS);

        if(validate_acc(user))
        {
            cout<<"Enter the amount you want to deposit : ";
            ll amount;
            cin>>amount;
            user->deposit_money(amount);    
        }
    }

    //Withdraw money from account
    else if(choice==5)
    {

        Account*user=find_acc(ALL_ACCOUNT_NO,ALL_ACCOUNTS);

         if(validate_acc(user))
         {
            cout<<"Enter the amount you want to withdraw : ";
            ll amount;
            cin>>amount;
            user->withdraw_money(amount);
        }
    }



    //Transfer from one account to another
    else if(choice==6)
    {

        Account*user1=find_acc(ALL_ACCOUNT_NO,ALL_ACCOUNTS);
        Account*user2=NULL;

        if(validate_acc(user1) )
        {
            user2=find_acc(ALL_ACCOUNT_NO,ALL_ACCOUNTS,2);
            if(validate_acc(user2))
            {
                ll amount;
                cout<<"Enter the amount to transfer : ";
                cin>>amount;
                transfer_money(user1,user2,amount);
            }
        }
    }

    //View Transaction history
    else if(choice==7)
    {

        Account*user=find_acc(ALL_ACCOUNT_NO,ALL_ACCOUNTS);

         if(validate_acc(user))
        {
            user->view_transaction_history();
        }
    }

    //Deleting Account
    else if(choice==8)
    {

        Account*user=find_acc(ALL_ACCOUNT_NO,ALL_ACCOUNTS);
        
        if(validate_acc(user))
        {
            acc_termination(ALL_ACCOUNT_NO,ALL_ACCOUNTS,user);
        }
    }

    //Program ends
    else if(choice==9)
    {
        cout<<endl<<"*****************************************Thankyou*****************************************"<<endl<<endl;
    }

    //No valid Input
    else
    {
        cout<<endl<<"*****************************************Invalid Input*****************************************"<<endl;
    }

    //Ask for choice again
    goto start;
    return 0;
}