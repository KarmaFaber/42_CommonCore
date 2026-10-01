/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:17:23 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/07 11:21:13 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <typeinfo>

#define CMAGENTA			"\033[0;35m"
#define CRED				"\033[0;31m"
#define CGREEN				"\033[0;32m"
#define CCYAN				"\e[36m"
#define CBLACK				"\033[0;30m"
#define CYELLOW				"\033[0;33m"
#define BG_BRIGHT_YELLOW	"\e[103m"
#define CRESET				"\033[0m"
#define TEST_S				"========================== START TESTS: ============================"
#define TEST_1				"   ⇢   Test 1: char array   ⇠   "
#define TEST_2				"   ⇢   Test 2: const char array   ⇠   "
#define TEST_3				"   ⇢   Test 3: string array   ⇠   "
#define TEST_4				"   ⇢   Test 4: int array   ⇠   "
#define TEST_5				"   ⇢   Test 5: float   ⇠   "
#define TEST_6				"   ⇢   Test 6: instantiated template function   ⇠   "
#define TEST_7				"   ⇢   Test 7: instantiated template function -> cast int to float ⇠   "
#define TEST_B				"\n⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒\n"
#define TEST_E				"\n========================== END OF TESTS. ==========================="

static void	showMsg(const char* color, const char* msg, const char* reset)
{
	std::cout << color << msg << reset << std::endl;
}
//---not const STR func---------------------------
void	str_to_lower(std::string &str)
{
	for (size_t i = 0; i < str.length(); i++)
		str[i] = std::tolower(str[i]);
}

void	str_to_upper(std::string &str)
{
	for (size_t i = 0; i < str.length(); i++)
		str[i] = std::toupper(str[i]);
}

//---not const CHAR func---------------------------
void	char_to_lower(char &c)
{
	c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
}

//---const func------------------------------
void 	printChar(const char &c)
{
	std::cout <<'[' << c << ']' << ' ';
}

void	printInt(const int &n)
{
	std::cout <<'[' << n << ']' << ' ';
}

void	printFloat(const float &n)
{
	std::cout <<'[' << n << ']' << ' ';
}

void	printString(const std::string &s)
{
	std::cout <<'[' << s << ']'  << ' ' ;
}

//instantiated template function
template<typename T>
void printSquare(const T &x)
{
	std::cout <<'[' << x * x << ']' << ' ';
}

template<typename T>
void printAsFloat(const T &x)
{
	float f = static_cast<float>(x);
	std::cout << '[' << f << "] (type: " << typeid(f).name() << ") \n";
}

template<typename T>
void doubleValue(T &x)
{
	x *= 2;
}

//MAIN
int main()
{
	showMsg(CMAGENTA, TEST_S ,CRESET);

	//test_1 ⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_1 ,CRESET);
	char chars[] = {'A', 'B', 'C', 'D', '\0'};
	iter(chars, 4, char_to_lower);
	iter(chars, 4, printChar);
	showMsg(CBLACK, TEST_B ,CRESET);

	//test_2 ⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_2 ,CRESET);
	const char constChars[] = {'x', 'y', 'z'};
	showMsg(CRED, "here we can't use: iter(constChars, 3, char_to_lower);" ,CRESET);
	//iter(constChars, 3, char_to_lower);
	showMsg(CGREEN, "but we can use: iter(constChars, 3, printChar); ->" ,CRESET);
	iter(constChars, 3, printChar);
	showMsg(CBLACK, TEST_B ,CRESET);

	//test_3 ⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_3 ,CRESET);
	std::string words[] = {"hElLo", "WoRlD", "AmelIa", "niCe DaYY"};
	showMsg(CCYAN, "original: " ,CRESET);
	iter(words, 4, printString);
	iter(words, 4, str_to_upper);
	showMsg(CCYAN, "\nstr_to_upper: " ,CRESET);
	iter(words, 4, printString);
	iter(words, 4, str_to_lower);
	showMsg(CCYAN, "\nstr_to_lower: " ,CRESET);
	iter(words, 4, printString);
	showMsg(CBLACK, TEST_B ,CRESET);

	//test_4⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_4 ,CRESET);
	int numbers[] = {1, 2, 3, 4, 5, 77};
	iter(numbers, 6, printInt);
	showMsg(CBLACK, TEST_B ,CRESET);

	//test_5⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_5 ,CRESET);
	float f_numbers[] = {0.f, 2.f, 3.3f, -1.2e-3f, .0f, 22.025};
	iter(f_numbers, 6, printFloat);
	showMsg(CBLACK, TEST_B ,CRESET);

	//test_6⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_6 ,CRESET);
	int arr[] = {1, 2, 3, 4};
	showMsg(CCYAN, "original: " ,CRESET);
	iter(arr, 4, printInt);												// ➨ iter<int, void(*)(const int&)>(int*, size_t, void(*)(const int&))
	showMsg(CCYAN, "\nafter instantiated template function: printSquare<int>" ,CRESET);
	iter(arr, 4, printSquare<int>);
	showMsg(CCYAN, "\nafter instantiated template function: doubleValue" ,CRESET);
	iter(arr, 4, static_cast<void(*)(int&)>(doubleValue<int>));			// ➨ iter<int, ???>(int*, size_t, ???) ➨ explicit cast ➨ iter<int, void(*)(int &)>(int*, size_t, void(*)(int &))
	iter(arr, 4, printSquare<int>);										// ➨ iter<int, ???>(int*, size_t, ???) ➨ inferable type ➨ iter<int, void(*)(int &)>(int*, size_t, void(*)(int &))
	showMsg(CBLACK, TEST_B ,CRESET);

	//test_7⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_7 ,CRESET);
	int ints[] = {10, 20, 30, 40};
	showMsg(CCYAN, "original: " ,CRESET);
	iter(ints, 4, printInt);
	showMsg(CCYAN, "\ncasting int to float: " ,CRESET);
	iter(ints, 4, printAsFloat<int>);

	showMsg(CMAGENTA, TEST_E, CRESET);

	// 🔹🔹🔹 FINAL NOTES 🔹🔹🔹
	showMsg(CYELLOW, "\n 🧐 TEMPLATE RECAP — iter() with functions or template functions:\n", CRESET);

	showMsg(CMAGENTA, "use a normal function in iter:⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒", CRESET);
	showMsg(CMAGENTA, "The compiler selects the appropriate overload based on the type of array passed.", CRESET);
	std::cout
	<< "✅  Regular (non-template) function — type known and deducible:\n"
	<< "    iter(arr, 4, printInt); ➨  void printInt(" << CGREEN << "const int &n" << CRESET <<"); \n\n"
	<< "       The compiler sees: ➨ iter<int, " << CGREEN << "void(*)(const int&)" << CRESET <<">(int*, size_t, " << CGREEN << "void(*)(const int&)" << CRESET <<")\n"
	<< std::endl;;

	showMsg(CMAGENTA, "use template in iter:⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒", CRESET);
	showMsg(CMAGENTA, "But since doubleValue is not yet instantiated with a specific type,", CRESET);
	showMsg(CMAGENTA, " the compiler cannot resolve it and will ask you to specify the data type you are passing to it.", CRESET);

	std::cout
	<< "❌  Template function not instantiated — type not deducible:\n"
	<< "    iter(arr, 4, doubleValue);\n\n"
	<< "       The compiler sees: ➨ iter<int, " << CRED << "\?\?\?" << CRESET <<">(int*, size_t, " << CRED << "\?\?\?" << CRESET <<")\n"
	<< CRED << "                                      ..." << CRESET << "\n"
	<< CRED << "                                      void(*)(int&)" << CRESET << "\n"
	<< CRED << "                                      void(*)(float&)" << CRESET << "\n"
	<< CRED << "                                      void(*)(T&)" << CRESET << "\n"
	<< CRED << "                                      ..." << CRESET << "\n"

	<< "✅  Instantiated template — deducible type:\n"
	<< "    iter(arr, 4, doubleValue<int>);\n\n"
	<< "       The compiler sees: ➨ iter<int, " << CGREEN << "void(*)(int &)" << CRESET <<">(int*, size_t, " << CGREEN << "void(*)(int &)" << CRESET <<")\n\n"

	<< "✅  Instantiated template + explicit cast — type forced:\n"
	<< "    iter(arr, 4, static_cast<void(*)(int&)>(doubleValue<int>));\n\n"
	<< "       The compiler sees: ➨ iter<int, " << CGREEN << "void(*)(int &)" << CRESET <<">(int*, size_t, " << CGREEN << "void(*)(int &)" << CRESET <<")\n"
	<< std::endl;;
	return (0);
}