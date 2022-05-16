#ifndef COBJECT_LIBRARY_H
#define COBJECT_LIBRARY_H

#ifndef __cplusplus

// FoxObject is a struct that will be used to store the variables and methods, behaving like a class.

typedef struct {
    void **variables;
    char **varNames;
    unsigned short lastVar;
    void *(**methods)();
    char **methodNames;
    unsigned short lastMethod;
} FoxObject;

// A macro that is used to get the variable from the FoxObject, and cast it to the type given.
#define getVariableU(class, name, type) (type) getVariable(class, name)
// A macro that is used to call the method from the FoxObject, and cast it to the type given.
#define callMethodU(class, name, args, type) (type) callMethod(class, name, args)

// Initializing an FoxObject.
FoxObject initObject(const void *constructor, const void *deconstructor, void **args);
// Creating a new FoxObject, and copying the parent's variables and methods into it.
FoxObject inheritObject(FoxObject parent, void **args);
// Calling the deconstructor of the FoxObject.
void removeObject(FoxObject *obj, void **args);

// A function that returns the index of the element in the array that has the same name as the name given.
int getIndex(char **arr, const char *name, int size);

// Adding a variable to the FoxObject.
void addVariable(FoxObject *class, char *name, void *value);
// Getting the variable from the FoxObject.
void *getVariable(FoxObject class, const char *name);
// Setting the variable of the FoxObject to the value given.
void setVariable(FoxObject *class, const char *name, void *value);

// Adding a method to the FoxObject.
void addMethod(FoxObject *class, char *name, void *function);
// Calling the method of the FoxObject.
void *callMethod(FoxObject class, const char *name, void **args);
// Setting the method of the FoxObject to the function given.
void setMethod(FoxObject *class, const char *name, void *function);

#endif

#endif //FoxObject_LIBRARY_H

