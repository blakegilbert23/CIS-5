/*
 * File:   main.cpp
 * Author: Blake Gilbert
 * Created on January 25, 2022, 5:00 AM
 * Purpose: Play a game of blackjack against the house (computer)
 *
 */

//System Level Libraries
#include <iostream>  //Input-Output Library
#include <iomanip>   //Format Library
#include <string>    //String Library
#include <cmath>     //Math Library
#include <fstream>   //File IO Library
#include <iomanip>   //Format Library
#include <vector>    //Vector Library
#include <algorithm> //Vector Library
using namespace std;

//User Defined Libraries go here

//Global CONSTANTS (not global VARIABLES) go here (constants from Physics, Chemistry, Engineering, and Conversions between systems of units)
const unsigned short PERCNV = 100; //convert to percentage

//Function Prototypes go here
bool playAnotherHand(float, float);
int  buyChips(int &, int &);
void bet(int &, int &);
void compareCards(int, int, int, int &, float &, float &);
void displayFinal(int, int);
void fillSuit(int []);
void fillSuit(vector<int>);
void inputFromFile();
void outputToFile(int);
void printInstructions();
void resultsTable();

//Execution begins here
int main(int argc, char **argv) {
    //Initialize Random Seed once here
    srand(static_cast<unsigned int>(time(0)));

    //consts
    static int suitSz = 14; //number of cards in a suit

    //Declare  Variables here
    bool
        again; //used to play another hand
    char
        pDraw, //player chooses whether to draw another card
        dDraw, //dealer chooses whether to draw another card
        cont ; //used to continue on
    unsigned short
        newCard, //value of new card
        pCount,  //number player has
        dCount;  //number computer has
    int
        pStack, //amount of money player has
        pBet,   //amount of money player is betting
        start,  //amount of money player started with
        rsult;  //amount of money player won
    float
        pWin , //how many times the player has won
        dWin ; //how many times the dealer has won
    int
        allHrts[suitSz], //all hearts
        allSpds[suitSz]; //all spades
    vector<int>
        allClbs, //all clubs
        allDmnd; //all diamonds

    //assign known variables here
    pWin=dWin=1;

    //fill deck
    fillSuit(allHrts); //fill all hearts
    fillSuit(allSpds); //fill all spades
    fillSuit(allClbs); //fill all clubs
    fillSuit(allDmnd); //fill all diamonds

    //initial game setup
    inputFromFile();                  // input information from other file
    printInstructions();              // instructions
    pStack = buyChips(pStack, start); // enter initial money

    //actual game
    do {
        //bet
        bet(pStack, pBet);

        //initial card values
        pCount = rand() % 11 + 1; //add random card to players hand
        pCount = rand() % 10 + 1; //add random card to players hand
        dCount = rand() % 11 + 1; //other card gets revealed later

        //player's turn
        do {
            //prompt player to draw new card
            cout << "Chips remaining: $" << pStack << endl;
            cout << "Current bet: $"     << pBet   << endl;
            cout << "Player count: "     << pCount << endl;
            cout << "Dealer count: "     << dCount << endl;
            cout << endl;
            cout << "Do you want to draw another card?"    << endl;
            cout << "Press 'y' for yes; press 'n' for no." << endl;
            cout << "Then, press 'enter to continue."      << endl;
            cin  >> pDraw;
            cout << endl;
            //add new card if player chooses yes
            if  (pDraw == 'y')   pCount += rand() % 11 + 1;
        } while (pDraw == 'y' && pCount < 21);

        //computer's turn
        if (pCount > 21) {
            cout << "Player busted." << endl; //game is over if player goes over 21
            dWin++; //increase dealer's wins
            cout << endl;
        }
        else {
            //dealer flips other card
            cout   << "Dealer flips other card"   << endl;
            dCount += rand() % 11 + 1; //reveal dealer's other card
            cout   << "Dealer now has " << dCount << endl;
            cout   << endl;
            //dealer continues to draw if they have less than 17; dealer must stay if they have 17 or higher

            if (dCount < 17) {
                while (dCount < 17) {
                    cout    << "Dealer draws another card." << endl;
                    cout    << endl;
                    dCount  += rand() % 11 + 1; //dealer draws another card
                    cout    << "Dealer now has " << dCount  << endl;
                    cout    << endl;
                    cout    << "To continue, press any key" << endl;
                    cout    << "Then, press 'enter'"        << endl;
                    cin     >> cont;
                    cout    << endl;
                }
                if (dCount > 21) {
                    cout   << "Player wins. Dealer busted." << endl;
                    pWin++; //increase player wins
                    cout   << endl;
                }
            }
            else cout << "Dealer has " << dCount << " and must stay." << endl << endl;

            //compare player cards to dealer cards to see who wins
            compareCards(pCount, dCount, pBet, pStack, pWin, dWin);
        }

        //ask if player wants to play another hand
        again = playAnotherHand(pWin, dWin);

    } while (again);

    //end of game
    displayFinal(pStack, start); // display final winnings/losses
    resultsTable();              // display results table
    outputToFile(pStack);        // output final stack to other file

    //Exit the program
    return 0;
}

//play another hand
bool playAnotherHand(float pWin=1, float dWin=1) {
    char cont;
    cout << "Play another hand?"                   << endl;
    cout << "Your chance of winning is " << fixed << setprecision(2) << (pWin/(pWin + dWin)) * PERCNV << "%" << endl;
    cout << "Press 'y' for yes; press 'n' for no." << endl;
    cout << "Then, press 'enter to continue."      << endl;
    cin  >> cont;
    cout << endl;
    switch (cont) {
        case 'y': return true ; break;
        case 'n': return false; break;
        default : return false; break;
    }
}

//buy intitial chips
int buyChips(int &pStack, int &start) {
    cout  << "How many chips are you starting with?" << endl; //prompt the player to input starting money
    cout    << "Enter a number between 0-1000." << endl;
    cin   >> pStack;
    cout  << endl;
    if (pStack>=0 && pStack<=1000) {
        start  = pStack;
        return pStack;
    }
    else {
        cout << "That number is not between 0-1000. You are clearly not taking this seriously. Goodbye." << endl;
        exit(0);
    }
}

//bet
void bet(int &pStack, int &pBet) {
    cout    << "Chips remaining: $" << pStack << endl;
    cout    << "How much do you want to bet?" << endl;
    cin     >> pBet;
    cout    << endl;
    pStack  -= pBet;
    if (pStack < 0)  cout << "You're spending money that you don't have. That's a self-destructive habit." << endl;
    if (pStack == 0) cout << "You have $0 left. Be careful" << endl;
}

//compare cards at end of round
void compareCards(int pCount, int dCount, int pBet, int &pStack, float &pWin, float &dWin) {
    if (pCount > dCount || dCount > 21) {
        cout   << "Player wins."   << endl;
        pWin++;
        cout   << "Player gains $"    << pBet       << endl;
        pStack += (pBet * 2);
        cout   << "Chips remaining: $" << pStack    << endl;
        cout   << endl;
    }
    else if (dCount > pCount && dCount <= 21 || pCount > 21) {
        cout   << "Dealer wins"   << endl;
        dWin++;
        cout   << "Player loses $"     << pBet      << endl;
        cout   << "Chips remaining: $" << pStack    << endl;
        cout   << endl;
    }
    else {
        cout    << "It's a tie hand."    << endl;
        cout    << "Player loses $" << 0 << endl;
        pStack += pBet;
        cout    << "Chips remaining: $" << pStack << endl;
        cout    << endl;
    }
}

//display final results
void displayFinal(int pStack, int start) {
    float final = abs(static_cast<float>(pStack)) - abs(static_cast<float>(start));
    pStack >= start
            ? cout << "You won $"  << fixed << setprecision(2) << showpoint << final << "! Nice!"                  << endl << endl
            : cout << "You lost $" << fixed << setprecision(2) << showpoint << final << ". Better luck next time!" << endl << endl;;
}

//fill the deck with all cards in one suit (arrays)
void fillSuit(int arr[]){
    //fill array with numbers
    //on the 11th iteration, assign values to the face cards
    for (int i=1; i<=11; i++) {
        if (i == 11) {
            arr[i]   = 10; //jack  counts as 10
            arr[i+1] = 10; //queen counts as 10
            arr[i+2] = 10; //king  counts as 10
            arr[i+3] = 11; //ace   counts as 11
        }
        else
            arr[i] = i; //print out numbered cards
    }
}

//fill the deck with all cards in one suit (vectors)
void fillSuit(vector<int> vect) {
    for (int i=0; i<11; i++) {
        if (i == 11) {
            vect.push_back(10); //jack  counts as 10
            vect.push_back(10); //queen counts as 10
            vect.push_back(10); //king  counts as 10
            vect.push_back(11); //ace   counts as 11
        }
        else {
            vect.push_back(i); //print out numbered cards
        }
    }
}

//input line from file
void inputFromFile() {
    string line;    // used to store input line from another file
    fstream myFile; // other file
    myFile.open("IOFile.txt", ios::in); //open other file
    if (myFile.is_open()) {
        getline(myFile, line); //get first line from file
        cout << line << endl;  //output first line from file
        myFile.close();        //close file
    }
}

//output results to other file
void outputToFile(int pStack) {
    fstream myFile; // other file
    myFile.open("IOFile.txt", ios::app); //open other file
    if (myFile.is_open()) {
        myFile << "You left with $" << pStack << " this time" << endl; //output final results
        myFile.close(); //close file
    }
}

//print all instructions to game
void printInstructions() {
    string instruction; //stores current instruction
    //output new instruction with each iteration of loop
    for (int i = 0; i < 5; i++) {
        switch(i){
            case 0: instruction = "The goal of the game is to draw cards until you get 21."; break;
            case 1: instruction = "If you get over 21, you automatically lose"; break;
            case 2: instruction = "If you feel that you might go over 21 by drawing another card, you can choose to stay"; break;
            case 3: instruction = "After you stay, it is now the dealer's turn"; break;
            case 4: instruction = "Whoever gets the higher number under 21 wins"; break;
        }
        cout << instruction << endl; //output line
    }
    cout << endl; //create space for next section
}

//show results table
void resultsTable() {
    //string array
    string results[2][6];
    //row1: categories
    results[0][0] = "RATING";
    results[0][1] = "Great       ";
    results[0][2] = "Good       " ;
    results[0][3] = "Ok       "   ;
    results[0][4] = "Bad       "  ;
    results[0][5] = "Awful       ";
    //row2: ranges
    results[1][0] = "RANGES";
    results[1][1] = "+$500 or higher";
    results[1][2] = "+$250 to $500"  ;
    results[1][3] = "-$250 to +$250" ;
    results[1][4] = "-$250 to -$500" ;
    results[1][5] = "-$500 or lower" ;
    //print out
    for (int i=0; i<2; i++) {
        for (int j=0; j<6; j++) {
            if (i==0 || j==0)
                cout << setw(15) << left << results[i][j] << " |";
            else
                cout << setw(15) << left << results[i][j] << " |";
        }
        cout << endl;
    }
}
