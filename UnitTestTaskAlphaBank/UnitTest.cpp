#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace TaskAlphaBank;

namespace UnitTestTaskAlphaBank
{
	[TestClass]
	public ref class UnitTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		make_elephant^ new_elephant;
		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		#pragma region Additional test attributes
	
		#pragma endregion 

		[TestMethod]
		//проверка метода open_words_file
		void TestMethodOpenWordsFile()
		{
			new_elephant = gcnew make_elephant();
			String^ testfile = "testwords.txt";
			array<String^>^ ar_words = {"КОТ","ТОН"};
			array<String^>^ ar_words_err = {"КОТ","ТОННА"};

			//если файла не существует (должен вернуть 0)
			if(File::Exists(testfile))
			{
				File::Delete(testfile);
			} 
			Assert::AreEqual(new_elephant->open_words_file(testfile),0);

			//если файл неправильного формата (должен вернуть 0)
			File::WriteAllLines("testwords.bin", ar_words, Encoding::Default);
			Assert::AreEqual(new_elephant->open_words_file("testwords.bin"),0);

			//если файл пустой (должен вернуть 0)
			File::WriteAllText(testfile,"");
			Assert::AreEqual(new_elephant->open_words_file(testfile),0);
			//если в файле слова разной длины
			File::WriteAllLines(testfile, ar_words_err, Encoding::Default);
			Assert::AreEqual(new_elephant->open_words_file(testfile),0);

			//если в файле правильные значения (должен вернуть 1)
			File::WriteAllLines(testfile, ar_words, Encoding::Default);
			Assert::AreEqual(new_elephant->open_words_file(testfile),1);
		};

		[TestMethod]
		//проверка метода set_dictionary_words
		void TestMethodOpenDictionaryFile()
		{
			new_elephant = gcnew make_elephant();
			//название файла со словарем
			String^ dicfile = "testdictionary.txt";
			array<String^>^ ar_dic = {"КОТ","ТОН","НОТА","КОТЫ","РОТ","РОТА","ТОТ"};
			
			//если файла не существует (должен вернуть 0)
			if(File::Exists(dicfile))
			{
				File::Delete(dicfile);
			}
			Assert::AreEqual(new_elephant->open_dictionary_file(dicfile),0);

			//если файл неправильного формата (должен вернуть 0)
			File::WriteAllLines("testdictionary.bin",ar_dic,Encoding::Default);
			Assert::AreEqual(new_elephant->open_dictionary_file("testdictionary.bin"),0);

			//если файл пустой (должен вернуть 0)
			new_elephant->new_words->start = "КОТ";
			new_elephant->new_words->end = "ТОН";
			File::WriteAllText(dicfile,"");
			Assert::AreEqual(new_elephant->open_dictionary_file(dicfile),0);

			//если в файле правильные значения (должен вернуть 1)
			new_elephant->new_words->start = "КОТ";
			new_elephant->new_words->end = "ТОН";
			File::WriteAllLines(dicfile,ar_dic,Encoding::Default);
			Assert::AreEqual(new_elephant->open_dictionary_file(dicfile),1);
		}

	

		[TestMethod]
		//проверка метода compare
		void TestMethodCompare()
		{
			new_elephant = gcnew make_elephant();
			//должен вернуть количество отличающихся букв
			Assert::AreEqual(new_elephant->compare("КОТ","ТОН"),2);
			Assert::AreEqual(new_elephant->compare("КОТ","ТОТ"),1);
		}


		[TestMethod]
		//проверка слова
		void TestMethodCheckUpWord()
		{
			new_elephant = gcnew make_elephant();
			new_elephant->new_words->start = "КОТ";
			new_elephant->new_words->end = "ТОН";
			array<String^>^ ar_dic = {"СОК","ТОТ","РОТ"};
			//если слово больше, чем начальное
			Assert::AreEqual(new_elephant->check_up_word("ТОННА"),0);
			//если слово равно начальному
			Assert::AreEqual(new_elephant->check_up_word("КОТ"),0);
			//если слово уже есть в листе
			new_elephant->dictionary_words->AddRange(ar_dic);
			Assert::AreEqual(new_elephant->check_up_word("СОК"),0);
			//если слово удовлетворяет заданным параметрам
			Assert::AreEqual(new_elephant->check_up_word("КИТ"),1);
		}

		[TestMethod]
		//проверка  метода find_the_shortest
		void TestMethodFindTheShortest()
		{
			new_elephant = gcnew make_elephant();
			int count = 3;
			array<String^>^ ar_dic = {"КОТ","ТОТ","РОТ"};
			array<String^>^ ar_dic_err = {"КОТ","СОК","ТОН"};
			//если цепочку построить возможно
			new_elephant->dictionary_words->AddRange(ar_dic);
			array<int,2>^ matrix = {{0,1,1},{1,0,1},{1,0,1}};
			Assert::AreNotEqual(new_elephant->find_the_shortest(matrix,count),nullptr);
			new_elephant->dictionary_words->Clear();
			//если цепочку построить невозможно
			array<int,2>^ matrix_err = {{0,0,0},{0,0,0},{0,0,0}};
			new_elephant->dictionary_words->AddRange(ar_dic_err);
			Assert::AreEqual(new_elephant->find_the_shortest(matrix_err,count),nullptr);
			new_elephant->dictionary_words->Clear();
		}

		[TestMethod]
		//проверка  метода make_chain
		void TestMethodMakeChain()
		{
			new_elephant = gcnew make_elephant();
			//если цепочку построить возможно
			array<String^>^ ar_dic = {"КОТ","ТОТ","РОТ"};
			new_elephant->dictionary_words->AddRange(ar_dic);
			Assert::AreEqual(new_elephant->make_chain(),1);
			new_elephant->dictionary_words->Clear();
			//если цепочку построить невозможно
			array<String^>^ ar_dic_err = {"КОТ","СОК","ТОН"};
			new_elephant->dictionary_words->AddRange(ar_dic_err);
			Assert::AreEqual(new_elephant->make_chain(),0);
			new_elephant->dictionary_words->Clear();
		}

	};
}
