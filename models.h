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
	Table del(const char*, const char*, bool comp(const char*, const char*));
	Table del(const char*, const int, bool comp(const int, const int));
	void insert(const char*, const char*, const bool, const int);
	Table sort(const char*, bool);
	void drop();
};
