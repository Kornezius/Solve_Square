#define RED             0x4
#define BLUE            0x1
#define GREEN           0x2
#define WHITE           0xF
#define YELLOW          0xE
#define MAGENTA         0xD

#define PRINT_YES       ((strcmp(word,"Yes")  == 0) || (strcmp(word,"yes")  == 0) || (strcmp(word,"y")  == 0) || (strcmp(word,"Y")  == 0))
#define PRINT_NO        ((strcmp(word,"No") == 0) || (strcmp(word,"no") == 0) || (strcmp(word,"n")  == 0) || (strcmp(word,"N")  == 0))
#define COMPARE_ANSW    (if_not_same(test.answ_ref, answ_test))
#define COMPARE_X1      (if_not_same(x1_test, test.x1_ref))
#define COMPARE_X2      (if_not_same(x2_test, test.x2_ref))
#define TEST_CONDITIONS (COMPARE_ANSW || COMPARE_X1 || COMPARE_X2)

#define my_assert(cond)                               \
if (!(cond == 1))                                     \
    {                                                 \
    printf("file %s\nline %d\n", __FILE__, __LINE__); \
    printf("  ____  ___   ___   ___   ___    \n");    \
    printf(" |     |   | |   | |   | |   |   \n");    \
    printf(" |____ |___| |___| |   | |___|   \n");    \
    printf(" |     |___  |___  |   | |___    \n");    \
    printf(" |____ |   | |   | |___| |   |   \n");    \
    abort();                                          \
    }


enum answers {E_ZERO, E_ONE, E_TWO, E_MANY};
enum tests_error { E_TESTS_ERROR, E_TESTS_OK, E_SYMBOL};


struct testCase
{
    double a, b, c;
    double answ_ref;
    double x1_ref, x2_ref;
    double count_test;
};

const int END_OF_SCANF              = 3;
const int COL_PROV                  = 10;
const double EPSILON                = 0.00001;
const int MAX_LEN_WORD_YES_NO       = 4;
const int MAX_LEN_WORD_PROGRAM_FILE = 9;
const int MAX_TESTS                 = 10;
const int PARAMETERS                = 7;

const struct testCase all_tests_program[MAX_TESTS] =
{
    {.a = 1, .b = 2, .c = 1, .answ_ref = 1, .x1_ref = -1, .x2_ref = 0, .count_test = 1},
    {.a = 1, .b = 9, .c = 8, .answ_ref = 2, .x1_ref = -1, .x2_ref = -8, .count_test = 2},
    {.a = 0, .b = 0, .c = 1, .answ_ref = 3, .x1_ref = 0, .x2_ref = 0, .count_test = 3},
    {.a = 0, .b = 4, .c = 2, .answ_ref = 1, .x1_ref = -0.5, .x2_ref = 0, .count_test = 4},
    {.a = 0, .b = 0, .c = 0, .answ_ref = 3, .x1_ref = 0, .x2_ref = 0, .count_test = 5},
    {.a = -6, .b = -5, .c = -9, .answ_ref = 0, .x1_ref = 0, .x2_ref = 0, .count_test = 6},
    {.a = 3, .b = 4, .c = 18, .answ_ref = 0, .x1_ref = 0, .x2_ref = 0, .count_test = 7},
    {.a = -1, .b = 5, .c = 4, .answ_ref = 2, .x1_ref = -0.701562, .x2_ref = 5.70156, .count_test = 8},
    {.a = 0.6, .b = 0.8, .c = 0.3, .answ_ref = 0, .x1_ref = 0, .x2_ref = 0, .count_test = 9},
    {.a = 0.1, .b = 0.2, .c = 0.1, .answ_ref = 1, .x1_ref = -1, .x2_ref = 0, .count_test = 10},
};

void input                  (double* a, double* b, double* c);
void output                 (int r, double x1, double x2);
answers solve               (double a, double b, double c, double* x1, double* x2);
answers solve_line          (double b, double c, double *x1);
answers solve_dis_not_zero  (double a, double b, double d, double* x1, double* x2);
answers solve_dis_zero      (double a, double b, double* x1);
bool if_zero                (double a);
bool if_not_same            (double a, double d);
void run_test_one           (testCase test, int* run_test_check);
tests_error run_tests       ();
void error_picture          ();
void ok_picture             ();
void run_test_dialog        (int* test_ok);
void input_numbers_dialog   ();
void hello_picture          ();
void error_incorrect_symbol ();
void input_yes_no           (char* word);
void input_and_solve        ();
void reading_from_file      (int* run_test_check);
void reading_from_program   (int* run_test_check);
tests_error count_of_check  (int run_test_check);
