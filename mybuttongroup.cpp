#include <mybuttongroup.h>

QPushButton *MyButtonGroup::arr[5][6] ;
bool MyButtonGroup::clicked = false ;
int MyButtonGroup::prevId1 = -1;
int MyButtonGroup::prevId2 = -1;
QString MyButtonGroup::st[5][6];
QString MyButtonGroup::prev = "";
vector<QPushButton *> MyButtonGroup::butVec ;
int MyButtonGroup::playerId = 1 ;
int MyButtonGroup::player1Score = 0 ;
int MyButtonGroup::player2Score = 0 ;
QPushButton * MyButtonGroup::prevResults ;
QPushButton * MyButtonGroup::nextResults ;
QPushButton * MyButtonGroup::newGame ;
QTableWidget * MyButtonGroup::table1 ;
size_t MyButtonGroup::timeKeeper = 0 ;
int MyButtonGroup::player1Time = 0 ;
int MyButtonGroup::player2Time= 0 ;
int MyButtonGroup::highScore = 0 ;
int MyButtonGroup::gameNumber = 1 ;
bool MyButtonGroup::gameOverFlag = false ;
