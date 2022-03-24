#include <stdio.h>
#include <malloc.h>
#include <math.h>
int main(){
    int x[4] = {2, 4, 6, 8};//공부시간
    int y[4] = {81, 93, 91, 97};//시험점수
    double meanX = 0, meanY = 0;
    
    for(int n = 0; n < sizeof(x)/sizeof(int); n++){
        meanX += x[n];
        meanY += y[n];
    }
    meanX = (double)(meanX / (sizeof(x)/sizeof(int)));
    meanY = (double)(meanY / (sizeof(y)/sizeof(int)));

    double divisor = 0;//분모
    for(int n = 0; n < sizeof(x)/sizeof(int); n++){
        divisor += (double)((x[n]-meanX)*(x[n]-meanX));
    }

    double dividend = 0;//분자
    for(int n = 0; n < sizeof(y)/sizeof(int); n++){
        dividend += (double)((x[n]-meanX)*(y[n]-meanY));
    }

    double a, b;
    a = dividend / divisor;//기울기
    b = meanY - (meanX*a);//y절편

    double *predic = malloc(sizeof(x)/sizeof(int)*sizeof(double));
    for(int n = 0; n < sizeof(y)/sizeof(int); n++){
        predic[n] = a*x[n]+b;
    }

    double predict_result = 0;
    for(int n = 0; n < sizeof(y)/sizeof(int); n++){
        printf("공부시간: %d, 실제점수: %d, 예측점수: %f\n", x[n], y[n], predic[n]);
        predict_result += (predic[n] - y[n])*(predic[n] - y[n]);
    }

    predict_result = sqrt(predict_result/(sizeof(y)/sizeof(int)));
    printf("rmse: %f",predict_result);
}