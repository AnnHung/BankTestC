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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>

/***CONTANT****/
const char CONFIGURATION_FILE_PATH[] = ".\\config.dat";
const char DATA_FILE_PATH[] = ".\\data.dat";
const long MAX_BANK_QUANTITY = 99999999;
const int PAGINATION_NUMBER = 1000;
const int BANK_NAME_LENGTH = 50;
/**************/

/*DECLARATION*/
struct CONFIGURATION{
    int currentSequence;
};
struct BANK{
    long bankId;
    char bankName[50];
};
/*************/

/****FUNCTION****/
void printDirection();
struct CONFIGURATION* getConfiguration();
void addNewBank();
void saveNewBank(struct BANK *newBank);
void listAllBanks();
void updateBank();
void printBankInfo(struct BANK *bank);
/****************/

struct CONFIGURATION *appConfig;

int main(int argc, char** argv) {
    int isRunning = 1;
    printf("start");
    appConfig = getConfiguration();
    /****TEST*****/
    /*
    printf("Current sequence: %d\n", appConfig->currentSequence);
    appConfig->currentSequence += 1;
    saveConfiguration(appConfig);
    appConfig = getConfiguration();
    printf("New sequence: %d\n",appConfig->currentSequence);
    */
    /*************/
    printDirection();
    while(1 == isRunning){        
        char choice = getc(stdin);
        switch(choice){
            case '1':
                addNewBank();
                printDirection();
                break;
            case '2':
                listAllBanks();
                printDirection();
                break;
            case '3':
                updateBank();
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

void printDirection(){
    printf("BANK MANAGEMENT\n");
    printf("Please choose menu option by input the suggested key below:\n");
    printf("1, Add new Bank.\n");
    printf("2, List all Banks.\n");
    printf("3, Update bank by Id.\n");
    printf("Q, Exit.\n");
}

struct CONFIGURATION* getConfiguration(){
    FILE *sequenceFile = fopen(CONFIGURATION_FILE_PATH, "rb");
    if(NULL == sequenceFile){
        fclose(sequenceFile);
        FILE *newSequenceFile = fopen(CONFIGURATION_FILE_PATH,"wb+");
        struct CONFIGURATION *newConfig = malloc(sizeof(struct CONFIGURATION));
        newConfig->currentSequence = 0;
        fwrite(newConfig,sizeof(struct CONFIGURATION),1,newSequenceFile);
        fclose(newSequenceFile);        
        return newConfig;
    }else{
        struct CONFIGURATION *existedConfig;        
        fread(existedConfig,sizeof(struct CONFIGURATION),1,sequenceFile);
        return existedConfig;
    }
}

void saveConfiguration(struct CONFIGURATION *newConfig){
    FILE *configFile = fopen(CONFIGURATION_FILE_PATH,"w+");
    fwrite(newConfig, sizeof(struct CONFIGURATION),1,configFile);
    fclose(configFile);
    printf("NEW CONFIGURATION SAVED.\n");
}

void addNewBank(){
    fflush(stdin);
    struct BANK *newBank = malloc(sizeof(struct BANK));
    printf("ADD NEW BANK.\n");
    printf("Please insert bank name: \n");   
    char *newBankName = malloc(sizeof(char[BANK_NAME_LENGTH]));
    fgets(newBankName,BANK_NAME_LENGTH,stdin);
    strcpy(newBank->bankName,newBankName);    
    fflush(stdin);
    saveNewBank(newBank);
}

void saveNewBank(struct BANK *newBank){
    FILE *bankDataFile = fopen(DATA_FILE_PATH,"ab+");
    int newSequence = appConfig->currentSequence+=1;
    newBank->bankId = newSequence;
    fwrite(newBank,sizeof(struct BANK),1,bankDataFile);
    printf("SAVE NEW BANK SUCCESS.\n");
    fclose(bankDataFile);
}

void listAllBanks(){
    FILE *bankDatFile = fopen(DATA_FILE_PATH,"rb");
    if(NULL == bankDatFile){
        printf("File's not exists.\n");
        return;
    }
    struct BANK allBanks[PAGINATION_NUMBER];
    fread(allBanks, sizeof(struct BANK), PAGINATION_NUMBER, bankDatFile);
    fseek(bankDatFile, 0L, SEEK_END);
    int fileSize = ftell(bankDatFile);
    fseek(bankDatFile, 0L, SEEK_SET);
    int size = fileSize/sizeof(struct BANK);
    printf("Number of elements: %d\n", size);
    for(int count = 0;count < size;count++){
        if(0 != sizeof(allBanks[count])){
            printBankInfo(&allBanks[count]);
        }
    }
    fclose(bankDatFile);
}

void updateBank(){
    printf("Enter bank id to process: \n");
    long bankId;
    char *strBankId = malloc(sizeof(char[8]));
    while(1==1){
        fgets(strBankId, 8, stdin);
        if(isdigit(*strBankId)){
            break;
        }else{
            printf("Please enter digit only.");
        }
    }
    fflush(stdin);    
    bankId = atol(strBankId);
    FILE *datFile = fopen(DATA_FILE_PATH,"rb+");    
    struct BANK *ptrBank = malloc(sizeof(struct BANK));
    fread(ptrBank, sizeof(struct BANK), 1, datFile);
    int foundLoc = 0;
    int count = 0;
    fseek(datFile, 0, SEEK_END);
    int eof = ftell(datFile);
    fseek(datFile,0,SEEK_SET);
    int seek;
    while(NULL != ptrBank || seek > eof){
        if(bankId == ptrBank->bankId){
            foundLoc = ftell(datFile) - sizeof(struct BANK);            
            break;
        }else{
            count += 1;
            seek = sizeof(struct BANK) * count;
            fseek(datFile, seek, SEEK_SET);
            fread(ptrBank, sizeof(struct BANK), 1, datFile);
        }
    }
    if(NULL != ptrBank){
        printf("Found one result: \n");
        printBankInfo(ptrBank);
    }else{
        printf("No result found;");
        return;
    }
    
    printf("UPDATE Bank Name: \n");
    char *updateBankName = malloc(sizeof(char[BANK_NAME_LENGTH]));
    fgets(updateBankName, BANK_NAME_LENGTH, stdin);
    
    if(NULL != updateBankName && updateBankName[0] != '\0'){
        strcpy(ptrBank->bankName, updateBankName);
    }
    fseek(datFile, foundLoc, SEEK_SET);
    fwrite(ptrBank, sizeof(struct BANK),1,datFile);
    fclose(datFile);
    printf("BANK UPDATE SUCCESSFULLY.\n");
}

void printBankInfo(struct BANK *bank){
    printf("*****************BANK INFO*****************\n");
    printf("Bank ID: %ld\n",bank->bankId);
    printf("Bank Name: %s\n",bank->bankName);
}