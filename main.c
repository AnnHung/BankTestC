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
#include <conio.h>
#include <math.h>

#define ESC_KEY 27
#define SPACE_KEY 32
#define ERROR_KEY 77
#define Y_CN 1
#define Y_HS 2
#define N_CN 3
#define N_HS 4

/***CONTANT****/
const char CONFIGURATION_FILE_PATH[] = "G:\\Dev\\Development\\Source\\C\\BankTest\\config.dat";
const char DATA_FILE_PATH[] = "G:\\Dev\\Development\\Source\\C\\BankTest\\data.dat";
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

void printDirection(){
    printf("BANK MANAGEMENT MENU:\n");
    printf("Please choose menu option by input the suggested key below:\n");
    printf("1, Add new Bank.\n");
    printf("2, List all Banks.\n");
    printf("3, Update bank by Id.\n");
    printf("4, Delete bank by Id.\n");
    printf("5, Search bank in Hanoi by status and bank type.\n");
    printf("6, Sort banks.\n");
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
    /*char *tmpStr;*/
    struct BANK *newBank = malloc(sizeof(struct BANK));
    printf("ADD NEW BANK.\n");
   /*Bank name*/
    printf("Please insert bank name: \n"); 
    char *newBankName = malloc(sizeof(char[BANK_NAME_LENGTH]));
    fgets(newBankName,BANK_NAME_LENGTH,stdin);
    processInput(newBankName, BANK_NAME_LENGTH);
    /*tmpStr = strtok(newBankName,"\n");*/
    strcpy(newBank->bankName, newBankName);
    fflush(stdin);
    /*Bank address*/
    printf("Please insert bank address: \n");
    char *newBankAddress = malloc(sizeof(char[BANK_ADDRESS_LENGTH]));
    fgets(newBankAddress,BANK_ADDRESS_LENGTH,stdin);    
    fflush(stdin);
    processInput(newBankAddress, BANK_ADDRESS_LENGTH);
    /*tmpStr = strtok(newBankAddress,"\n");*/
    strcpy(newBank->bankAddress, newBankAddress);
    /*Bank phone*/
    printf("Please insert bank phone: \n"); 
    char *newBankPhone = malloc(sizeof(char[BANK_PHONE_LENGTH]));
    fgets(newBankPhone,BANK_PHONE_LENGTH,stdin);
    processInput(newBankPhone, BANK_PHONE_LENGTH);
    /*tmpStr = strtok(newBankPhone,"\n");*/
    strcpy(newBank->phoneNo,newBankPhone);
    fflush(stdin);
    /*Bank type*/
    printf("Please insert bank type(CN/HS): \n"); 
    printf("CN(Chi Nhanh) \n"); 
    printf("HS(Hoi So) \n");
    char *newBankType = malloc(sizeof(char[BANK_TYPE_LENGTH]));
    while(1==1){
        fgets(newBankType,BANK_TYPE_LENGTH,stdin);
        /*tmpStr = strtok(newBankType,"\n");*/
        processInput(newBankType, BANK_TYPE_LENGTH);
        fflush(stdin);
        if('\0' != newBankType[0] && 
                (0 == strcmp(BANK_TYPE_CN,newBankType) || 
                0 == strcmp(BANK_TYPE_HS,newBankType))){
            break;
        }else{ 
            printf("Value must be 'CN' or 'HS'; Please re-insert: \n"); 
        }
    }
    strcpy(newBank->bankType,newBankType);
    /*Member type*/
    printf("Please insert member type(NN/CP/KB): \n"); 
    printf("NN(Ngan Hang Nha Nuoc) \n"); 
    printf("CP(Ngan Hang TMCP) \n");
    printf("KV(Kho Bac) \n");
    char newBankMemberType[BANK_MEMBER_TYPE_LENGTH];
    while(1==1){
        fgets(newBankMemberType,BANK_MEMBER_TYPE_LENGTH,stdin);
        processInput(newBankMemberType, BANK_MEMBER_TYPE_LENGTH);
        /*tmpStr = strtok(newBankMemberType,"\n");*/
        fflush(stdin);
        if ('\0' != newBankMemberType[0] 
                && (0 == strcmp(BANK_MEMBER_TYPE_NN, newBankMemberType) 
                || 0 == strcmp(BANK_MEMBER_TYPE_CP, newBankMemberType) 
                || 0 == strcmp(BANK_MEMBER_TYPE_KB, newBankMemberType))) {
            break;
        }else{
            printf("Value must be 'NN' or 'CP' or 'KB'; Please re-insert: \n"); 
        }
    }
    strcpy(newBank->memberType,newBankMemberType);
    fflush(stdin);
    /*Bank status*/
    printf("Please insert bank status(Y/N): \n"); 
    printf("Y(Dang Hoant Dong) \n"); 
    printf("N(Da Dung Hoat Dong) \n");
    char newBankStatus[BANK_STATUS_LENGTH];
    while(1==1){
        fgets(newBankStatus,BANK_STATUS_LENGTH,stdin);
        processInput(newBankStatus, BANK_STATUS_LENGTH);
        /*tmpStr = strtok(newBankStatus,"\n");*/
        fflush(stdin);
        if('\0' != newBankStatus[0] && 
                (BANK_STATUS_TYPE_ACTIVE == (char)newBankStatus[0] || 
                 BANK_STATUS_TYPE_DEACTIVE == (char)newBankStatus[0])){
            break;
        }else{
            printf("Value must be 'Y' or 'N'; Please re-insert: \n"); 
        }
    }
    strcpy(newBank->status, newBankStatus);
    /*Bank found date*/
    printf("Please enter bank found date: dd/mm/yyyy:\n");
    int day, month, year;
    scanf("%d/%d/%d",&day, &month, &year);
    struct BANK_DATE *newFoundDate = malloc(sizeof(struct BANK_DATE));
    newFoundDate->day = day;
    newFoundDate->month = month;
    newFoundDate->year = year;
    memcpy(&(newBank->foundDate), newFoundDate, sizeof(struct BANK_DATE));
        
    newBank->isDeleted = 0;
    
    if(BANK_STATUS_TYPE_ACTIVE == newBank->status[0] && 0 == strcmp(BANK_TYPE_CN, newBank->bankType)){newBank->searchFlag = Y_CN;}
    else if(BANK_STATUS_TYPE_ACTIVE == newBank->status[0] && 0 == strcmp(BANK_TYPE_HS, newBank->bankType)){newBank->searchFlag = Y_HS;}
    else if(BANK_STATUS_TYPE_DEACTIVE == newBank->status[0] && 0 == strcmp(BANK_TYPE_CN, newBank->bankType)){newBank->searchFlag = N_CN;}
    else if(BANK_STATUS_TYPE_DEACTIVE == newBank->status[0] && 0 == strcmp(BANK_TYPE_HS, newBank->bankType)){newBank->searchFlag = N_HS;}
    
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

void listAllBanks(int search){
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
    printTableHeaded();
    for(int count = 0;count < size;count++){
        if((0 != sizeof(allBanks[count])) && (0 == allBanks[count].isDeleted)){
            if(0 == search){
                printBankInfo(&allBanks[count]);
            }else if(search == allBanks[count].searchFlag && 0 <= isContainSubString("Ha Noi", allBanks[count].bankAddress)){   
                printBankInfo(&allBanks[count]);
            }
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
        int choice = 0;
        /*Bank Name*/
        while(1==1){
            printf("Do you want to change bank name? ESC for cancel, [SPACE] for skip, Enter to proceed: \n");
            choice = getch();
            if(ESC_KEY == choice){return;}
            if(SPACE_KEY == choice){break;}
            fflush(stdin);
            printf("Enter new bank name: \n");
            char *updateBankName = malloc(sizeof(char[BANK_NAME_LENGTH]));
            fgets(updateBankName, BANK_NAME_LENGTH, stdin);        
            if(NULL != updateBankName && updateBankName[0] != '\0'){
                processInput(updateBankName, BANK_NAME_LENGTH);
                strcpy(ptrBank->bankName, updateBankName);
                break;
            }
        }
        choice = 0;
        while(1==1){
            fflush(stdin);
            printf("Do you want to change bank address, press -> key, ESC to cancel to skip: \n");
            choice = getch();
            if(ESC_KEY == choice){return;}
            if(SPACE_KEY == choice){break;}
            fflush(stdin);
            printf("Enter new bank address: \n");
            char *updateBankAddrss = malloc(sizeof(char[BANK_ADDRESS_LENGTH]));
            fgets(updateBankAddrss, BANK_ADDRESS_LENGTH, stdin); 
            if(NULL != updateBankAddrss && updateBankAddrss[0] != '\0'){
                processInput(updateBankAddrss, BANK_ADDRESS_LENGTH);
                strcpy(ptrBank->bankAddress, updateBankAddrss);
                break;
            }
        }
        choice = 0;
        while(1==1){
            fflush(stdin);
            printf("Do you want to change bank phone, press [SPACE] key, ESC to cancel to skip: \n");
            choice = getch();
            if(ESC_KEY == choice){return;}
            if(SPACE_KEY == choice){break;}
            fflush(stdin);
            printf("Enter new bank phone: \n");
            char *updateBankPhone = malloc(sizeof(char[BANK_PHONE_LENGTH]));
            fgets(updateBankPhone, BANK_ADDRESS_LENGTH, stdin);        
            if(NULL != updateBankPhone && updateBankPhone[0] != '\0'){
                processInput(updateBankPhone, BANK_ADDRESS_LENGTH);
                strcpy(ptrBank->phoneNo, updateBankPhone);
                break;
            }
        }
        choice = 0;
         while(1==1){
            fflush(stdin);
            printf("Do you want to change bank type, press [SPACE] key, ESC to cancel to skip: \n");
            choice = getch();
            if(ESC_KEY == choice){return;}
            if(SPACE_KEY == choice){break;}
            fflush(stdin);
            printf("Enter new bank type: \n");
            char *updateBankType = malloc(sizeof(char[BANK_TYPE_LENGTH]));
            while(1==1){
                fgets(updateBankType,BANK_TYPE_LENGTH,stdin);
                /*tmpStr = strtok(newBankType,"\n");*/
                processInput(updateBankType, BANK_TYPE_LENGTH);
                fflush(stdin);
                if('\0' != updateBankType[0] && 
                        (0 == strcmp(BANK_TYPE_CN,updateBankType) || 
                        0 == strcmp(BANK_TYPE_HS,updateBankType))){
                    break;
                }else{ 
                    printf("Value must be 'CN' or 'HS'; Please re-insert: \n"); 
                }
                
            }     
            strcpy(ptrBank->bankType, updateBankType);
            break;
        }
        choice = 0;
        while(1==1){
            fflush(stdin);
            printf("Do you want to change bank member type, press [SPACE] key, ESC to cancel to skip: \n");
            choice = getch();
            if(ESC_KEY == choice){return;}
            if(SPACE_KEY == choice){break;}
            fflush(stdin);
            printf("Enter new bank member type: \n");
            char *updateBankMemberType = malloc(sizeof(char[BANK_MEMBER_TYPE_LENGTH]));
            while(1==1){
                fgets(updateBankMemberType,BANK_MEMBER_TYPE_LENGTH,stdin);
                /*tmpStr = strtok(newBankType,"\n");*/
                processInput(updateBankMemberType, BANK_MEMBER_TYPE_LENGTH);
                fflush(stdin);
                if ('\0' != updateBankMemberType[0] 
                        && (0 == strcmp(BANK_MEMBER_TYPE_NN, updateBankMemberType) 
                        || 0 == strcmp(BANK_MEMBER_TYPE_CP, updateBankMemberType) 
                        || 0 == strcmp(BANK_MEMBER_TYPE_KB, updateBankMemberType))) {
                    break;
                }else{
                    printf("Value must be 'NN' or 'CP' or 'KB'; Please re-insert: \n"); 
                }
            }     
            strcpy(ptrBank->memberType, updateBankMemberType);
            break;
        }
        choice = 0;
        while(1==1){
            fflush(stdin);
            printf("Do you want to change bank status, press [SPACE] key, ESC to cancel to skip: \n");
            choice = getch();
            if(ESC_KEY == choice){return;}
            if(SPACE_KEY == choice){break;}
            fflush(stdin);
            printf("Enter new bank status: \n");
            char *updateBankStatus = malloc(sizeof(char[BANK_STATUS_LENGTH]));
            while(1==1){
                fgets(updateBankStatus,BANK_STATUS_LENGTH,stdin);
                /*tmpStr = strtok(newBankType,"\n");*/
                processInput(updateBankStatus, BANK_STATUS_LENGTH);
                fflush(stdin);
                if('\0' != updateBankStatus[0] && 
                    (BANK_STATUS_TYPE_ACTIVE == (char)updateBankStatus[0] || 
                     BANK_STATUS_TYPE_DEACTIVE == (char)updateBankStatus[0])){
                    break;
                }else{
                    printf("Value must be 'Y' or 'N'; Please re-insert: \n"); 
                }
            }     
            strcpy(ptrBank->status, updateBankStatus);
            break;
        }
        choice = 0;
        while(1==1){
            fflush(stdin);
            printf("Do you want to change bank found date, press [SPACE] key, ESC to cancel to skip: \n");
            choice = getch();
            if(ESC_KEY == choice){return;}
            if(SPACE_KEY == choice){break;}
            fflush(stdin);
            printf("Enter new bank found date: \n");
            struct BANK_DATE *updateBankFoundDate = malloc(sizeof(struct BANK_DATE));
            printf("Please enter new bank found date: dd/mm/yyyy:\n");
            int day, month, year;
            scanf("%d/%d/%d",&day, &month, &year);
            updateBankFoundDate->day = day;
            updateBankFoundDate->month = month;
            updateBankFoundDate->year = year;
            memcpy(&(ptrBank->foundDate), updateBankFoundDate, sizeof(struct BANK_DATE));
            break;
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
    printf("%-8.8ld|%-30.50s|%-40.100s|%-15.20s|%-7.4s|%-9.8s|%-9.6s|%-2.2d/%-2.2d/%-4.4d\n",bank->bankId,bank->bankName, bank->bankAddress, bank->phoneNo, bank->bankType, bank->memberType, bank->status, bank->foundDate.day,bank->foundDate.month, bank->foundDate.year);
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
}

void printTableHeaded(){
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");      
    printf("Id      |Name                          |Address                                 |Phone          |Type   |Member   |Status   |Found Date\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    
}

void processInput(char *input, int size){
    /*
    if(NULL != input){
        char *tmpChar;
        tmpChar = strtok(input,"\n");
        if(NULL == tmpChar){
            tmpChar = strtok(input,"\0");
        }
        if(NULL == tmpChar){
            tmpChar = strtok(input, "\r");
        }
        return tmpChar;
    }else{
        return NULL;
    }
    */
    if(NULL != input){
        int count = 0;
        for(;count < size; count++){
            if('\n' == *(input + count) || '\r' == *(input + count)){
                *(input + count) = '\0';
            }
        }
    }
}

void searchBank(){
    printf("Enter criteria to search bank in Hanoi:([status]<space>[CN|HS])\n");
    char *status, *bankType;
    status = malloc(sizeof(char[BANK_STATUS_LENGTH]));
    bankType = malloc(sizeof(char[BANK_TYPE_LENGTH]));
    while(1==1){
        fflush(stdin);
        scanf("%s %s", status, bankType);
        if ((status[0] == '\0' && bankType[0] == '\0') 
                || (BANK_STATUS_TYPE_ACTIVE != status[0] && BANK_STATUS_TYPE_DEACTIVE != status[0]) 
                || (0 != strcmp(BANK_TYPE_CN, bankType) && 0 != strcmp(BANK_TYPE_HS, bankType))) {
            printf("Please re-enter criteria...\n");
            continue;
        }
        break;
    }
    
    if(BANK_STATUS_TYPE_ACTIVE == status[0] && 0 == strcmp(BANK_TYPE_CN, bankType)){listAllBanks(Y_CN);}
    else if(BANK_STATUS_TYPE_ACTIVE == status[0] && 0 == strcmp(BANK_TYPE_HS, bankType)){listAllBanks(Y_HS);}
    else if(BANK_STATUS_TYPE_DEACTIVE == status[0] && 0 ==  strcmp(BANK_TYPE_CN, bankType)){listAllBanks(N_CN);}
    else if(BANK_STATUS_TYPE_DEACTIVE == status[0] && 0 == strcmp(BANK_TYPE_HS, bankType)){listAllBanks(N_HS);}   
}

int isContainSubString(char *keyword, char *source){
    int bingo = 0;
    int kLen = strlen(keyword);
    int sLen = strlen(source);
    if(kLen > sLen){
        return -1;
    }else if(kLen == sLen){
        return strcmp(source, keyword) != 0 ? -1 : 0;
    }else{
        int kIndex = 0;
        for(int sIndex = 0; sIndex < sLen; sIndex++){
            if(*(keyword) == *(sIndex + source)){
                bingo = 1;
                int start = keyword;
                int result = sIndex;
                while(1 == bingo && kIndex < kLen){
                    kIndex+=1;
                    if(*(kIndex + keyword) != *(sIndex + kIndex + source)){
                        bingo = 0;
                        kIndex = 0;
                        keyword = start;
                    }
                }
                if(kIndex >= kLen && bingo == 1){
                    return result;
                }
            }
        }
    }
    return -1;
}

void sortBanks(){
    printf("Enter 'asc' or 'dsc' to sort banks: \n");
    char *choice = malloc(sizeof(char[4]));
    fflush(stdin);
    fgets(choice, 4, stdin);
    if(0 == strcmp(choice, "asc")){
        listAllBanks(0);
    }else if(0 == strcmp(choice, "dsc")){
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
        int index = size - 1;
        printTableHeaded();
        for(; index > 0; index--){
            printBankInfo(&allBanks[index]);
        }
    }else{
        printf("Sort type not supported.\n");
    }
}