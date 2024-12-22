LinkedList **create_overflow_buckets(hash_table *table);
void free_overflow_buckets(hash_table *table);
LinkedList *allocate_list();
LinkedList *linkedlist_insert(LinkedList *list, hash_table_item *item);
hash_table_item *linkedlist_remove(LinkedList *list);
void free_linkedlist(LinkedList *list);
