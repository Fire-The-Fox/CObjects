#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"

typedef FoxObject Animal;
typedef Animal Hybrid;

/* A constructor for the Animal FoxObject. */
void Animal_constructor(Animal *this);
/* A deconstructor for the Animal FoxObject. It is called when the FoxObject is removed. */
void Animal_deconstructor();
/* Creating a new Animal FoxObject. */
Animal Animal_New();

/* Creating a new FoxObject that inherits from the Animal FoxObject. */
Hybrid Hybrid_New(Animal parent);
/* A method that is called when the `sound` method is called on the FoxObject. */
void Hybrid_Say(const Hybrid *this);

int test_fun(const FoxObject *this);

int main() {
    /* Creating a new Animal FoxObject and assigning it to the variable `AnimalTemplate`. */
    Animal AnimalTemplate = Animal_New();

    /* Creating two new FoxObjects that inherit from the Animal FoxObject. */
    Hybrid dog = Hybrid_New(AnimalTemplate);
    Hybrid cat = Hybrid_New(AnimalTemplate);

    /* Setting the variables of the FoxObjects. */
    setVariable(&dog, "type", "Dog");
    setVariable(&dog, "sound", "Bark");
    setVariable(&cat, "type", "Cat");
    setVariable(&cat, "sound", "Meow");

    /* Calling the `sound` method on the `dog` and `cat` FoxObject. */
    callMethod(dog, "sound", NULL);
    callMethod(cat, "sound", NULL);

    /* Removing the FoxObjects from memory. */
    removeObject(&dog, NULL);
    removeObject(&cat, NULL);
    removeObject(&AnimalTemplate, NULL);
    
    FoxObject test = initObject(NULL, NULL, NULL);
    int cislo = 5165;
    addVariable(&test, "cislo", &cislo);
    addMethod(&test, "fun", &test_fun);
    
	printf("\nMethod call returned: %d\n", callMethodU(test, "fun", NULL, int*));
    
    removeObject(&test, NULL);

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

int test_fun(const FoxObject *this) {
	return *getVariableU(*this, "cislo", int*);
}
