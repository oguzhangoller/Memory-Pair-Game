#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include "mybuttongroup.h"
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLabel>
#include <ctime>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv); //QApplication
    QMainWindow *window = new QMainWindow(); // QMainWindow


        window->setWindowTitle(QString::fromUtf8("Card Match Game")); // setting window's title as Card Match Game
        window->resize(1200, 600); // resize window for table

        QWidget *centralWidget = new QWidget(window); //QWidget


     //vector for storing animals as QString

    vector<QString> animalVec = {"cat","cat","dog","dog","bird","bird","elephant","elephant","horse","horse","bear","bear",
                               "shark","shark","dolphin","dolphin","dragon","dragon","ant","ant","lion","lion","eagle","eagle",
                               "hawk","hawk","zebra","zebra","wolf","wolf"};
    srand(time(NULL));

    //stack for animals as QString to push randomly from vector of animal
    stack<QString> animalStack ;

    QHBoxLayout* layout = new QHBoxLayout();     //QHBoxLayout
    MyButtonGroup* group = new MyButtonGroup(centralWidget);    //MyButtonGroup class initialization 
    
    int size  = animalVec.size();           //size of vector of animal
    for(int i= 0 ; i<size ; i++){           // for loop to push animal QString stack from vector
        int index = rand()%size;                    //get random index according to vector size
        animalStack.push(animalVec[index]);         //get animal with random index of vector of QString and push it to stack 
        animalVec.erase(animalVec.begin() + index);     //erase the animal of that index in vector
        i=-1 ;  // decrement i to fit in vector index 
        size-- ; // decrement vector size 
    }


    QTableWidget *table = new QTableWidget(); //QTableWidget
    MyButtonGroup::table1 = table ;      //Assign table pointer to table1 from MyButtonGroup
    QTableWidgetItem *tableItem ;       // QTableWidgetItem
    table->verticalHeader()->setVisible(false);     // set invisible to vertical header of table to remove numbers
    table->horizontalHeader()->setVisible(false);   // set invisible to horizontal header of table to remove numbers
    table->horizontalHeader()->setDefaultSectionSize(200);  //set size of horizontal header
    table->verticalHeader()->setDefaultSectionSize(50); //set size of horizontal header



        table->setRowCount(9);     // set row number to 9 according given table in description
        table->setColumnCount(6); // set column number 

        table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding); //set size policy for cells in table


        QPushButton *newGame=new QPushButton("New Game");   //QPushButton pointer for newGame
        MyButtonGroup::newGame = newGame;   //Assign new game pointer to newgame QPushButton from MyButtonGroup
        QPushButton *prevResult=new QPushButton("Prev. Results");   //QPushButton pointer for previous results
        MyButtonGroup::prevResults = prevResult;             //Assign prev result pointer to prev result QPushButton from MyButtonGroup
        QPushButton *nextResult=new QPushButton("Next Results");    //QPushButton pointer for next results
        MyButtonGroup::nextResults = nextResult;            //Assign next result pointer to next reuslt QPushButton from MyButtonGroup
        
        for (int i = 0; i < 3; ++i) {           // for loop to set table item for created buttons above in specific coordinates
            tableItem= new QTableWidgetItem();
            table->setItem(i,5,tableItem);
        }

        //add buttons which are  newGame, prevResults, nextResults buttons to table in specific coordinates
        table->setCellWidget(0,5,newGame);
        table->setCellWidget(1,5,prevResult);
        table->setCellWidget(2,5,nextResult);

        // add these buttons to MyGroupButton 
        group->addButton(newGame);
        group->addButton(prevResult);
        group->addButton(nextResult);
        MyButtonGroup::timeKeeper = time(NULL);

       

        QLabel *score=new QLabel("Score");          // QLabel pointer for score
        QLabel *time=new QLabel("Time(secs)");       // QLabel pointer for time(secs)
        QLabel *player1=new QLabel("Player1");      // QLabel pointer for player1
        QLabel *player2=new QLabel("Player2");      // QLabel pointer for player2
        QLabel *gameNo=new QLabel("Game no: "+ QString::number(MyButtonGroup::gameNumber));     //QLabel for game number with gameNuber from MyButtonGroup class
        QLabel *highestScore=new QLabel("Highest Score: " + QString::number(MyButtonGroup::highScore)); //QLabel for highScore with highScore from MyButtonGroup class

        for (int i = 0; i < 2; ++i) {   //for loop to set item to table in specific locations
            tableItem= new QTableWidgetItem();  //intialize tableItem 
           table->setItem(i+1,0,tableItem); //set table item to table
           tableItem= new QTableWidgetItem();   //intialize tableItem 
           table->setItem(0,i+1,tableItem); //set table item to table
        }

        // set QLabels to specific locations in table
        table->setCellWidget(1,0,score); 
        table->setCellWidget(2,0,time);
        table->setCellWidget(0,1,player1);
        table->setCellWidget(0,2,player2);
        table->setCellWidget(0,4,gameNo);
        table->setCellWidget(1,4,highestScore);

    
        //add QPushButtons to table with nested for loop
    for(int i=0 ; i<5 ; i++){
        for(int j=0 ; j<6 ; j++){
            QPushButton * buttonX = new QPushButton("?",centralWidget); //QPushButton pointers with text "?"
            tableItem= new QTableWidgetItem();//initalize new QTableWidgetItem in every loop

            MyButtonGroup::st[i][j] = animalStack.top(); // add the animals from randomly pushed stack to array from MyButtonGroup class
            animalStack.pop(); // pop animal that assigned to array above from stack
            
            MyButtonGroup::arr[i][j] = buttonX ; // add buttons to array from MyButtonGroup 


            table->setItem(i+4,j,tableItem); //set table item to table
            table->setCellWidget(i+4, j, buttonX); // add buttons to table 
            group->addButton(buttonX); // add buttons to MyButtonGroup class to identify which button is clicked 

            if(animalStack.empty()) // if stack is empty breaks the loop
                break;

        }
    }

    window->setCentralWidget(table); // set table to window

    window->show(); // shows window


    return app.exec(); // returns QApplicaiton

}
