/*
 * File:   main.cpp
 * Author: Blake Gilbert
 * Created on January 25, 2022, 5:00 PM
 * Purpose: Play a game of blackjack against the house (computer)
 *
 */

//System Level Libraries
#include <iostream> //Input-Output Library
#include <iomanip>  //Format Library
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
    char
        pDraw, //player chooses whether to draw another card
        dDraw, //dealer chooses whether to draw another card
        cont , //used to move onto dealer's next card
        again; //used to play another hand
    unsigned short
        newCard, //value of new card
        pCount,  //number player has
        dCount;  //number computer has
    int
        pStack, //amount of money player has
        pBet,   //amount of money player is betting
        start,  //amount of money player started with
        rsult;  //amount of money player won

    //initial money
    cout  << "How many chips do you have?" << endl;
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
        if (pStack < 0) cout << "You're spending money that you don't have. That's a self-destructive habit." << endl;

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
                cout   << "Player wins with higher hand."   << endl;
                cout   << "Player gains $"    << pBet       << endl;
                pStack += (pBet * 2);
                cout   << "Chips remaining: $" << pStack    << endl;
                cout   << endl;
            }
            else if (dCount > pCount && dCount <= 21) {
                cout   << "Dealer wins with higher hand."   << endl;
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
        cin  >> again;
        cout << endl;
    } while (again == 'y');

    //display final winnings/losses
    if (pStack > 0) {
        pStack >= start
            ? cout << "You won $"  << pStack - start << "! Nice!" << endl
            : cout << "You lost $" << start - pStack << ". Better luck next time!" << endl;
    }
    else cout << "You lost all of your money. I hope you don't make a habit of this." << endl;

    //Exit the program
    return 0;
}
