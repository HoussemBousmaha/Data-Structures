#ifndef HASH_H_
#define HASH_H_

void print_table(int *table, int table_size);

// maps every "value" to a certain index in a table of size "TABLE_SIZE"
int hash_function(int value, int table_size);

// creates a hash table with unique random values
void init_hash_table(int *table, int table_size);

bool insert(int *table, int data, int table_size);
bool search(int *table, int data, int table_size);

#endif
