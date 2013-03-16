char* *loop;
char* *file;
#include "Data.h"
#include "Autoreleasepool.h"
#include "Dictionary.h"
bool loop_recording = NO;
bool file_recording = NO;
bool if_mode = YES;

String filename;
four_byte looplinenumber = 0;
four_byte filelinenumber = 0;

eight_byted loopcount;
eight_byted filecount = 1;

Dictionary _fbmd;
#define kVarMax 1000
typedef struct{
    String *words;
    four_byte wordCount;
}Code;
typedef Code wordset;
#define makeCode(words,count) (Code){words,count}

no_return initProcessor(no_param);
String processCode(String code);
String performLevel1Task(String task,String extra,Code *code,String original);
String performLevel2Task(String task,String extra,Code *code,String original);
String performLevel3Task(String task,String extra,Code *code,String original);
String performLevel4Task(String task,String extra,Code *code,String original);
String performLevel5Task(String task,String extra,Code *code,String original);
Code   breakDown(String code);
String foldIntoString(Code arr);

#define string_type getFourByteForKey(_fbmd,"newline_type")
#define number_type getFourByteForKey(_fbmd,"__num_type")


no_return initProcessor(no_param){
    loop_recording = NO;
    _fbmd = dictionaryWithCapacity(kVarMax);
    addFourByteWithKey(_fbmd, addStringToMainStack("\n"), "newline");
    addFourByteWithKey(_fbmd, addStringToMainStack("string"), "newline_type");
    addFourByteWithKey(_fbmd, addStringToMainStack("\n\n\n\n\n\n"), "clear");
    addFourByteWithKey(_fbmd, addStringToMainStack("string"), "clear_type");
    
    addFourByteWithKey(_fbmd, addNumberToMainStack(0), "__num");
    addFourByteWithKey(_fbmd, addStringToMainStack("number"), "__num_type");
    //addFourByteWithKey(_fbmd, addNumberToMainStack(0), "no");
    
}
Code breakDown(String code){
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
    if(code[length-1] != ' '){code[length] = ' ';length++;}
    Code c;
    four_byte spaceCount = 0;
    for (int i = 0; i<length; i++) {
        if(code[i] == ' ')spaceCount++;
        
    }
    four_byte wordcount = spaceCount;
    c.wordCount = wordcount;
    c.words = (String*)calloc(wordcount, sizeof(String));
    four_byte level = 0;
    String temporary = (String)calloc(length+1,sizeof(char));
    for (int i = 0; /*i<length*/; i++) {
        if(code[i] != ' '){
            //lengths[level]++;
            temporary[i] = code[i];
        }
        else{
            c.words[level] = (String)calloc(i+1, sizeof(char));
            for(int r = 0;r<i;r++){
                c.words[level][r] = temporary[r];
            }
            level++;
            code += i+1;
            length -= i+1;
            i = -1;
            
        }
        if (length<1) {
            break;
        }
    };
    /*
     bool stringmode = NO;
     for (int i = 0; i < c.wordCount; i++) {
     if(c.words[i][0] == '"')stringmode = YES;
     if(stringmode == NO){
     if(c.words[i][0] == 0)
     }
     }
     */
    return c;
}
int i;
int a;
String processCode(String code){
    if(loop_recording){
        StrcmpIf(code, ==, "end loop"){
            loop_recording = NO;
            for(a = 0;a<loopcount;a++)
                for (i = 0; i<looplinenumber; i++) {
                    processCode(loop[i]);
                }
        }
        else{
            loop[looplinenumber] = code;
            looplinenumber++;
        }
        return "Success";
    }
    StrcmpIf(code, ==, "save"){file_recording = NO;printf("%s Saved\n\n",filename);return "Success";}
    
    if(file_recording){
        printf("%s\n",code);
        StrcmpIf(code, ==, "start"){
            file_recording=NO;
            for(a = 0;a<filecount;a++)
                for (i = 0; i<filelinenumber; i++) {
                    processCode(file[i]);
                }
            file_recording = YES;
            filelinenumber = 0;
            file = malloc(1000*4);
            printf("\n");
            file_recording=YES;
            return "Success";
        }
        else{
            file[filelinenumber] = code;
            filelinenumber++;
        }
        return "Success";
    }
    String error = "";
    String task = "";
    String extra;
    StrcmpIf(code, ==, "stop looping")a = i = (loopcount>looplinenumber)?loopcount:looplinenumber;
    Code c = breakDown(code);
    if(c.wordCount < 1)return "No command";
    //check for print call... task = "print" extra = "var" || "num" || "str"
    if(strcmp(c.words[0], "print") == 0){
        task = "print";
        if(c.wordCount != 1){
            byte fl = c.words[1][0];
            byte ll = c.words[c.wordCount-1][strlen(c.words[c.wordCount-1])-1];
            if(fl >= '-' && fl <= '9')extra = "num";
            else if ((fl == '\"' && ll == '\"') || (fl == '\'' && ll == '\''))extra = "str";
            else extra = "var";
        }
        else error = "No parameters provided for 'print' call";
    }
    //check for variable declarations
    if(strcmp(c.words[0], "create") == 0){
        task = "declare";
        if(c.wordCount < 3)error = "Not enough parameters for call of 'create'";
        if(c.wordCount > 3)error = "Too many parameters for call of 'create'";
        
    }
    //check for variable setting
    if(strcmp(c.words[0], "set") == 0 && c.wordCount > 3)if(strcmp(c.words[2], "to") == 0)task = "set";
    
    StrcmpIf(c.words[0],==,"loop"){
        loop_recording = YES;
        looplinenumber = 0;
        loop = malloc(1000*4);
        loopcount = atof(c.words[1]);
        return "Success";
    }
    StrcmpIf(c.words[0],==,"open"){
        file_recording = YES;
        filelinenumber = 0;
        file = malloc(1000*4);
        // loopcount = atof(c.words[1]);
        printf("\n%s:\n",c.words[1]);
        filename = c.words[1];
        return "Success";
    }
    StrcmpIf(c.words[0], ==, "run"){
        StrcmpIf(c.words[1], ==, filename){
            for(a = 0;a<filecount;a++)
                for (i = 0; i<filelinenumber; i++) {
                    processCode(file[i]);
                }
            printf("\n");
            return "Success";
        }
        else{
            printf("%s not recognized\n",c.words[1]);
            return "Success";
        }
    }
    
    
    
    if(strcmp(task, "") == 0)error = "Undentified command";
    //Finally we perform the desired task and return the output
    return (strcmp(error, "") == 0)?performLevel1Task(task, extra, &c,code):error;
}

String performLevel1Task(String task,String extra,Code *code,String original){
    String error = "Success";
    bool level2 = NO;
    // Print call
    if(strcmp(task,"print") == 0){
        if(code->wordCount > 1){
            if(strcmp(extra, "num") == 0){
                String i = code->words[1];
                double a = atof(i);
                if(floor(a) == a)
                    printf("%1.0f",a);
                else
                    printf("%.2f",a);
            }
            else if(strcmp(extra, "str") == 0){
                code->words[1] += 1;
                code->words[code->wordCount-1][strlen(code->words[code->wordCount-1])-1] = 0;
                for (int i = 1; i<code->wordCount; i++) {
                    printf("%s",code->words[i]);
                    if(i != code->wordCount-1)printf(" ");
                }
            }
            else if(strcmp(extra, "var") == 0){
                if(code->wordCount > 3){ 
                    if(code->words[1][0] == '(' && code->words[code->wordCount-1][strlen(code->words[code->wordCount-1])-1] == ')')level2 = YES;
                }
                else{
                    String ct = (String)calloc(strlen(code->words[1])+6 , sizeof(char));
                    sprintf(ct, "%s_type",code->words[1]);
                    String calledType = getS(getFourByteForKey(_fbmd, ct));
                    if(strcmp(calledType, "number") == 0)
                        if(floor(getN(getFourByteForKey(_fbmd, code->words[1]))) == getN(getFourByteForKey(_fbmd, code->words[1])))printf("%.0f",getN(getFourByteForKey(_fbmd, code->words[1])));
                        else printf("%.2f",getN(getFourByteForKey(_fbmd, code->words[1])));
                    if(strcmp(calledType, "string") == 0){
                        //code->words[3] += 1;
                        //code->words[code->wordCount-1][strlen(code->words[code->wordCount-1])-1] = 0;
                        String str = getS(getFourByteForKey(_fbmd, code->words[1]));
                        //str += 1;
                        //str[strlen(str)-1] = 0;
                        printf("%s",str);
                    }
                }
            }
        }
        else error = "Not enough parameters found for call of 'print' ";
    }
    // Declaration
    if(strcmp(task,"declare") == 0){
        String calledType = (String)calloc(strlen(code->words[2])+6 , sizeof(char));
        sprintf(calledType, "%s_type",code->words[2]);
        if(strcmp(code->words[1],"number") == 0){
            addFourByteWithKey(_fbmd, addNumberToMainStack(0), code->words[2]);
            addFourByteWithKey(_fbmd, number_type, calledType);
        }
        else if (strcmp(code->words[1],"string") == 0){
            addFourByteWithKey(_fbmd, addStringToMainStack(""), code->words[2]);
            addFourByteWithKey(_fbmd, string_type, calledType);
        }
        else error = "Unknown type for variable declaration";
    }
    // Setting
    if(strcmp(task,"set") == 0){
        String ct = (String)calloc(strlen(code->words[1])+6 , sizeof(char));
        sprintf(ct, "%s_type",code->words[1]);
        String calledType = getS(getFourByteForKey(_fbmd, ct));
        String setteeType;
        byte fl = code->words[3][0];
        byte ll = code->words[code->wordCount-1][strlen(code->words[code->wordCount-1])-1];
        if(fl >= '-' && fl <= '9')setteeType = "number";
        else if ((fl == '\"' && ll == '\"') || (fl == '\'' && ll == '\''))setteeType = "string";
        else setteeType = "var";
        if(strcmp(calledType, setteeType) == 0){
            if(strcmp(calledType, "number") == 0){
                setFourByteForKey(_fbmd, addNumberToMainStack(atof(code->words[3])), code->words[1]);
            }
            else if(strcmp(calledType, "string") == 0){
                four_byte jump = 8 + (four_byte)strlen(code->words[1]);
                original += jump+1;
                String news = (String)calloc(strlen(original), sizeof(char));
                strcpy(news, original);
                news[strlen(news)-1] = 0;
                setFourByteForKey(_fbmd, addStringToMainStack(news), code->words[1]);
            }
        }
        else if(strcmp(setteeType, "var") == 0){
            if(code->wordCount > 5){ if((code->words[3][0] == '(' && code->words[code->wordCount-1][strlen(code->words[code->wordCount-1])-1] == ')') || (code->words[3][0] == '[' && code->words[code->wordCount-1][strlen(code->words[code->wordCount-1])-1] == ']'))level2 = YES;}
            four_byte fb = getFourByteForKey(_fbmd, code->words[3]);
            if(fb == -1)error = "Unknown Variable for call of 'set'";
            else{
                String ct = (String)calloc(strlen(code->words[3])+6 , sizeof(char));
                sprintf(ct, "%s_type",code->words[3]);
                String calledType2 = getS(getFourByteForKey(_fbmd, ct));
                if(strcmp(calledType2, calledType) == 0)setFourByteForKey(_fbmd, getFourByteForKey(_fbmd, code->words[3]), code->words[1]);
                else error = "Types for call of 'set' do not match";
            }
        }
        else error = "Types for call of 'set' do not match";
    }
    return (level2)?performLevel2Task(task, extra, code,original):error;
}


String performLevel2Task(String task,String extra,Code *code,String original){
    String error = "Success";
    // Print call, expression is expected
    if(strcmp(task, "print") == 0){
        if((code->wordCount - 1) % 2 != 1)error = "Expression does not balance out";
        else{
            code->words[1] += 1;
            code->words[code->wordCount - 1][strlen(code->words[code->wordCount - 1])-1] = 0;
            
            eight_byted first;
            eight_byted second;
            eight_byted result;
            String firstCount = code->words[1];
            String secondCount = code->words[3];
            if(firstCount[0] > '0'-1 && firstCount[0] < '9'+1){
                first = atof(firstCount);
                if(secondCount[0] > '0'-1 && secondCount[0] < '9'+1){
                    second = atof(secondCount);
                }
                else{
                    second = getN(getFourByteForKey(_fbmd, secondCount));
                }
            }
            else{
                first = getN(getFourByteForKey(_fbmd, firstCount));
                if(secondCount[0] > '0'-1 && secondCount[0] < '9'+1){
                    second = atof(secondCount);
                }
                else{
                    second = getN(getFourByteForKey(_fbmd, secondCount));
                }
            }
            switch (code->words[2][0]) {
                case '+':
                    result = first + second;
                    break;
                case '-':
                    result = first - second;
                    break;
                case '*':
                    result = first * second;
                    break;
                case '/':
                    result = first / second;
                    break;
                    
                default:
                    break;
            }
            printf("%.2f",result);
        }
    }
    
    if(strcmp(task, "set") == 0){
        if((code->wordCount - 1) % 2 != 1)error = "Expression does not balance out";
        else{
            code->words[3] += 1;
            code->words[code->wordCount - 1][strlen(code->words[code->wordCount - 1])-1] = 0;
            
            eight_byted first;
            eight_byted second;
            eight_byted result;
            String firstCount = code->words[3];
            String secondCount = code->words[5];
            if(firstCount[0] > '0'-1 && firstCount[0] < '9'+1){
                first = atof(firstCount);
                if(secondCount[0] > '0'-1 && secondCount[0] < '9'+1){
                    second = atof(secondCount);
                }
                else{
                    second = getN(getFourByteForKey(_fbmd, secondCount));
                }
            }
            else{
                first = getN(getFourByteForKey(_fbmd, firstCount));
                if(secondCount[0] > '0'-1 && secondCount[0] < '9'+1){
                    second = atof(secondCount);
                }
                else{
                    second = getN(getFourByteForKey(_fbmd, secondCount));
                }
            }
            switch (code->words[4][0]) {
                case '+':
                    result = first + second;
                    break;
                case '-':
                    result = first - second;
                    break;
                case '*':
                    result = first * second;
                    break;
                case '/':
                    result = first / second;
                    break;
                    
                default:
                    break;
            }
            setFourByteForKey(_fbmd, addNumberToMainStack(result), code->words[1]);
        }
    }
    
    
    return error;
}
