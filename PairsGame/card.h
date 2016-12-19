#ifndef CARD_H // if not defined, define card.h
#define CARD_H

#include <QDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QTime>
#include <QWidget>
#include <QTimer>

class Card : public QWidget { // Card subclass

    Q_OBJECT

public:
    enum CardMode { // enum to identify the state of cards
        HIDDEN,
        SHOWN,
        ACTIVE
    };

private:
    int x, y; // position of cards
    int N; // value of cards
    CardMode m_CardMode;
    QPushButton *m_Button;

public:
    Card(int i, int j, int n); // constructor
    inline int getN() { return N; } // getter for n
    inline CardMode getMode() { return m_CardMode; } // getter to identify cards' mode
    void setMode(CardMode e); // setter of cardmode

public slots:
    void clicked(); // clicked slot

signals:
    void selected(int i, int j, int n); // signal that shows card is selected

};

class MyGrid : public QWidget { // subclass of QWidget to implement grid layout for cards

    Q_OBJECT

private:
    int m_size; // size of grid, it can be changed in constructor
    int m_x, m_y; // temporary position's of selected cards
    QTimer *m_Wait; // timer for waiting after cards are shown

public:
    MyGrid(int size); // constructor
    bool player1; // boolean to detect if current player is player 1 or player2

public slots:
    void cardSelected(int x, int y, int n); // slot of cards selected
    void hideCards(); // slot that hide cards if not match
    void gameWonMessage(); // slot that pops message when game ends
    void newGame(); // slot that starts new game
    void prevf(); // slot for previous results button
    void nextf(); // slot for next button

signals:
    void gameWon(); // signal for game has been won
    void increment1(int); // signal to increment player1's point
    void increment2(int); // signal to increment player1's point
    void stop1(); // signal to stop timer of player 1
    void stop2(); // signal to stop timer of player 2
    void start1(); //signal to start timer of player 1
    void start2(); // signal to start timer of player 2
    void newgame(); // signal to start a new game
};

class Timer : public QTimer { // subclass of QTimer that has useful slots :))

    Q_OBJECT

public:

private:

public:

public slots:
    void countup1();  // slot that increments timer of player 1
    void countup2();  // slot that increments timer of player 2
    void stop1f();  // slot that stops timer of player 1
    void stop2f();  // slot that stops timer of player 2
    void start1f();  // slot that starts timer of player 1
    void start2f();  // slot that starts timer of player 2
    void prevf();  // slot for previous button
    void nextf();  // slot for next button

signals:


};

#endif // CARD_H
