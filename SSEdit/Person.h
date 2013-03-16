//
//  Person.h
//  SpecialChar
//
//  Created by stephen kaufer on 8/10/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Person_h
#define Person_h
#include "Data.h"



typedef data Person;

typedef byte Gender;
#define MALE (Gender)1
#define FEMALE (Gender)2
#define genderAsString(gender) (gender == MALE)?"MALE":"FEMALE"


Person makePerson(short age,String name/*,Gender gender*/);
short ageOf(Person p);
String nameOf(Person p);
short *ptrAgeOf(Person p);
//String *ptrNameOf(Person p);
void setAge(Person p,short newAge);
//Gender genderOf(Person p);

#define ClassMakePerson(title,age,name) \
Person title = makePerson(age, name); \
short *title##_age = ptrAgeOf(title); \
String title##_name = nameOf(title)

Person makePerson(short age,String name/*, Gender gender*/){
    unsigned long len = strlen(name);
    len++;
    Person p = (Person)makeData(22 + (len*2));
    *p = (signed char)-1;
    p++;
    short p_age = age;
    *p = p_age;
    p+=2;
    short name_length = len;
    *p = name_length;
    p+=2;
    p = strcpy(p, name);
    p+=name_length;
    String desc = (String)makeData(name_length + 2/*short size*/ + 14);
    sprintf(desc, "%s is %hi years old",name,age);
    p = strcpy(p, desc);
    return p;
}
short ageOf(Person p){
    p = findStart(p);
    return (short)*p;
}
short *ptrAgeOf(Person p){
    p = findStart(p);
    return (short *)p;
}
void setAge(Person p,short newAge){
    p = findStart(p);
    *p = newAge;
}
String nameOf(Person p){
    p = findStart(p);
    p+=4;
    //short len = (short)*p;
    return (char *)p;
}
String *ptrNameOf(Person p){
    p = findStart(p);
    p+=4;
    //short len = (short)*p;
    return (char **)p;
}
/*Gender genderOf(Person p){
    p = findStart(p);
    p += 4;
    return *p;
}*/

#endif
