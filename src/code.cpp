#include <string>
// ============================================================
// CSCI 232 Assignment 05 – Evolution of Data Structures
// Student Implementation
// ============================================================
std::string AUTHOR_NAME       = "Kade Heggem";
std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced. Any collaboration or use of external resources has been properly cited. I am fully aware of the consequences of academic dishonesty and agree to abide by the university's academic integrity policy.";
// ===========================================================

#include "code.hpp"
#include <iostream>
#include <format>

// ============================================================
// STAGE 0: Legacy C Union
// ============================================================

/// Converts a LegacyData union to a formatted string.
/// Format specs:
/// 'i' -> integer value as string (e.g., "42")
/// 'd' -> double value formatted to 2 decimal places (e.g., "3.14")
/// 'c' -> string pointer content (or "nullptr" if cPtr is null)
/// default -> "unknown"

std::string printLegacyData(LegacyData data, char type) {
    std::string result = "unknown";
    
    if(type == 'i'){
        result = std::format("{}", data.i);
        return result;
    }

    if(type == 'd'){
        result = std::format("{}", data.d);
        return result;
    }

    if(type == 'c'){

        if(data.cPtr != NULL) {
            result = std::format("{}", data.cPtr);
            return result;
        }

        else
            return "nullptr";
    }

    return result;
}

// ============================================================
// STAGE 1: C-Style Struct
// ============================================================

/// Initializes a structNode with value, type indicator, and nullptr nextPtr.
void initStructNode(structNode* nPtr, LegacyData val, char type) {
    if(nPtr == NULL){
        return;
    }

    else {
    nPtr->value = val;
    nPtr->typeData = type;
    nPtr->nextPtr = nullptr;
    };
}

/// Dynamically allocates two structNodes.
/// Node 1: int 5 ('i')
/// Node 2: double 3.14 ('d')
/// Links Node 1 -> Node 2 -> nullptr
/// Returns pointer to Node 1.
structNode* createTwoStructNodes() {
    structNode* node1Ptr = new structNode();
    LegacyData a;
    a.i = 5;
    initStructNode(node1Ptr, a, 'i');

    structNode* node2Ptr = new structNode();
    LegacyData b;
    b.d = 3.14;
    initStructNode(node2Ptr, b, 'd');

    node1Ptr->nextPtr = node2Ptr;

    return node1Ptr;
}

// ============================================================
// STAGE 2: Early C++ Class (Classic Constructor)
// ============================================================

/// Constructor: Assign fields inside curly braces.
/// DO NOT use member initializer lists here!

// uncomment the following code to implement the classNode constructor

classNode::classNode(LegacyData val, classNode* nPtr, char type) {
    value = val;
    nextPtr = nPtr;
    typeData = type;
}

/// Dynamically allocates two classNodes (int 5, double 3.14) and links them.
classNode* createTwoClassNodes() {
    LegacyData a;
    a.i = 5;
    classNode* node1Ptr = new classNode(a, NULL, 'i');

    LegacyData b;
    b.d = 3.14;
    classNode* node2Ptr = new classNode(b, NULL, 'd');

    node1Ptr->nextPtr = node2Ptr;

    return node1Ptr;
}

// ============================================================
// STAGE 3: C++98 Templates
// ============================================================

/// Dynamically allocates two classNodeT<int> objects (int 5, int 3) and links them.
classNodeT<int>* createTwoTemplateNodes() {
    classNodeT<int>* node1Ptr = new classNodeT<int>(5);
    classNodeT<int>* node2Ptr = new classNodeT<int>(3);

    node1Ptr->nextPtr = node2Ptr;

    return node1Ptr;
}

// ============================================================
// STAGE 4: C++17 Variant and LinkedList Manager
// ============================================================


LinkedList::LinkedList() {
    this->headPtr = nullptr;
    this->counter = 0;
}

LinkedList::~LinkedList() {
    destroyList();
}

void LinkedList::destroyList() {
    if (headPtr == nullptr)
    {
        return;
    }

    while (headPtr != nullptr)
    {
        classNodeVariant* tempPtr = headPtr;
        headPtr = headPtr->nextPtr;
        delete tempPtr;
        counter--;
    }
}

int LinkedList::addFirst(classNodeVariant* newNodePtr) {

    if (newNodePtr == nullptr)
    {
        return -1;
    }

    newNodePtr->nextPtr = headPtr;
    headPtr = newNodePtr;
    counter++;

    return 0;
}

int LinkedList::addLast(classNodeVariant* newNodePtr) {
    if (newNodePtr == nullptr)
    {
        return -1;
    }

    newNodePtr->nextPtr = NULL;

    if (headPtr == nullptr)
    {
        headPtr = newNodePtr;
    }

    else
    {
        classNodeVariant* tempPtr = headPtr;

        while(tempPtr->nextPtr != nullptr)
        {
            tempPtr = tempPtr->nextPtr;
        }

        tempPtr->nextPtr = newNodePtr;
    }

    counter++;
    return 0;
}

int LinkedList::deleteFirst() {
    if (headPtr == nullptr)
    {
        return -1;
    }

    else
    {
        classNodeVariant* tempPtr = headPtr;
        headPtr = headPtr->nextPtr;
        delete tempPtr;
        counter--;
    }

    return 0;
}

int LinkedList::deleteLast() {
    if (headPtr == nullptr)
    {
        return -1;
    }

    if (headPtr->nextPtr == nullptr)
    {
        delete headPtr;
        headPtr = nullptr;
    }

    else
    {
        classNodeVariant* tempPtr = headPtr;

        while(tempPtr->nextPtr->nextPtr != nullptr)
        {
            tempPtr = tempPtr->nextPtr;
        }

        delete tempPtr->nextPtr;
        tempPtr->nextPtr = nullptr;
    }

    counter--;
    return 0;
}

int LinkedList::deleteValue(ModernData targetValue) {
    if (headPtr == nullptr) {
        return -1;
    }

    // Handle deleting the head node
    if (headPtr->value == targetValue) {
        classNodeVariant* tempPtr = headPtr;
        headPtr = headPtr->nextPtr;
        delete tempPtr;
        counter--;
        return 0;
    }

    classNodeVariant* tempPtr = headPtr;

    while (tempPtr->nextPtr != nullptr && tempPtr->nextPtr->value != targetValue) {
        tempPtr = tempPtr->nextPtr;
    }

    if (tempPtr->nextPtr == nullptr) {
        return -1;
    }

    classNodeVariant* tempPtr2 = tempPtr->nextPtr;
    tempPtr->nextPtr = tempPtr2->nextPtr;
    delete tempPtr2;

    counter--;
    return 0;
}

int LinkedList::printList() {
    if (headPtr == nullptr) {
        return -1;
    }

    classNodeVariant* tempPtr = headPtr;

    while (tempPtr != nullptr) {

        if (std::holds_alternative<int>(tempPtr->value))
        {
            std::cout << std::get<int>(tempPtr->value) << std::endl;
        }

        else if (std::holds_alternative<double>(tempPtr->value)) 
        {
            std::cout << std::get<double>(tempPtr->value) << std::endl;
        }

        else if (std::holds_alternative<std::string>(tempPtr->value)) 
        {
            std::cout << std::get<std::string>(tempPtr->value) << std::endl;
        }

        tempPtr = tempPtr->nextPtr;
    }

    return 0;
}

int LinkedList::listLength() {
    if (headPtr == NULL)
    {
        return 0;
    }
    
    int count = 0;
    classNodeVariant *currentPtr = headPtr;

    while(currentPtr != NULL)
    {
        count++;
        currentPtr = currentPtr->nextPtr;
    }

    return count;
}