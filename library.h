#ifndef COBJECT_LIBRARY_H
#define COBJECT_LIBRARY_H

#ifndef __cplusplus

// CObject is a struct that will be used to store the variables and methods, behaving like a class.

struct CObject {
    void **variables;
    char **varNames;
    unsigned short lastVar;
    void *(**methods)();
    char **methodNames;
    unsigned short lastMethod;
};

// Creating a new type called CObject_t, which is a struct CObject.
typedef struct CObject CObject_t;

// A macro that is used to get the variable from the CObject, and cast it to the type given.
#define getVariableU(class, name, type) (type) getVariable(class, name)
// A macro that is used to call the method from the CObject, and cast it to the type given.
#define callMethodU(class, name, args, type) (type) callMethod(class, name, args)

// Initializing an CObject.
CObject_t initObject(const void *constructor, const void *deconstructor, void **args);
// Creating a new CObject, and copying the parent's variables and methods into it.
CObject_t inheritObject(CObject_t parent, void **args);
// Calling the deconstructor of the CObject.
void removeObject(CObject_t *obj, void **args);

// A function that returns the index of the element in the array that has the same name as the name given.
int getIndex(char **arr, const char *name, int size);

// Adding a variable to the CObject.
void addVariable(CObject_t *class, char *name, void *value);
// Getting the variable from the CObject.
void *getVariable(CObject_t class, const char *name);
// Setting the variable of the CObject to the value given.
void setVariable(CObject_t *class, const char *name, void *value);

// Adding a method to the CObject.
void addMethod(CObject_t *class, char *name, void *function);
// Calling the method of the CObject.
void *callMethod(CObject_t class, const char *name, void **args);
// Setting the method of the CObject to the function given.
void setMethod(CObject_t *class, const char *name, void *function);

#endif

#endif //COBJECT_LIBRARY_H
