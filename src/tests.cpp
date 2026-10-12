#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <sstream>
#include <iostream>

// ============================================================
// STAGE 0 Tests
// ============================================================

/// Create a LegacyData union with an int (42). Call printLegacyData.
/// Verify the returned string matches "42".
void test_printLegacyData_int(void) 
{
    LegacyData a;
    a.i = 42;

    std::string resultVal = printLegacyData(a, 'i');

    TEST_ASSERT_TRUE(resultVal == "42");
}

/// Create a LegacyData union with a double (3.14). Call printLegacyData.
/// Verify the returned string matches "3.14".
void test_printLegacyData_double(void) 
{
    LegacyData b;
    b.d = 3.14;

    std::string resultVal = printLegacyData(b, 'd');

    TEST_ASSERT_TRUE(resultVal == "3.14");
}

// ============================================================
// STAGE 1 Tests
// ============================================================

/// Call createTwoStructNodes().
/// Verify head->value contains int 5 with type 'i', and head->nextPtr->value contains double ~3.14 with type 'd'.
/// Clean up allocated memory.
void test_createTwoStructNodes_links_correctly(void) 
{
    structNode* resultPtr = createTwoStructNodes();

    TEST_ASSERT_EQUAL('i', resultPtr->typeData);
    TEST_ASSERT_EQUAL(5, resultPtr->value.i);

    TEST_ASSERT_EQUAL('d', resultPtr->nextPtr->typeData);
    TEST_ASSERT_TRUE(resultPtr->nextPtr->value.d == 3.14);

    delete resultPtr->nextPtr;
    delete resultPtr;
}

// ============================================================
// STAGE 2 Tests
// ============================================================

/// Call createTwoClassNodes().
/// Verify head->value contains int 5 with type 'i', and head->nextPtr->value contains double ~3.14 with type 'd'.
/// Clean up allocated memory.
void test_createTwoClassNodes_links_correctly(void) 
{
    classNode* resultPtr = createTwoClassNodes();

    TEST_ASSERT_EQUAL('i', resultPtr->typeData);
    TEST_ASSERT_EQUAL(5, resultPtr->value.i);

    TEST_ASSERT_EQUAL('d', resultPtr->nextPtr->typeData);
    TEST_ASSERT_TRUE(resultPtr->nextPtr->value.d == 3.14);

    delete resultPtr->nextPtr;
    delete resultPtr;
}

// ============================================================
// STAGE 3 Tests
// ============================================================

/// Call createTwoTemplateNodes().
/// Verify head->value is 5 and head->nextPtr->value is 3.
/// Clean up allocated memory.
void test_createTwoTemplateNodes_links_correctly(void) 
{
    classNodeT<int>* resultPtr = createTwoTemplateNodes();

    TEST_ASSERT_EQUAL(5, resultPtr->value);

    TEST_ASSERT_EQUAL(3, resultPtr->nextPtr->value);

    delete resultPtr->nextPtr;
    delete resultPtr;
}

// ============================================================
// STAGE 4: LinkedList Tests
// ============================================================

/// Create a LinkedList. Add two nodes using addFirst.
/// Verify listLength() returns 2 after insertions.
void test_linkedList_addFirst_updates_counter(void) 
{
    LinkedList list;

    classNodeVariant* node1Ptr = new classNodeVariant(ModernData{5});
    classNodeVariant* node2Ptr = new classNodeVariant(ModernData{3});

    list.addFirst(node1Ptr);
    list.addFirst(node2Ptr);

    int length = list.listLength();

    TEST_ASSERT_EQUAL(2, length);
}

/// Create a LinkedList. Add nodes (10, then 20) using addLast.
/// Capture std::cout and verify elements appear in order ("10" before "20").
void test_linkedList_addLast_places_at_end(void) 
{
    LinkedList list;

    classNodeVariant* node1Ptr = new classNodeVariant(ModernData{10});
    classNodeVariant* node2Ptr = new classNodeVariant(ModernData{20});

    list.addLast(node1Ptr);
    list.addLast(node2Ptr);

    std::stringstream buffer;
    std::streambuf* originalBuffer = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    list.printList();

    std::cout.rdbuf(originalBuffer);
    std::string content = buffer.str();

    size_t pos10 = content.find("10");
    size_t pos20 = content.find("20");

    TEST_ASSERT_TRUE(pos10 < pos20);
}

/// Create a LinkedList with an int, double, and string.
/// Call deleteValue() with the double value (3.14).
/// Verify list length decreases to 2 and second call returns -1.
void test_linkedList_deleteValue_removes_variant(void) 
{
    LinkedList list;

    classNodeVariant* node1Ptr = new classNodeVariant(ModernData{5});
    classNodeVariant* node2Ptr = new classNodeVariant(ModernData{3.14});
    classNodeVariant* node3Ptr = new classNodeVariant(ModernData{"ExampleString"});

    list.addFirst(node1Ptr);
    list.addFirst(node2Ptr);
    list.addFirst(node3Ptr);

    int length = list.listLength();
    TEST_ASSERT_EQUAL(3, length);

    list.deleteValue(3.14);
    int returnVal = list.deleteValue(3.14);

    int newLength = list.listLength();
    TEST_ASSERT_EQUAL(2, newLength);

    TEST_ASSERT_EQUAL(-1, returnVal);
}

/// Create a LinkedList and insert three nodes.
/// Call destroyList().
/// Verify listLength() becomes 0.
void test_linkedList_destroyList_clears_all(void) 
{
    LinkedList list;

    classNodeVariant* node1Ptr = new classNodeVariant(ModernData{5});
    classNodeVariant* node2Ptr = new classNodeVariant(ModernData{3.14});
    classNodeVariant* node3Ptr = new classNodeVariant(ModernData{"ExampleString"});

    list.addFirst(node1Ptr);
    list.addFirst(node2Ptr);
    list.addFirst(node3Ptr);

    list.destroyList();
    int length = list.listLength();

    TEST_ASSERT_EQUAL(0, length);
}

/// Create a LinkedList with nodes (10, 20, 30).
/// Call deleteFirst().
/// Verify listLength() becomes 2 and operation returns 0.
void test_linkedList_deleteFirst(void) 
{
    LinkedList list;

    classNodeVariant* node1Ptr = new classNodeVariant(ModernData{10});
    classNodeVariant* node2Ptr = new classNodeVariant(ModernData{20});
    classNodeVariant* node3Ptr = new classNodeVariant(ModernData{30});

    list.addFirst(node1Ptr);
    list.addFirst(node2Ptr);
    list.addFirst(node3Ptr);

    int returnVal = list.deleteFirst();
    int length = list.listLength();

    TEST_ASSERT_EQUAL(0, returnVal);
    TEST_ASSERT_EQUAL(2, length);
}

/// Create a LinkedList with nodes (10, 20, 30).
/// Call deleteLast().
/// Verify listLength() becomes 2 and operation returns 0.
void test_linkedList_deleteLast(void) 
{
    LinkedList list;

    classNodeVariant* node1Ptr = new classNodeVariant(ModernData{10});
    classNodeVariant* node2Ptr = new classNodeVariant(ModernData{20});
    classNodeVariant* node3Ptr = new classNodeVariant(ModernData{30});

    list.addFirst(node1Ptr);
    list.addFirst(node2Ptr);
    list.addFirst(node3Ptr);

    int returnVal = list.deleteLast();
    int length = list.listLength();

    TEST_ASSERT_EQUAL(0, returnVal);
    TEST_ASSERT_EQUAL(2, length);
}

/// Create a LinkedList with nodes (1, 2.5, "test").
/// Redirect std::cout buffer and call printList().
/// Verify printed output contains "1", "2.5" (or "2.50"), and "test".
void test_linkedList_printList(void) 
{
    LinkedList list;

    classNodeVariant* node1Ptr = new classNodeVariant(ModernData{1});
    classNodeVariant* node2Ptr = new classNodeVariant(ModernData{2.5});
    classNodeVariant* node3Ptr = new classNodeVariant(ModernData{"test"});

    list.addFirst(node1Ptr);
    list.addFirst(node2Ptr);
    list.addFirst(node3Ptr);


    std::stringstream buffer;
    std::streambuf* originalBuffer = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    list.printList();

    std::cout.rdbuf(originalBuffer);
    std::string content = buffer.str();

    TEST_ASSERT_EQUAL_STRING("test\n2.5\n1\n", content.c_str());
}