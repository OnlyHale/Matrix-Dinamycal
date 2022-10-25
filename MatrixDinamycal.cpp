/***************************************************************************************
*Project Name : MatrixDinamycal                                                        *
*File Name    : MatrixDinamycal.cpp                                                    *
*Language     : CPP,MSVS ver 2015 and above                                            *
*Programmers  : Ратников Роман Олегович,Фицайло Александр Александрович,               *
*                               группа:М3О-110Б-20                                     *
*Modified By  :                                                                        *
*Created      : 18/05/2021                                                             *
*Last Revision: 19/05/2021                                                             *
*Comment      : Двумерные массивы                                                      *
***************************************************************************************/


#include <iostream>
#include <fstream>
using namespace std;
                                                           
//Функция записи и печати матрицы
int** IntMatr(const char* fName,  //   Файл
	int& N,                     //   Число строк            
	int& M,                     // Число столбцов
	int& Error)                                             
{   //Изначально нет ошибок
    Error = 0;
	fstream fin;
	fin.open(fName);
	//Проверка на существование файла
	if (!fin)
	{
		cout << " Файл " << fName << " не найден" << endl;			//Сообщение об ошибке
		fin.close();					            //Закрыть файл
		Error = 1;                               //Появилась ошибка
		return nullptr;					                //Выход 
	}
	//Проверка на пустоту файл
	if (fin.peek() == EOF)
	{
		cout << " Файл " << fName << " пуст" << endl;
		fin.close();
		Error = 2;
		return nullptr;
	}

	fin >> N >> M;
	//Указатели
	int* pN = &N;
	int* pM = &M;
	//Проверка ввода на корректные данные
	if (fin.fail())
	{
		fin.close();
		cout << " Ошибка ввода . Некорректные данные." << endl;
		Error = 3;
		return nullptr;
	}
	//Технологическая печать 
	cout << " N = " << *pN << endl;
	cout << " M = " << *pM << endl;
	//Проверка на натуральность N
	if (*pN <= 0)
	{
		fin.close();
		cout << " Ошибка ввода .N не может быть меньше 1 " << endl;
		Error = 4;
		return nullptr;
	}
	//Проверка на натуральность M
	if (*pM <= 0)
	{
		fin.close();
		cout << " Ошибка ввода .M не может быть меньше 1 " << endl;
		Error = 5;
		return nullptr;
	}
	                                  //Убраны 2 ошибки на превышение MAXN

	//Выделение памяти для двумерного массива N на M
	//Массив указателей
	int** Matr = new int* [*pN];
	//Выделение памяти для строк
	for (int i = 0;i < *pN;i++)
	{
		*(Matr+i) = new int[*pM];
	}

    //Запись матрицы
	for (int i = 0;i < *pN;i++)
	{
		for (int j = 0; j < *pM;j++)
		{

			//Если недостаточно данных
			if (fin.eof())
			{
				fin.close();
				cout << " Ошибка ввода. Недостаточно данных." << endl;
				Error = 6;
				return nullptr;

			}

			fin >> *(*(Matr + i)+j);
			//Если встречены некорректные данные
			if (fin.fail())
			{
				fin.close();
				cout << " Ошибка ввода .Некорректные данные ." << endl;
				Error = 7;
				return nullptr;
			}
		}
	}
	//Если превышено количество данных
	if (!fin.eof())
	{
		fin.close();
		cout << " Ошибка ввода . Превышено количество данных." << endl;
		Error = 8;
		return nullptr;


	}
	//Печать матрицы
	for (int i = 0;i < *pN;i++)
	{
		for (int j = 0; j < *pM;j++)
			cout << "\t" << *(*(Matr+i)+j) << ' ';
		cout << endl;
	}
	return Matr;
}


// Функция определения максимального числа,которое повторялось в матрице
void MAXP(int **Matr, int N, int M)
{   //Индексовые переменные
	int i;
	int j;
	//Указатели
	int* pN = &N;
	int* pM = &M;
	//Переменная для сохранения значения
	int Bufer;
	int max;   // Максимальное значение , которое повторялось
	//Изначально нет повтора чисел в матрице
	bool Repeat = false;
	int *arrMAXP= new int [(*pN) * (*pM)]; // Вектор для сортировки
	//Запись матрицы в вектор
	for (i = 0;i < *pN;i++)
	{
		for (j = 0;j < *pM;j++)
		{
			
			*((arrMAXP + i * (*pM)) + j) = *(*(Matr+i)+j);

			  
		}

	}

	//Сортировка чисел от большего значения к меньшему 
	for (i = 0;i < (*pN) * (*pM);i++)
	{
		for (j = (*pN) * (*pM) - 1; j > 0;j--)

		{
			if (*(arrMAXP+j) > *(arrMAXP+j-1))

			{
				Bufer = *(arrMAXP + j - 1);
				*(arrMAXP + j - 1) = *(arrMAXP + j );
				*(arrMAXP + j) = Bufer;
			}
		}


	}
   //Поиск первого повторяющегося числа


	for (i = 0;i < (*pN) * (*pM) - 1;i++)
	{
		if (*(arrMAXP+i) == *(arrMAXP+i + 1))
		{   //Есть повтор
			Repeat = true;
			max = *(arrMAXP+i);
			break;
		}


	}
	//Если есть повтор
	if (Repeat)
	{
		cout << " Максимальное число , которое повторяется:  " << max << endl;
	}
	else
	{
		cout << " В матрице нет повторяющихся чисел" << endl;
	}
   
}
  //Подсчёт строк в матрице, в которых нет чётных чисел
void CHET(int** Matr, int N, int M)

{


	int Counter = N;      //Всего строк
	//Указатели
	int* pN = &N;
	int* pM = &M;
	for (int i = 0;i < *pN; i++)
	{
		for (int j = 0;j < *pM;j++)
		{
			if (*(*(Matr+i)+j) % 2 == 0)  //Если есть чётное число в строке
			{
				Counter--;
				break;
			}
		}
	}
	cout << " Количество строк  без  чётных чисел: " << Counter << endl;

}

//Функция очистки памяти
void DeleteMatr(int** Matr, int N)

{
	int* pN = &N;
	//Удаление строк
	for (int i = 0; i < *pN;i++)
	{
		delete[]Matr[i];

	}
	//Удаление массива указателей
	delete[]Matr;
}
int main()
{
	setlocale(LC_ALL, "Rus");         //Русский язык в консоли
	system("color F0");           //Белая консоль,чёрные буквы
	//Двумерные массивы
	int** A=nullptr;
	int** B=nullptr;

	int N;  //Кол-во строк
	int M;  //Кол-во чисел в строке(Столбцов)

	const char* fName = "A.txt";         // Корректный тест
	//const char* fName = "A0.txt";      // Корректный тест , нет повторяющихся чисел
	//const char* fName = "Aф.txt";      // Некорректный тест.Несуществующий файл
	//const char* fName = "A1.txt";      // Некорректный тест.Пуcтой файл
	//const char* fName = "A2.txt";      // Некорректный тест.Некорректные N и M
	//const char* fName = "A3.txt";      // Некорректный тест. N или M не целые(Некорректные)
	//const char* fName = "A4.txt";      // Некорректный тест. Числа в матрице некорректные
	//const char* fName = "A5.txt";      // Некорректный тест. Недостаточно данных
	//const char* fName = "A6.txt";      // Некорректный тест , N меньше 1
	//const char* fName = "A7.txt";      // Некорректный тест , M меньше 1
	//const char* fName = "A8.txt";      // Некорректный тест , Превышено количество данных



	const char* fName2 = "B.txt";       // Корректный тест
	//const char* fName2 = "B0.txt";      // Корректный тест , нет повторяющихся чисел
	//const char* fName2 = "Ba.txt";      // Некорректный тест.Несуществующий файл
	//const char* fName2 = "B1.txt";      // Некорректный тест .Пуcтой файл
	//const char* fName2 = "B2.txt";      // Некорректный тест.Некорректные N или M
	//const char* fName2 = "B3.txt";      // Некорректный тест. N или M не целые (Некорректные)
	//const char* fName2 = "B4.txt";      // Некорректный тест. Числа в матрице некорректные
	//const char* fName2 = "B5.txt";      // Некорректный тест. Недостаточно данных
	//const char* fName2 = "B6.txt";      // Некорректный тест , N меньше 1
	//const char* fName2 = "B7.txt";      // Некорректный тест , M меньше 1
	//const char* fName2 = "B8.txt";      // Некорректный тест , Превышено количество данных


	
	int Error;
	cout << "\t Матрица А" << endl;
	A = IntMatr(fName, N, M,Error);
	
	if (Error == 0)
	{
		CHET(A, N, M);
		MAXP(A, N, M);
		DeleteMatr(A, N);
	}
	

	Error = 0;  //Изначально ошибок нет в следующей матрице перед проверкой

	cout << "\t Матрица B" << endl;
	B = IntMatr(fName2, N, M,Error);
	if (Error == 0)
	{
		
		CHET(B, N, M);
		MAXP(B, N, M);
		DeleteMatr(B, N);
	}

	return 0;
}
