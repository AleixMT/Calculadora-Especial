//
// Created by Sergi Vives on 4/5/20.
//

#include "main.h"


/**
* Returns the factorial of a given natural number recursively.
* Precondition: parameter "value" is a natural number.
* Postcondition: return = value * acum; value = value - 1 where value is a natural number.
* Errors: Unsigned long long integer overflow. This happens when result is bigger than ULLONG_MAX 18.446.744.073.709.551.615
* (0xffffffffffffffff). Maximum calulable factorial is 20!. 21! cause overflow:
* 2,432,902,008,176,640,000 = 20! < ULLONG_MAX < 21! = 51,090,942,171,709,440,000
* Params:
* - value: Number to calculate factorial.
* - acum: Acumulator used for the recursive calls to acumulate the computing of the result.
*/
long long unsigned int private_factorial(unsigned int value, long long unsigned int acum)
{
    if (value == 1) return acum;
    else return private_factorial(value - 1, value * acum);
}


/**
* Returns the factorial of natural number "value" calling private_factorial, initializing inner parameters and
* returning direct cases. Uses long long integers since a factorial can be a very large number and overflow is likely,
* even if the value parameter is just an unsigned int. Factorial numbers bigger than 20! return -1 since they can not be
* computed.
* Precondition: parameter "value" is a natural or 0.
* Postcondition: return = value! only if "value" parameter is bigger than 20.
* Errors: Not defined. We control the call to private_factorial to discard possible errors.
* Params:
* - value: number to calculate factorial.
*/
long long unsigned int public_factorial(unsigned int value)
{
    if (value == 0) return 1;
    else if (value > 20) return -1;
    else return private_factorial(value, 1);
}


/**
* Returns the position where the "value" element is located. If it is not in the array it will return -1.
* Precondition: array is sorted in ascending order: lower index position have lower values.
* Postcondition: return = alpha: alpha is a natural number such as : array[alpha] == value | -1
* Errors: Not defined. The order of the list is checked in another function before entering this.
* Params:
* - array: Contains the list of numbers where we will do the search.
* - value: Value that we are looking for.
* - num_elemens: Indicates how many elements are present in the array.
* - *num_accessed_positions: used as a return parameter where we will store the number of positions accessed during the search.
*/
bool binary_search(int *array, unsigned int num_elemens, int value, unsigned int *num_accessed_positions)
{
    (*num_accessed_positions)++;  // Increment the number of accessed positions in every recursive call since the degree of recursivity = 1
    unsigned int half = (num_elemens - 1) / 2;  // Calculate the half element

    if (array[half] == value)  // The element is the actual middle
    {
        return true;
    }
    else if (num_elemens == 1)  // We did not find the element
    {
        return false;
    }
    if (array[half] < value)  // Right side of the array
    {
        return binary_search(&array[half + 1], num_elemens / 2, value, num_accessed_positions);
    }
    else  // Left side of the array
    {
        return binary_search(&array[0], num_elemens / 2, value, num_accessed_positions);
    }
}


/**
* Clears stdin.
* Precondition: True.
* Postcondition: True
* Errors: Not defined.
*/
void clean_stdin()
{
    while (getchar() != '\n');
}


/**
* Main program to interact with the calculator.
* Precondition: True.
* Postcondition: A certain operation is performed with the corresponding postconditions.
* Errors: Not defined. All user inputs are checked before performing any operation.
*/
int main(int nargs, char* args[])
{
    unsigned int option;  // Temporary storage of the option selected by user
    char endline;  // Temporary storage of endline character to validate user input

    do {
        printf("\n\n");
        printf("****************************\n");
        printf("*** CALCULADORA ESPECIAL ***\n");
        printf("****************************\n\n");
        printf("Escull quina operació vols fer escribint el nombre de la opció i prement Intro:\n");
        printf("1.- Factorial\n");
        printf("2.- Fibonacci\n");
        printf("3.- Màxim comú divisor\n");
        printf("4.- Moviments Torres de Hanoi\n");
        printf("5.- Cerca dicotómica\n");
        printf("6.- Suma digital\n");
        printf("7.- Arrel digital\n");
        printf("8.- Sortir\n\n");

        printf("Introdueix nombre d'opció: ");
        if (scanf("%u%c", &option, &endline) == 2 && endline == '\n')  // Checks that the user did not input trash
        {
            switch (option) {
                case 1:
                {
                    // check user input for the factorial
                    bool correct_input_factorial = false;
                    unsigned int value;
                    while (!correct_input_factorial)
                    {
                        printf("\n\nIntrodueix un nombre natural per a calcular el factorial: ");
                        correct_input_factorial = scanf("%u%c", &value, &endline) == 2 && endline == '\n';  // Checks that the user did not input trash
                        if (!correct_input_factorial)
                        {
                            clean_stdin();
                            printf("\nERROR: No has introduït un nombre natural. Torna-ho a intentar...");
                        }
                    }
                    long long unsigned int result = public_factorial(value);
                    if (result == -1)
                    {
                        printf("\nERROR: El factorial d'aquest nombre és tan gran que ha causat desbordament. Torna-ho a intentar amb un altre nombre.");
                    }
                    else
                    {
                        printf("\nEl factorial de %u es %llu.", value, result);
                    }

                    break;
                }
                case 2:
                {
                    break;
                }
                case 3:
                {
                    break;
                }
                case 4:
                {
                    break;
                }
                case 5:
                {
                    int *array_list = malloc(sizeof(int) * MAX_ELEMENTS);  // Reserve space for the array
                    // Open File
                    FILE *file_pointer;
                    file_pointer = fopen("input_cerca_dicotomica.txt", "r");
                    if (file_pointer == NULL) {
                        printf("\nError opening the file");
                        break;
                    }

                    // Fill the array with elements until MAX_ELEMENTS is reached or EOF is reached
                    unsigned int num_elems;  // Declared here to allow access
                    for (num_elems = 0; fscanf(file_pointer, "%i", &array_list[num_elems]) != EOF && num_elems < MAX_ELEMENTS; num_elems++) {}

                    // Check that the list is sorted before doing binary search
                    int previous = INT_MIN;
                    bool sorted = true;  // List is sorted until we found the opposite
                    for (int i = 0; i < num_elems && sorted; i++)
                    {
                        if (previous > array_list[i]) sorted = false;
                    }
                    if (!sorted)  // If list is not sorted abort this method
                    {
                        printf("\nERROR: La llista del fitxer no está ordenada");
                        break;
                    }

                    // check user input for the binary search
                    int value;
                    bool correct_input_search = false;
                    while (!correct_input_search)
                    {
                        printf("\n\nIntrodueix un nombre per a cercar a la llista: ");
                        correct_input_search = scanf("%i%c", &value, &endline) == 2 && endline == '\n';  // Checks that the user did not input trash
                        if (!correct_input_search)
                        {
                            clean_stdin();
                            printf("\nERROR: Has introduït un valor incorrecte per a cercar. Torna-ho a intentar...");
                        }
                    }

                    // Binary search
                    unsigned int num_accessed_positions = 0;
                    bool found = binary_search(array_list, num_elems, value, &num_accessed_positions);
                    if (found)
                    {
                        printf("\nL'element %i s'ha trobat. \n%u accessos a la llista.", value, num_accessed_positions);
                    }
                    else
                    {
                        printf("\nL'element %i no s'ha trobat. \n%u accessos a la llista.", value, num_accessed_positions);
                    }

                    // Release resources
                    free(array_list);
                    fclose(file_pointer);
                    break;
                }
                case 6:
                {
                    break;
                }
                case 7:
                {
                    break;
                }
                case 8:
                {
                    return 0;
                    break;
                }
                default:
                {
                    printf("\nERROR: Aquesta opció no existeix... \n");
                    break;
                }
            }
        }
        else
        {
            printf("\nERROR: No has introduït un nombre vàlid per a la selecció de la opció. Torna-ho a intentar...");
            clean_stdin();
        }

    } while (true);

    return 0;
}


