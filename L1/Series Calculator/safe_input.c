// file to store safe input functions

#include <stdbool.h>
#include <string.h>

// to have HUGE_VAL only for strtod
#include <math.h>
#include <stdlib.h>

// The is_bool function checks if the input is a single character '0' or '1'
bool is_bool(char *s) {
    return (strlen(s) == 1 && (s[0] == '0' || s[0] == '1'));
}

bool safe_mode_input() {
    char input[100];  // Buffer to store user input, size 3 to include null-terminator

    while (true) {
        printf("Use mode 0 - \"by accuracy\", 1 - \"by m members\": ");
        
        // Read input with scanf (only 2 characters max, plus null-terminator)
        if (scanf("%2s", input) == 1) {
            // Use the is_bool function to check if input is '0' or '1'
            if (is_bool(input)) {
                return input[0] == '1';  // Return true for '1', false for '0'
            }
        }

        printf("Please enter a valid number (0 or 1)!\n");
    }
}

// simple string check
bool is_real(char *s){
    char real_alphabet[] = "0123456789.-";
    int s_len = strlen(s);

    // check if len is greater than 0
    if (s_len < 1){
        return false;
    }

    // check that no character out of alphabet
    for (int i=0; i<s_len;i++){
        bool flag = false; // suppose character is not in alpha

        for (int j=0;j<12;j++){
            if (s[i] == real_alphabet[j]){
                flag = true; // its in alpha
            }
        }
        if (flag != true){
            return false;
        }
    }

    // conuters for dots and minuses
    int dot_counter = 0, minus_counter = 0;

    for (int i=0; i<s_len;i++){
        if (s[i] == '.'){
            dot_counter++;

            // not more than 1 dot
            if (dot_counter > 1){
                return false;
            }
            // dot is not the first or last character
            if (i == 0 || i == s_len-1){
                return false;
            }
        } 
        // for minuses
        else{
            if (s[i] == '-'){
                minus_counter++;
                // no more than 1 minus
                if (minus_counter > 1){
                    return false;
                }

                // minus is not first element
                if (i > 0){
                    return false;
                }
            }
        }
    }
    // return true if nothing is wrong with the number
    return true;
}

// function that safely inputs a real number and returns it as double
// pre_input_str is defined because i have more than one different use for this funciton
double safe_real_input(char *pre_input_str) {

    char x[100];  
    printf("%s", pre_input_str);
    scanf("%s", x);  
    if (!is_real(x)) {
        printf("Please enter a real number with a . separator!\n");
        
        return safe_real_input(pre_input_str); // try again
    }

    
    double dx = strtod(x, NULL);
    // conversion error
    if (dx == HUGE_VAL || dx == -HUGE_VAL){
        printf("Conversion Fault!\n");
        return safe_real_input(pre_input_str); // try again
    }

    return dx;  // string to double
}

unsigned int safe_m_input(){
    char uint_alphabet[] = "0123456789";

    // buffer owerflow vulnerabilty
    char s[100];
    printf("Enter the positive integer M - desired number of calculated members of the series: \n");
    scanf("%s", s);

    int s_len = strlen(s);

    // check if len > 0
    if (s_len < 1){
        printf("You must enter a number!\n");
        return safe_m_input();
    }

    // check the alphabet
    for (int i=0;i<s_len;i++){
        bool flag = false; // suppose that char is not in alphabet
        for (int j=0;j<10;j++){
            if (s[i] == uint_alphabet[j]){
                flag = true; // char is in alphabet
                break; // next char
            }
        }
        if (!flag){
            printf("Enter a positive integer number!\n");
            return safe_m_input();
        }
    }
    // conversion to int
    unsigned int m = atoi(s);

    return m;
}