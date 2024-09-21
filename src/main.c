#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "hash_table.h"

#define HT_INITIAL_BASE_SIZE 53

void test_ht_operations() {
    // Step 1: Create a new hash table
    ht_hash_table* ht = ht_new();
    assert(ht != NULL);  // Ensure that the table is created

    // Step 2: Test inserting key-value pairs
    ht_insert(ht, "key1", "value1");
    ht_insert(ht, "key2", "value2");
    ht_insert(ht, "key3", "value3");

    // Step 3: Test retrieving key-value pairs
    char* value1 = ht_search(ht, "key1");
    char* value2 = ht_search(ht, "key2");
    char* value3 = ht_search(ht, "key3");

    // Ensure that the retrieved values match the inserted ones
    assert(value1 != NULL && strcmp(value1, "value1") == 0);
    assert(value2 != NULL && strcmp(value2, "value2") == 0);
    assert(value3 != NULL && strcmp(value3, "value3") == 0);

    printf("Key-value retrieval test passed!\n");

    // Step 4: Test deleting a key
    ht_delete(ht, "key2");
    value2 = ht_search(ht, "key2");
    assert(value2 == NULL);  // The value should be deleted

    printf("Key deletion test passed!\n");

    // Step 5: Clean up the hash table
    ht_del_hash_table(ht);
    printf("Hash table deletion test passed!\n");
}

void test_resize_up_and_down() {
    ht_hash_table* ht = ht_new();

    printf("Initial hash table size: %d\n", ht->size);

    // Insert items to trigger resize up based on 70% load factor
    int threshold = (int)(ht->size * 0.7);  // 70% of the current size
    for (int i = 1; i <= threshold + 1; i++) {
        char key[10], value[10];
        sprintf(key, "key%d", i);
        sprintf(value, "value%d", i);
        ht_insert(ht, key, value);
    }

    // Check if resizing up occurred
    printf("Hash table size after inserting %d items: %d\n", threshold + 1, ht->size);
    assert(ht->size > HT_INITIAL_BASE_SIZE);  // Size should have increased after resizing up

    // Ensure all items can still be found
    for (int i = 1; i <= threshold + 1; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        assert(ht_search(ht, key) != NULL);
    }
    printf("All items correctly found after resizing up.\n");

    // Delete items to trigger resize down
	printf("TEST1");
	printf("TEST1");
	printf("TEST1");
	printf("TEST1");
	printf("TEST1");
    for (int i = 1; i <= threshold - 2; i++) {  // Deleting enough to drop below 10%
        char key[10];
        sprintf(key, "key%d", i);
        ht_delete(ht, key);
    }

    // Check if resizing down occurred
    printf("Hash table size after deleting %d items: %d\n", threshold - 2, ht->size);
    assert(ht->size < HT_INITIAL_BASE_SIZE * 2);  // Size should have decreased after resizing down

    // Ensure remaining items can still be found
    for (int i = threshold - 1; i <= threshold + 1; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        assert(ht_search(ht, key) != NULL);
    }
    printf("All remaining items correctly found after resizing down.\n");

    // Clean up
    ht_del_hash_table(ht);
    printf("Hash table successfully deleted.\n");
}

int main() {
	test_ht_operations();
	test_resize_up_and_down();
	printf("All tests passed!\n");
	return 0;
}

