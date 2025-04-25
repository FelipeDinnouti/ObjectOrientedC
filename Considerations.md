The build command must include every .c file

For polymorphism to work, a class must inherit a parent class by having the parent class as a member in its struct. That however implies that the member is by value and not by reference (pointer).
However, PersonCreate() returns a pointer

Each class has its destructor method.
Each object contains itself and their parent class's instances.
Each destructor method cleans self. However, a object is a bunch of classes instances in one struct (so it only needs to be freed once)