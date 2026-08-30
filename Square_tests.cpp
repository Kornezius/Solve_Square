
//----------------------------------------------------------------------
//! Run one test to check program
//!
//! @param [in] test - structure with coefficients and reference answers
//! @param [out] run_test_check run_test_check - number of correct tests
//----------------------------------------------------------------------
void run_test_one(struct testCase test, int* run_test_check)
{
    double x1_test = 0, x2_test = 0;

    assert(run_test_check);

    int answ_test = solve(test.a, test.b, test.c, &x1_test, &x2_test);

    if TEST_CONDITIONS
    {
        txSetConsoleAttr(RED);
        printf("%lg Test FAILED a = %lg, b = %lg, c = %lg\n"
                "x1_test = %lg, x2_test = %lg, answ_test = %d\n"
                "x1_ref  = %lg, x2_ref  = %lg, answ_ref = %lg\n\n",
                test.count_test, test.a, test.b, test.c, x1_test,
                x2_test, answ_test, test.x1_ref, test.x2_ref, test.answ_ref);
    }
    else
    {
            (*run_test_check)++;
    }
}

//-----------------------------------------------------
//! Run all tests to check program
//!
//! @return true or false (all tests was correct or not)
//-----------------------------------------------------
tests_error run_tests()
{
    int run_test_check = 0;

    printf("Читать тесты из файла или из программы(file/program):");
    char from_test[MAX_LEN_WORD_PROGRAM_FILE] = {};
    scanf("%8s",from_test);

    if  (strcmp(from_test,"file") == 0)
    {
        reading_from_file(&run_test_check);
    }
    else if (strcmp(from_test,"program") == 0)
    {
        reading_from_program(&run_test_check);
    }
    else
    {
        return E_SYMBOL;
    }

    count_of_check(run_test_check);

}

//---------------------------------------------
//! Reading parameters for tests from file
//!
//! @param [out] run_test_check - count of test
//---------------------------------------------
void reading_from_file(int* run_test_check)
{
    txSetConsoleAttr(GREEN);
    printf("Running tests from file Square_test_file.txt\n");

    struct testCase all_tests[MAX_TESTS] = {};

    FILE* test_file = fopen("Square_test_file.txt","r");
    if (test_file)
    {
        double* buffer = (double *) calloc(PARAMETERS, sizeof(double));


        for (int count_of_test = 0; count_of_test < MAX_TESTS; count_of_test++)
        {
            my_assert(0 <= count_of_test && count_of_test < MAX_TESTS);

            for (int i = 0; i < PARAMETERS; i++)
            {
                my_assert(0 <= i && i < PARAMETERS);

                double a = 0;
                int check_fscanf = 0;

                check_fscanf = fscanf(test_file, "%lg", &a);
                if (check_fscanf)
                {
                    buffer[i] = a;
                }
            }
            all_tests[count_of_test] = {buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6]}; // TODO
            run_test_one(all_tests[count_of_test], run_test_check);
            free(buffer);
        }
    }
}

//---------------------------------------------
//! Reading parameters for tests from program
//!
//! @param [out] run_test_check - count of test
//---------------------------------------------
void reading_from_program(int* run_test_check)
{
    txSetConsoleAttr(GREEN);
        printf("Running tests from program\n");
        for (int i = 0; i < MAX_TESTS; i++)
        {
            run_test_one(all_tests_program[i], run_test_check);
        }
}

//---------------------------------------------
//! Return all test ok or not
//!
//! @param [in] run_test_check - count of test
//!
//! return all ok or not
//---------------------------------------------
tests_error count_of_check(int run_test_check)
{
    if (run_test_check < COL_PROV)
    {
        txSetConsoleAttr(RED);
        printf("Верны %d / 10 проверок\n",run_test_check);

        return E_TESTS_ERROR;
    }
    else
    {
        txSetConsoleAttr(GREEN);
        printf("Верны %d / 10 проверок\n",run_test_check);

        return E_TESTS_OK;
    }
}
