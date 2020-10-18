#ifndef STRUCT_H
#define STRUCT_H

#define EMPTY '\t'

struct Node {
	char *name;
    int count;
	struct Node *left, *right, *dataFirst, *dataSecond;

	/*dataFirst and dataSecond can hold different things depending on what Node is.
	If Node is:
	1. animal dataFirst and dataSecond hold nothing
	2. tree dataFirst holds animals that are on tree and dataSecond nothing
	3. forest dataFirst holds trees that are in the forest and dataSecond holds animals that are in the forest
	*/
};

typedef struct Node* Set;

extern Set forests, trees, animals;

extern Set* search(Set *pointerToSet, char* name);

extern bool isAterisk(char *string);

extern bool isArgumentEmpty(char *string);

#endif /* STRUCT_H */