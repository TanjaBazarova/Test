#include "stdafx.h"
#include "make_elephant.h"
using namespace TaskAlphaBank;

make_elephant::make_elephant()
{
	dictionary_words = gcnew List<String^>();
	result = gcnew List<String^>();
	new_words = gcnew words();

}
//чтение слов из файла
int make_elephant::open_words_file(String^ name_of_file)
{
	if (!File::Exists(name_of_file) )
		return 0;
	if (Path::GetExtension( name_of_file ) != ".txt")
		return 0;
	StreamReader^ sr = gcnew StreamReader(name_of_file, Encoding::Default);
   try
   {
      if ((new_words->start = sr->ReadLine()) && (new_words->end = sr->ReadLine()) && (new_words->start->Length == new_words->end->Length))
      {
		  sr->Close();
		  return 1;
      }
	  else return 0;
   }
   finally
   {
      if (sr)
         delete (IDisposable^)sr;
   }
}

//открытие файла-словар€ и выборка слов по длине
int make_elephant::open_dictionary_file(String^ name_of_file)
{
	if (!File::Exists(name_of_file))
		return 0;
	if(Path::GetExtension( name_of_file ) != ".txt")
		return 0;
	StreamReader^ new_sr = gcnew StreamReader(name_of_file, Encoding::Default);
	try
	{
		String^ word = "";
		while ( word = new_sr->ReadLine() )
		{
			if(check_up_word(word))
				dictionary_words->Add(word);	
		}
	}
   finally
   {
      if (new_sr)
            delete (IDisposable^)new_sr;
   }
   if (dictionary_words->Count == 0)
		return 0;
   else
   {
		dictionary_words->Insert(0,new_words->start);	
	    dictionary_words->Add(new_words->end);
		return 1;
   }
}
//проверка слова
int make_elephant::check_up_word(String^ word)
{
	if (word->Length != new_words->start->Length)
		return 0;
	if ((String::Compare(word,new_words->start) == 0) || (String::Compare(word,new_words->end) == 0))
		return 0;
	if(dictionary_words->Contains(word) == true)
		return 0;
	return 1;
}

//сравнение слов
int make_elephant::compare(String^ first, String^ second)
{
	int count_letter = 0;
	for (int i=0; i<first->Length; i++)
	{
		if (first[i] != second[i]) count_letter++;
	}
	return count_letter;
}

//формирование цепочки слов
int make_elephant::make_chain()
{
	int count = dictionary_words->Count;
	array<int,2>^ matrix = gcnew array<int,2>(count,count);
	//заполнение матрицы смежности
	for (int i=0; i<count; i++)
	{
		for (int j=0; j<count; j++)
		{
			if(compare(dictionary_words[i], dictionary_words[j]) == 1)
				matrix[i,j] = 1;
			else matrix[i,j] = 0;
		}
	}
	//поиск кратчайшей цепочки
	if (find_the_shortest(matrix,count) != nullptr)
		return 1;
	else 
		return 0;
}
//поиск кратчайшей цепочки
List<String^>^ make_elephant::find_the_shortest(array<int,2>^ matrix, int count)
{
	int v = 0;
	int i = 0;
	array<int>^ found = gcnew array<int>(count);
	array<int>^ way_len = gcnew array<int>(count);
	array<int>^ way = gcnew array<int>(count);
	for (int i=0; i<count; i++)
    {
      way_len[i] = INT_MAX; found[i] = 0;  
    }
   way[0] = 0; 
   way_len[0] = 0; 
   found[0] = 1;  
   while(1)
   {
      for( i=0; i <count; i++)
      {
         if(matrix[v,i] == 0)continue; 
         if(found[i] == 0 && way_len[i] > way_len[v] + matrix[v,i])  
         {
            way_len[i] = way_len[v] + matrix[v,i];	
            way[i] = v;
         }
      }
      int w = INT_MAX; 
      v = -1;           
      for(i = 0; i < count; i++) 
      {
         if(found[i] == 0 && way_len[i] < w) 
         {
            v = i;
            w = way_len[i];
         }
      }
      if(v == -1)
      {
         return nullptr;
      }
      if(v == count-1) 
      {       
   	   i = count-1;
   	   while(i != 0)
         {
            result->Add(dictionary_words[i]);
            i = way[i];
         }
   	   break;
      }
      found[v]=1;
   }
   result->Add(dictionary_words[0]);
   return result;
}

//вывод результата
void make_elephant::print_result()
{
	int count = result->Count - 1;
	while(count >= 0)
	{
		Console::WriteLine(result[count]);
		count--;
	}
}

int make_elephant::main()
{
	String^ words_file;
	String^ dictionary_file;
	Console::WriteLine("¬ведите название файла с начальным и конечным словами:");
	words_file = Console::ReadLine();
	Console::WriteLine("¬ведите название файла со словарем:");
	dictionary_file = Console::ReadLine();
	Console::Clear();
	if(open_words_file(words_file) && open_dictionary_file(dictionary_file))
	{
		if(make_chain())
			print_result();
		else Console::WriteLine("ќшибка!");
	}
	else Console::WriteLine("ќшибка открыти€ файлов!");
	_getch();
    return 0;
}


make_elephant::~make_elephant()
{
	dictionary_words->Clear();
	result->Clear();
}