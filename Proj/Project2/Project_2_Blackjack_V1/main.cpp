/*
 * File:   main.cpp
 * Author: Blake Gilbert
 * Created on January 25, 2022, 5:00 AM
 * Purpose: Play a game of blackjack against the house (computer)
 *
 */

//System Level Libraries
#include <iostream> //Input-Output Library
#include <iomanip>  //Format Library
#include <string>   //String Library
#include <cmath>    //Math Library
#include <fstream>  //File IO Library
using namespace std;

//User Defined Libraries go here

//Global CONSTANTS (not global VARIABLES) go here (constants from Physics, Chemistry, Engineering, and Conversions between systems of units)
const unsigned short PERCNV = 100; //convert to percentage

//Function Prototypes go here
void printInstructions();
void inputFromFile();
void outputToFile(int);
void buyChips(int &, int &);
void bet(int &, int &);
void compareCards(int, int, int, int &);
bool playAnotherHand(int, int);
void displayFinal(int, int);

//Execution begins here
int main(int argc, char **argv) {
    //Initialize Random Seed once here
    srand(static_cast<unsigned int>(time(0)));

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


    //assign known variables here
    pWin=dWin=1;

    //initial game setup
    inputFromFile();         //input information from other file
    printInstructions();     //instructions
    buyChips(pStack, start); //enter initial money

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
                    cout   << endl;
                }
            }
            else cout << "Dealer has " << dCount << " and must stay." << endl << endl;

            //compare player cards to dealer cards to see who wins
            compareCards(pCount, dCount, pBet, pStack);
        }

        //ask if player wants to play another hand
        again = playAnotherHand(pWin, dWin);

    } while (again);

    //display final winnings/losses
    displayFinal(pStack, start);

    //output final stack to other file
    outputToFile(pStack);

    //Exit the program
    return 0;
}

void printInstructions() {
    string instruction;
    for (int i = 0; i < 5; i++) {
        switch(i){
            case 0: instruction = "The goal of the game is to draw cards until you get 21."; break;
            case 1: instruction = "If you get over 21, you automatically lose"; break;
            case 2: instruction = "If you feel that you might go over 21 by drawing another card, you can choose to stay"; break;
            case 3: instruction = "After you stay, it is now the dealer's turn"; break;
            case 4: instruction = "Whoever gets the higher number under 21 wins"; break;
        }
        cout << instruction << endl;
    }
    cout << endl;
}

void inputFromFile() {
    string line;    // used to store input line from another file
    fstream myFile; // other file
    myFile.open("IOFile.txt", ios::in);
    if (myFile.is_open()) {
        getline(myFile, line);
        cout << line << endl;
        myFile.close();
    }
}

void outputToFile(int pStack) {
    fstream myFile; // other file
    myFile.open("IOFile.txt", ios::app);
    if (myFile.is_open()) {
        myFile << "You left with $" << pStack << " this time" << endl;
        myFile.close();
    }
}

void buyChips(int &pStack, int &start) {
    cout  << "How many chips are you starting with?" << endl; //prompt the player to input starting money
    cin   >> pStack;
    start  = pStack;
    cout  << endl;
}

void bet(int &pStack, int &pBet) {
    cout    << "Chips remaining: $" << pStack << endl;
    cout    << "How much do you want to bet?" << endl;
    cin     >> pBet;
    pStack  -= pBet;
    cout    << endl;
    if (pStack < 0)  cout << "You're spending money that you don't have. That's a self-destructive habit." << endl;
    if (pStack == 0) cout << "You have $0 left. Be careful" << endl;
}

void compareCards(int pCount, int dCount, int pBet, int &pStack) {
    if (pCount > dCount || dCount > 21) {
        cout   << "Player wins."   << endl;
        cout   << "Player gains $"    << pBet       << endl;
        pStack += (pBet * 2);
        cout   << "Chips remaining: $" << pStack    << endl;
        cout   << endl;
    }
    else if (dCount > pCount && dCount <= 21 || pCount > 21) {
        cout   << "Dealer wins"   << endl;
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

bool playAnotherHand(int pWin, int dWin) {
    char cont;
    cout << "Play another hand?"                   << endl;
    cout << "Your chance of winning is " << (pWin/(pWin + dWin)) * PERCNV << "%" << endl;
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

void displayFinal(int pStack, int start) {
    float final = abs(static_cast<float>(pStack)) - abs(static_cast<float>(start));
    pStack >= start
            ? cout << "You won $"  << fixed << setprecision(2) << showpoint << final << "! Nice!"                  << endl
            : cout << "You lost $" << fixed << setprecision(2) << showpoint << final << ". Better luck next time!" << endl;
}
