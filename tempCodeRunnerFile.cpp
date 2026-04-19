#include <iostream>
#include <string>
using namespace std;

class Box {
    double length, width, height;
    string label;
public:
    // 1. DEFAULT constructor â€” no parameters
    Box() : length(1), width(1), height(1), label("default") {
        cout << "Default constructor called\n";
    }

    // 2. PARAMETERISED constructor
    Box(double l, double w, double h, string lbl="box")
        : length(l), width(w), height(h), label(lbl) {
        cout << "Parameterised constructor: " << label << "\n";
    }

    // 3. COPY constructor â€” called when object is copied
    Box(const Box &other)
        : length(other.length), width(other.width),
          height(other.height), label(other.label + "_copy") {
        cout << "Copy constructor: " << label << "\n";
    }

    double volume() const { return length * width * height; }
    string getLabel() const { return label; }

    // DESTRUCTOR â€” ~ prefix, no params, no return type
    // Called automatically when object goes out of scope or delete is used
    ~Box() {
        cout << "Destructor called for: " << label << "\n";
    }
};

// CONSTRUCTOR INITIALIZER LIST vs body assignment
class WithPointer {
    int *data;
    int  size;
public:
    WithPointer(int n) : size(n) {
        data = new int[n];   // heap allocation in constructor
        for(int i=0;i<n;i++) data[i]=i*10;
    }
    ~WithPointer() {
        delete[] data;       // MUST free in destructor â€” avoids memory leak
        cout << "Memory freed\n";
    }
};

int main() {
    Box b1;                          // Default constructor
    Box b2(3.0, 2.0, 4.0, "big");   // Parameterised
    Box b3 = b2;                     // Copy constructor
    Box b4(b2);                      // Copy constructor (explicit)

    cout << "Volume: " << b2.volume() << "\n";  // 24
    cout << "b3 label: " << b3.getLabel() << "\n";  // big_copy

    {
        WithPointer wp(5);   // constructor allocates heap
    }   // destructor called here â€” memory freed automatically
    // "Memory freed" printed

    // Destructors called in REVERSE order of construction when main exits:
    // b4, b3, b2, b1
    return 0;
}