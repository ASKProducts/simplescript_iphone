//
//  Autoreleasepool.h
//  SpecialChar
//
//  Created by stephen kaufer on 8/18/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Autoreleasepool_h
#define Autoreleasepool_h

#include "Data.h"

#pragma mark - definitions

#define kautoreleaseNestingMax 10
four_byte autoreleaseNestingCount = -1;

typedef four_byte holder;
typedef eight_byted Number;
//#define String char*
Number *mainStack[kautoreleaseNestingMax];
four_byte mainStackLength[kautoreleaseNestingMax];

no_return initMainStack(no_param);
no_return freeMainStack(no_param);
no_return printMainStack(no_param);

#define startautoreleasepool autoreleaseNestingCount++;initMainStack();
#define endautoreleasepool freeMainStack();autoreleaseNestingCount--;
#define autoreleasepool(...) startautoreleasepool __VA_ARGS__ endautoreleasepool

holder addNumberToMainStack(Number value);
no_return addNumbersToMainStack(Number cap,UNDEFINED_END_OF_PARAMETERS);
no_return addNumberPtrsToMainStack(Number cap,UNDEFINED_END_OF_PARAMETERS);
holder addStringToMainStack(String value);
no_return addCharsToMainStack(String value);
no_return addStringPtrsToMainStack(Number cap,UNDEFINED_END_OF_PARAMETERS);

Number getN(holder h);
String getS(holder h);
holder defN(Number value);
holder defS(String value);
#define customNULL -123.0
#define customNULLI -123
#define customNULLC (char)-123
#define customNULLB (byte)-123
#define customNULLP (void*)-123
#define customNULLCP (char*)-123
#define customNULLS (String)-123
#define customNULLD (data)-123

#define blank defN(customNULL)
#define Slen(h) (getN((h)+1))  


#pragma mark - creations

no_return initMainStack(no_param){
    mainStackLength[autoreleaseNestingCount] = 0;
    mainStack[autoreleaseNestingCount] = (Number*)malloc(mainStackLength[autoreleaseNestingCount] * 8);
    printf("\n Opening stack number %d \n\n",autoreleaseNestingCount+1);
}
no_return freeMainStack(no_param){
    mainStackLength[autoreleaseNestingCount] = 0;
    free(mainStack[autoreleaseNestingCount]);
    printf("\n\n Freeing all data in stack number %d \n\n",autoreleaseNestingCount+1);
}
no_return printMainStack(no_param){
    printf("\n{");
    for (int i = 0; i<mainStackLength[autoreleaseNestingCount]; i++) {
        printf("%f",mainStack[autoreleaseNestingCount][i]);
        if(i != (mainStackLength[autoreleaseNestingCount]-1))printf(",");
    }
    printf("},%d doubles = %d bytes = %d bits\n",mainStackLength[autoreleaseNestingCount], mainStackLength[autoreleaseNestingCount]*8,mainStackLength[autoreleaseNestingCount]*64);
}

holder addNumberToMainStack(Number value){
    Number *temporaryStack = (Number*)malloc(mainStackLength[autoreleaseNestingCount] * sizeof(Number));
    for (int i = 0; i<mainStackLength[autoreleaseNestingCount]; i++) {
        temporaryStack[i] = mainStack[autoreleaseNestingCount][i];
    }
    mainStack[autoreleaseNestingCount] = (Number*)malloc(4 + mainStackLength[autoreleaseNestingCount] * sizeof(Number));
    for (int i = 0; i<mainStackLength[autoreleaseNestingCount]; i++) {
        mainStack[autoreleaseNestingCount][i] = temporaryStack[i];
    }
    //char *tempHolder = mainStack + mainStackLength[autoreleaseNestingCount];
    //*tempHolder = value;
    mainStack[autoreleaseNestingCount] += mainStackLength[autoreleaseNestingCount];
    *mainStack[autoreleaseNestingCount] = value;
    mainStack[autoreleaseNestingCount] -= mainStackLength[autoreleaseNestingCount];
    mainStackLength[autoreleaseNestingCount]++;
    return mainStackLength[autoreleaseNestingCount] - 1;
}
no_return addNumbersToMainStack(Number cap,UNDEFINED_END_OF_PARAMETERS){
    va_list nums;
    va_start(nums, cap);
    byte triggered = 0;
    for (int i = 0; i<cap; i++) {
        Number n = va_arg(nums, Number);
        if(n != customNULL && !triggered)
            addNumberToMainStack(n);
        else{
            triggered = 1;
            addNumberToMainStack(customNULL);
        }
    }
}
#define allocate(cap) addNumbersToMainStack(cap,customNULL)
no_return addNumberPtrsToMainStack(Number cap,UNDEFINED_END_OF_PARAMETERS){
    addNumbersToMainStack(cap,customNULL);
    four_byte bnest = mainStackLength[autoreleaseNestingCount] - (four_byte)cap;
    
    va_list strs;
    va_start(strs, cap);
    byte triggered = 0;
    for (int i = 0; i<cap; i++) {
        Number n = va_arg(strs, Number);
        if(n != customNULL && !triggered){
            mainStack[autoreleaseNestingCount][bnest] = (Number)defN(n);
            bnest++;
        }
        else
            triggered = 1;
    }
}
no_return addCharsToMainStack(String value){
    eight_byte length = strlen(value);
    for (int i = 0; i<length; i++) {
        char theChar = value[i];
        Number m = theChar;
        addNumberToMainStack(m);
    }
}
holder addStringToMainStack(String value){
    eight_byte length = strlen(value);
    holder h = addNumberToMainStack(-124);
    addNumberToMainStack((Number)length);
    addCharsToMainStack(value);
    return h;
}
no_return addStringPtrsToMainStack(Number cap,UNDEFINED_END_OF_PARAMETERS){
    addNumbersToMainStack(cap,customNULL);
    four_byte bnest = mainStackLength[autoreleaseNestingCount] - (four_byte)cap;
    
    va_list strs;
    va_start(strs, cap);
    byte triggered = 0;
    for (int i = 0; i<cap; i++) {
        String n = va_arg(strs, String);
        if(n != customNULLS && !triggered){
            mainStack[autoreleaseNestingCount][bnest] = (Number)defS(n);
            bnest++;
        }
        else
            triggered = 1;
    }
}


Number getN(holder h){
    Number *na = mainStack[autoreleaseNestingCount];
    na += h;
    return (Number)*na;
}
#define getD(d) ((double)*(mainStack[autoreleaseNestingCount]+d))
String getS(holder h){
    Number length = getN(++h);
    String val = (String)malloc(length);
    h++;
    for (int i = 0; i<length; i++) {
        char c = (char)getN(h++);
        val[i] = c;
    }
    return val;
}
#define setN(holder,value) holder = addNumberToMainStack(value)
#define setS(holder,value) holder = addStringToMainStack(value)
#define setAN(holder,cap,...) hodler = defAN(cap,__VA_ARGS__)
#define setAS(holder,cap,...) holder = defAS(cap,__VA_ARGS__)
holder defN(Number n){
    return addNumberToMainStack(n);
}
holder defS(String s){
    return addStringToMainStack(s);
}

#define defAN(cap,...) (defN(-125)+1);addNumberPtrsToMainStack(cap,__VA_ARGS__);
#define defAS(cap,...) (defN(-125)+1);addStringPtrsToMainStack(cap,__VA_ARGS__);

#define ARR ((Number)*(mainStack[autoreleaseNestingCount]+
#define O +
#define EAO ))
#define getAOS(arr,num) getS(ARR arr O num EAO)
#define getAON(arr,num) ARR (ARR arr O num EAO) EAO
void fillWithArgs(holder **ha,four_byte cap,UNDEFINED_END_OF_PARAMETERS);
#define __holder_data_array__(name,cap,...) holder *name = (holder*)malloc(cap * sizeof(holder)); fillWithArgs(&name,cap,__VA_ARGS__)
void fillWithArgs(holder **ha,four_byte cap,UNDEFINED_END_OF_PARAMETERS){
    
}
 

#endif
