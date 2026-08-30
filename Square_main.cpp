#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <assert.h>
#include <stdlib.h>
#include <TXlib.h>
#include "Square_functions.cpp"
#include "Square_tests.cpp"

// ------------------------------------------------------------------------
//!\mainpage Solve Square
//!This program solves square equations.
//! Program has 10 tests to check. You can choose: check the program or not.
//! It can solve square equations with real numbers into coefficients.
//! All you need to do is enter three coefficients.
//-------------------------------------------------------------------------

int main()
{
    #if defined NDEBUG
        #define my_assert(cond)
    #endif

    setlocale(LC_ALL, "");

    int test_ok = 0;

    run_test_dialog(&test_ok);

    if (test_ok == E_TESTS_OK)
    {
        input_numbers_dialog();
    }
    else if (test_ok == E_TESTS_ERROR)
    {
        txSetConsoleAttr(RED);
        fprintf(stderr,"Error\n"
        "Программа не прошла проверки\n");
        error_picture();
    }
    else if (test_ok == E_SYMBOL)
    {
        error_incorrect_symbol();
    }

    return 0;
}

//--------------------------------------------
//! Solves square equations ax^2 + bx + c = 0
//!
//! @param [in] a - coefficient
//! @param [in] b - coefficient
//! @param [in] c - coefficient
//! @param [out] x1 - point to the first root
//! @param [out] x2 - point to the second root
//!
//! @return Number of roots
//--------------------------------------------
answers solve(double a, double b, double c, double* x1, double* x2)
{
    my_assert(x1 != NULL);
    my_assert(x2 != NULL);
    my_assert(x1 != x2);

    double d = 0;

    d = b * b - (4 * a * c);

    if (if_zero(a))
    {
        return solve_line(b, c, x1);
    }
    else if (d < 0)
    {
        return E_ZERO;
    }
    else if (if_zero(d))
    {
        return solve_dis_zero(a, b, x1);
    }
    else
    {
        return solve_dis_not_zero(a, b, d, x1, x2);
    }
}

//-------------------------------------------
//! Input coefficients
//!
//! @param [out] a - point to the coefficient
//! @param [out] a - point to the coefficient
//! @param [out] c - point to the coefficient
//!
//-------------------------------------------

void input(double* a, double* b, double* c)
{
    int ch = 0;

    my_assert(a != NULL);
    my_assert(b != NULL);
    my_assert(c != NULL);
    my_assert(a!= b);
    my_assert(a != c);
    my_assert(b != c);

    txSetConsoleAttr(BLUE);
    printf("Введите три коэффицента(в формате: a b c):");
    txSetConsoleAttr(YELLOW);

    while ((scanf("%lg %lg %lg", a, b, c) < END_OF_SCANF) || ((ch = getchar()) != '\n'))
    {
        error_incorrect_symbol();
        txSetConsoleAttr(BLUE);
        printf("Повторите попытку:");
        txSetConsoleAttr(YELLOW);
        while ((ch = getchar()) != '\n');
    }
}

//-----------------------------------------------------
//! Output Number of roots, first answer, second answer
//!
//! @param [in] answ - Number of roots
//! @param [in] x1 - first root
//! @param [in] x2 - second root
//-----------------------------------------------------
void output(int answ, double x1, double x2)
{
    txSetConsoleAttr(MAGENTA);

    switch (answ)
    {
        case E_ZERO: printf("Ноль решений\n");
                break;
        case E_ONE:  printf("Одно решение: %lg\n", x1);
                break;
        case E_TWO:  printf("Два решения: %lg %lg\n", x1, x2);
                break;
        case E_MANY: printf("Множество решений\n");
                break;
        default:     fprintf(stderr,"Ошибка: невозможное число корней\n");
    }

    ok_picture();

}

//---------------------------------------------
//! Solve linear equation if a is 0, bx + c = 0
//!
//! @param [in] b - coefficient
//! @param [in] c - coefficient
//! @param [out] x1 - point to the first root
//!
//! @return Number of roots
//---------------------------------------------
answers solve_line(double b, double c, double* x1)
{
    my_assert(x1 != NULL);

    if (if_zero(b))
    {
        return E_MANY;
    }
    else
    {
        *x1 = - c / b;

        return E_ONE;
    }
}

//---------------------------------------------
//! Solve square equation if discriminant not 0
//!
//! @param [in] a - coefficient
//! @param [in] b - coefficient
//! @param [in] c - coefficient
//! @param [out] x1 - point to the first root
//! @param [out] x2 - point to the second root
//!
//! @return Number of roots
//---------------------------------------------
answers solve_dis_not_zero(double a, double b, double d, double* x1, double* x2)
{
    my_assert(x1 != NULL);
    my_assert(x2 != NULL);
    my_assert(x1 != x2);

    double sqrt_d = sqrt(d);
    *x1 = (- b + sqrt_d) / (2 * a);
    *x2 = (- b - sqrt_d) / (2 * a);

    return E_TWO;
}

//---------------------------------------------
//! Solve square equations if discriminant is 0
//!
//! @param [in] a - coefficient
//! @param [in] b - coefficient
//! @param [out] x1 - point to the root
//!
//! @return Number of roots
//---------------------------------------------
answers solve_dis_zero(double a, double b, double* x1)
{
    my_assert(x1 != NULL);

    *x1 = - b / (2 * a);

    return E_ONE;
}

//-------------------------------------------------
//! Compare double numbers with 0
//!
//! @param [in] a - double number
//!
//! @return true or false (this number zero or not)
//-------------------------------------------------
bool if_zero(double a)
{
    if (fabs(a) < EPSILON)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//---------------------------------------------------
//! Compare two double numbers
//!
//! @param [in] a - double number
//! @param [in] b - double number
//!
//! @return true or false (same there numbers or not)
//---------------------------------------------------
bool if_not_same(double a, double b)
{
    if (fabs(a - b) > EPSILON)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void run_test_dialog (int* test_ok)
{
    my_assert(test_ok != NULL);

    char word[MAX_LEN_WORD_YES_NO] = {};

    hello_picture();

    printf("Запустить тест программы(Yes/No):");
    scanf("%3s", word);

    int ch = 0;
    while ((!PRINT_YES) && (!PRINT_NO))
    {
        while ((ch = getchar()) != '\n');
        error_incorrect_symbol();
        txSetConsoleAttr(BLUE);
        printf("Повторите попытку:");
        txSetConsoleAttr(YELLOW);
        scanf("%3s", word);
    }
    if (PRINT_YES)
    {
        txSetConsoleAttr(MAGENTA);
        *test_ok = run_tests();
    }
    else if (PRINT_NO)
    {
        txSetConsoleAttr(MAGENTA);
        *test_ok = E_TESTS_OK;
    }
}

//----------------------------------------------
//! Does the user want to solve square equations
//!
//! @return true or false (yes or no)
//----------------------------------------------
void input_numbers_dialog()
{
    char word[MAX_LEN_WORD_YES_NO] = {};

    do
    {
        input_and_solve();

        input_yes_no(word);
    }
    while (PRINT_YES);

    if (!PRINT_NO)
    {
       error_incorrect_symbol();
    }
}

//--------------------------------
//! Message about incorrect symbol
//--------------------------------
void error_incorrect_symbol()
{
    txSetConsoleAttr(RED);
    printf("Error\n"
        "Введен некорректный симол\n");
    error_picture();
}

//---------------------------------
//! Picture if something went wrong
//----------------=----------------
void error_picture()
{
    txSetConsoleAttr(YELLOW);
    printf(" __________  \n");
    printf(" |        |  \n");
    printf(" | x    x |  \n");
    printf(" |        |  \n");
    printf(" |  ----  |  \n");
    printf(" |________|  \n");
    txSetConsoleAttr(RED);
}

//----------------------
//! Picture if all is ok
//----------------------
void ok_picture()
{
    txSetConsoleAttr(YELLOW);
    printf(" __________  \n");
    printf(" |        |  \n");
    printf(" | 0    0 |  \n");
    printf(" |        |  \n");
    printf(" |  ___/  |  \n");
    printf(" |________|  \n");
}

//----------------------------
//! First message with picture
//----------------------------
void hello_picture()
{
    txSetConsoleAttr(MAGENTA);
    printf("Программа решения квадратных уравнений\n");
    printf("               ______ \n");
    printf("              |      |\n");
    printf("              |      |\n");
    printf("              |______|\n\n");
}

//--------------------------------------
//! User input Yes or No
//! @param [out] word word - user answer
//--------------------------------------
void input_yes_no(char* word)
{
    assert(word != NULL);

    printf("Продолжить решать уравнения (Yes/No):");
    scanf("%3s", word);
}

//-----------------------------------------------------------------------
//! Combine input coefficients, solve square equations and output answers
//-----------------------------------------------------------------------
void input_and_solve()
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

    input(&a, &b, &c);

    int answ = solve(a, b, c, &x1, &x2);

    output(answ, x1, x2);
}
