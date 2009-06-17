/*
 * burger_noinf_e.c
 *
 *  Created on: Jun 14, 2009
 *      Author: matheus
 */

#include <stdio.h>
#include <math.h>

/* Programa de demonstracao que implementa o metodo de resolucao de equacao */
/* parabolica  por um metodo explicito */

float f(float x)
/* Funcao que da' a condicao inicial */
{
	if ((x > 0.0) && (x <= 0.2))
		return(0.2 - x);
	else
		return(0.0);
}

/*float f(float x);*/

int main(void)
{
	FILE *outf;

	float solucao[600][50],
		t, t0, tfim, x, x0, xfim, h, k, alfa, lambda;

	int i, j, nx, nt;

	if ((outf = fopen("difusao.dat", "w")) == NULL)
	{
		printf("\nProblemas na abertura do arquivo\n");
	}

	h = 0.001; 	/* Discretizacao do tempo */
	k = 0.01;  	/* Discretizacao do espaco */

	t0   = 0.0;
	tfim = 0.1;

	x0   = 0.0;
	xfim = 0.2;

	nt = (int) ((tfim - t0)/h) + 2;		/* Numero de "t's" */
	nx = (int) ((xfim - x0)/k) + 2;		/* Numero de "x's" */

	fprintf(stdout, "\n Numero de intervalos temporais %d e espaciais %d", nt, nx);

	/* Parametros fisicos e variavel auxiliar */

	alfa = 1.0;

	lambda = alfa * h/(k * k);
	/*fprintf(stdout, "\n lambda = %f",lambda);*/
	x = x0;
	t = t0;

	/* Condicao inicial */
	for (j = 0; j < nx; j++)
	{
		solucao[0][j] = f(x);
		/*fprintf(stdout, "\n %d - solucao[0][%d] = %f", j, j, solucao[0][j]);*/

		x += k;
		/*fprintf(stdout, "\n x = %f",x);*/
	}

	/* Condicao de contorno */
	for (i = 0; i < nt; i++)
	{
		fprintf(stdout, "\n i = %d",i);
		t += h;
		solucao[i+1][0] = f(x0);
		solucao[i+1][nx - 1] = f(xfim);

		fprintf(stdout, "\n phi(%d,%d) = %f",i+1,0,solucao[i+1][0]);

		//for (j = 1; j < nx - 1; j++)
		{
			/*solucao[i + 1][j] = lambda * (solucao[i][j + 1] + solucao[i][j - 1]) +
				(1.0 - 2.0 * lambda) * solucao[i][j];*/
			/*fprintf(stdout, "\n phi(%d,%d) = %f*(phi(%d,%d) + phi(%d,%d)) + %f*phi(%d,%d) = %f",
					(i+1),j,lambda,i,(j+1),i,(j-1),(1.0 - 2.0 * lambda),i,j,solucao[i + 1][j]);*/
			solucao[i + 1][j] = (1 - 2*lambda - (h/k)*(solucao[i][j+1] - solucao[i][j]))*solucao[i][j] +
				lambda*(solucao[i][j+1] + solucao[i][j-1]);
			fprintf(stdout, "\n phi(%d,%d) = %f*%f + %f*(%f + %f) = %f",(i+1),j,(1.0 - 2.0 * lambda),solucao[i][j],
				lambda,solucao[i][j + 1],solucao[i][j - 1],solucao[i + 1][j]);
		}

		fprintf(stdout, "\n phi(%d,%d) = %f",i+1,(nx-1),solucao[i+1][nx-1]);
	}

	x = x0;

	for (j = 0; j < nx; j++)
	{
		fprintf(outf, "%f ", x);
		for (i = 0; i < nt; i++)
		{
			fprintf(outf, "%f ", solucao[i][j]);
		}
		fprintf(outf, "\n");
		x += k;
	}

}
