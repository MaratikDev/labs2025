#ifndef ITERATOR_H
#define ITERATOR_H

template <typename T>
class Vector;

template <typename T>
class Iterator {
private:
    Vector<T>& container_obj;
    int index;
public:

    Iterator<T>(Vector<T>& container_obj);
    Iterator<T> next();
    T& value();
    bool is_end();
    Iterator<T> &operator++(){
        if (index < container_obj.get_length()) {
            index++;
        }
        return *this;
    }
    T& operator*();
    bool operator ==(Iterator<T>& b);
    bool operator !=(Iterator<T>& b);
};
#endif // ITERATOR_H
