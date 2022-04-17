#include <stdio.h>
#include <string.h>
#include "library.h"

typedef CObject_t Animal;
typedef Animal Hybrid;

/* A constructor for the Animal CObject. */
void Animal_constructor(Animal *this);
/* A deconstructor for the Animal CObject. It is called when the CObject is removed. */
void Animal_deconstructor();
/* Creating a new Animal CObject. */
Animal Animal_New();

/* Creating a new CObject that inherits from the Animal CObject. */
Hybrid Hybrid_New(Animal parent);
/* A method that is called when the `sound` method is called on the CObject. */
void Hybrid_Say(const Hybrid *this);

int main() {
    /* Creating a new Animal CObject and assigning it to the variable `AnimalTemplate`. */
    Animal AnimalTemplate = Animal_New();

    /* Creating two new CObjects that inherit from the Animal CObject. */
    Hybrid dog = Hybrid_New(AnimalTemplate);
    Hybrid cat = Hybrid_New(AnimalTemplate);

    /* Setting the variables of the CObjects. */
    setVariable(&dog, "type", "Dog");
    setVariable(&dog, "sound", "Bark");
    setVariable(&cat, "type", "Cat");
    setVariable(&cat, "sound", "Meow");

    /* Calling the `sound` method on the `dog` and `cat` CObject. */
    callMethod(dog, "sound", NULL);
    callMethod(cat, "sound", NULL);

    /* Removing the CObjects from memory. */
    removeObject(&dog, NULL);
    removeObject(&cat, NULL);
    removeObject(&AnimalTemplate, NULL);

    return 0;
}

void Animal_constructor(Animal *this) {
    addVariable(this, "sound", "Animal sound");
}

void Animal_deconstructor() {
    printf("Executing deconstructor\n");
}

Animal Animal_New() {
    return initObject(&Animal_constructor, &Animal_deconstructor, NULL);
}

Hybrid Hybrid_New(Animal parent) {
    Hybrid inherit = inheritObject(parent, parent.variables);
    addMethod(&inherit, "sound", &Hybrid_Say);
    addVariable(&inherit, "type", "Hybrid");
    return inherit;
}

void Hybrid_Say(const Hybrid *this) {
    printf("%s says: %s\n", getVariableU(*this, "type", char*), getVariableU(*this, "sound", char*));
}