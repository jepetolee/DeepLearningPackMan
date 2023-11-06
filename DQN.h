#pragma once

#include <stdlib.h>
#include <math.h>
double learning_rate = 0.1;

typedef struct NeuralNetworkOutput {
	double** array0;
    double** array1;
    double** array2;
    double** array3;
    
    double** derivativeArray1;
    double** derivativeArray2;
    double** derivativeArray3;
    double** derivativeArray4;
}NeuralNetworkOutput;

typedef struct NeuralNetworkWeight {
   double** weight1;
   double** weight2;
   double** weight3;
}NeuralNetworkWeight;

void flatten_2d_array(double** arr, int rows, int cols, double** flat) {
    int index = 0 ,i,j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            flat[0][index++] = arr[i][j];
        }
    }
}

double gelu(double x) {
    return 0.5 * x * (1.0 + tanh(sqrt(2.0 / M_PI) * (x + 0.044715 * pow(x, 3))));
}
double gelu_derivative(double x) {
    double cdf = 0.5 * (1.0 + tanh(sqrt(2.0 / M_PI) * (x + 0.044715 * pow(x, 3))));
    return 0.5 + 0.5 * cdf * (1.0 + cdf * (x + 0.044715 * pow(x, 3) + 0.75 * pow(x, 2) * (1.0 - cdf)));
}

void softmax(double** input, int length, double** output) {
    double max_val = input[0][0];
    double sum = 0.0;
    int i;
    for (i = 1; i < length; i++) {
        if (input[0][i] > max_val) {
            max_val = input[0][i];
        }
    }

    for (i = 0; i < length; i++) {
        output[0][i] = exp(input[0][i] - max_val); // 각 원소에 exp(x - max_val) 적용
        sum += output[0][i];
    }

    for (i = 0; i < length; i++) {
        output[0][i] /= sum; // 확률 분포로 정규화
    }
}

int argmax(double** input, int length) {
    double max_val = input[0][0];
    int max_index = 0;
    int i;
    for (i = 1; i < length; i++) {
        if (input[0][i] > max_val) {
            max_val = input[0][i];
            max_index = i;
        }
    }

    return max_index;
}

void xavier_uniform_2d(double** matrix, int rows, int cols) {
    double scale = sqrt(6.0 / (rows + cols));
    int i,j;
    for ( i = 0; i < rows; i++) {
        for ( j = 0; j < cols; j++) {
            matrix[i][j] = ((double)rand() / RAND_MAX) * 2.0 * scale - scale;
        }
    }
}

void forward_pass(double** A, double** B, double** C,int M,int P, int N) {
    int i, j, k;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0.0;
            for (k = 0; k < P; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
            C[i][j] = gelu(C[i][j]);
        }
    }
}

void backward_pass(double** input, double** weights, double** output, double** d_output, double** d_input, int rows, int cols) {
    int i,j,k;
	for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            double d_gelu = 0.5 * (1.0 + tanh(sqrt(2.0 / M_PI) * (output[i][j] + 0.044715 * pow(output[i][j], 3))));
            double delta = d_gelu * d_output[i][j];
            for (k = 0; k < cols; k++) {
                d_input[i][k] += delta * weights[j][k];
                weights[j][k] += delta * input[i][k]*learning_rate;
            }
        }
    }
}

void convolution(double** input, double** output, double** kernel,int INPUT_WIDTH,int KERNEL_SIZE) {
	int i,j,m,n;
    for ( i = 0; i < INPUT_WIDTH - KERNEL_SIZE; i += 2) {
        for ( j = 0; j < INPUT_WIDTH - KERNEL_SIZE; j += 2) {
            double sum = 0.0;
            for (m = 0; m < KERNEL_SIZE; m++) {
                for (n = 0; n < KERNEL_SIZE; n++) {
                    sum += (input[i + m][j + n] * kernel[m][n]);
                }
            }
            output[i / 2][j / 2] = gelu(sum);
        }
    }
}

void convolution_backward(double** input, double** kernel, double** d_output, double** d_input, double** d_kernel,int INPUT_HEIGHT,int KERNEL_SIZE) {
    int i,j,m,n = 0;
    for ( i = 0; i < (INPUT_HEIGHT - KERNEL_SIZE) / 2; i++) {
        for ( j = 0; j < (INPUT_HEIGHT - KERNEL_SIZE) / 2; j++) {
            double d_output_value = d_output[i][j];
            d_output_value *= gelu_derivative(d_output_value);
            for ( m = 0; m < KERNEL_SIZE; m++) {
                for ( n = 0; n < KERNEL_SIZE; n++) {
                    d_input[i * 2 + m][j * 2 + n] += d_output_value * kernel[m][n];
                    d_kernel[m][n] += d_output_value * input[i * 2 + m][j * 2 + n] *learning_rate;
                }
            }
        }
    }
}

double euclidean_distance(Coordinate c1, Coordinate c2) {
    double dx = c1.x - c2.x;
    double dy = c1.y - c2.y;
    return sqrt(dx * dx + dy * dy);
}


NeuralNetworkWeight NN;
NeuralNetworkOutput out;
double** flatten;

void initializeArrays(){
	int i,j;
    flatten =(double **)malloc(1 * sizeof(double *));
	for (i = 0; i < 1; i++) {
        flatten[i] = (double *)malloc(25 * sizeof(double));
    } 
	packmanMap =(double **)malloc(30 * sizeof(double *));
	
	for (i = 0; i < 30; i++) {
        packmanMap[i] = (double *)malloc(30 * sizeof(double));
    }
	for (i = 0; i < 30; i++) {
			for (j = 0; j < 30; j++) {
        packmanMap[i][j] =mapStructure[i][j];
    }
    }
	NN.weight1 =(double **)malloc(4 * sizeof(double *));
	for (i = 0; i < 4; i++) {
        NN.weight1[i] = (double *)malloc(4 * sizeof(double));
    }
    xavier_uniform_2d(NN.weight1,4,4);
    NN.weight2 =(double **)malloc(3 * sizeof(double *));
	for (i = 0; i < 3; i++) {
        NN.weight2[i] = (double *)malloc(3 * sizeof(double));
    }
    xavier_uniform_2d(NN.weight2,3,3);
    NN.weight3 =(double **)malloc(25 * sizeof(double *));
	for (i = 0; i < 25; i++) {
        NN.weight3[i] = (double *)malloc(16 * sizeof(double));
    }
    xavier_uniform_2d(NN.weight3,25,16);
    
    out.array0 =(double **)malloc(30 * sizeof(double *));
	for (i = 0; i < 30; i++) {
        out.array0[i] = (double *)malloc(30 * sizeof(double));
    }
    
    for (i = 0; i < 30; i++) {
    for (j = 0; j < 30; j++) {
            out.array0[i][j] = 1.0;
        }
    }

    out.array1 =(double **)malloc(13 * sizeof(double *));
	for (i = 0; i < 13; i++) {
        out.array1[i] = (double *)malloc(13 * sizeof(double));
    }
    out.array2 =(double **)malloc(5 * sizeof(double *));
	for (i = 0; i < 5; i++) {
        out.array2[i] = (double *)malloc(5 * sizeof(double));
    }
    out.array3 =(double **)malloc(1 * sizeof(double *));
	for (i = 0; i < 1; i++) {
        out.array3[i] = (double *)malloc(16 * sizeof(double));
    }
    
    out.derivativeArray1 =(double **)malloc(1 * sizeof(double *));
	for (i = 0; i < 1; i++) {
        out.derivativeArray1[i] = (double *)malloc(16 * sizeof(double));
    }
    out.derivativeArray2 =(double **)malloc(5 * sizeof(double *));
	for (i = 0; i < 5; i++) {
        out.derivativeArray2[i] = (double *)malloc(5 * sizeof(double));
    }
    out.derivativeArray3 =(double **)malloc(13 * sizeof(double *));
	for (i = 0; i < 13; i++) {
        out.derivativeArray3[i] = (double *)malloc(13 * sizeof(double));
    } 
    out.derivativeArray4 =(double **)malloc(30 * sizeof(double *));
	for (i = 0; i < 30; i++) {
        out.derivativeArray4[i] = (double *)malloc(30 * sizeof(double));
    }     
}

int DQNprocess(){
	
    
	double ** probabilities;
    int i;
 
    
    probabilities =(double **)malloc(1 * sizeof(double *));
	for (i = 0; i < 1; i++) {
        probabilities[i] = (double *)malloc(16 * sizeof(double));
    } 
    
    convolution(packmanMap,out.array1,NN.weight1,30,4);
    convolution(out.array1,out.array2,NN.weight2,13,3);
    flatten_2d_array(out.array2,5,5,flatten);
    forward_pass(flatten,NN.weight3,out.array3,1,25,16);
    softmax(out.array3,16,probabilities);
    
    return argmax(probabilities, 16);
}

void DQNbackward(){
	int i,j;
    for (i = 0; i < 1; i++) {
    for (j = 0; j < 16; j++) {
            out.derivativeArray1[i][j] = 1.0;
        }
    }
	double loss= (euclidean_distance(pacMan.position, ghosts[0].position)+euclidean_distance(pacMan.position, ghosts[1].position))/2;
	backward_pass(out.array2,NN.weight3,out.array3,out.derivativeArray2,out.derivativeArray1,1,16);
	convolution_backward(out.array1,NN.weight2, out.array2,out.derivativeArray3,out.derivativeArray2,5,3);
	convolution_backward(out.array0,NN.weight1, out.array1,out.derivativeArray4,out.derivativeArray3,13,4);
	
}
