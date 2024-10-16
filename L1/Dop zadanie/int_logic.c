#include <stdio.h>
#include <stdbool.h>

int int_sum(int a, int b){
    int tmp = (a & b) << 1; // аналог "в уме"
    int ones = (a ^ b); // сумма с единицами без переноса
    if (tmp & ones){
        return int_sum(tmp, ones); 
    }
    return tmp | ones; 
}

// Функция для получения отрицательного числа
int minus_x_int(int x){
    return int_sum(~x, 1);
}

// Умножение целых чисел с использованием побитовых операций
int multiply_int(int a, int b){

    bool sign = 0; // 0 - положительный результат, 1 - отрицательный
    if (a < 0 && b < 0){
        sign = 0; // оба отрицательные -> результат положительный
        a = minus_x_int(a); // превращаем a в положительное
        b = minus_x_int(b); // превращаем b в положительное
    } else if (a < 0 && b >= 0){
        sign = 1; // только a отрицательное -> результат отрицательный
        a = minus_x_int(a); // превращаем a в положительное
    } else if (a >= 0 && b < 0){
        sign = 1; // только b отрицательное -> результат отрицательный
        b = minus_x_int(b); // превращаем b в положительное
    }

    int result = 0; 
    int multiplier = a;

    while (b > 0) {
        // Если младший бит b равен 1, добавляем сдвинутое a к результату
        if (b & 1) {
            result = int_sum(result, multiplier);
        }
        // Сдвигаем a влево (умножаем на 2)
        multiplier <<= 1;
        // Сдвигаем b вправо (делим на 2)
        b >>= 1;
    }

    return sign ? minus_x_int(result) : result; // если результат отрицательный, меняем знак
}

// Целочисленное деление с округлением
int int_division(int dividend, int divisor) {
    if (divisor == 0) {
        printf("Ошибка: Деление на ноль.\n");
        return 0; 
    }

    bool sign = 0; // 0 - положительный результат, 1 - отрицательный
    if (dividend < 0 && divisor < 0) {
        sign = 0; // оба отрицательные -> результат положительный
        dividend = minus_x_int(dividend); // делаем делимое положительным
        divisor = minus_x_int(divisor); // делаем делитель положительным
    } else if (dividend < 0 && divisor >= 0) {
        sign = 1; // делимое отрицательное -> результат отрицательный
        dividend = minus_x_int(dividend); // делаем делимое положительным
    } else if (dividend >= 0 && divisor < 0) {
        sign = 1; // делитель отрицательный -> результат отрицательный
        divisor = minus_x_int(divisor); // делаем делитель положительным
    }
    
    int quotient = 0;
    int accumulator = divisor;
    int position = 0;

    while (accumulator <= dividend) {
        accumulator <<= 1; // сдвигаем делитель влево
        position = int_sum(position, 1); // увеличиваем позицию бита
    }

    while (position >= 0) {
        if (dividend >= accumulator) {
            dividend = int_sum(dividend, minus_x_int(accumulator)); // вычитаем аккумулятор из делимого
            quotient = int_sum(quotient, 1 << position); // добавляем к частному
        }
        accumulator >>= 1; // сдвигаем аккумулятор вправо
        position = int_sum(position, minus_x_int(1)); // уменьшаем позицию бита
    }

    // если остаток >= половине делителя, округляем вверх
    int remainder = dividend;
    int half_divisor = divisor >> 1;

    if (remainder >= half_divisor) {
        quotient = int_sum(quotient, 1); // округляем частное вверх
    }

    return sign ? minus_x_int(quotient) : quotient; // применяем знак к результату
}
