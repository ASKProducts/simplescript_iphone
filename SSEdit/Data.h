//
//  Data.h
//  SpecialChar
//
//  Created by stephen kaufer on 8/10/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Data_h
#define Data_h
#import "SSAppDelegate.h"
#import "SSViewController.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"
#include "math.h"
#define printf(...) \
do{printf(__VA_ARGS__); \
[SharedVC setTvtext:[SharedVC.tvtext stringByAppendingFormat:@__VA_ARGS__]];  \
}while(0)
//#define printf(...) printf(__VA_ARGS__)

typedef char byte;
typedef unsigned char ubyte;
typedef byte *bytePtr;
typedef byte byte_array[];
typedef byte *data;
#define makeData(size) (data)malloc(size)


typedef void zero_byte; typedef byte no_byte_array[0]; typedef zero_byte no_return; typedef zero_byte no_param;
typedef byte one_byte; typedef byte one_byte_array[1];
typedef short two_byte; typedef unsigned short utwo_byte; typedef byte two_byte_array[2];
typedef byte three_byte_array[3];
typedef int four_byte; typedef unsigned int ufour_byte; typedef float four_bytef; typedef byte four_byte_array[4]; 
typedef byte five_byte_array[5];
typedef byte six_byte_array[6];
typedef byte seven_byte_array[7];
typedef double eight_byted; typedef long int eight_byte; typedef unsigned long int ueight_byte; typedef byte eight_byte_array[8];


#define UNDEFINED_END_OF_PARAMETERS ...

#define xgetline(before) before##__LINE__
#define getline(before) xgetline(before)

#define repeat(count) for(four_byte getline(line) = 0;getline(line) < count; getline(line)++)
#define repeatUntil(condition) while(!(condition))
#define LOOP while(1)
#define BREAK_OUT_OF_LOOP break
#define SKIP_LOOP_COUNT continue


#undef YES
#undef NO
#define YES 1
#define NO 0

#define String char*
#define Stringptr String*
#define StringsAreSame(str1,str2) (strcmp(str1,str2) == 0)
#define StrcmpIf(str1,op,str2) if(strcmp(str1,str2) op 0)
typedef struct{
    String *words;
    four_byte wordCount;
}wordset;
wordset breakDownWordset(String code,char ch);
wordset breakDownWordset(String code,char ch){
    eight_byte length = strlen(code);
    String t = code;
    code = (String)calloc(length+2, sizeof(char));
    int tr = 0;
    for(int r = 0;r<length;r++){
        if(t[tr] == '\\' && t[tr+1] == 'n'){
            code[r] = '\n';
            tr+=2;
        }
        else{
            code[r] = t[tr];
            tr++;
        }
    }
    if(code[length-1] != ch){code[length] = ch;length++;}
    wordset c;
    four_byte spaceCount = 0;
    for (int i = 0; i<length; i++) {
        if(code[i] == ch)spaceCount++;
        
    }
    four_byte wordcount = spaceCount;
    c.wordCount = wordcount;
    c.words = (String*)calloc(wordcount, sizeof(String));
    four_byte level = 0;
    String temporary = (String)calloc(length+1,sizeof(char));
    for (int i = 0;; i++) {
        if(code[i] != ch)temporary[i] = code[i];
        else{
            c.words[level] = (String)calloc(i+1, sizeof(char));
            for(int r = 0;r<i;r++)c.words[level][r] = temporary[r];
            level++;
            code += i+1;
            length -= i+1;
            i = -1;
            
        }
        if (length<1) {
            break;
        }
    };
    return c;
}



typedef union{
    ubyte bit : 1;
}Bit;
typedef Bit *Binary;
#define makeBlankBin(bitcount) (Binary)calloc(bitcount,sizeof(Binary))
#define bininc(bin) do{four_byte level = 0;while(++bin[level++].bit != 1);}while(0)
#define bindecr(bin) do{four_byte level = 0;while(--bin[level++].bit != 0);}while(0)
#define addDec2Bin(dec,bin) do{four_byte level = -1;while(++level < dec){bininc(bin);}}while(0)
#define takeDecFromBin(dec,bin) do{four_byte level = -1;while(++level < dec){bindecr(bin);}}while(0)
#define printbin(bin,bitcount) do{four_byte level = bitcount-1;while(--level > -1){printf("%d",bin[level].bit);}}while(0)










typedef union{
    ubyte bit : 1; ubyte boolean : 1; /* 0 - 1 */
    ubyte two_bits : 2; /* 0 - 3 */
    ubyte three_bits : 3; /* 0 - 7 */
    ubyte four_bits : 4; /* 0 - 15 */
    ubyte five_bits : 5; /* 0 - 31 */
    ubyte six_bits : 6; /* 0 - 63 */
    ubyte seven_bits : 7; /* 0 - 127 */
    ubyte eight_bits : 8; ubyte character; ubyte one_byte; /* 0 - 255 */
    utwo_byte nine_bits : 9; /* 0 - 511 */
    utwo_byte ten_bits : 10; /* 0 - 1023 */
    utwo_byte eleven_bits : 11; /* 0 - 2047 */
    utwo_byte twelve_bits : 12; /* 0 - 4095 */
    utwo_byte thirteen_bits : 13; /* 0 - 8191 */
    utwo_byte fourteen_bits : 14; /* 0 - 16383 */
    utwo_byte fifteen_bits : 15; /* 0 - 32767 */
    utwo_byte sixteen_bits : 16; utwo_byte shortint; utwo_byte two_byte; /* 0 - 65535 */
    ufour_byte seventeen_bits : 17; /* 0 - 131071 */
    ufour_byte eighteen_bits : 18; /* 0 - 262143 */
    ufour_byte nineteen_bits : 19; /* 0 - 524287 */
    ufour_byte twenty_bits :20; /* 0 - 1048575 */
    ufour_byte twentyone_bits :21; /* 0 - 2097151 */
    ufour_byte twentytwo_bits :22; /* 0 - 4194303 */
    ufour_byte twentythree_bits :23; /* 0 - 8388607 */
    ufour_byte twentyfour_bits :24; ufour_byte three_byte : 24; /* 0 - 16777215 */
    ufour_byte twentyfive_bits :25; /* 0 - 33554431 */
    ufour_byte twentysix_bits :26; /* 0 - 67108863 */
    ufour_byte twentyseven_bits :27; /* 0 - 134217727 */
    ufour_byte twentyeight_bits :28; /* 0 - 268435455 */
    ufour_byte twentynine_bits :29; /* 0 - 536870911 */
    ufour_byte thirty_bits :30; /* 0 - 1073741823 */
    ufour_byte thirtyone_bits :31; /* 0 - 2147483647 */
    ufour_byte thirtytwo_bits :32; ufour_byte integer; ufour_byte four_byte; /* 0 - 4294967295 */
    
}unumb;
#define unc(bitcount,value) (unumb){.bitcount##_bits = value}
#define uncb(bytecount,value) (unumb){.bytecount##_byte = value}










#endif
