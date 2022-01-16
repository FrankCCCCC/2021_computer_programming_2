#include <iostream>
#include <stdio.h>
#include "function.h"

using namespace std;

Matrix::Matrix()
{
    matrix_size = 0;
}

Matrix::Matrix (const int MAT_size , const int MAT[50][50])
{
    int j,k;
    matrix_size = MAT_size;
    for(j=0;j<MAT_size;j++)
    {
        for(k=0;k<MAT_size;k++)
        {
            matrix[j][k] = MAT[j][k];
        }
    }

}

Matrix Matrix::row( const int a, const int b) const
{
    int tmp;
    int i;
    int j,k;
    int mat[50][50];

    for(j=0;j<matrix_size;j++)
    {
        for(k=0;k<matrix_size;k++)
        {
            mat[j][k] = matrix[j][k];
        }
    }

    for(i=0 ;i<matrix_size; i++)
    {
        tmp = mat[a][i];
        mat[a][i] = mat[b][i];
        mat[b][i] = tmp;
    }
    return Matrix(matrix_size, mat);
}

void Matrix::output() const
{
    int i,j;
    for(i=0;i<matrix_size;i++)
    {
		cout<<matrix[i][0];
        for(j=1;j<matrix_size;j++)
        {
            cout<<" "<<matrix[i][j];
        }
        cout << endl;
    }
}

Matrix Matrix::rotate90() const
{
    int j,k;
    int mat[50][50];
    int output[50][50];

    for(j=0;j<matrix_size;j++)
    {
        for(k=0;k<matrix_size;k++)
        {
            mat[j][k] = matrix[j][k];
        }
    }

    for(j=0;j<matrix_size;j++)
    {
        for(k=0;k<matrix_size;k++)
        {
            output[k][matrix_size-j-1] = mat[j][k];
        }
    }
    return Matrix(matrix_size, output);
}

Matrix Matrix::rotatecounter90() const
{
    int tmp;
    int i;
    int j,k;
    int mat[50][50];
    int output[50][50];

    for(j=0;j<matrix_size;j++)
    {
        for(k=0;k<matrix_size;k++)
        {
            mat[j][k] = matrix[j][k];
        }
    }

    for(j=0;j<matrix_size;j++)
    {
        for(k=0;k<matrix_size;k++)
        {
            output[k][j] = mat[j][matrix_size-k-1];
        }
    }
    return Matrix(matrix_size, output);
}

void Matrix::symmetric() const
{
    int i,j;
    int c=0;
    int mat[50][50];

    for(i=0;i<matrix_size;i++)
    {
        for(j=0;j<matrix_size;j++)
        {
            mat[i][j] = matrix[i][j];
        }
    }


    for(i=0;i<matrix_size;i++)
    {
        for(j=i;j<matrix_size;j++)
        {
            if(mat[i][j] == mat[j][i]) continue;
            else
            {
                c = 1;
                break;
            }
        }
        if(mat[i][j] != mat[j][i]) break;
    }
    if(c != 1) cout << "yes\n";
    else cout << "no\n";
}
