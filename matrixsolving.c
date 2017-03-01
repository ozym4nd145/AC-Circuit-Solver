#include <math.h>
#include "ac.h"
#define complex struct complex

int n;//size of b, x 

complex add(complex a,complex b)
{
	complex res;
	res.real = a.real+b.real;
	res.img = a.img+b.img;
	return res;	
}

complex sub(complex a,complex b)//a-b
{
	complex res;
	res.real = a.real-b.real;
	res.img = a.img-b.img;
	return res;	
}

complex div_(complex a,complex b)// a / b
{
	complex res;
	res.real = a.real*b.real-a.img*b.img;
	res.img = a.real*b.img+a.img*b.real;
	return res;
}

complex mult(complex a,complex b)
{
	double temp=b.real*b.real+b.img*b.img;
	b.img*=-1;
	complex res=mult(a,b);
	res.real /= temp;
	res.img /= temp;
	return res;
}

double abs_(complex a)
{
	double res=a.real*a.real+a.img*a.img;
	res = sqrt(res);
	return res;
}


complex inverted_mat[11005][11005];
void solve()
{

invert();
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < 1; j++) 
            {
                for (int k = 0; k < n; k++)
                {	 
                    result[i] = add(result[i], mult(inverted_mat[i][k], constants[k]) );
                }
            }
        }

}

//struct complex a[][] is in "ac.h"
void invert() 
{
 
        complex x[n][n];
        complex b[n][n];
        
        int index[n];
        
        for (int i=0; i<n; ++i) 
        {b[i][i].real=1;b[i][i].img=0;}
 

        gaussian(index);

 
        for (int i=0; i<n-1; ++i)
            for (int j=i+1; j<n; ++j)
                for (int k=0; k<n; ++k)
                    {b[index[j]][k] = sub(b[index[j]][k],mult(a[index[j]][i],b[index[i]][k]));}

 
        for (int i=0; i<n; ++i) 
        {
            x[n-1][i] = div_(b[index[n-1]][i],a[index[n-1]][n-1]);
            for (int j=n-2; j>=0; --j) 
            {
                x[j][i] = b[index[j]][i];
                for (int k=j+1; k<n; ++k) 
                {
                    x[j][i] = sub(x[j][i],mult(a[index[j]][k], x[k][i]) );
                }
                x[j][i] = div_(x[j][i], a[index[j]][j]);
            }
        }

        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j)
		        inverted_mat[i][j]=x[i][j];
}
 

//struct complex a[][] is in "ac.h" 
void gaussian(int index[]) 
{
       
        double c[n];
 

        for (int i=0; i<n; ++i) 
            index[i] = i;
 

        for (int i=0; i<n; ++i) 
        {
            double c1 = 0;
            for (int j=0; j<n; ++j) 
            {
                double c0 = abs_(a[i][j]);
                if (c0 > c1) c1 = c0;
            }
            c[i] = c1;
        }
 

        int k = 0;
        for (int j=0; j<n-1; ++j) 
        {
            double pi1 = 0;
            for (int i=j; i<n; ++i) 
            {
                double pi0 = abs_(a[index[i]][j]);
                pi0 /= c[index[i]];
                if (pi0 > pi1) 
                {
                    pi1 = pi0;
                    k = i;
                }
            }
 

            int itmp = index[j];
            index[j] = index[k];
            index[k] = itmp;
            for (int i=j+1; i<n; ++i) 	
            {
                complex pj = div_(a[index[i]][j], a[index[j]][j]);
 

                a[index[i]][j] = pj;
 

                for (int l=j+1; l<n; ++l)
                    a[index[i]][l] = sub(a[index[i]][l], mult(pj, a[index[j]][l]));
            }
        }
    }
