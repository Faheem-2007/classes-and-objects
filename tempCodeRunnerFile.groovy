#include <iostream>
using namespace std;

class Animal {
public:
    // WITHOUT virtual — static binding (early binding)
    void sound_static() { cout << "Animal sound\n"; }

    // WITH virtual — dynamic binding (late binding)
    virtual void sound() { cout << "Animal sound\n"; }
};

class Dog : public Animal {
public:
    void sound_static() { cout << "Woof\n"; }   // hides base version
    void sound() override { cout << "Woof\n"; } // overrides base version
};

class Cat : public Animal {
public:
    void sound_static() { cout << "Meow\n"; }
    void sound() override { cout << "Meow\n"; }
};

int main() {
    Dog dog; Cat cat;

    // ── WITHOUT VIRTUAL: pointer type decides ──────────
    Animal *p = &dog;
    p->sound_static();  // "Animal sound" ← WRONG! Calls Animal's version
                        // because p is Animal*, binding at compile time

    // ── WITH VIRTUAL: object type decides ─────────────
    p->sound();         // "Woof" ← CORRECT! Calls Dog's version
                        // because actual object is Dog, binding at runtime

    // Polymorphic array — the power of virtual
    Animal *animals[] = { &dog, &cat };
    for (int i=0; i<2; i++) {
        animals[i]->sound();   // Woof, Meow — correct for each object
    }
     return 0;
}