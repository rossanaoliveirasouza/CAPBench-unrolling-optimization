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
	for (factor = 2; factor < n; factor+=10)
	{
		/* Divisor found. */
		if ((n%factor) == 0)
			sum += factor;

		if ((n % (factor+1)) == 0 && factor < n)
			sum += factor+1;
		if ((n % (factor+2)) == 0 && factor < n)
			sum += factor+2;
		if ((n % (factor+3)) == 0 && factor < n)
			sum += factor+3;
		if ((n % (factor+4)) == 0 && factor < n)
			sum += factor+4;
		if ((n % (factor+5)) == 0 && factor < n)
			sum += factor+5;
		if ((n % (factor+7)) == 0 && factor < n)
			sum += factor+7;
		if ((n % (factor+8)) == 0 && factor < n)
			sum += factor+8;
		if ((n % (factor+9)) == 0 && factor < n)
			sum += factor+9;
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
		
		for (i = start; i <= end; i+=2) 
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

			j = i +1 - start;
				
			/* Not my task. */
			if (tasks[j] != tid)
				continue;
				
			num[j] = sumdiv(i);
			den[j] = i;
				
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
		for (j = 0; j < i; j+=10)
		{
			/* Friends. */
			if ((num[i] == num[j]) && (den[i] == den[j]))
				nfriends++;
			if ((num[i] == num[j+1]) && (den[i] == den[j]) && j + 1 < i)
				nfriends++;
			if ((num[i] == num[j+2]) && (den[i] == den[j]) && j + 1 < i)
				nfriends++;
			if ((num[i] == num[j+3]) && (den[i] == den[j]) && j + 1 < i)
				nfriends++;
			if ((num[i] == num[j+4]) && (den[i] == den[j]) && j + 1 < i)
				nfriends++;
			if ((num[i] == num[j+5]) && (den[i] == den[j]) && j + 1 < i)
				nfriends++;
			if ((num[i] == num[j+6]) && (den[i] == den[j]) && j + 1 < i)
				nfriends++;
			if ((num[i] == num[j+7]) && (den[i] == den[j]) && j + 1 < i)
				nfriends++;
			if ((num[i] == num[j+8]) && (den[i] == den[j]) && j + 1 < i)
				nfriends++;
			if ((num[i] == num[j+9]) && (den[i] == den[j]) && j + 1 < i)
				nfriends++;		
		}		
	}

	free(tasks);
	free(num);
	free(den);
	
	return (nfriends);
}
