#include "unit_test.h"
#include <stdlib.h>
#include <setjmp.h>

ut_test_list_t	*ut_tests = 0;
jmp_buf			ut_env;


void				ut_sigsegv_(int u)
{
	(void)u;
	longjmp(ut_env, 1);
}

ut_test_list_t		*ut_create_list_(ut_test f, char *n)
{
	ut_test_list_t	*tmp;

	tmp = malloc(sizeof(ut_test_list_t));
	tmp->next = 0;
	tmp->test = f;
	tmp->name = n;
	return (tmp);
}

void			ut_add_test_(ut_test f, char *n)
{
	ut_test_list_t	*tmp;

	if (!ut_tests)
	{
		ut_tests = ut_create_list_(f, n);
	}
	else
	{
		tmp = ut_tests;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = ut_create_list_(f, n);
	}
}

int			ut_run_all_tests_(void)
{
	int		_test_fails;
	int		count;
	ut_test_list_t	*tmp;

	signal(SIGBUS, &ut_sigsegv_);
	signal(SIGSEGV, &ut_sigsegv_);
	signal(SIGILL, &ut_sigsegv_) ;
	_test_fails = 0;
	count = 0;
	if (!ut_tests)
	{
		return (0);
	}
	puts("----- Starting all unit tests -----");
	tmp = ut_tests;
	while (tmp)
	{
		if (setjmp(ut_env))
		{
			UT_SEGV(tmp);
			_test_fails++;
		}
		else
		{
			UT_RUN_TEST(tmp);
		}
		count++;
		tmp = tmp->next;
	}
	printf("End of test : %d out of %d test passed.\n", count - _test_fails, count);
	puts("-----    End of unit tests    -----");
	return (_test_fails);
}

