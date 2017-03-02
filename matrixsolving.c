#include <math.h>
#include "ac.h"



complex add(complex a,complex b)
{
	complex res;
	res.real = a.real + b.real;
	res.img = a.img + b.img;
	return res;	
}

complex sub(complex a,complex b)//a-b
{
	complex res;
	res.real = a.real-b.real;
	res.img = a.img-b.img;
	return res;	
}

complex mult(complex a,complex b)
{
	complex res;
	res.real = a.real * b.real - a.img * b.img;
	res.img = a.real*b.img + a.img * b.real;
	return res;
}

complex div_(complex a,complex b)// a / b
{
	double temp=b.real*b.real+b.img*b.img;
	complex c;c.real=b.real;c.img=-1*b.img;
    
	complex res=mult(a,c);
	res.real /= temp;
	res.img /= temp;
	return res;
}

complex make_complex(double r,double i)
{
    complex res;
    res.real=r;res.img=i;
    return res;
}

double abs_(complex a)
{
	double res=a.real*a.real+a.img*a.img;
	res = sqrt(res);
	return res;
}



void init()//initialise for testing
{
    n=2;
	//scanf("%d",&n);

    a = (complex**)calloc((n+10),sizeof(complex*));
    for (int i = 0; i < n; ++i) 
    {a[i] = (complex*)calloc((n+10),sizeof(complex));}

	a[0][0].real=2;a[0][0].img=0;		a[0][1].real=3;a[0][1].img=0;
	a[1][0].real=3;a[1][0].img=0;		a[1][1].real=2;a[1][1].img=0;

    for(i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
        {ao[i][j]=a[i][j];}
    }
    // for(int i=0;i<n;++i)
    // {
    //     for(int j=0;j<n;++j)
    //     {scanf("%lf%lf",&a[i][j].real,&a[i][j].img);}
    // }   
values = (complex*)calloc((n+10),sizeof(complex));
    
    values[0].real=4;values[0].img=-2;
    values[1].real=5;values[1].img=-1;
    // for(int i=0;i<n;++i)
    // {
    //     scanf("%lf%lf",&values[i].real,&values[i].img);
    // }
}

void print()
{
    int i,j;
    for(i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
        {printf("inverted_mat[%d][%d]=(%lf, %lf)\n",i,j,inverted_mat[i][j].real,inverted_mat[i][j].img);}
    printf("\n");
    }
    for(i=0;i<n;++i)
    {
        printf("answer[%d]=(%lf, %lf)\n",i,answer[i].real,answer[i].img);
    }

}

void test()
{

t = (complex*)calloc((n+10),sizeof(complex));
    
printf("n=%d\n",n);

int i,j;
    /*for(i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
        {printf("a[%d][%d]=(%lf, %lf)       matrix[%d][%d]=(%lf, %lf)\n",i,j,ao[i][j].real,ao[i][j].img,i,j,matrix[i][j].real,matrix[i][j].img);}
    printf("\n");
    }*/

    for(i=0;i<n;++i)
    {
        t[i].real=0;t[i].img=0;
//        printf("t[%d]=(%lf, %lf)\n",i,t[i].real,t[i].img);
        for(j=0;j<n;++j)
        {
            t[i] = add(t[i],mult(ao[i][j], answer[j]));   
            //printf("t[%d]=(%lf, %lf)\n",i,t[i].real,t[i].img);

        }
         //       printf("t[%d]=(%lf, %lf)\n",i,t[i].real,t[i].img);

    }
    int error=0;
    for(i=0;i<n;++i)
    {printf("t[%d]=(%lf, %lf)\n",i,t[i].real,t[i].img);
        
        if(t[i].real!=values[i].real)    
        {++error;printf("t[%d].real=%lf, values[%d].real= %lf \n",i,t[i].real,i,values[i].real);}
        if(t[i].img!=values[i].img)
        {++error;printf("t[%d].img=%lf, values[%d].img= %lf \n",i,t[i].img,i,values[i].img);}

    }
    printf("Error count=%d\n",error);
    print();
}

void solve_matrix()
{int i,j;

inverted_mat = (complex**)calloc((n+10),sizeof(complex*));
for (i = 0; i < n; i++) 
{inverted_mat[i] = (complex*)calloc((n+10),sizeof(complex));}


invert();

answer = (complex*)calloc((n+10),sizeof(complex));

        for (int i = 0; i < n; i++) 
        {
                for (int k = 0; k < n; k++)
                {	 
                    answer[i] = add(answer[i], mult(inverted_mat[i][k], values[k]) );
                }      
        }
}



/*
int main()
{
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {ao[i][j]=a[i][j];}
    }

    init();
    solve_matrix();

//    print();
    test();
}*/

//struct complex a[][] is in "ac.h"
void invert() 
{
    complex** x;
    complex** b;

x = (complex**)calloc((n+10),sizeof(complex*));
for (int i = 0; i < n; i++) 
{x[i] = (complex*)calloc((n+10),sizeof(complex));}
b = (complex**)calloc((n+10),sizeof(complex*));
for (int i = 0; i < n; i++) 
{b[i] = (complex*)calloc((n+10),sizeof(complex));}
        
        int index[n];
        

        for(int i=0;i<n;++i)
        {
            for(int j=0;j<n;++j)
            {b[i][j].real=0;b[i][j].img=0;}
        }
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
		        {inverted_mat[i][j].real=x[i][j].real;inverted_mat[i][j].img=x[i][j].img;}


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
