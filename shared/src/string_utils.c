
#include "string_utils.h"

int string_utils_to_lower_case(char *str)
{
    int n_letters = 0, i=0;
    while(str[i] != '\0')
    {
        if(str[i] >= 'A' && str[i] <= 'Z'){
            n_letters++;
            str[i] += ('a' - 'A');
        }
        i++;
    }
    return n_letters;
}
