/*
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * friendly-numbers.c - Friendly numbers kernel.
 */

#include <global.h>
#include <omp.h>
#include <stdlib.h>
#include <util.h>
#include "fn.h"

/*
 * Computes the Greatest Common Divisor of two numbers.
 */
static int gcd(int a, int b)
{
  int c;
  
  /* Compute greatest common divisor. */
  while (a != 0)
  {
     c = a;
     a = b%a;
     b = c;
  }
  
  return (b);
}

/*
 * Some of divisors.
 */
static int sumdiv(int n)
{
	int sum;    /* Sum of divisors. */
	int factor; /* Working factor.  */
	
	sum = 1 + n;
	
	/* Compute sum of divisors. */

	// Loop unrolling com incremento de 4
	for (factor = 2; factor < n; factor += 4)
	{
		// Verificar divisibilidade para 4 fatores consecutivos
		if ((n % factor) == 0)
			sum += factor;
		
		if ((n % (factor + 1)) == 0)
			sum += (factor + 1);

		if ((n % (factor + 2)) == 0)
			sum += (factor + 2);

		if ((n % (factor + 3)) == 0)
			sum += (factor + 3);
	}

	// Lidar com qualquer fator restante
	for (; factor < n; factor++)
	{
		if ((n % factor) == 0)
			sum += factor;
	}
	
	return (sum);
}

/*
 * Computes friendly numbers.
 */
int friendly_numbers(int start, int end) 
{
	int n;        /* Divisor.                    */
	int *num;     /* Numerator.                  */
	int *den;     /* Denominator.                */
	int range;    /* Range of numbers.           */
	int i, j;     /* Loop indexes.               */
	int nfriends; /* Number of friendly numbers. */
	int *tasks;   /* Tasks.                      */
	int tid;      /* Thread id.                  */
	
	range = end - start + 1;
	
	num = smalloc(sizeof(int)*range);
	den = smalloc(sizeof(int)*range);
	tasks = smalloc(sizeof(int)*range);
	
	/* Balance workload. */
	balance(tasks, range, nthreads);
	
	/* Compute abundances. */
	#pragma omp parallel private(i, j, tid, n) default(shared)
	{
		tid = omp_get_thread_num();
		
		for (i = start; i <= end; i += 4)
		{
			j = i - start;

			/* Not my task. */
			if (tasks[j] != tid)
				continue;

			num[j] = sumdiv(i);
			den[j] = i;

			n = gcd(num[j], den[j]);
			num[j] /= n;
			den[j] /= n;

			j = i + 1 - start;
			if (tasks[j] != tid)
				continue;

			num[j] = sumdiv(i + 1);
			den[j] = i + 1;

			n = gcd(num[j], den[j]);
			num[j] /= n;
			den[j] /= n;

			j = i + 2 - start;
			if (tasks[j] != tid)
				continue;

			num[j] = sumdiv(i + 2);
			den[j] = i + 2;

			n = gcd(num[j], den[j]);
			num[j] /= n;
			den[j] /= n;

			j = i + 3 - start;
			if (tasks[j] != tid)
				continue;

			num[j] = sumdiv(i + 3);
			den[j] = i + 3;

			n = gcd(num[j], den[j]);
			num[j] /= n;
			den[j] /= n;
		}
	}


	/* Check friendly numbers. */
	nfriends = 0;
	#pragma omp parallel for private(i, j) default(shared) reduction(+:nfriends)
	for (i = 1; i < range; i++)
	{
		int limit = i < range - 4 ? i + 4 : range; // Evita acessar além do limite de range
		
		for (j = 0; j < limit; j += 4)
		{
			/* Friends. */
			if ((num[i] == num[j]) && (den[i] == den[j]))
				nfriends++;

			if ((num[i] == num[j+1]) && (den[i] == den[j+1]))
				nfriends++;

			if ((num[i] == num[j+2]) && (den[i] == den[j+2]))
				nfriends++;

			if ((num[i] == num[j+3]) && (den[i] == den[j+3]))
				nfriends++;
		}
	}

	free(tasks);
	free(num);
	free(den);
	
	return (nfriends);
}
