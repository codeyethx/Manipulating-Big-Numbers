/**
* Creates program that reads a pair of big numbers and uses mathematical
* operations to solve it.
* @file big.cpp
* @author Gift Chidera U.
* @date February 28, 2022
*/

#include <iostream>

using namespace std;

/**
* Return the value of the digit represented by the given character
* @param the_char the character to convert to a digit
* @returns the numerical value of the digit represented by the given character
*/
short to_digit(const char _char)
{
   return _char - '0';
}

/**
* Increase the capacity (doubling it) of the given array with the given capacity
* @param p_number a dynamically allocated array of shorts to double
* @param current_capacity the current capacity of p_number
*/
void increase_capacity(short* & p_number, size_t & current_capacity)
{
   const size_t new_capacity = current_capacity * 2;
   short* p_new_number = new short[new_capacity];
   for (size_t digit_index = 0; digit_index < current_capacity; digit_index++)
   p_new_number[digit_index] = p_number[digit_index];
   delete[] p_number;
   p_number = p_new_number;
   current_capacity = new_capacity;
}

/**
* Read a big number from the standard input
* @param initial_capacity the initial capacity for the array storing the big number
* @param num_digits the number of digits in the big number after reading it
* @returns a pointer to dynamically allocated memory storing the big number
*/
short* read_number(const size_t initial_capacity, size_t & num_digits)
{
   short* p_number = new short[initial_capacity];
   size_t current_capacity = initial_capacity;
   num_digits = 0;
   char current_char = cin.get();
   while (current_char != '\n')
   {
      if (current_capacity == num_digits)
      {
         increase_capacity(p_number, current_capacity);
      }
   p_number[num_digits++] = to_digit(current_char);
   current_char = cin.get();
   }
   return p_number;
}

/**
* Prints the big number with the given number of digits
* @param p_number the big number to print
* @param digits_in_number the number of digits in the big number
*/
void print_number(short * p_number, const size_t digits_in_number)
{
   bool flag = false;
   int count = 0;
   for (size_t digit_index = 0; digit_index < digits_in_number; digit_index++)
   {
      if (p_number[digit_index] > 0)
      {
         count++;
      }
   }
   if (count > 0)
   {
      for (size_t digit_index = 0; digit_index < digits_in_number; digit_index++)
      {
         if (p_number[digit_index] > 0 || flag)
         {
            cout << p_number[digit_index];
            flag = true;
         }
      }
   }
   else
   {
      cout << 0;
   }
   cout << endl;
}

/**
* Function to add given numbers
* @param first_number is first number on the second row
* @param sec_number is the second number on the third row
* @param digits_in_number holds the size of the dynamic array
*/
short* add_numbers(short* first_number, short* sec_number, const size_t digits_in_number)
{
   short* number = new short[digits_in_number];
   int carry_over = 0;
   size_t current_capacity = digits_in_number;
   for (int index = current_capacity - 1; index >= 0; index--)
   {
      int sum = first_number[index] + sec_number[index] + carry_over;
      if (sum >= 10 && index > 0)
      {
         number[index] = sum - 10;
         carry_over = 1;
      }
      else
      {
         number[index] = sum;
         carry_over = 0;
      }
   }
   return number;
}

/**
* Function to subtract given numbers
* @param first_number is the first number of the second row from input
* @param sec_number is the second number of the third row from input
* @param digits_in_number holds the size of the dynamic array
*/
short* sub_numbers (short* first_number, short* sec_number, const size_t digits_in_number)
{
   short* number = new short[digits_in_number];
   int take_away = 0;
   for (int index = digits_in_number - 1; index >= 0; index--)
   {
      first_number[index] -= take_away;
      int diff = first_number[index] - sec_number[index];
      if (diff < 0)
      {
         number[index] = diff + 10;
         take_away = 1;
      }
      else
      {
         number[index] = diff;
         take_away = 0;
      }
   }
   return number;
}

/**
* Reads symbol after given capacity and executes correct thing for it
* @param symbol reads the mathematical operation
* @param first_number is first number on the second row of input file
* @param sec_number is the second number of the third row from input
* @param digits_in_number holds the size of the dynamic array
*/
short* read_symbol(char symbol, short* first_number, short* sec_number, const size_t digits_in_number) {

   if (symbol == '+') {
      return add_numbers(first_number, sec_number, digits_in_number);
   }
   if (symbol == '-') {
      return sub_numbers(first_number, sec_number, digits_in_number);
   }
   if (symbol == '%') {
      return sec_number;
   }
}

/**
* Pad the given big number with zeros until it has a new length
* @param p_number the big number to pad
* @param digits_in_number the number of digits in the big number
* @param new_digits the number of digits the padded number should have
*/
void pad_number(short* & p_number, size_t & digits_in_number, const size_t new_digits)
{
   short* p_new_number = new short[new_digits];
   const size_t num_zeros = new_digits - digits_in_number;
   for (size_t pad_index = 0; pad_index < num_zeros; pad_index++)
   p_new_number[pad_index] = 0;
   for (size_t digit_index = 0; digit_index < digits_in_number; digit_index++)
   p_new_number[num_zeros + digit_index] = p_number[digit_index];
   delete[] p_number;
   p_number = p_new_number;
   digits_in_number = new_digits;
}

/**
* Given two big numbers, padd the smaller one.
* @param p_number1 the first big number
* @param digits_in_number1 the number of digits in the first big number
* @param p_number2 the second big number
* @param digits_in_number2 the number of digits in the second big number
*/
void pad_numbers(short* & p_number1, size_t & digits_in_number1, short* & p_number2, size_t & digits_in_number2)
{
   if (digits_in_number1 > digits_in_number2)
   {
      const size_t new_digits = digits_in_number1;
      pad_number(p_number2, digits_in_number2, new_digits);
   }
   else
   {
      const size_t new_digits = digits_in_number2;
      pad_number(p_number1, digits_in_number1, new_digits);
   }
}

// Controls execution of program
int main() {
   size_t initial_capacity = 0;
   cin >> initial_capacity;
   cin.get();
   char for_symbol = cin.get();
   cin.get();
   size_t digits_in_number1 = 0, digits_in_number2 = 0;
   short* p_number1 = read_number(initial_capacity, digits_in_number1);
   short* p_number2 = read_number(initial_capacity, digits_in_number2);
   pad_numbers(p_number1, digits_in_number1, p_number2, digits_in_number2);
   short* result = read_symbol(for_symbol, p_number1,p_number2,digits_in_number1);
   print_number(result, digits_in_number1);
   delete[] p_number1;
   delete[] p_number2;
   delete[] result;
   return 0;
}
