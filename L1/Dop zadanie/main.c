#include <stdio.h>
#include <stdbool.h>
#include "int_logic.c"
#include "safe_input.c"

// int_log2 для вычисления логарифма по основанию 2 (работает только с положительными числами)
int int_log2(int x) {
    int res = 0;
    while (x >>= 1) {
        res = int_sum(res, 1);
    }
    return res;
}

// int_abs для получения абсолютного значения числа
int int_abs(int x) {
    return x < 0 ? minus_x_int(x) : x;
}

// int_cbrt для вычисления кубического корня (с учетом знака)
int int_cbrt(int x) {
    int sign = x < 0 ? -1 : 1; // Определяем знак исходного числа
    x = int_abs(x); // Работаем с абсолютным значением

    int r = 1;
    // Подбираем значение r, пока r^3 <= x
    while (multiply_int(int_sum(r, 1), multiply_int(int_sum(r, 1), int_sum(r, 1))) <= x) {
        r = int_sum(r, 1);
    }

    return sign < 0 ? minus_x_int(r) : r; // Возвращаем результат с корректным знаком
}

int main(void) {
    // Ввод значений a, b и c
    int a = safe_input_int("Введите целое a: ");
    int b = safe_input_int("Введите целое b: ");
    int c = safe_input_int("Введите целое c: ");

    // Проверка условий для корректности вычислений
    if (c == 0) {
        printf("Ошибка: значение c не должно быть равно нулю.\n");
        return 1;
    }

    // Вычисление ab_product = a * b
    int ab_product = multiply_int(a, b);
    int abs_ab_product = int_abs(ab_product); // Работаем с положительным значением для логарифма

    // Проверка на корректное значение для логарифма
    if (abs_ab_product == 0) {
        printf("Ошибка: произведение a * b не должно быть равно нулю.\n");
        return 1;
    }

    // log2(|a * b|)
    int log_ab = int_log2(abs_ab_product);

    // Проверка на логарифм равный 0, чтобы избежать деления на 0
    if (log_ab == 0) {
        printf("Ошибка: log2(a * b) равно нулю, что приведет к делению на ноль.\n");
        return 1;
    }

    // (-a + c)
    int neg_a = minus_x_int(a);
    int neg_a_plus_c = int_sum(neg_a, c);

    // (-a + c) / log_ab с округлением
    int div_result = int_division(neg_a_plus_c, log_ab);

    // cbrt(div_result) 
    int cube_root = int_cbrt(div_result);

    // cube_root / c
    int cube_root_div_c = int_division(cube_root, c);

    // Проверка деления 1 на cube_root_div_c, чтобы избежать деления на 0
    if (cube_root_div_c == 0) {
        printf("Ошибка: cube_root / c равно нулю, что приведет к делению на ноль.\n");
        return 1;
    }

    // 1 / (cube_root / c)
    int final_result = int_division(1, cube_root_div_c);

    printf("Результат выражения 1/cbrt((round((-a+c)/(log2(|a*b|)))/c)) равен: %d\n", final_result);

    return 0;
}
