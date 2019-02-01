// Actually fName and sName can have up to 19 non-null symbols.
// Anyway last symbol cutting off for value separating in memory
// due to outputtipng  purposes. I can output 20 symbols one-by-one, but
// it much worse than just outputting as char pointer until null-byte
struct Person
{
	// short id;
	char fName[20];
	char sName[20];
	bool male;
	short age;
};

struct Table{
	Person* rows;
	int length;

	Table(const char*);
	Table();
	~Table();

	void print(bool);
	Table select(const char*, const char*, bool comp(const char*, const char*));
	Table select(const char*, const int, bool comp(const int, const int));
	Table& del(const char*, const char*, bool comp(const char*, const char*));
	Table& del(const char*, const int, bool comp(const int, const int));
	Table& insert(char*, char*, bool, int);
	Table& insert(Person*, const int);
	Table sort(const char*, const bool);
	void save(const char*);
};
