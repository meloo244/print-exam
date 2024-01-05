#include <stdarg.h> // Inclusion de la bibliothèque pour la gestion des arguments variables
#include <unistd.h> // Inclusion de la bibliothèque pour les fonctions d'écriture et de gestion de la mémoire

// Fonction pour écrire une chaîne de caractères dans la sortie standard et mettre à jour la longueur
void put_str(char *str, int *len)
{
    if (!str)	// si str et nul
        str = "(null)";
    while (*str) // tant que pointeur de str
        *len += write(1, str++, 1); // pointeur de len += write( de "str++")
}

// Fonction pour écrire un nombre dans une base donnée dans la sortie standard et mettre à jour la longueur
void put_digit(long long int nbr, int base, int *len)
{
    char *hexa = "0123456789abcdef"; // hexa et = as [0123456789abcdef]
    if (nbr < 0) // si nbr et plus petit que 0
    {
        nbr = nbr * -1; // nbr et egale a nbr de "* -1"
        *len += write(1, "-", 1); // pointeur de len et "+=" as write de "-"
    }
    if (nbr >= base) // si nbr et plus grand egale ">=" de base
        put_digit((nbr / base), base, len); // ont rappel put-digit
    *len += write(1, &hexa[nbr % base], 1); // pointeur de len += as write de &hexa[nbr % base]
}

// Fonction principale pour émuler la fonction printf
int ft_printf(const char *format, ...)
{
    int len; // Variable pour suivre la longueur de la sortie
    va_list ptr; // Variable pour gérer la liste d'arguments variables

    len = 0; // pas oublie d initialise len as 0
    va_start(ptr, format); // Initialisation de la liste d'arguments variables
    while (*format)
    {
        if ((*format == '%') && *(format + 1)) // si format de '%' et format + 1
        {
            format++; // incrementation format
            if (*format == 's') // si format et == as S
                put_str(va_arg(ptr, char *), &len); // Appel de la fonction put_str avec l'argument de type chaîne de caractères
            else if (*format == 'd') // si format et == as D
                put_digit((long long int)va_arg(ptr, int), 10, &len); // Appel de la fonction put_digit avec l'argument de type entier décimal
            else if (*format == 'x') // si format et == as X
                put_digit((long long int)va_arg(ptr, unsigned int), 16, &len); // Appel de la fonction put_digit avec l'argument de type entier hexadécimal
        }
        else // sinon
            len += write(1, format, 1); // len += write de format
        format++; // pas oublie d incremente format
    }
    return (va_end(ptr), len); // Finalisation de l'utilisation de la liste d'arguments variables et retour de la longueur totale
}

/*
Divise et conquiers : Comprends chaque fonction individuellement avant de les relier ensemble.

Comprendre les bibliothèques : Prends le temps de comprendre l'utilité des bibliothèques incluses (<stdarg.h> et <unistd.h>).

Mots-clés : Souligne les mots-clés importants comme void, if, while, write, va_list, va_start, va_arg, va_end, etc.

Notation : Comprends la notation *len += write(1, str++, 1); et comment elle contribue à la longueur du résultat.

Types de données : Assure-toi de comprendre pourquoi long long int est utilisé dans la fonction put_digit.

Les boucles : Observe comment les boucles while et la récursivité sont utilisées pour atteindre l'objectif.

Applicabilité : Comprends dans quel contexte ce code peut être utilisé, par exemple, pour formater une sortie similaire à printf.

*/
