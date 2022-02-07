/*
 * File:   main.cpp
 * Author: Blake Gilbert
 * Created on January 26, 2022, 5:00 AM
 * Purpose: Play a game of blackjack against the house (computer)
 *
 */

//System Level Libraries
#include <iostream> //Input-Output Library
#include <iomanip>  //Format Library
#include <string>   //String Library
using namespace std;

//User Defined Libraries go here

//Global CONSTANTS (not global VARIABLES) go here (constants from Physics, Chemistry, Engineering, and Conversions between systems of units)

//Function Prototypes go here

//Execution begins here
int main(int argc, char **argv)
{
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
        final;  //final winnings/losses
    string
        instruction; //instructions at the start of the game

    //instructions
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

    //initial money
    cout  << "How many chips are you starting with?" << endl;
    cin   >> pStack;
    start  = pStack;
    cout  << endl;

    //actual game
    do {
        //bet
        cout    << "Chips remaining: $" << pStack << endl;
        cout    << "How much do you want to bet?" << endl;
        cin     >> pBet;
        pStack  -= pBet;
        cout    << endl;
        if (pStack < 0)  cout << "You're spending money that you don't have. That's a self-destructive habit." << endl;
        if (pStack == 0) cout << "You have $0 left. Be careful" << endl;

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
            cout << "Dealer wins. Player busted." << endl; //game is over if player goes over 21
            cout << "Player loses $"    << pBet   << endl;
            cout << "Chips remaining: $" << pStack << endl;
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
                    newCard  = rand() % 11 + 1; //dealer draws another card
                    dCount  += newCard;
                    cout    << "Dealer now has " << dCount  << endl;
                    cout    << endl;
                    cout    << "To continue, press any key" << endl;
                    cout    << "Then, press 'enter'"        << endl;
                    cin     >> cont;
                    cout    << endl;
                }
                if (dCount > 21) {
                    cout   << "Player wins. Dealer busted." << endl; //hand is over if player goes over 21
                    cout   << "Player gains $"    << pBet   << endl;
                    pStack += (pBet * 2);
                    cout   << "Chips remaining: $" << pStack   << endl;
                    cout   << endl;
                }
            }
            else cout << "Dealer has " << dCount << " and must stay." << endl << endl;

            //compare player cards to dealer cards to see who wins
            if (pCount > dCount || dCount > 21) {
                cout   << "Player wins."   << endl;
                cout   << "Player gains $"    << pBet       << endl;
                pStack += (pBet * 2);
                cout   << "Chips remaining: $" << pStack    << endl;
                cout   << endl;
            }
            else if (dCount > pCount && dCount <= 21) {
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

        //ask if player wants to continue
        cout << "Play another hand?"                   << endl;
        cout << "Press 'y' for yes; press 'n' for no." << endl;
        cout << "Then, press 'enter to continue."      << endl;
        cin  >> cont;
        switch (cont) {
            case 'y': again = true ; break;
            case 'n': again = false; break;
        }
        cout << endl;
    } while (again);

    //display final winnings/losses
    if (pStack > 0) {
        pStack >= start
            ? final = static_cast<float>(pStack) - static_cast<float>(start)
            : final = static_cast<float>(start)  - static_cast<float>(pStack);
        pStack >= start
            ? cout << "You won $"  << fixed << setprecision(2) << showpoint << final << "! Nice!"                  << endl
            : cout << "You lost $" << fixed << setprecision(2) << showpoint << final << ". Better luck next time!" << endl;
    }
    else cout << "You lost all of your money. I hope you don't make a habit of this." << endl;

    //Exit the program
    return 0;
}
