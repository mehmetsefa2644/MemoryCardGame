#include "card.h"  // include header

#include <QApplication>
#include <QAction>
#include <QActionGroup>
#include <QDialog>
#include <QGridLayout>
#include <QLocale>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QTranslator>
#include <QVBoxLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QHash>
#include <QDebug>


QLCDNumber *time1; // declerations of lcdnumbers
QLCDNumber *time2;
QLCDNumber *gamelcd;
QLCDNumber *highlcd;
QLCDNumber *score1;
QLCDNumber *score2;
Timer *simulationTimer; // declarations of our powerful timers :)
Timer *simulationTimer2;
int player1point=0;  // point of player 1
int player2point=0;  // point of player 2
int gameno = 1;  // game number
int highestscore = 0;  //highest score

QHash <int, int> hash;  // hash table that stores previous games' properties

int main(int argc, char **argv)  // main function :)
{
    QApplication app(argc, argv);
    QWidget widget;
    QHBoxLayout *top, *bottom, *gamehrz, *highhrz; // horizontal layouts
    QVBoxLayout *main, *topleft, *topright, *topleftr, *topleftrr, *boslayout, *toprightl;  // vertical layouts

    MyGrid *game = new MyGrid(6);  // creates our grid of cards
    widget.connect(game, SIGNAL(gameWon()), game, SLOT(gameWonMessage())); // when game ends, pop up message

    QPushButton *new_game = new QPushButton("New game");  // creates new game button
    widget.connect(new_game, SIGNAL(clicked()), game, SLOT(newGame()));  // when new game is clicked, create new game

    QPushButton *prev = new QPushButton("Prev. Results");  // creates prev. button
    widget.connect(prev, SIGNAL(clicked()), game, SLOT(prevf()));  // when prev. clicked, show prev results

    QPushButton *next = new QPushButton("Next Results");  // creates next button
    widget.connect(next, SIGNAL(clicked()), game, SLOT(nextf()));  // when clicked, show next results

    QLabel *bos = new QLabel(" "); // boş label
    QLabel *score = new QLabel("        Score");  // score label
    QLabel *time = new QLabel("        Time");  // time label

    QLabel *pl1 = new QLabel("Player 1 ");  // player 1 label
    score1 = new QLCDNumber;  // score 1 lcd
    widget.connect(game, SIGNAL(increment1(int)), score1, SLOT(display(int)));

    time1 = new QLCDNumber;

    QLabel *pl2 = new QLabel("Player 2");
    score2 = new QLCDNumber;
    widget.connect(game, SIGNAL(increment2(int)), score2, SLOT(display(int)));

    time2 = new QLCDNumber;

    QLabel *gamelbl = new QLabel("Game No: ");
    gamelcd = new QLCDNumber;
    gamelcd->display(gameno);

    QLabel *highest = new QLabel("Highest Score:");
    QLabel *bos2 = new QLabel(" ");
    highlcd = new QLCDNumber;

    simulationTimer = new Timer;  // timer that for player 1's lcd
    simulationTimer->start(1000);  // 1 sec
    widget.connect(simulationTimer, SIGNAL(timeout()),simulationTimer, SLOT(countup1()));  // each 1 sec, count up
    widget.connect(game, SIGNAL(stop1()),simulationTimer, SLOT(stop1f()));  // stop when player changed
    widget.connect(game, SIGNAL(start1()),simulationTimer, SLOT(start1f()));  // start when player changed


    simulationTimer2 = new Timer;  // timer that for player 1's lcd
    widget.connect(simulationTimer2, SIGNAL(timeout()),simulationTimer2, SLOT(countup2()));  // each 1 sec, count up
    widget.connect(game, SIGNAL(stop2()),simulationTimer2, SLOT(stop2f()));  // stop when player changed
    widget.connect(game, SIGNAL(start2()),simulationTimer2, SLOT(start2f()));  // start when player changed

    /////////////////////////////////LAYOUTS////////////////////////////////////////////////////////////////////
    topright = new QVBoxLayout;  // top-right layout
    topright->addWidget(new_game);
    topright->addWidget(prev);
    topright->addWidget(next);

    gamehrz = new QHBoxLayout;  // horizontal layout for game score and lcd
    gamehrz->addWidget(gamelbl);
    gamehrz->addWidget(gamelcd);

    highhrz = new QHBoxLayout;  // horizontal layout for high score and lcd
    highhrz->addWidget(highest);
    highhrz->addWidget(highlcd);

    toprightl = new QVBoxLayout; // top-right-left layout
    toprightl->addLayout(gamehrz);
    toprightl->addLayout(highhrz);
    toprightl->addWidget(bos2);

    topleft = new QVBoxLayout;  // top-left layout
    topleft->addWidget(bos);
    topleft->addWidget(score);
    topleft->addWidget(time);

    topleftr = new QVBoxLayout; // top-left-right layout
    topleftr->addWidget(pl1);
    topleftr->addWidget(score1);
    topleftr->addWidget(time1);

    topleftrr = new QVBoxLayout;  //  top-left-right-right layout
    topleftrr->addWidget(pl2);
    topleftrr->addWidget(score2);
    topleftrr->addWidget(time2);

    boslayout = new QVBoxLayout;  // bos layout

    top = new QHBoxLayout;  // top layout
    top->addLayout(topleft);
    top->addLayout(topleftr);
    top->addLayout(topleftrr);
    top->addLayout(boslayout);
    top->addLayout(toprightl);
    top->addLayout(topright);

    bottom = new QHBoxLayout;  // bottom layout
    bottom->addWidget(game);

    main = new QVBoxLayout;  // main layout
    main->addLayout(top);
    main->addLayout(bottom);

    widget.setLayout(main);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    widget.setFixedHeight(250); // fixed sizes of windows
    widget.setFixedWidth(500);
    widget.show();  // show widget

    return app.exec();
}
int m_simulation = 0;  // player1 time
int m_simulation2 = 0;  // player2 timer

void Timer::stop1f()  // stop player 1 timer
{
    simulationTimer->stop();
}

void Timer::stop2f()  // stop player 2 timer
{
    simulationTimer2->stop();
}

void Timer::start1f()  // start player 1 timer
{
    simulationTimer->start(1000);
}

void Timer::start2f()  // start player 2 timer
{
    simulationTimer2->start(1000);
}

void Timer::countup1()  // count up for player 1 timer
{
    m_simulation++;
    time1->display(m_simulation);
}

void Timer::countup2()  // count up for player 2 timer
{
    m_simulation2++;
    time2->display(m_simulation2);
}

void Timer::prevf() // count up
{
   m_simulation2++;
   time2->display(m_simulation2);
}

void Timer::nextf()  // count up
{
   m_simulation2++;
   time2->display(m_simulation2);
}

MyGrid::MyGrid(int size)  // constructor
  : m_size(size), m_x(-1), m_y(0) // setting size and default positions
{
    QGridLayout *layout = new QGridLayout;  // creating grid layout
    setLayout(layout); // setting layout
    int n;
    for(n = 0; n < size*(size-1); n++)
    {
        // Choose the position of the card
        int r = (int)( ((double)rand()) / RAND_MAX * (size*(size-1)-n) );

        // Looking for empty grid cell
        int p = 0;
        while(r >= 0)
        {
            if(layout->itemAtPosition(p/size, p%size) == NULL) // if cell not null
            {
                r--;
                if(r < 0)
                {
                    Card *c = new Card(p/size, p%size, n/2); // create card
                    connect(c, SIGNAL(selected(int, int, int)), // when selected, call card selected
                        this, SLOT(cardSelected(int, int, int)));
                    layout->addWidget(c, p/size, p%size);
                }
            }
            p++;
        }
    }

    m_Wait = new QTimer;  // timer for waiting for cards that are chosen wrong
    m_Wait->setSingleShot(true);
    connect(m_Wait, SIGNAL(timeout()), this, SLOT(hideCards()));

}

#define GET_CARD(i, j) static_cast<Card*>(grid->itemAtPosition((i), (j))->widget()) // get card at i-th, j-th position

void MyGrid::cardSelected(int x, int y, int n) // when card is selected
{

    if(m_Wait->isActive()) // if there ara already active cards, return
        return ;

    QGridLayout *grid = static_cast<QGridLayout*>(layout());
    GET_CARD(x, y)->setMode(Card::ACTIVE);  // setting card active

    if(m_x == -1) // if it is the first selected card, store position for comparing them later
    {
        m_x = x;
        m_y = y;
    }
    else
    {
        if(GET_CARD(m_x, m_y)->getN() == n)  // if cards match
        {
            GET_CARD(m_x, m_y)->setMode(Card::SHOWN); // set cards mode as shown because cards match
            GET_CARD(x, y)->setMode(Card::SHOWN);
            m_x = -1; // set temporary x -1 again
            int i, j;
            for(i = 0; i < m_size-1; i++)  // check every card if there are hidden cards(if game should end)
            {
                for(j = 0; j < m_size; j++)
                {
                    if(GET_CARD(i, j)->getMode() == Card::HIDDEN){ // if there is hidden card( game not ended )
                        if(player1){ // if player 1 gain the point
                            emit increment1(++player1point);
                            emit stop1();
                            emit start2();
                        }
                        else{  // if player 2 gain the point
                            emit increment2(++player2point);
                            emit stop2();
                            emit start1();
                        }
                        player1 = !player1;  // change the player
                        return ;
                    }
                }

            }
            if(player1){  // if these codes are running, it means that game is ended :) if player 1 who play last
                emit increment1(++player1point);
                emit stop1();
            }
            else{ // if player 2 play last
                emit increment2(++player2point);
                emit stop2();
            }
            emit gameWon(); // game has ended

        }
        else  // this means cards does not match
        {
            if(player1){ // player 1 played last, change timers
                emit stop1();
                emit start2();
            }
            else{  // player 2 played last, change timers
                emit stop2();
                emit start1();
            }
            m_x = -1;
            m_Wait->start(1500); // wait for 1.5 secs to see the nonmatching cards
            player1 = !player1;  // change player
        }
    }
}

void MyGrid::hideCards() // function that hides cards
{
    QGridLayout *grid = static_cast<QGridLayout*>(layout());
    int i, j;
    for(i = 0; i < m_size-1; i++)  // look at each cards if there is active card, change its mode to hidden
    {
        for(j = 0; j < m_size; j++)
        {
            if(GET_CARD(i, j)->getMode() == Card::ACTIVE)
                GET_CARD(i, j)->setMode(Card::HIDDEN);
        }
    }

}
void MyGrid::newGame()  // function that starts new game
{
    QGridLayout *grid = static_cast<QGridLayout*>(layout());
    int i, j;
    for(i = 0; i < m_size-1; i++) // firstly, player wants to play a new game, all cards must be at mode hidden
    {
        for(j = 0; j < m_size; j++)
        {
            if(GET_CARD(i, j)->getMode() == Card::ACTIVE || GET_CARD(i, j)->getMode() == Card::SHOWN)
                GET_CARD(i, j)->setMode(Card::HIDDEN); // change all cards' modes to hidden
        }
    }

    hash.insertMulti(gameno, player1point);  // store previous games' properties to hash table
    hash.insertMulti(gameno, player2point);
    hash.insertMulti(gameno, m_simulation);
    hash.insertMulti(gameno, m_simulation2);

    m_simulation=0;  // reset timers
    time1->display(m_simulation);
    m_simulation2=0;
    time2->display(m_simulation2);
    simulationTimer2->stop();
    simulationTimer->start(1000);

    if(highestscore==0){  // change high score

        if(player1point > player2point){
            highlcd->display(player1point);
        }
        else if(player1point < player2point){
            highlcd->display(player2point);
        }
    }else{
        if(player1point > highestscore){
            highlcd->display(player1point);
        }
        else if(highestscore < player2point){
            highlcd->display(player2point);
        }

    }

    player1point=0;  // reset player points
    emit increment1(player1point);
    player2point=0;
    emit increment2(player2point);

    gamelcd->display(++gameno);  // increment game number
}

void MyGrid::prevf()  // show previous games' results
{
    QList<int> values = hash.values(--gameno);  // parse previous game's properties from hash table

    if(!values.empty()){  // show previous results
    gamelcd->display(gameno);
    score1->display(values[3]);
    score2->display(values[2]);
    time1->display(values[1]);
    time2->display(values[0]);
    emit stop1();
    }else{
        ++gameno; // if values empty do not increment game number stupidly
    }
}
void MyGrid::nextf()  // show nextgames' results
{
    QList<int> values = hash.values(++gameno); // parse next games'properties from hash table

    if(!values.empty()){  // show properties
    gamelcd->display(gameno);
    score1->display(values[3]);
    score2->display(values[2]);
    time1->display(values[1]);
    time2->display(values[0]);
    emit stop1();
    }else{
        --gameno;  // if values empty do not decrement game number stupidly
    }
}

void MyGrid::gameWonMessage()  // if game ended pop up this awesome message :D
{   if(player1point > player2point){
        QMessageBox::information(this, tr("Victory"),
            tr("Player 1 won the game!"));
    }
    else if(player1point < player2point){
        QMessageBox::information(this, tr("Victory"),
            tr("Player 2 won the game!"));
    }
}


Card::Card(int i, int j, int n) // constructor for Card class
  : x(i), y(j), N(n), m_CardMode(Card::HIDDEN)  // properties of card objects
{
    m_Button = new QPushButton("?", this);
    connect(m_Button, SIGNAL(clicked()),
        this, SLOT(clicked()));
}

void Card::clicked()  // when clicked
{
    if(m_CardMode == Card::HIDDEN)
        emit selected(x, y, N);
}

void Card::setMode(CardMode e)  // set mode of cards
{
    m_CardMode = e;
    switch(e)
    {
    case Card::HIDDEN: // if hiden, put ?
        m_Button->setText("?");
        break;
    case Card::SHOWN:  // if shown display numbers
        m_Button->setText(QString::number(N));
        break;
    case Card::ACTIVE:  // if active display numbers
        m_Button->setText(QString::number(N));
        break;
    }

    QFont f = font();
    f.setBold(m_CardMode == Card::ACTIVE); // set bold font if active
    setFont(f);

    QFont fo = font();
    fo.setUnderline(m_CardMode == Card::SHOWN);  // set underlined and bold if shown
    fo.setBold(m_CardMode == Card::SHOWN);
    setFont(fo);
}
