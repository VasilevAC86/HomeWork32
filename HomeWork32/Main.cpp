# include <iostream>
#include<string>

unsigned int N; // Глобальная переменная для хренения числа N

std::string to_binary(int n); // Функция для предстваления десятичного числа в двоичном формате
int return_quantity_1(const std::string &text); // Функция, возвращающая кол-во единиц в двоичном представлении числа
int exam_value(int value, int length); // Функция проверки значения на предмет вхождения в диапазон
void change_bit(std::string &text, int index_first_bit, int index_second_bit, int length); // Процедура смены мест битов в двоичном представлении числа

int main() {
	// Задача 1. Возведение числа 2 в степень n	
	std::cout << "\033[91mTask 1. Raising 2 to the power N.\033[0m\n\n\033[93mEnter a number N =\033[0m ";
	std::cin >> N;
	N--; // Уменьшаем степень числа на единицу, чтобы убрать битовый сдвиг степени 1
	unsigned int result = 2 << N;
	std::cout << "\n2 ^ " << ++N << " = \033[92m" << result << "\033[0m\n\n";

	// Задача 2. Кол-во единиц в числе N
	std::cout << "\033[91mTask 2. Number of units in number N.\033[0m\n\n\033[93mEnter a number N =\033[0m ";
	std::cin >> N;
	std::cout << "\nQuantity of ones in binary representation of a number " << N << " is \033[92m" << return_quantity_1(to_binary(N)) << "\033[0m\n\n";
	
	// Задача 3. Замена index 1 на index 2 двоичного представления числа N
	std::cout << "\033[91mTask 3. Changing indices in the binary representation of a number\033[0m\n\n\033[93mEnter a number N =\033[0m ";
	std::cin >> N;
	std::string text = to_binary(N);
	unsigned int quantity_symbols = text.length(); // Кол-во символов двоичного представления числа N
	std::cout << "It length is " << quantity_symbols << " symbols\n";
	unsigned int index_first_bit, index_second_bit; //Переменные для хранения индексов битов, которые необходимо поменять местами
	do {
		std::cout << "\n\033[93mEnter a number of position the first bit -> \033[0m";
		std::cin >> index_first_bit;
		index_first_bit = exam_value(index_first_bit, quantity_symbols - 1);
		std::cout << "\n\033[93mEnter a number of position the second bit -> \033[0m";
		std::cin >> index_second_bit;
		index_second_bit = exam_value(index_second_bit, quantity_symbols - 1);
		if (index_second_bit <= index_first_bit) {
			std::cout << "\033[91mInput error!\033[0m The index of the second bit cannot be less than the index of the first bit.\nEnter a number of position the first bit one more time -> ";
			std::cin >> index_first_bit;
			std::cout << "Enter a number of position the second bit one more time -> ";
			std::cin >> index_second_bit;
		}
	} while (index_second_bit <= index_first_bit);
	change_bit(text, index_first_bit, index_second_bit, quantity_symbols);

	return 0;
}

std::string to_binary(int n) {
	unsigned int number_source = n; // Исходное значение числа n
	std::string result;
	result.reserve(32); // Резервируем память под 32 символа в строке
	while (n > 1) { // Цикл записи в строку result результата поэтапного перевода перевода числа N из десятичного формата в двоичный
		result += std::to_string(n % 2); // Конкатинируем строку на остаток деления по модуля числа 
		n /= 2; // Уменьшаем число в два раза
	}
	result += n = 1 ? '1' : '0'; // Конкатинируем строку на остаток от числа n после цикла деления на 2
	std::reverse(result.begin(), result.end()); // Переворачиваем строку
	std::cout << "\nNumber " << number_source << " in binary is " << result << '\n';
	return result;
}

int return_quantity_1(const std::string& text) {
	int result = 0;
	int length = text.length();
	for (int i = 0; i < length; ++i) // Цикл подсчёта кол-ва символов единиц в строке
		if (text[i] == '1')
			result++;
	return result;
}

int exam_value(int value, int length) {
	while (value < 0 || value > length) {
		std::cout << "\033[91mInput error!\033[0m The entered value must be between 0 and " << length << "\nEntered the value one more time -> ";
		std::cin >> value;
	}
	return value;
}

void change_bit(std::string &text, int index_first_bit, int index_second_bit, int length) {	
	// Находим значения битов соответствующих индексов по правилами позиционирования двоичных чисел	
	int value_first = text[length - 1 - index_first_bit]; 
	int value_second = text[length - 1 - index_second_bit];
	text[length - 1 - index_first_bit] = value_second;
	text[length - 1 - index_second_bit] = value_first;		
	if (text[0] == '0') { // Если после замены битов местами, обновлённая строка двоичной интерпритации числа начинается с символа '0', то \
						убираем лишние нули из строки и пересчитываем длину строки
		text = text.substr(text.find('1'));
		length = text.length();
	}
	int number = 0; // Число в десятичном формате после после замены битов местами	
	for (int i = 0; i < length; ++i) {	// Цикл перевода двоичной интерпритации числа в десятичную
		if (text[i] == '1')
			number += pow(2, (length - 1 - i));		
	}	
	std::cout << "\nNumber after swapping bits in binary representation is \033[93m" << text << "\033[0m\nNumber after swapping bits in decimal notation is \033[03m"<<number<<"\033[0m\n";	
}
