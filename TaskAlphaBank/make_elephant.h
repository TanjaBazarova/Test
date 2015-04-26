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
		//����� � �������� �����
		public:words^ new_words;
		//����� � �������
		public:List<String^>^ dictionary_words; 
		//���������
		List<String^>^ result; 

		public: make_elephant();				
		//������ ���� �� �����
		public: int open_words_file(String^ name_of_file);
		//�������� �����-������� � ������� ���� �� �����
		public: int open_dictionary_file(String^ name_of_file);
		//�������� �����
		public: int check_up_word(String^ word);
		//��������� ����
		public: int compare(String^ first, String^ second);			
		//������������ ������� ����
		public: int make_chain();
		//����� ���������� �������
		public: List<String^>^ find_the_shortest(array<int,2>^,int count);
		//����� ����������
		public:void print_result();
		public: int main();
		make_elephant::~make_elephant();
		
	};
}
