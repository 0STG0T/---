// file to store calculation funcitons

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// calculates factorial of positive integer m
// using long long int to reduce the bottleneck of huge factorials
unsigned long long int factorial(unsigned m){
    unsigned long long int fact = 1;

    // handling x = 0
    if (m == 0){
        return 1;
    }

    for (unsigned int i=2;i<=m;i++){
        fact *= i;
    }

    return fact;
}

// calculates real x to the power of positive integer m
// using long double to reduce the bottleneck of huge powers
long double power(double x, unsigned int m){
    if (m==0){
        return 1;
    } else if (m == 1) {
        return x;
    }

    double r = x;

    for (int i=1;i<m;i++){
        r *= x;
    }

    return r;
}  

// calculates one member of the series: r = x^m / (2m)!, where x - real, m - positive integer
double calculate_one_member(double x, unsigned int m){
    double r = power(x, 2*m) / factorial(2*m);
    
    return r;
}

// calculates |x| for real x
double absolute(double x){
    if (x < 0){
        return -x;
    }

    return x;
}

// unsign structure to return an object with 2 values
struct result_struct
{
    double result;
    int m_members;
};

// ch(x) calculation by series untill a certain level m of accuracy is reached
struct result_struct calculate_ch_untill_accuracy(double x, double accuracy_level, bool show_m_members){
    double result_current = 1.0, result_previous = 0.0, current_accuracy=1.0, current_member=0;

    unsigned int m = 1; // starting from number 2, bc first member is 1
    
    // looping while accuracy is reached
    while (current_accuracy > accuracy_level){
        result_previous = result_current;
        current_member = calculate_one_member(x, m);
        
        result_current += current_member;
        
        // accuracy should be always positive
        current_accuracy = absolute(result_current-result_previous);
        m++;
       
    }
    if (show_m_members){
        printf("Calculated with %d members.\n", m);
    }
    
    struct result_struct result;
    
    result.result = result_current;
    result.m_members = m;

    return result;
}

// ch(x) claculation funtion that approximates by calculating n members of the series
double calculate_ch_untill_n_members(double x, unsigned int n){
    double result = 1.0;

    // starting from i=1 bc first member = 1
    for (int i=1;i < n;i++){
        result += calculate_one_member(x, i);
    }
    
    return result;
}