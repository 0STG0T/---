// a file to test my functions
// bruteforce testing

#include "calculations.c"
#include <stdio.h>
#include <math.h>

// testing factorial function by bruteforcing it
void test_factorial(){
    printf("n - n!\n");
    for (int n=0;n<100;n++){
        long long int f = factorial(n);
        // if factorial is less than zero - it overflowed
        if (f < 0){
            printf("Factorial overflowed on n = %d\n\n", n);
            break;
        }
        printf("%d - %lld\n", n, f);
    }
    printf("\n");
}

// testing power function by bruteforcing it
void test_power(){
    printf("n - pow(n)\n");
    for (int n=0;n<25;n++){
        long double f = power(10, n);
        printf("%d - %Lf\n", n, f);
    }
    printf("\n");
}

// see if there is the difference between different ch calculation methods
void test_difference_between_ch_methods(){
    bool no_difference = true;

    // iterating through different xs
    for (double x=1; x<=20; x*=1.5){
        // iterating through possible accuracies
        for (double accuracy=0.1; accuracy > 0.0001; accuracy*=0.5){
            //accuracy method results
            struct result_struct acc_method_ch = calculate_ch_untill_accuracy(x, accuracy, false);
            int m_members = acc_method_ch.m_members;
            double acc_method_ch_result = acc_method_ch.result;

            // calculating m_members method for the same m members as in acc method
            double m_members_method_ch_result = calculate_ch_untill_n_members(x, m_members);

            // getting the difference
            double diff = absolute(m_members_method_ch_result - acc_method_ch_result) ;

            if (diff > 0){
                printf("x: %f, acc: %f, members: %d, diff: %f\n", x, accuracy, m_members, diff);
                no_difference = false;
            }

        }
    }
    if (no_difference){
        printf("No difference between different methods\n\n");
    }
}

// compare math.h cosh (ideal) and my series methods
void test_methods_with_math_cosh(double x){
    // testing by accuracy
    double ideal_cosh = cosh(x);
    printf("Comparing accuracy method with math.h cosh()\n");
    printf("Accuracy - Difference\n");
    for (double accuracy=5;accuracy > 0.00001;accuracy*=0.1){
        double diff = absolute(ideal_cosh - calculate_ch_untill_accuracy(x, accuracy, false).result);
        printf("Accuracy: %f, diff: %f\n", accuracy, diff);
    }

    // testing by m_members
    printf("\nComparing m members method with math.h cosh()\n");
    printf("m - Difference\n");
    for (int m=1;m < 20; m+=1){
        double diff = absolute(ideal_cosh - calculate_ch_untill_n_members(x, m));
        printf("Members: %d, diff: %f\n", m, diff);
    }
    
}

int main(){
    test_factorial();
    test_power();
    test_difference_between_ch_methods();
    test_methods_with_math_cosh(5);
    return 0;
}
