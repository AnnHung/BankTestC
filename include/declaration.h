/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   declaration.h
 * Author: nguye
 *
 * Created on May 16, 2018, 11:20 AM
 */

#ifndef DECLARATION_H
#define DECLARATION_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* DECLARATION_H */

#define ESC_KEY 27
#define SPACE_KEY 32
#define ERROR_KEY 77
#define Y_CN 1
#define Y_HS 2
#define N_CN 3
#define N_HS 4
#define _USE_32BIT_TIME_T 0

/***CONTANT****/
const char CONFIGURATION_FILE_PATH[] = ".\\config.dat";
const char DATA_FILE_PATH[] = ".\\data.dat";
const long MAX_BANK_QUANTITY = 99999999;
const int PAGINATION_NUMBER = 1000;
const int BANK_NAME_LENGTH = 50;
const int BANK_ADDRESS_LENGTH = 50;
const int BANK_PHONE_LENGTH = 30;
const int BANK_TYPE_LENGTH = 2+1;
const int BANK_MEMBER_TYPE_LENGTH = 2+1;
const int BANK_STATUS_LENGTH = 1+1;
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

struct BANK_DATE{
    int day;
    int month;
    int year;
};

struct BANK{
    long bankId;
    char bankName[50];    
    char bankAddress[100];
    char phoneNo[30];
    char bankType[3];
    char memberType[3];
    char status[2];
    int searchFlag;
    int isDeleted;    
    struct BANK_DATE foundDate;
};

/*************/

/****FUNCTION****/
void printDirection();
struct CONFIGURATION* getConfiguration();
void addNewBank();
void saveNewBank(struct BANK *newBank);
void listAllBanks(int search);
void updateBank(int isDelete);
void printBankInfo(struct BANK *bank);
void printTableHeaded();
void processInput(char *input, int size);
void searchBank();
int isContainSubString(char *keyword, char *source);
void sortBanks();
/****************/