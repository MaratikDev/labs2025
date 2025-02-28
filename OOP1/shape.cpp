#include "shape.h"

Shape::Shape(std::string name){
    this->name = name;
}
std::ostream& operator<<(std::ostream& os, const Shape& shape) {
    shape.print(os);
    return os;
}
