extern int CURRENT_YEAR;
extern int CURRENT_MONTH;
extern int CURRENT_DAY;

void get_expiration_date(int creation_year, int creation_month,
                         int creation_day, int& exp_year, int& exp_month,
                         int& exp_day);

void input_date(int& year, int& month, int& day);
void get_date_string(char date_str[11], int year, int month, int day);
void initialize_current_date();
