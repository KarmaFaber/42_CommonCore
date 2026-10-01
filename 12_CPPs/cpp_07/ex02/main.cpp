/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:25:37 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/07 13:11:37 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include <iostream>
#include <string>

#define CMAGENTA			"\033[0;35m"
#define CRED				"\033[0;31m"
#define CGREEN				"\033[0;32m"
#define CCYAN				"\e[36m"
#define CBLACK				"\033[0;30m"
#define CYELLOW				"\033[0;33m"
#define BG_BRIGHT_YELLOW	"\e[103m"
#define CRESET				"\033[0m"
#define TEST_S				"========================== START TESTS: ============================"
#define TEST_1				"   ⇢   Test 1: Empty Array   ⇠   "
#define TEST_2				"   ⇢   Test 2: Out of Bounce Exception   ⇠   "
#define TEST_3				"   ⇢   Test 3: Int Array   ⇠   "
#define TEST_4				"   ⇢   Test 4: STR Array   ⇠   "
#define TEST_5				"   ⇢   Test 5: Copy Constructor unsing (int array)   ⇠   "
#define TEST_6				"   ⇢   Test 6: Const Instance and size()    ⇠   "
#define TEST_7				"   ⇢   Test 7: Template function inside class template   ⇠   "
#define TEST_B				"\n⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒\n"
#define TEST_E				"\n========================== END OF TESTS. ==========================="

static void	showMsg(const char* color, const char* msg, const char* reset)
{
	std::cout << color << msg << reset << std::endl;
}

// helper print function
template<typename T>
void printArray(const Array<T> &arr)
{
	for (unsigned int i = 0; i < arr.size(); i++)
		std::cout << '[' << arr[i] << "] ";
	std::cout << std::endl;
}

// template inside class template test
template<typename T>
void multiplyByTwo(T &x)
{
	x *= 2;
}

int main()
{
	showMsg(CMAGENTA, TEST_S ,CRESET);

	//test_1: Empty Array⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_1 ,CRESET);
	{
		Array<int> empty;
		showMsg(CCYAN, "Empty array created. Size:", CRESET);
		std::cout << " size = " << empty.size() << std::endl;
	}
	showMsg(CBLACK, TEST_B ,CRESET);

	//test_2: Out of Bounds Exception⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_2 ,CRESET);
	{
		Array<int> nums(3);
		try
		{
			std::cout << CCYAN << "Attempting to access index 3 of 3-element array: " << CRESET << nums[2] << std::endl;
			showMsg(CCYAN, "Attempting to access index 5 of 3-element array...", CRESET);
			std::cout << nums[5] << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << "Caught exception: "
					  << CRED << e.what() 
					  << CRESET << std::endl;
		}
	}
	showMsg(CBLACK, TEST_B ,CRESET);

	//test_3: Int Array⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_3 ,CRESET);
	{
		Array<int> intArr(5);
		for (unsigned int i = 0; i < intArr.size(); i++)
			intArr[i] = i * 10;
		showMsg(CCYAN, "Int Array contents:", CRESET);
		printArray(intArr);
	}
	showMsg(CBLACK, TEST_B ,CRESET);

	//test_4: String Arra⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_4 ,CRESET);
	{
		Array<std::string> strArr(3);
		strArr[0] = "Hello";
		strArr[1] = "Template";
		strArr[2] = "World";
		showMsg(CCYAN, "String Array contents:", CRESET);
		printArray(strArr);
	}
	showMsg(CBLACK, TEST_B ,CRESET);

	//test_5: Copy Constructor⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_5 ,CRESET);
	{
		Array<int> original(3);
		for (unsigned int i = 0; i < original.size(); i++)
			original[i] = i + 1;

		Array<int> copy(original);
		showMsg(CCYAN, "Original:", CRESET);
		printArray(original);
		showMsg(CCYAN, "Copy:", CRESET);
		printArray(copy);

		showMsg(CYELLOW, "Modifying copy[0] = 99; (original must stay the same)", CRESET);
		copy[0] = 99;
		copy[1] = 77;
		copy[2] = 33;
		showMsg(CCYAN, "Original after modification:", CRESET);
		printArray(original);
		showMsg(CCYAN, "Copy after modification:", CRESET);
		printArray(copy);
	}
	showMsg(CBLACK, TEST_B ,CRESET);

	//test_6: Const Instance⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_6 ,CRESET);
	{
		const Array<float> floats(4);
		printArray(floats);
		std::cout << CCYAN << "Const float array created. size() = " << CRESET << floats.size()  << std::endl;
	}
	showMsg(CBLACK, TEST_B ,CRESET);

	//test_7: Template function inside class template⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒⭒
	showMsg(BG_BRIGHT_YELLOW, TEST_7 ,CRESET);
	{
		Array<int> numbers(4);
		for (unsigned int i = 0; i < numbers.size(); i++)
			numbers[i] = i + 1;
		showMsg(CCYAN, "Original numbers:", CRESET);
		printArray(numbers);

		showMsg(CCYAN, "Doubling each element via multiplyByTwo<T>:", CRESET);
		for (unsigned int i = 0; i < numbers.size(); i++)
			multiplyByTwo(numbers[i]);
		printArray(numbers);
	}

	showMsg(CMAGENTA, TEST_E ,CRESET);
	return (0);
}