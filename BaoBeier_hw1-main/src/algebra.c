#include "algebra.h"
#include <stdio.h>
#include <math.h>


Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    // ToDo
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrices must have the same dimensions to be added.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result; 
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    // ToDo
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: Matrices must have the same dimensions to be added.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return result; 
    return create_matrix(0, 0);
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    // ToDo
     if (a.cols != b.rows) {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }

    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

Matrix scale_matrix(Matrix a, double k)
{
    // ToDo
     Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] * k;
        }
    }
    return result; 
}

Matrix transpose_matrix(Matrix a)
{
    // ToDo
    Matrix result = create_matrix(a.cols, a.rows);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[j][i] = a.data[i][j];
        }
    }
    return result; 
}


double det_matrix(Matrix a) {
    double result=0;
    if(a.rows != a.cols){
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    if(a.rows == 1){
        return a.data[0][0];
    }
    for(int k=0;k<a.rows;k++){
        Matrix temp = create_matrix(a.rows-1,a.cols-1);
        for(int i=0;i<a.rows-1;i++){
            for(int j=0;j<a.cols;j++){
                if(j<k){
                    temp.data[i][j]=a.data[i+1][j];
                }else if(j>k){
                    temp.data[i][j-1]=a.data[i+1][j];
                }
            }
        }
        result+=pow(-1,k)*a.data[0][k]*det_matrix(temp);
    }
    return result;
}


Matrix inv_matrix(Matrix a)
{
    // ToDo
    if(a.rows != a.cols){
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    else if(det_matrix(a)==0){
        printf("Error: The matrix is singular.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows,a.cols);
        for(int i=0;i<a.rows;i++){
            for(int j=0;j<a.cols;j++){
                Matrix temp = create_matrix(a.rows-1,a.cols-1);
                for(int k=0;k<a.rows;k++){
                    for(int q=0;q<a.cols;q++){
                        if(k<i&&q<j){
                            temp.data[k][q]=a.data[k][q];
                        }else if(k>i&&q<j){
                            temp.data[k-1][q]=a.data[k][q];
                        }else if(k<i&&q>j){
                            temp.data[k][q-1]=a.data[k][q];
                        }else if(k>i&&q>j){
                            temp.data[k-1][q-1]=a.data[k][q];
                        }
                    }   
                }
                result.data[j][i]=det_matrix(temp)*pow(-1,i+j)/det_matrix(a);
            }
        }
    return result;
}


int rank_matrix(Matrix a)
{
    // ToDo
    if(a.rows!=a.cols){
        printf("The input matrix must be a square matrix");
        return 0;
    }
    for(int i=0;i<a.rows-1;i++){
        for(int k=i+1;k<a.cols;k++){
            if(a.data[k][i]!=0){
                double mul=a.data[i][i]/a.data[k][i];
                for(int q=i;q<a.rows;q++){
                    a.data[k][q]=a.data[k][q]*mul-a.data[i][q];
                }
            }
        }
    }
    int flag=0;
    for(int i=0;i<a.rows;i++){
        for(int j=0;j<a.cols;j++){
            if(a.data[i][j]!=0){
                flag-=1;
                break;
            }
        }
        flag+=1;
    }
    return a.rows-flag;
    return 0;
}

double trace_matrix(Matrix a)
{
    // ToDo
    double result=0;
    if(a.rows != a.cols){
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    for(int i=0;i<a.rows;i++){
        for(int j=0;j<a.cols;j++){
            if(i == j){
                result += a.data[i][j];
            }
        }
    }
    return result;
    return 0;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}