typedef struct tag_keys_in_play {
	struct tag_keys_in_play *prev, *next;
	std::string value;
	unsigned int index, expiration_time;
} KeysInPlay;

class HashTable {
        public:
        HashTable(int table_size, int key_expiration);
        ~HashTable();
        bool increment(const char *key, int amount = 1);
        int get_count(const char *key);
        KeysInPlay *first_key();
        KeysInPlay *next_key();
		void kill_key(KeysInPlay *key);
        private:
        int *table, table_size, key_expiration;
        KeysInPlay *keys_in_play, *current_key;
        unsigned int compute_index(const char *key);
};


