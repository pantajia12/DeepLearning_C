#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
int main(){
    int x[4] = {2, 4, 6, 8};//공부시간
    int y[4] = {81, 93, 91, 97};//시험점수
    
    //경사 하강법(오차가 최소인 예측선)
    
    int num_epoch = 1000001; //최대 반복 횟수

    double learning_rate = 0.00005; //학습률

    double a = 1; //기울기
    double b = 1; //y절편
        
    for(int epoch = 0; epoch < num_epoch; epoch++){
        int n = epoch % 4;

        double p = a * x[n] + b;
        double error = p - y[n];
            
        a = a - learning_rate * error * x[n];
        b = b - learning_rate * error;
        
        double predict_result = 0;
        for(int n = 0; n < sizeof(y) / sizeof(int); n++){
            predict_result += ((a * x[n] + b) - y[n])*((a * x[n] + b)- y[n]);
        }
        predict_result = sqrt(predict_result / (sizeof(y) / sizeof(int)));

        if(epoch % 1000 == 0){
            printf("%d a = %.5f, b = %.5f, rmse = %.5f\n",epoch, a, b, predict_result);
        }

    }
    puts("--------------------------------------------------------");

    //선형회귀(정확한 예측선)
    double meanX = 0; //x 평균값
    double meanY = 0; //y 평균값
    
    for(int n = 0; n < sizeof(x) / sizeof(int); n++){
        meanX += x[n];
        meanY += y[n];
    }
    meanX = (double)(meanX / (sizeof(x) / sizeof(int)));
    meanY = (double)(meanY / (sizeof(y) / sizeof(int)));

    double divisor = 0; //기울기 분모
    for(int n = 0; n < sizeof(x) / sizeof(int); n++){
        divisor += (double)((x[n] - meanX) * (x[n] - meanX));
    }

    double dividend = 0; //기울기 분자
    for(int n = 0; n < sizeof(y) / sizeof(int); n++){
        dividend += (double)((x[n] - meanX) * (y[n] - meanY));
    }

    a = dividend / divisor; //기울기
    b = meanY - (meanX * a); //y절편

    double *predic = malloc(sizeof(x) / sizeof(int) * sizeof(double));
    for(int n = 0; n < sizeof(y) / sizeof(int); n++){
        predic[n] = a * x[n] + b;
    }

    double predict_result = 0;
    for(int n = 0; n < sizeof(y) / sizeof(int); n++){
        printf("공부시간: %d, 실제점수: %d, 예측점수: %f\n", x[n], y[n], predic[n]);
        predict_result += (predic[n] - y[n]) * (predic[n] - y[n]);
    }

    predict_result = sqrt(predict_result / (sizeof(y) / sizeof(int)));
    printf("a = %.5f, b = %.5f, rmse: %f",a, b,predict_result);
    free(predic);
}