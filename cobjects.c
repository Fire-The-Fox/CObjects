#include "cobjects.h"

#include <stdlib.h>
#include <string.h>

CObject_t initObject(const void *constructor, const void *deconstructor, void **args) {
    CObject_t obj;

    /* Allocating memory for the methods array. */
    obj.methods = malloc(sizeof(void*) * 2);

    /* Making sure constructor and deconstructor won't have garbage values from malloc. */
    obj.methods[0] = NULL;
    obj.methods[1] = NULL;

    /* Size of how many methods are in methods array. */
    obj.lastMethod = 2;
    obj.lastVar = 0;

    /* Casting the pointer to a char pointer, then casting it back to a char double pointer. */
    obj.methodNames = (char **) malloc(sizeof(char**) * obj.lastMethod);

    /* Allocating memory for the method names, and copying the names into the memory. */
    obj.methodNames[0] = (char*) malloc(11);
    memcpy(obj.methodNames[0], "constructor", 11);
    obj.methodNames[1] = (char*) malloc(13);
    memcpy(obj.methodNames[1], "deconstructor", 13);

    /* Checking if the constructor is not null, and if it is not, it sets the constructor to the first method in the
    methods array, and then calls the constructor. */
    if (constructor != NULL) {
        obj.methods[0] = constructor;
        obj.methods[0](&obj, args);
    }

    /* Checking if the deconstructor is not null, and if it is not, it sets the deconstructor to the second method in the
    methods array. */
    if (deconstructor != NULL) obj.methods[1] = deconstructor;

    return obj;
}

CObject_t inheritObject(CObject_t parent, void **args) {
    CObject_t inherited;

    /* Allocating memory for the methods and variables arrays, and then setting the first method to null for removing garbage
    value. */
    inherited.methods = malloc(sizeof(void*) * parent.lastMethod);
    inherited.variables = malloc(sizeof(void**) * parent.lastVar);
    inherited.methods[0] = NULL;

    /* Allocating memory for the method and variable names. */
    inherited.methodNames = (char **) malloc(sizeof(char**) * parent.lastMethod);
    inherited.varNames = (char **) malloc(sizeof(char**) * parent.lastVar);

    /* Size of how many methods are in methods array. */
    inherited.lastMethod = parent.lastMethod;
    inherited.lastVar = 0;

    /* Copying the methods and method names from the parent CObject to the inherited CObject. */
    for (int i = 0; i < parent.lastMethod; i++) {
        inherited.methods[i] = parent.methods[i];

        inherited.methodNames[i] = malloc(sizeof(parent.methodNames[i]));
        strcpy(inherited.methodNames[i], parent.methodNames[i]);
    }

    /* Calling the constructor of the inherited CObject. */
    if (inherited.methods[0] != NULL) inherited.methods[0](&inherited, args);

    return inherited;
}

void removeObject(CObject_t *obj, void **args) {
    /* Calling the deconstructor of the object. */
    obj->methods[1](obj, args);

    /* Freeing the memory that was allocated for the method names, variable names, methods, and variables. */
    free(obj->methodNames);
    free(obj->varNames);
    free(obj->methods);
    free(obj->variables);
}

void addVariable(CObject_t *class, char *name, void *value) {

    /* Checking if the CObject has any variables, and if it does, it reallocates the memory for the variables array. */
    if (class->lastVar == 0) {
        class->variables = malloc(sizeof(void **) * 1);
        class->varNames = (char **) malloc(sizeof(char**) * 1);
        class->lastVar++;
    } else {
        class->lastVar++;
        class->variables = (void**) realloc(class->variables, class->lastVar);
    }

    /* Setting the variable name and value to the last index of the variables array. */
    class->varNames[class->lastVar-1] = name;
    class->variables[class->lastVar-1] = value;
}

void *getVariable(CObject_t class, const char *name) {

    /* Getting the index of the variable name in the variable names array, and then using that index to get the variable
    from the variables array. */
    return class.variables[getIndex(class.varNames, name, class.lastVar)];
}

int getIndex(char **arr, const char *name, int size) {
    int index;

    /* Getting the index of the variable name in the variable names array. */
    for (index = 0; index < size; index++) {
        if (!strcmp(arr[index], name)) {
            break;
        }
    }

    /* Checking if the index is equal to the size of the array, and if it is, it returns -1, otherwise it returns the
    index. */
    if (index == size) return -1;
    return index;
}

void setVariable(CObject_t *class, const char *name, void *value) {

    /* Getting the index of the variable name in the variable names array, and then using that index to set the variable
    in the variables array. */
    int index = getIndex(class->varNames, name, class->lastVar);

    class->variables[index] = value;
}

void addMethod(CObject_t *class, char *name, void *function) {

    class->lastMethod++;
    /* Reallocating the memory for the methods array, and then casting it to a void pointer double pointer. */
    class->methods = (void *(**)()) realloc(class->methods, class->lastMethod);

    /* Setting the method name and function to the last index of the methods array. */
    class->methodNames[class->lastMethod-1] = name;
    class->methods[class->lastMethod-1] = function;

}

void *callMethod(CObject_t class, const char *name, void **args) {

    /* Getting the index of the method name in the method names array, and then using that index to call the method
    from the methods array. */
    int index = getIndex(class.methodNames, name, class.lastMethod);

    return class.methods[index](&class, args);
}

void setMethod(CObject_t *class, const char *name, void *function) {

    /* Getting the index of the method name in the method names array, and then using that index to set the method
    in the methods array. */
    int index = getIndex(class->methodNames, name, class->lastMethod);

    class->methods[index] = function;
}
