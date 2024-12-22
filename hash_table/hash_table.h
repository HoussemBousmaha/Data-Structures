// function for hash table here
unsigned int hash_function(char *key);
hash_table_item *create_hash_table_item(char *key, char *value);
hash_table *init_hash_table(int size);
void handle_collision(hash_table *table, unsigned int index, hash_table_item *item);
void free_hash_table_item(hash_table_item *item);
void free_table(hash_table *table);
void hash_table_insert(hash_table *table, char *key, char *value);
void hash_table_insert_multiple_hash_table_items(hash_table *ht);
char *hash_table_search(hash_table *ht, char *key);
void hash_table_print_search(hash_table *table, char *key);
void random_string(char* st);
void hash_table_insert_multiple_items(hash_table *ht);
bool print_hash_table(hash_table *ht);
