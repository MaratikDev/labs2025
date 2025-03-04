#ifndef LOGIC_H
#define LOGIC_H

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "appcontext.h"
#include <stdio.h>
// Файл, представляющий основную (бизнес) логику приложения,
// ничего не должен знать о Qt объектах, должен быть полностью написан на c/c++ (ОП/ООП)
#define DEFAULT_VALUE "0"
#define DEFAULT_SYSTEM 10
#define COUNT_OF_BIT_IN_NUMBER 32
#define MINUS '-'
#define MIN_SYSTEM 2
#define MAX_SYSTEM 36
#define DIGIT_0 '0'
#define DIGIT_9 '9'
#define DIGIT_A 'A'
#define DIGIT_Z 'Z'
#define DIGIT_A_SMALL 'a'
#define DIGIT_Z_SMALL 'z'
enum ResultLogic {
    Ok,
    OutOfFourBytes,
    WrongSystem,
    UnacceptableNumber,
    Empty
};

#ifdef __cplusplus
extern "C" {
#endif
// Не забывайте что функции - это действия и должны описываться глаголами
enum ResultLogic convert(struct AppContext* context, char* inputValue, int inputSystem, int outputSystem);
void initialize(struct AppContext* context);
void saveInputValue(struct AppContext* context, char* inputValue);
void saveInputSystem(struct AppContext* context, int inputSystem);
void saveOutputSystem(struct AppContext* context, int outputSystem);
void changeValues(struct AppContext* context);
unsigned int toDecimal(const char* number, int base, int isMinus);
char* fromBinaryToDecimal(const char* number);
char* fromDecimal(unsigned int decimal, int base);
int isValidNumber(const char* number, int base);
int findLengthOfNumber(int base);
char* toBinary(const char* number, int base);
#ifdef __cplusplus
}
#endif

#endif // LOGIC_H
