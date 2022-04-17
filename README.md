# CObjects

Trying to implement C library with object support

## How to compile the library

```
mkdir build
cd build
cmake ..
make all
```

## Example

```c
#include <stdio.h>
#include <string.h>
#include "cobjects.h"

typedef CObject_t Animal;

/* A constructor for the Animal CObject. */
void Animal_constructor(Animal *this);
/* A deconstructor for the Animal CObject. It is called when the CObject is removed. */
void Animal_deconstructor();
/* Creating a new Animal CObject. */
Animal Animal_New();

int main() {
    Animal AnimalTemplate = Animal_New();
    
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
```