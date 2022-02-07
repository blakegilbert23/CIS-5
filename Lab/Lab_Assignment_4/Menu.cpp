/*
 * File:   main.cpp
 * Author: Blake Gilbert
 * Created on January 19th, 2022, 10:51 AM
 * Purpose:  Basic Menu with Functions for exams and homework
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <iomanip>   //Format Library
#include <string>    //String Library
#include <vector>    //Vector Library
#include <algorithm> //Algorithm Library
#include <cmath>     //Math Library
using namespace std; //STD Name-space where Library is compiled

//User Libraries

//Global Constants not Variables
//Math/Physics/Science/Conversions/Dimensions
const float PI             = 4 * atan(1);  //Pi equation
const float RADCNV         = PI / 180;     //convert from degrees to radians
const float GRMCONV        = 45359.2;      //convert to grams
const unsigned char PERCNV = 100;          //convert to percentage

//Function Prototypes
void prob0();
void prob1();
void prob2();
void prob3();
void prob4();
void prob5();
void prob6();
void prob7();
void prob8();
void prob9();

//Code Begins Execution Here with function main
int main(int argc, char** argv) {
    //Set random number seed once here

    //Declare variables here
    int choose;//Choose a problem

    //Initialize variables here
    do{
        cout<<"Choose from the following Menu Items"<<endl;
        cout<<"Problem 0"<<endl;
        cout<<"Problem 1"<<endl;
        cout<<"Problem 2"<<endl;
        cout<<"Problem 3"<<endl;
        cout<<"Problem 4"<<endl;
        cout<<"Problem 5"<<endl;
        cout<<"Problem 6"<<endl;
        cout<<"Problem 7"<<endl;
        cout<<"8 or greater, all negatives to exit"<<endl;
        cin>>choose;

        switch(choose){
            case 0:prob0();break;
            case 1:prob1();break;
            case 2:prob2();break;
            case 3:prob3();break;
            case 4:prob4();break;
            case 5:prob5();break;
            case 6:prob6();break;
            case 7:prob7();break;
            default:cout<<"Exiting the Menu"<<endl;
        }

        cout<<endl<<endl;
    }while(choose>=0 && choose<=9);

    return 0;
}

void prob0(){
    //Declare  Variables here
    string name1, name2, name3; //user-entered names
    vector<string> allNmes;     //array containing all names

    //Initialize Variables here
    cout << "Sorting Names" << endl;
    cout << "Input 3 names" << endl;
    cin >> name1 >> name2 >> name3;
    //push user inputs into array that stores all names
    allNmes.push_back(name1);
    allNmes.push_back(name2);
    allNmes.push_back(name3);

    //Map inputs/knowns to the output
    sort(allNmes.begin(), allNmes.end());

    //loop through array containing all names and output them to the console.
    //remove endline from final output
    for (int i = 0; i < allNmes.size(); i++)
    {
        i != (allNmes.size() - 1)
            ? cout << allNmes[i] << endl
            : cout << allNmes[i];
    }
}

void prob1(){
    //Declare  Variables here
    int
        bksPrch, //books purchased
        ttlPnts; //total points

    //Initialize Variables here
    cout << "Book Worm Points" << endl;
    cout << "Input the number of books purchased this month." << endl;
    cin >> bksPrch;
    ttlPnts = 0;

    //Map inputs/knowns to the output
    // detmerine points based on books purchased
    ttlPnts = bksPrch == 0 ? 4 :
              bksPrch == 1 ? 5 :
              bksPrch == 2 ? 15 :
              bksPrch == 3 ? 30 : 60;

    //Display Output
    cout << "Books purchased = " << setw(2) << bksPrch << endl;
    cout << "Points earned   = " << setw(2) << ttlPnts;
}

void prob2(){
    //Declare  Variables here
    int
        balFee,  //fee is balance is below $400
        mnthFee, //monthly fee
        chkCnt;  //check count
    float
        feeRate, //fee rate
        chkFee,  //check fee
        strtBal, //starting balance
        crrtBal; //starting balance

    //Initialize Variables here
    cout << "Monthly Bank Fees" << endl;
    cout << "Input Current Bank Balance and Number of Checks" << endl;
    cin >> strtBal >> chkCnt;
    if (strtBal < 0) cout << "Account is overdrawn" << endl; //display overdraft warning if account is below zero
    mnthFee = 10; //monthly fee

    //Map inputs/knowns to the output
    balFee = strtBal < 400 ? 15 : 0; //add $15 to the service fee if user has a balance of less than $400
    //calculate fee rate based on checks written
    feeRate = chkCnt < 20                  ? 0.10 :
              chkCnt >= 20 && chkCnt <= 39 ? 0.08 :
              chkCnt >= 40 && chkCnt <= 59 ? 0.06 : 0.04;
    chkFee  = feeRate * chkCnt; //find the check fee
    crrtBal = strtBal - mnthFee - balFee - chkFee;  //find currnent balance

    //Display Output
    cout << fixed << setprecision(2) << showpoint;
    cout << "Balance     $" << setw(9) << strtBal << endl;
    cout << "Check Fee   $" << setw(9) << chkFee << endl;
    cout << "Monthly Fee $" << setw(9) << static_cast<float>(mnthFee) << endl;
    cout << "Low Balance $" << setw(9) << static_cast<float>(balFee) << endl;
    cout << "New Balance $" << setw(9) << crrtBal;
}

void prob3(){
    //Declare  Variables here
    string r1Name, r2Name, r3Name;
    string fName, sName, tName;
    int r1Time, r2Time, r3Time;
    int fTime, sTime, tTime;
    vector<int> allTmes;

    //Initialize Variables here
    cout << "Race Ranking Program" << endl;
    cout << "Input 3 Runners" << endl;
    cout << "Their names, then their times" << endl;
    cin >> r1Name >> r1Time;
    cin >> r2Name >> r2Time;
    cin >> r3Name >> r3Time;
    //push runners time into an array
    allTmes.push_back(r1Time);
    allTmes.push_back(r2Time);
    allTmes.push_back(r3Time);
    //sort array by fastest speed
    sort(allTmes.begin(), allTmes.end());

    //Map inputs/knowns to the output
    //sort runners by time
    fName = allTmes[0] == r1Time ? r1Name :
            allTmes[0] == r2Time ? r2Name : r3Name;
    sName = allTmes[1] == r1Time ? r1Name :
            allTmes[1] == r2Time ? r2Name : r3Name;
    tName = allTmes[2] == r1Time ? r1Name :
            allTmes[2] == r2Time ? r2Name : r3Name;
    //match runners time with runners name
    fTime = fName == r1Name ? r1Time :
            fName == r2Name ? r2Time : r3Time;
    sTime = sName == r1Name ? r1Time :
            sName == r2Name ? r2Time : r3Time;
    tTime = tName == r1Name ? r1Time :
            tName == r2Name ? r2Time : r3Time;

    //Display Output
    cout << fName << "\t" << setw(3) << fTime << endl;
    cout << sName << "\t" << setw(3) << sTime << endl;
    cout << tName << "\t" << setw(3) << tTime;
}

void prob4(){
    //Declare  Variables here
    char pckge;
    float hours, bill, ot;

    //Initialize Variables here
    cout << "ISP Bill" << endl;
    cout << "Input Package and Hours" << endl;
    cin >> pckge >> hours;

    //Map inputs/knowns to the output
    //calculate bill based on package and hours used
    switch(pckge){
        case 'A': bill = hours > 10 ?  9.95 + ((hours - 10) * 2.00) :  9.95; break;
        case 'B': bill = hours > 20 ? 14.95 + ((hours - 20) * 1.00) : 14.95; break;
        default: bill = 19.95;
    }

    //Display Output
    cout << fixed << setprecision(2);
    cout << "Bill = $" << setw(6) << bill;
}

void prob5(){
    //Declare  Variables here
    char
        rck,    //choice option
        ppr,    //choice option
        scr,    //choice option
        p1Chce, //player1 guess
        p2Chce; //player2 guess
    string
        rckWins, //message when rock wins
        pprWins, //message when paper wins
        scrWins, //message when scissor wins
        tieGame, //output message when game ties
        outcome; //outcome of game

    //Initialize Variables here
    cout << "Rock Paper Scissors Game" << endl;
    cout << "Input Player 1 and Player 2 Choices" << endl;
    cin >> p1Chce >> p2Chce;
    //convert letters to game options
    rck = 'r';
    ppr = 'p';
    scr = 's';
    //game outcomes
    rckWins = "Rock breaks scissors.";
    pprWins = "Paper covers rock.";
    scrWins = "Scissors cuts paper.";
    tieGame = "It's a tie.";

    //Map inputs/knowns to the output
    //determine outcome of game
    switch (tolower(p1Chce)) {
        case 'r': outcome = tolower(p2Chce) == rck ? tieGame :
                            tolower(p2Chce) == ppr ? pprWins : rckWins; break;
        case 'p': outcome = tolower(p2Chce) == rck ? pprWins :
                            tolower(p2Chce) == ppr ? tieGame : scrWins; break;
        case 's': outcome = tolower(p2Chce) == rck ? rckWins :
                            tolower(p2Chce) == ppr ? scrWins : tieGame; break;
    }

    //Display Output
    cout << outcome;
}

void prob6(){
    //Declare  Variables here
    int n1000s, n100s, n10s, n1s;
    unsigned short arabic;
    string roman = "";

    //Initialize Variables here
    cout<<"Arabic to Roman numeral conversion." << endl;
    cout<<"Input the integer to convert." << endl;
    cin >> arabic;
    //convert digits
    n1000s = arabic / 1000;
    n100s  = (arabic - n1000s * 1000) / 100;
    n10s   = arabic % 100/ 10;
    n1s    = arabic % 10;

    //Map inputs/knowns to the output
    //convert the 1000s
    switch(n1000s){
        case 3: roman += "M";
        case 2: roman += "M";
        case 1: roman += "M";
    }
    //convert the 100s
    switch(n100s){
        case 9: {
            roman += "C";
            roman += "M";
            break;
        }
        case 8: case 7: case 6: {
            roman += "D";
            for (int i = 0; i < n100s - 5; i++) roman += "C";
            break;
        }
        case 5: {
            roman += "D";
            break;
        }
        case 4: {
            roman += "C";
            roman += "D";
            break;
        }
        case 3: case 2: case 1: {
            for (int i = 0; i < n100s; i++) roman += "C";
            break;
        }

    }
    //convert the 10s
     switch(n10s){
        case 9: {
            roman += "X";
            roman += "C";
            break;
        }
        case 8: case 7: case 6: {
            roman += "L";
            for (int i = 0; i < n10s - 5; i++) roman += "X";
            break;
        }
        case 5: {
            roman += "L";
            break;
        }
        case 4: {
            roman += "X";
            roman += "L";
            break;
        }
        case 3: case 2: case 1: {
            for (int i = 0; i < n10s; i++) roman += "X";
            break;
        }
    }
    //convert the 1s
    switch(n1s){
        case 9: {
            roman += "I";
            roman += "X";
            break;
        }
        case 8: case 7: case 6: {
            roman += "V";
            for (int i = 0; i < n1s - 5; i++) roman += "I";
            break;
        }
        case 5: {
            roman += "V";
            break;
        }
        case 4: {
            roman += "I";
            roman += "V";
            break;
        }
        case 3: case 2: case 1: {
            for (int i = 0; i < n1s; i++) roman += "I";
            break;
        }
    }

    //Display Output
    arabic < 1000 || arabic > 3000
        ? cout << arabic << " is Out of Range!"
        : cout << arabic << " is equal to " << roman;
}

void prob7(){
    //Declare  Variables here
    string sign1, sign2, type1, type2;

    //Initialize Variables here
    cout << "Horoscope Program which examines compatible signs." << endl;
    cout << "Input 2 signs." << endl;
    cin >> sign1 >> sign2;

    //Map inputs/knowns to the output
    //find type of sign 1
    type1 = (sign1 == "Aries"  || sign1 == "Leo"     || sign1 == "Sagittarius")   ? "Fire" :
            (sign1 == "Taurus" || sign1 == "Virgo"   || sign1 == "Capricorn")     ? "Earth":
            (sign1 == "Gemini" || sign1 == "Libra"   || sign1 == "Aquarius")      ? "Air"  : "Water";
    //find type of sign 2
    type2 = (sign2 == "Aries"  || sign2 == "Leo"     || sign2 == "Sagittarius")   ? "Fire" :
            (sign2 == "Taurus" || sign2 == "Virgo"   || sign2 == "Capricorn")     ? "Earth":
            (sign2 == "Gemini" || sign2 == "Libra"   || sign2 == "Aquarius")      ? "Air"  : "Water";

    //Display Output
    type1 == type2
        ? cout << sign1 << " and " << sign2 << " are compatible " << type1 << " signs."
        : cout << sign1 << " and " << sign2 << " are not compatible signs.";
}

