#include "calculations.c"
#include "safe_input.c"
#include <stdbool.h>

int main(void){
    bool mode = safe_mode_input(); // 0 - accuracy, 1 - m members
    // input x variable
    double x = safe_real_input("Type a real number for X variable with a . separator if needed: ");

    // calculate using m members
    if (mode){
        // input m members
        unsigned int m_members = safe_m_input();
        printf("Calculated ch(x) using %d members: %f\n", m_members, calculate_ch_untill_n_members(x, m_members));
        
    }
    // calculate using accuracy
    else{
        // input accuracy
        double accuracy = safe_real_input("Type a positive number for accuracy with a . separator if needed: ");
        // check if accuracy is positiive number
        while (accuracy <= 0){
            printf("Accuracy must be positive real number! Try again.\n");
            accuracy = safe_real_input("Type a positive number for accuracy with a . separator if needed: ");
        }

        printf("Calculated ch(x) using accuracy %f: %f", accuracy, calculate_ch_untill_accuracy(x, accuracy, true).result);
    }

}