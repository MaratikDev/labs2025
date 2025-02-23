#ifndef ITERATOR_H
#define ITERATOR_H

template <typename T>
class m_vector;

template <typename T>
class Iterator {
private:
    m_vector<T>& container_obj;
    int index;
public:

    Iterator<T>(m_vector<T>& container_obj);
    Iterator<T> next();
    T value();
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

template <typename T>
Iterator<T>::Iterator(m_vector<T>& container_obj): container_obj(container_obj) {
    this->index = 0;
}

template <typename T>
Iterator<T> Iterator<T>::next() {
    if (index < container_obj.get_length()) {
        index++;
    }
    return *this;
}

template <typename T>
T Iterator<T>::value() {
    return this->container_obj.get_elem(index);
}

template <typename T>
bool Iterator<T>::is_end() {
    return index >= container_obj.get_length();
}


template <typename T>
T& Iterator<T>::operator*() {
    return container_obj.get_elem(index);
}
template <typename T>
bool Iterator<T>::operator ==(Iterator<T>& b) {
    return &container_obj == &b.container && index == b.index;
}

template <typename T>
bool Iterator<T>::operator !=(Iterator<T>& b) {
    return !(&container_obj == &b.container && index == b.index);
}
#endif // ITERATOR_H
