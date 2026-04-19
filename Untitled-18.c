
#include <iostream>
using namespace std;

// â”€â”€ SINGLE INHERITANCE â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
// One base â†’ one derived
class Animal
{
public:
    string name;
    void breathe() { cout << name << " is breathing\n"; }
};

class Dog : public Animal{// Dog inherits Animal
                          public :
                              void bark(){cout << name << " says: Woof!\n";
}
}
;

// â”€â”€ MULTILEVEL INHERITANCE â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
// A â†’ B â†’ C  (chain)
class Vehicle
{
public:
    int speed;
    void move() { cout << "Vehicle moving at " << speed << " km/h\n"; }
};

class Car : public Vehicle
{ // Car inherits Vehicle
public:
    string brand;
    void honk() { cout << brand << " beeps!\n"; }
};

class ElectricCar : public Car
{ // ElectricCar inherits Car (and Vehicle)
public:
    int batteryLevel;
    void charge() { cout << "Charging... " << batteryLevel << "%\n"; }
};

// â”€â”€ HIERARCHICAL INHERITANCE â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
// One base â†’ many derived
class Shape
{
public:
    string color;
    void describe() { cout << color << " shape\n"; }
};

class Circle : public Shape
{
public:
    double radius;
    double area() { return 3.14159 * radius * radius; }
};

class Rectangle : public Shape
{
public:
    double w, h;
    double area() { return w * h; }
};

class Triangle : public Shape
{
public:
    double base, height;
    double area() { return 0.5 * base * height; }
};

int main()
{
    // Single
    Dog d;
    d.name = "Rex";
    d.breathe(); // Rex is breathing   (inherited)
    d.bark();    // Rex says: Woof!    (own)

    // Multilevel â€” ElectricCar has ALL methods from Vehicle and Car
    ElectricCar ec;
    ec.speed = 120;
    ec.brand = "Tesla";
    ec.batteryLevel = 80;
    ec.move();   // Vehicle moving at 120 km/h
    ec.honk();   // Tesla beeps!
    ec.charge(); // Charging... 80%

    // Hierarchical
    Circle c;
    c.color = "red";
    c.radius = 5.0;
    Rectangle r;
    r.color = "blue";
    r.w = 4.0;
    r.h = 6.0;
    c.describe();                                   // red shape
    cout << "Circle area: " << c.area() << "\n";    // 78.54
    cout << "Rectangle area: " << r.area() << "\n"; // 24
    return 0;
}
// ACCESS SPECIFIER on inheritance controls re-exposure:
// class D : public B    â†’ public/protected members keep their access
// class D : protected B â†’ public members become protected in D
// class D : private B   â†’ public/protected become private in D