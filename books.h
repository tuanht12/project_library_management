extern int ISBNS[100];
extern char BOOKNAMES[100][100];
extern char BOOKAUTHORS[100][100];
extern char BOOKPUBLISHERS[100][100];
extern int BOOKYEARS[100];
extern int BOOKGENRES[100];
extern char BOOKSHELVES[100][50];
extern int BOOKCOUNTS[100];

void initialize_book_data();
void initialize_test_books();

void print_all_books();
void add_book(int isbn, int num_copies);
