#ifndef UNIT_TEST_H
# define UNIT_TEST_H

# include <stdio.h>
# include <signal.h>

# define UT_TEST(name)		int ut_test_ ## name(void)
# define UT_ASSERT(cond)	if(!(cond)) { ut_last_err = #cond; return (1);}
# define UT_RUN_TEST(test_)	printf("%s%-20s", "[\033[33mUT\033[0m] Testing ", test_->name); if((test_->test())) \
							{ printf("[\033[31;1mFAIL\033[0m]\t\033[31;1m( %s )\033[0m\n", ut_last_err); _test_fails++; } \
							else { puts("[\033[32;1mOk !\033[0m]");}
# define UT_SEGV(test_)		puts("[\033[34;1mSEGV\033[0m]");
# define UT_BEGIN_TEST()	
# define UT_END_TEST()		return (0)
# define UT_ADD_TEST(name)	ut_add_test_(&ut_test_ ## name, #name)
# define UT_RUN_ALL_TESTS()	ut_run_all_tests_()

/*
 *  Bonus
 */

# define UT_ASSERT_EQ(a, b)		UT_ASSERT((a) == (b))
# define UT_ASSERT_NEQ(a, b)	UT_ASSERT((a) != (b))

typedef	int (*ut_test)(void);

typedef struct				ut_test_list_s
{
	ut_test					test;
	char					*name;
	struct ut_test_list_s	*next;
}							ut_test_list_t;

extern ut_test_list_t		*ut_tests;
extern char					*ut_last_err;

void						ut_sigsegv_(int);
ut_test_list_t				*ut_create_list_(ut_test, char *);
void						ut_add_test_(ut_test, char *);
int							ut_run_all_tests_(void);

#endif /* !UNIT_TEST_H */
