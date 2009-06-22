/*
 * burger_noinf_e.c
 *
 *  Created on: Jun 14, 2009
 *      Author: matheus
 */

#include <stdio.h>
#include <math.h>
/*#include "string.h";*/

#define PI 3.1415926

/* Programa de demonstracao que implementa o metodo de resolucao de equacao */
/* de conveccao  por um metodo explicito */

/*float f(float x);*/
float f(float x)
/* Funcao que da' a condicao inicial */
{
	if ((x > 0.0) && (x <= 0.2))
		return(0.2 - x);
	else
		return(0.0);
}

int main(void)
{
	fprintf(stdout, "Universidade Federal Fluminense - UFF");
	fprintf(stdout, "\nAluno: Matheus de Sá Erthal");
	fprintf(stdout, "\nLista de exercícios 2009 - Questão II");
	fprintf(stdout, "\nResolução da Equação de Burger num meio infinito por um método explícito.\n");

	FILE *outf;
	FILE *cmdplotf;

	/*char comandoplot[] = "plot ";*/

	float solucao[600][1200],
		  t, t0, tfim, x, x0, xfim, xpulso,
		  deltat, deltax, alfa, c, v, k;

	int i, j, nx, nt;

	if (((outf = fopen("burger_noinf_e.dat", "w")) == NULL) || ((cmdplotf = fopen("comando_plot.txt", "w")) == NULL))
	{
		printf("\nProblemas na abertura do arquivo");
	}

	fprintf(cmdplotf, "plot ");

	deltat = 0.001; /* Discretizacao do tempo */
	deltax = 0.01;   /* Discretizacao do espaco */

	t0   = 0.0;
	tfim = 0.1;

	x0   = 0.0;
	xfim = 0.2;

	alfa = 0.01;

	nt = (int) ((tfim - t0)/deltat);
	nx = (int) ((xfim - x0)/deltax);

	fprintf(stdout, "\nNumero de intervalos temporais %d e espaciais %d", nt, nx);

	/* Parametros fisicos e variavel auxiliar */

	/*v = 1.0;*/
	/*v = 1.1;*/
	v = 2.0;
	fprintf(stdout, "\nVelocidade = %f",v);

	c = v * deltat/deltax;

	k = (alfa*deltat)/(deltax*deltax);

	xpulso = (xfim - x0)/2.0;

	/* Condicao inicial */

	x = x0;

	for (j = 1; j < nx - 2; j++)
	{
		solucao[0][j] = f(x - xpulso);

		x += deltax;
	}

	t = t0;

	for (i = 0; i < nt; i++)
	{
		t += deltat;

		for (j = 1; j < nx - 1; j++)
		{
			solucao[i + 1][j] = (1 - 2*k)*solucao[i][j]  - c*(solucao[i][j + 1] - solucao[i][j]) +
				k*(solucao[i][j + 1] + solucao[i][j - 1]);
		}

		if ((i+1)%10 == 0)
			fprintf(cmdplotf, "'burger_noinf_e.dat' using %d:%d w l,",nx-1,i);
	}

	fprintf(cmdplotf, ";");

	x = x0;

	for (j = 0; j < nx; j++)
	{
		fprintf(outf, "%f ", x);
		for (i = 0; i < nt; i++)
		{
			fprintf(outf, "%f ", solucao[i][j]);
		}
		fprintf(outf, "\n");
		x += deltax;
	}

	fclose(cmdplotf);
	fclose(outf);
}

