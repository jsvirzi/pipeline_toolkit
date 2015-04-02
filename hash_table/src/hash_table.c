KeysInPlay *HashTable::first_key() {
		if(keys_in_play == 0) return 0;
		current_key = keys_in_play;
		printf("current key = %x. prev = %x. next = %x. index = %d\n", 
			(unsigned int)current_key, (unsigned int)current_key->prev, (unsigned int)current_key->next, current_key->index); 
		return current_key;
}

KeysInPlay *HashTable::next_key() {
        KeysInPlay *key = current_key->next;
		current_key = key;
		printf("current key = %x. prev = %x. next = %x. index = %d\n", 
			(unsigned int)current_key, (unsigned int)current_key->prev, (unsigned int)current_key->next, current_key->index); 
		return (key == keys_in_play) ? 0 : key;
}

void HashTable::kill_key(KeysInPlay *key) {
	table[key->index] = 0;
	KeysInPlay *key_a = key->prev;
	KeysInPlay *key_b = key->next;
	if(key_a == key_b) {
		keys_in_play = 0;
	} else {
		key_a->next = key_b;
		key_b->prev = key_a;
	}
	delete key;
}

unsigned int HashTable::compute_index(const char *key) {
        unsigned int index = 0;
		for(;*key;++key) index = *key + (index << 5) - index;
		index = index % table_size;
        return index;
}

int HashTable::get_count(const char *key) {
        int index = compute_index(key);
        return table[index];
};

HashTable::HashTable(int table_size, int key_expiration) {
	this->key_expiration = key_expiration;
	this->table_size = table_size;
	table = new int [ table_size ];
	memset(table, 0, table_size * sizeof(int));
	keys_in_play = 0;
}

bool HashTable::increment(const char *key_string, int amount) {
	int index = compute_index(key_string);
	if(table[index] == 0) {
		KeysInPlay *key = new KeysInPlay;
		if(keys_in_play == 0) {
			keys_in_play = key;
			key->prev = key->next = key;
		}

		key->expiration_time = time(0) + key_expiration;
		key->value = key_string;
		key->index = index;

	/* insert the key into the linked chain */
		KeysInPlay *last_key = keys_in_play->prev;
		last_key->next = key;
		key->prev = last_key;
		keys_in_play->prev = key;
		key->next = keys_in_play;
	}
	table[index] += amount;
	return true;
};

HashTable::~HashTable() {
	delete [] table;
};


