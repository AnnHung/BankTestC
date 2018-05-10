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
const int BANK_ADDRESS_LENGTH = 50;
const int BANK_PHONE_LENGTH = 30;
const int BANK_TYPE_LENGTH = 2;
const int BANK_MEMBER_TYPE_LENGTH = 2;
const int BANK_STATUS_LENGTH = 1;
const char BANK_TYPE_HS[] = "HS";
const char BANK_TYPE_CN[] = "CN";
const char BANK_MEMBER_TYPE_NN[] = "NN";
const char BANK_MEMBER_TYPE_CP[] = "CP";
const char BANK_MEMBER_TYPE_KB[] = "KB";
const char BANK_STATUS_TYPE_ACTIVE = 'Y';
const char BANK_STATUS_TYPE_DEACTIVE = 'N';
/**************/

/*DECLARATION*/
struct CONFIGURATION{
    int currentSequence;
};
struct BANK{
    long bankId;
    char bankName[50];    
    char bankAddress[100];
    char phoneNo[30];
    char bankType[2];
    char memberType[2];
    char status;
    int isDeleted;
    struct BANK_DATE *foundDate;
};
struct BANK_DATE{
    int day;
    int month;
    int year;
};
/*************/

/****FUNCTION****/
void printDirection();
struct CONFIGURATION* getConfiguration();
void addNewBank();
void saveNewBank(struct BANK *newBank);
void listAllBanks();
void updateBank(int isDelete);
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
                updateBank(0);
                printDirection();
                break;
            case '4':
                updateBank(1);
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
    printf("4, Delete bank by Id.\n");
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
    /*Bank name*/
    printf("Please insert bank name: \n"); 
    char *newBankName = malloc(sizeof(char[BANK_NAME_LENGTH]));
    fgets(newBankName,BANK_NAME_LENGTH,stdin);
    strcpy(newBank->bankName,newBankName);
    fflush(stdin);
    /*Bank address*/
    printf("Please insert bank address: \n"); 
    char *newBankAddress = malloc(sizeof(char[BANK_ADDRESS_LENGTH]));
    fgets(newBankName,BANK_ADDRESS_LENGTH,stdin);
    strcpy(newBank->bankAddress,newBankAddress);
    fflush(stdin);
    /*Bank phone*/
    printf("Please insert bank phone: \n"); 
    char *newBankPhone = malloc(sizeof(char[BANK_ADDRESS_LENGTH]));
    fgets(newBankName,BANK_ADDRESS_LENGTH,stdin);
    strcpy(newBank->bankAddress,newBankAddress);
    fflush(stdin);
    /*Bank type*/
    printf("Please insert bank type(CN/HS): \n"); 
    printf("CN(Chi Nhanh) \n"); 
    printf("HS(Hoi So) \n");
    char *newBankType = malloc(sizeof(char[BANK_TYPE_LENGTH]));
    fgets(newBankType,BANK_TYPE_LENGTH,stdin);
    while(1==1){
        fgets(newBankType,BANK_TYPE_LENGTH,stdin);
        fflush(stdin);
        if('\0' != newBankType[0] || 
                0 != strcmp(BANK_TYPE_CN,newBankType) || 
                0 != strcmp(BANK_TYPE_HS,newBankType)){
            printf("Value must be 'CN' or 'HS'; Please re-insert: \n"); 
        }
    }
    strcpy(newBank->bankType,newBankType);
    /*Member type*/
    printf("Please insert member type(NN/CP/KB): \n"); 
    printf("NN(Ngan Hang Nha Nuoc) \n"); 
    printf("CP(Ngan Hang TMCP) \n");
    printf("KV(Kho Bac) \n");
    char *newBankMemberType = malloc(sizeof(char[BANK_MEMBER_TYPE_LENGTH]));
    fgets(newBankMemberType,BANK_TYPE_LENGTH,stdin);
    while(1==1){
        fgets(newBankMemberType,BANK_MEMBER_TYPE_LENGTH,stdin);
        fflush(stdin);
        if ('\0' != newBankType[0] 
                || 0 != strcmp(BANK_MEMBER_TYPE_NN, newBankMemberType) 
                || 0 != strcmp(BANK_MEMBER_TYPE_CP, newBankMemberType) 
                || 0 != strcmp(BANK_MEMBER_TYPE_KB, newBankMemberType)) {
            printf("Value must be 'NN' or 'CP' or 'KB'; Please re-insert: \n"); 
        }
    }
    strcpy(newBank->memberType,newBankMemberType);
    fflush(stdin);
    /*Bank status*/
    printf("Please insert bank status(Y/N): \n"); 
    printf("Y(Dang Hoant Dong) \n"); 
    printf("N(Da Dung Hoat Dong) \n");
    char *newBankStatus = malloc(sizeof(char[BANK_STATUS_LENGTH]));
    fgets(newBankStatus,BANK_TYPE_LENGTH,stdin);
    while(1==1){
        fgets(newBankStatus,BANK_TYPE_LENGTH,stdin);
        fflush(stdin);
        if('\0' != newBankStatus[0] || 
                0 != strcmp(BANK_STATUS_TYPE_ACTIVE,newBankStatus) || 
                0 != strcmp(BANK_STATUS_TYPE_DEACTIVE,newBankStatus)){
            printf("Value must be 'Y' or 'N'; Please re-insert: \n"); 
        }
    }
    strcpy(newBank->status,newBankStatus);
    /*Bank found date*/
    printf("Please enter bank found date: dd/mm/yyyy:\n");
    int day, month, year;
    scanf("%d/%d/%/d",day, month, year);
    
    
    newBank->isDeleted = 0;
    
    saveConfiguration(appConfig);
    fflush(stdin);
    saveNewBank(newBank);
}

void saveNewBank(struct BANK *newBank){
    FILE *bankDataFile = fopen(DATA_FILE_PATH,"ab+");
    int newSequence = appConfig->currentSequence+=1;
    saveConfiguration(appConfig);
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
    for(int count = 0;count < size;count++){
        if((0 != sizeof(allBanks[count])) && (0 == allBanks[count].isDeleted)){
            printBankInfo(&allBanks[count]);
        }
    }
    fclose(bankDatFile);
}

void updateBank(int isDeleted){
    if(0 == isDeleted){
        printf("Enter bank id to update: \n");
    }else if(1 == isDeleted){
        printf("Enter bank id to delete: \n");
    }
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
    if(0 == isDeleted){
        printf("UPDATE Bank Name: \n");
        char *updateBankName = malloc(sizeof(char[BANK_NAME_LENGTH]));
        fgets(updateBankName, BANK_NAME_LENGTH, stdin);

        if(NULL != updateBankName && updateBankName[0] != '\0'){
            strcpy(ptrBank->bankName, updateBankName);
        }
    }else if(1 == isDeleted){
        ptrBank->isDeleted = 1;
    }
    fseek(datFile, foundLoc, SEEK_SET);
    fwrite(ptrBank, sizeof(struct BANK),1,datFile);
    fclose(datFile);
    free(ptrBank);
    if(0 == isDeleted){
        printf("BANK UPDATE SUCCESSFULLY.\n");
    }else if(1 == isDeleted){
        printf("BANK DELETE SUCCESSFULLY.\n");
    }
}

void printBankInfo(struct BANK *bank){
    printf("*****************BANK INFO*****************\n");
    printf("Bank ID: %ld\n",bank->bankId);
    printf("Bank Name: %s\n",bank->bankName);
}