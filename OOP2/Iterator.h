#ifndef ITERATOR_H
#define ITERATOR_H

template <typename T>
class Vector;

template <typename T>
class Iterator {
private:
    Vector<T>& containerObj;
    int index;
public:

    Iterator<T>(Vector<T>& containerObj);
    Iterator<T> next();
    T& value();
    bool isEnd();
    Iterator<T>& operator++(){
        if (index < containerObj.getLength()) {
            index++;
        }
        return *this;
    }
    T& operator*();
    bool operator ==(Iterator<T>& b);
    bool operator !=(Iterator<T>& b);
};
#endif // ITERATOR_H
