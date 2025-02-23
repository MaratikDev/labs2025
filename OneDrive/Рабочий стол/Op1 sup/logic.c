#include "logic.h"


enum ResultLogic update(struct AppContext* context, char* inputValue, int inputSystem, int outputSystem) {
    int isMinus = 0;
    enum ResultLogic result = Ok;

    if(!(inputValue && inputSystem && outputSystem)){
            result = Empty;
        }
    else{

        if (inputValue[0] == MINUS){
            isMinus = 1;
        }
        if(!isValidNumber(inputValue, inputSystem)){
            result = UnacceptableNumber;
        }
        else if(inputSystem < MIN_SYSTEM || inputSystem > MAX_SYSTEM || outputSystem < MIN_SYSTEM || outputSystem > MAX_SYSTEM){
            result = WrongSystem;
        }
        else if(strlen(inputValue) > findLengthOfNumber(inputSystem)){
            result = OutOfFourBytes;
        }

        else{
            if(inputSystem==outputSystem){
                strncpy(context->outputValue, inputValue, MAX_LENGTH_OF_NUMBER - 1);
            }
            else{
                if(isMinus){
                    inputValue++;
                }
                strncpy(context->outputValue, fromDecimal(toDecimal(inputValue, inputSystem, isMinus), outputSystem),MAX_LENGTH_OF_NUMBER - 1);
            }
        }
    }
    return result;



}
void initialize(struct AppContext* context) {
    strncpy(context->outputValue , DEFAULT_VALUE, MAX_LENGTH_OF_NUMBER - 1);

}

unsigned int toDecimal(const char* number, int base, int isMinus) {
    int decimal = 0;
    for (size_t i = 0; i < strlen(number); i++) {
        char ch = number[i];
        int digit;
        if (ch >= DIGIT_0 && ch <= DIGIT_9) {
            digit = ch - DIGIT_0;
        }
        else if (ch >= DIGIT_A && ch <= DIGIT_Z) {
            digit = ch - DIGIT_A + DEFAULT_SYSTEM;
        }
        else{
            digit = ch - DIGIT_A_SMALL + DEFAULT_SYSTEM;
        }
        decimal = decimal * base + digit;
    }
    return isMinus ? pow(2,COUNT_OF_BIT_IN_NUMBER) - decimal : decimal;

}

char* fromDecimal(unsigned int decimal, int base) {
    static char result[MAX_LENGTH_OF_NUMBER];
    int index = 0;
    while (decimal > 0) {
        int remainder = decimal % base;
        char digit;
        if (remainder < DEFAULT_SYSTEM) {
            digit = DIGIT_0 + remainder;
        } else {
            digit = DIGIT_A + (remainder - DEFAULT_SYSTEM);
        }
        result[index++] = digit;
        decimal /= base;
    }
    for(int i = index; i < findLengthOfNumber(base); i++){
        result[index++] = DIGIT_0;
    }
    result[index] = '\0';
    strrev(result);
    return result;
}

int isValidNumber(const char* number, int base) {
    int result = 1;
    if(*number == MINUS){
        number++;
    }
    for (size_t i = 0; i < strlen(number);i++) {
        char ch = number[i];
        int digit;
        if (ch >= DIGIT_0 && ch <= DIGIT_9) {
            digit = ch - DIGIT_0;
        } else if (ch >= DIGIT_A && ch <= DIGIT_Z) {
            digit = ch - DIGIT_A + DEFAULT_SYSTEM;
        } else if (ch >= DIGIT_A_SMALL && ch <= DIGIT_Z_SMALL) {
            digit = ch - DIGIT_A_SMALL + DEFAULT_SYSTEM;
        } else {
            result = 0;
            break;
        }
        if (digit >= base) {
            result = 0;
            break;
        }
    }
    return result;
}

int findLengthOfNumber(int base){
    return COUNT_OF_BIT_IN_NUMBER/ceil(log2(base));
}
