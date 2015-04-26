// TaskAlphaBank.h

#pragma once
#include <conio.h>
#include <limits.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::Text;

namespace TaskAlphaBank {


	public ref struct words
	{
		String^ start;
		String^ end;
	};

	public ref class make_elephant
	{
		//слова в исходном файле
		public:words^ new_words;
		//слова в словаре
		public:List<String^>^ dictionary_words; 
		//результат
		List<String^>^ result; 

		public: make_elephant();				
		//чтение слов из файла
		public: int open_words_file(String^ name_of_file);
		//открытие файла-словаря и выборка слов по длине
		public: int open_dictionary_file(String^ name_of_file);
		//проверка слова
		public: int check_up_word(String^ word);
		//сравнение слов
		public: int compare(String^ first, String^ second);			
		//формирование цепочки слов
		public: int make_chain();
		//поиск кратчайшей цепочки
		public: List<String^>^ find_the_shortest(array<int,2>^,int count);
		//вывод результата
		public:void print_result();
		public: int main();
		make_elephant::~make_elephant();
		
	};
}
