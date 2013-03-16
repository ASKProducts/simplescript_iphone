//
//  Dictionary.h
//  SpecialChar
//
//  Created by stephen kaufer on 8/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef SpecialChar_Dictionary_h
#define SpecialChar_Dictionary_h
#include "Data.h"
#include "Autoreleasepool.h"
typedef struct{
    String *DictionaryKeys;
    unumb *values;
    four_byte height;
}Dictionary;
Dictionary dictionaryWithCapacity(four_byte capacity);
no_return xaddFourByte(Dictionary *d,four_byte fb, String key);
four_byte getFourByteForKey(Dictionary d,String key);
no_return xsetFourByteForKey(Dictionary *d,four_byte fb,String key);
no_return printDictionaryfb(Dictionary d);
no_return printDictionaryfbStarting(Dictionary d,four_byte starting);



Dictionary dictionaryWithCapacity(four_byte capacity){
    Dictionary d;
    d.DictionaryKeys = (String*)calloc(capacity,sizeof(String));
    d.values = (unumb*)calloc(capacity,sizeof(unumb));
    d.height = 0;
    return d;
}
#define addFourByteWithKey(dictionary,fourbyte,key) xaddFourByte(&dictionary,fourbyte,key)
no_return xaddFourByte(Dictionary *d,four_byte fb, String key){
    d->DictionaryKeys[d->height] = key;
    d->values[d->height] = uncb(four,fb);
    d->height++;
}
four_byte getFourByteForKey(Dictionary d,String key){
    for (int i = 0; i<d.height; i++) {
        if(strcmp(d.DictionaryKeys[i], key) == 0)return d.values[i].four_byte;
    }
    return -1;
}
#define setFourByteForKey(d,fb,key) xsetFourByteForKey(&d,fb,key)
no_return xsetFourByteForKey(Dictionary *d,four_byte fb,String key){
    for (int i = 0; i<d->height; i++) {
        if(strcmp(d->DictionaryKeys[i], key) == 0)d->values[i].four_byte = fb;
    }
}
no_return printDictionaryfb(Dictionary d){
    printf("\n");
    for (int i = 0; i<d.height; i++) {
        printf("\"%s\" -> %d\n",d.DictionaryKeys[i],d.values[i].four_byte);
    }
    printf("\n");
}
no_return printDictionaryfbStarting(Dictionary d,four_byte starting){
    printf("\n");
    for (int i = starting-1; i<d.height; i++) {
        printf("\"%s\" -> %d\n",d.DictionaryKeys[i],d.values[i].four_byte);
    }
    printf("\n");
}

#endif
