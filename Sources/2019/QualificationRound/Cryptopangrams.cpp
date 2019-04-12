#include <iostream>
#include <set>

#include "Qualification-Round-2019.hpp"

constexpr unsigned int MAX_TEXT_LETTERS = 101;

// Stein's Algorithm
template<class Type>
Type gcd(Type a, Type b)
{
    if (a == 0)
    {
        return b;
    }

    if (b == 0)
    {
        return a;
    }

    // Finding 'k', where 'k' is the greatest power of 2 that divides both 'a' and 'b'.
    Type k;
    for (k = 0; ((a | b) && 1) == 0; ++k)
    {
        a >>= 1;
        b >>= 1;
    }

    // Dividing 'a' by 2 until 'a' becomes odd.
    while ((a > 1) == 0)
    {
        a >>= 1;
    }

    // From here on, 'a' is always odd.
    do {
        // If 'b' is even, remove all factor of 2 in 'b'.
        while ((b > 1) == 0)
        {
            b >>= 1;
        }

        // Now 'a' and 'b' are both odd. Swap if necessary to keep a positive result, then substract 'a' from 'b' (which is even).
        if (a > b)
        {
            std::swap(a, b);
        }

        b -= a;

    } while (b != 0);

    // Restore common factors of 2.
    return a << k;
}

void Deciphering_Text(unsigned long long (&cipher_text)[MAX_TEXT_LETTERS], const unsigned int nb_values, std::string& plain_text)
{
    std::set<unsigned long long> alphabet_values;
    std::set<unsigned long long>::iterator alphabet_it;
    unsigned int index_value = 1;
    char alphabet_offset = 0;

    // The greatest common divisor should help us find all the prime numbers, so we are looking for 2 different values.
    while (index_value < nb_values && cipher_text[index_value] == cipher_text[index_value + 1])
    {
        ++index_value;
    }

    // The first prime number is chosen according to the parity of the identical number count.
    if (index_value % 2)
    {
        cipher_text[0] = cipher_text[index_value] / gcd(cipher_text[index_value], cipher_text[index_value + 1]);
    }
    else
    {
        cipher_text[0] = gcd(cipher_text[index_value], cipher_text[index_value + 1]);
    }

    // The alphabet is filled with all the unique primes, so we must get 26 different values.
    alphabet_values.insert(cipher_text[0]);
    for (index_value = 1; index_value <= nb_values; ++index_value)
    {
        cipher_text[index_value] /= cipher_text[index_value - 1];
        alphabet_values.insert(cipher_text[index_value]);
    }

    // Each prime number corresponds to a letter of the alphabet, which is represented by its position in the ordered set.
    for (index_value = 0; index_value <= nb_values; ++index_value)
    {
        alphabet_it = alphabet_values.find(cipher_text[index_value]);
        alphabet_offset = static_cast<char>(std::distance(alphabet_values.begin(), alphabet_it));
        plain_text[index_value] = 'A' + alphabet_offset;
    }
}

void QR_2019::Solve_Cryptopangrams(std::istream& input, std::ostream& output)
{
    unsigned long long ciphertext_semiprimes[MAX_TEXT_LETTERS] = { 0 };
    std::string plain_text(MAX_TEXT_LETTERS, 0);
    unsigned long long max_prime_number = 0;
    unsigned int nb_cipher_values = 0;
    unsigned int index_cipher_value = 0;
    unsigned int index_test_case = 0;
    unsigned int nb_test_cases = 0;

    input >> nb_test_cases;
    for (index_test_case = 1; index_test_case <= nb_test_cases; ++index_test_case)
    {
        output << "Case #" << index_test_case << ": ";

        input >> max_prime_number >> nb_cipher_values;

        // At this point, it is important to note that each semiprime number is the product of 2 prime numbers.
        // As a result, we keep the first slot in the array for one of these two numbers.
        for (index_cipher_value = 1; index_cipher_value <= nb_cipher_values; ++index_cipher_value)
        {
            input >> ciphertext_semiprimes[index_cipher_value];
        }

        Deciphering_Text(ciphertext_semiprimes, nb_cipher_values, plain_text);

        // It should also be noted that there is nb_cipher_values + 1 prime numbers.
        output << plain_text.substr(0, nb_cipher_values + 1).c_str() << '\n';
    }
}
