#ifndef MYBUTTONGROUP_H
#define MYBUTTONGROUP_H

#include <QButtonGroup>
#include <QPushButton>
#include <QMessageBox>
#include <string>
#include <QString>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <QApplication>
#include <QTableWidget>
#include <QLabel>
#include <ctime>
#include <random>
#include <QWidget>
#include <time.h>
#include <iostream>

using namespace std;

//Derived Class from QButtonGroup
class MyButtonGroup: public QButtonGroup
{
  Q_OBJECT
  public:
    static QPushButton * arr[5][6]; // array for buttons
    static QString st[5][6]; // array for animals
    static vector<QPushButton *> butVec ;
    static QString prev ; 
    static int prevId1, prevId2 ;
    static bool clicked ;
    static int playerId ;
    static int player1Score ;
    static int player2Score ;
    static QTableWidget * table1 ;
    static QPushButton * prevResults ;
    static QPushButton * nextResults ;
    static QPushButton * newGame ;
    static size_t timeKeeper ;
    static int player1Time ;
    static int player2Time ;
    static int gameNumber ;
    static int highScore ;
    static QWidget * _parent;
    static bool gameOverFlag ; 


    MyButtonGroup(QWidget* parent) //MyButtonGroup constructor
    {
      this->setParent(parent);


      //connect buttonClicked signal to our custom slot 'buttonClick'
      connect(this , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));

    };
    ~ MyButtonGroup(){};// MyButton destructor


  public slots:
    //Slot method that is called when one of buttons in QButtonGroup is clicked
    // Take argument as QAbstacrionButton which is clicked button 
    void buttonClick(QAbstractButton* but )
    {


        if(but == prevResults){   // looks for clicked button is prevResults button
            QApplication::processEvents();
            return ;
        }
        else if(but == nextResults){    // looks for clicked button is nextResults button

            QApplication::processEvents();
            return ;
        }

        else if(but == newGame){    // looks for clicked button is newGame button
            startOver: //label
            vector<QString> animalShuffle ; //vector of QString to used when new game button is clicked
            if(player1Score > highScore) //looks for player1's score is higher than current highest score
                highScore = player1Score ; //if it is assign player1 score to highest score
            
            if(player2Score > highScore)  //looks for player1's score is higher than current highest score
                highScore = player2Score ;  //if it is assign player2 score to highest score
            
            gameNumber++ ;  //increment the game number by 1
            table1->setCellWidget(0,4,new QLabel("Game no: "+ QString::number(gameNumber)));  //set new game number with QString according to 'Game no' cell
            table1->setCellWidget(1,4,new QLabel("Highest Score: " + QString::number(highScore)));  //set new highest score with QString according to 'Highest Score' cell

            //assign -1 to previous ids while starting new game
            prevId1 = -1 ;  
            prevId2 = -1 ;
            
            //assign false to clicked flag
            clicked = false ;
            
            //assign zero to player's scores while starting new game
            player1Score = 0 ;
            player2Score = 0 ;
            

            
            //set new player' scores and playing times to table cells with QString
            table1->setCellWidget(1,1,new QLabel(QString::fromStdString(to_string(player1Score))));
            table1->setCellWidget(1,2,new QLabel(QString::fromStdString(to_string(player2Score))));
            table1->setCellWidget(2,1,new QLabel(QString::fromStdString(to_string(player1Time))));
            table1->setCellWidget(2,2,new QLabel(QString::fromStdString(to_string(player2Time))));
            
            //set cell's background red for player1 while starting new game
            table1->item(0, 1)->setBackground(Qt::red);
            table1->item(0, 2)->setBackground(Qt::white);
             QApplication::processEvents(); //process events immediately 
            
            playerId = 1 ; // assign 1 to player id to start new game from player1
            
            //nested for loop to assign all animal cards(buttons) as "?" while starting new game
            for(int i=0 ; i<5 ; i++){
                for(int j=0 ; j<6 ; j++){
                    arr[i][j]->setText("?"); //setting text for each button as "?"
                    arr[i][j]->setEnabled(true); //set enable true for making button clickable
                    animalShuffle.push_back(st[i][j]); // shuffle the array to assign animals to buttons randomly
                }
            }
            random_shuffle(animalShuffle.begin(),animalShuffle.end());  // shuffle the vector to assign animals to buttons randomly
            
            //nested for loop to assign new shuffled animal vector to animal array(st) 
            for(int i=0 ; i<5 ; i++){
                for(int j=0 ; j<6 ; j++){
                    st[i][j] = animalShuffle.back();
                    animalShuffle.erase(animalShuffle.end()-1);
                }
            }
            return ; 
        }

        //if the button is animal card it finds the button from animal array
       for(int i=0 ; i<5 ; i++){
           for(int j=0 ; j<6 ; j++){
               if(but==arr[i][j])
               {

                   if(prevId1 == i && prevId2 == j){ //if same button is clicked it breaks the loop
                       break;
                   }
                   
                   if(!clicked){  //if button is clicked 

                   but->setText(st[i][j]); // setting text animal from animal array to that butotn 
                   clicked = !clicked ; // change clicked flag 
                   prev = st[i][j]; // store the clicked animal in prev
                   
                   //stores clicked button's ids
                   prevId1 = i ; 
                   prevId2 = j ;

                   }
                   else{

                       clicked = !clicked ;

                       
                           //compares the animals with first one that we stored  , if they match increment the player's score
                       if(prev.compare(st[i][j]) == 0 ){ 
                           
                           if(playerId == 1){ // increment the player1's score if id is 1
                               player1Score++;

                           }
                           else{
                               player2Score++; // increment the player1's score if id is 2

                           }
                           
                           but->setText(""); //set text empty if animals are matched
                           but->setEnabled(false);  // set enabled false to prevent button clicked
                           arr[prevId1][prevId2]->setEnabled(false); // set enabled false to prevent button clicked
                            arr[prevId1][prevId2]->setText(""); //set text empty if animals are matched
                       }
                       else{
                           if(playerId==1){ // player1 can't find same animals set id to 2 to give turn to player2
                               playerId = 2;
                               size_t now = time(NULL);
                               player1Time +=  (int) (now - timeKeeper);
                               timeKeeper = time(NULL);

                           }
                           else {             // player2 can't find same animals set id to 2 to give turn to player2
                               playerId = 1 ;
                               size_t now = time(NULL);
                               player2Time +=  (int) (now - timeKeeper);
                               timeKeeper = time(NULL);
                           }
                           
                           but->setText(st[i][j]); // set text to button from animal array
                           QApplication::processEvents(); //process events

                           usleep(500000); //using time sleep to see the two cards open a little time
                           but->setText("?"); // set text "?" to that button if cards do not match
                           if(prevId1 != -1 && prevId2 != -1)
                                arr[prevId1][prevId2]->setText("?"); // set text "?" to other button if cards dont match
                           prev = " "; // assign the empty prev string for new round

                       }
                       //assign -1 to previous ids  for new round
                        prevId1 = -1 ; 
                        prevId2 = -1 ;
                   }
               }
           }
       }

       //set new player' scores to that buttons in table cells
       table1->setCellWidget(1,1,new QLabel(QString::fromStdString(to_string(player1Score))));
       table1->setCellWidget(1,2,new QLabel(QString::fromStdString(to_string(player2Score))));
       
       //set player1 cell in table background red if player1 plays 
       if(playerId == 1){
           table1->item(0, 1)->setBackground(Qt::red);
           table1->item(0, 2)->setBackground(Qt::white);
       }
       //set player2 cell in table background red if player2 plays 
       else{
           table1->item(0, 2)->setBackground(Qt::red);
           table1->item(0, 1)->setBackground(Qt::white);
       }

       //add player's playing time to time cells in table
       table1->setCellWidget(2,1,new QLabel(QString::fromStdString(to_string(player1Time))));
       table1->setCellWidget(2,2,new QLabel(QString::fromStdString(to_string(player2Time))));

       //if total rounds is equal to 15 give QMessageBox as 'Game Over'
       if((player1Score + player2Score) == 15){
           QMessageBox::information((QWidget *)this->parent(),"Game Over","Game Over");
           goto startOver; //go to startover label
       }

    };

};
#endif
