#ifndef APPCONTEXT_H
#define APPCONTEXT_H
#define MAX_LENGTH_OF_NUMBER 33

struct AppContext {
    char outputValue[MAX_LENGTH_OF_NUMBER];
    char inputValue[MAX_LENGTH_OF_NUMBER];
    int inputSystem;
    int outputSystem;
};

#endif // APPCONTEXT_H
