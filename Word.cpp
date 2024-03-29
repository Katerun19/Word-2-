#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <iterator>
#include <set>
using namespace std;

//Прочитать текстовый файл.Вывести список десяти наиболее часто встречаемых слов, каждое из которых не короче 4 символов.


template < typename TKey, typename TValue >
class descending_pair_value_comparer : public binary_function < pair<TKey, TValue>, pair<TKey, TValue>, bool >
{
public:
	bool operator() (const pair<TKey, TValue>& p1, const const pair<TKey, TValue>& p2)
	{
		return p1.second > p2.second;
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	string Word;
	ifstream file("Straustrup_CPP.txt");
	cout << "Наиболее часто встречаемые слова, каждое из которых не короче 4 символов:" << endl;
	if (file.is_open())																				//Если не достигнут конец файла, выполнять цикл
	{
		multiset <string> WordSet;																	//создадим множество слов.		
		while (file >> Word)
		{
			if (size(Word) >= 4) {																	//Если размер слова больше 4 знаков, записываем в множество
				WordSet.insert(Word);
			}
		}

		map <string, int> WordNumberMap;																		// Посчитаем сколько одинаковых слов в нашем множестве, 
		multiset <string> ::iterator it = WordSet.begin();											// и создадим пару "слово - количество вхождений"
		for (int i = 1; it != WordSet.end(); i++, it++) {
			int a = WordSet.count(*it);
			WordNumberMap.emplace(*it, a);
		}

		vector <pair<string, int>> VectorWord;															//создаем вектор из map'a, для сортировки по количеству вхождений
		copy(WordNumberMap.begin(), WordNumberMap.end(), back_insert_iterator <vector <pair <string, int>>>(VectorWord));
		sort(VectorWord.begin(), VectorWord.end(), descending_pair_value_comparer <string, int>());			//сортируем по убыванию


		for (vector <pair <string, int>> ::size_type i = 0; i < min(10u, VectorWord.size()); i++)
		{
			cout << VectorWord[i].second << ": " << VectorWord[i].first << endl;
		}
		file.close();
	}
	else
	{
		cout << "Could not open file" << endl;
	}
	return 0;
}