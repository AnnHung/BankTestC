/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: nguye
 *
 * Created on May 9, 2018, 9:38 PM
 */

#include "include/include.h"
#include "include/declaration.h"
#include "include/defaultimplementation.h"


int main(int argc, char** argv) {
    int isRunning = 1;
    printf("start");
    appConfig = getConfiguration();
    printDirection();
    while(1 == isRunning){        
        char choice = getc(stdin);
        switch(choice){
            case '1':
                addNewBank();
                printDirection();
                break;
            case '2':
                listAllBanks(0);
                printDirection();
                break;
            case '3':
                updateBank(0);
                printDirection();
                break;
            case '4':
                updateBank(1);
                printDirection();
                break;
            case '5':
                searchBank();
                printDirection();
                break;
            case '6':
                sortBanks();
                printDirection();
                break;
            case 'q':
                isRunning = 0;
                break;
            case 'Q':
                isRunning = 0;
                break;
            default:
                break;
        }        
    }
}
/*EOF*/