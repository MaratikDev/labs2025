#ifndef STATICITERATOR_H
#define STATICITERATOR_H
template <typename T>
class Vector;

template <typename T>
class StaticIterator {
private:
    const Vector<T>& containerObj;
    int index;
public:
    StaticIterator<T>(const  Vector<T>& containerObj);
    StaticIterator<T> next();
    const T& value() const;
    bool isEnd() const;
    const T& operator*() const;
    bool operator ==(StaticIterator<T>& b) const;
    bool operator !=(StaticIterator<T>& b) const;
    StaticIterator<T>& operator++();
};
#endif // STATICITERATOR_H
