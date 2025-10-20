// Global arrays
extern int USERIDS[100];
extern char USERNAMES[100][100];
extern int USER_GENDERS[100];
extern char USER_EMAILS[100][100];
extern char USER_ADDRESSES[100][100];
extern int USER_BIRTHDATES[100][3];
extern int USER_CREATION_DATES[100][3];
extern int USER_EXPIRATION_DATES[100][3];
// Initialize users
void initialize_user_data();

// Users related functions
int is_existing_user(int user_id);
int register_user(int user_id);
void print_user_info(int user_id);
