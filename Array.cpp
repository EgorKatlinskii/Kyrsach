#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

using namespace std;

int N, M;
bool f,g,q= false;

void function_cin(double**);

void function_sort(double**, double**, double*);

void print_array(double**, double**, double*);

int function_cek_one(int);

int function_cek_two(int);

void function_del(double**,double**,double*);

int main()
{
	setlocale(LC_ALL, "Russian");
	int command;
	while (true)
	{
		q = true;
		cout <<"________________________________________________________________________________________________________________________\n";
		cout << "Программа работает с математической матрицей.При запуске программы пользователю нужно указать размер матрицы.\n\
Далее начинается процесс работы с матрице.Заполнение происходит с помощью генератора рандомных значений.После заполненияначинается\
 сортировка.В процессе работы программа будет ограничевать пользователя от функций,которые не логично использовать на данном шаге.\n";
		cout <<"________________________________________________________________________________________________________________________\n";
		cout << "Ввод размера матрицы\n\nВведите количество строк:\n";
		cin >> N;
		N = function_cek_one(N);
		cout << "Введите количество столбцов:\n";
		cin >> M;
		M = function_cek_one(M);
		srand(time(NULL));
		
		double** p = new double* [N]; // создание двумерного массива
		for (int i = 0; i < N; i++)
		{
			p[i] = new double[M];
		}

		double** p_new = new double* [N]; // создание двумерного массива для вставки характеристик
		for (int i = 0; i < N; i++)
		{
			p_new[i] = new double[M];
		}
		double* summa = new double[M / 2];
		system("cls");
		while (q) // Основная панель 
		{
			cout << "1.Заполнить матрицу элементами.\n2.Расположить столбцы в соответствии с убыванием характеристик.\n";
			cout << "3.Печать первоначальной и отсортированной  матрицы в файл.\n4.Ввести новые параметры.\n5.Завершить сеанс.\n";
			cin >> command;
			command = function_cek_two(command);
			switch (command)
			{
			case (1):
				function_cin(p);
				break;
			case (2):
				function_sort(p, p_new, summa);
				break;
			case (3):
				print_array(p, p_new, summa);
				break;
			case(4):
				function_del(p, p_new, summa);
				system("cls");
				q = false;
				g = false;
				break;
			case(5):
				function_del(p,p_new,summa);
				return 0;
			default:
				system("cls");
				cout << "Ошибка!Некорректный ввод при выборе режима!\n\n";
				break;
			}
		}
	}
	
}

void function_del(double** p,double**p_new,double*summa )
{
	for (int i = 0; i < N; i++) //Чистка первоначального массива
	{
		delete[] p[i];
	}
	delete[] p;

	for (int i = 0; i < N; i++)// Чистка отсортированного массива
	{
		delete[] p_new[i];
	}
	delete[] p_new;

	delete[] summa;
}

int function_cek_two(int n)
{
	bool success = false;
	while (success == false) { // крутим пока false, в true тормозим
		if ((cin.fail() == 0) && (n))
			success = true; // если нет ошибок в входном потоке даём true для стопа цикла
		else {               // если есть ошибки
			cout << "Ошибка!Некорректный ввод при выборе режима!\n\n";
			cin.clear();    //очищает ошибки входного потока для флажка cin.fail
			cin.ignore(cin.rdbuf()->in_avail());  //удаляем символы в буфере
			cout << "Выберите один из выше перечисленных режимов: ";
			cin >> n;
		}
	}
	/*system("cls");*/
	return n;
}

int function_cek_one(int n)
{
	bool success = false;
	while (success == false) { // крутим пока false, в true тормозим
		if ((cin.fail() == 0) && (n) && n > 3)
			success = true; // если нет ошибок в входном потоке даём true для стопа цикла
		else {               // если есть ошибки
			cout << "Ошибка ввода!Некоректные данные!" << endl;
			cin.clear();    //очищает ошибки входного потока для флажка cin.fail
			cin.ignore(cin.rdbuf()->in_avail());  //удаляем символы в буфере
			cout <<"Введите данные: " ;
			cin >> n;
		}
	}
	/*system("cls");*/
	return n;
}

void function_cin(double** p) // заполнение массива элементами 
{
	
	double x;
	fstream file("D:\\PY\\Kursach.dat", ios::binary | ios::out); //Заполенение файла 
	if (!file.is_open())
	{
		cout << "Ошибка!Нет доступа к файлу!\n";
	}
	else
	{
		for (int i = 0;i < (N * M);i++)
		{
			x =- 0.1 * (rand() % 100);//генерация рандомного значения из диапозона [-10;-0.1]
			file.write((char*)&x, sizeof(x));
		}
		file.close();
	}
	


	fstream full_file("D:\\PY\\Kursach.dat", ios::binary | ios::in);// заполенение массива данными 
	if (!full_file.is_open())
	{
		cout << "Ошибка!Нет доступа к файлу!\n";
	}
	else
	{
		for (int i = 0;i < N;i++)
		{
			for (int j = 0; j < M; j++)
			{
				full_file.read((char*)&p[i][j], sizeof(p[i][j]));
			}
		}
		full_file.close();
		system("cls");
		cout << "Массив успешно заполнен!\n";
	}

	g = true;
}

void function_sort(double** p, double** p_new, double* summa) // подсчет характеристик и перестоновка столбцов 
{
	system("cls");
	if (g)
	{
		int* array_index = new int[M / 2];
		double sum_num = 0;
		int z = 0;
		for (int j = 1; j < M; j++)// Подcчет характеристик и запись индексов 
		{
			for (int i = 0; i < N; i++)
			{
				if (p[i][j] < 0 && j % 2 != 0)
				{
					sum_num += p[i][j];
					array_index[z] = j;
				}
			}
			if (sum_num != 0)
			{
				summa[z] = sum_num;
				sum_num = 0;
				z++;
			}

		}

		for (int i = 0;i < M / 2;i++) // сортировка характеристик по убывванию (изменение индексов в соответствии)
		{
			for (int j = i;j < M / 2;j++)
			{
				if (summa[j] < summa[i])
				{
					swap(summa[j], summa[i]);
					swap(array_index[j], array_index[i]);
				}
			}

		}

		for (int i = 0; i < M / 4; i++) //перестановка массива индексов и массива характеристик
		{
			swap(array_index[i], array_index[(M / 2) - i - 1]);
			swap(summa[i], summa[(M / 2) - i - 1]);
		}

		z = 0;

		for (int j = 0; j < M;j++) //Перестановка столбцов 
		{
			for (int i = 0;i < N;i++)
			{
				if (j % 2 != 0)
				{
					p_new[i][j] = p[i][array_index[z]];
				}
				else
				{
					p_new[i][j] = p[i][j];
				}
			}
			if (j % 2 != 0)
			{
				z++;
			}
		}
		system("cls");
		cout << "Матрица отсортирована!\n";
		f = true;
	}
	else
	{
		cout << "Сортировка невозможна.Матрица не заполнена!\n\n";
	}
	
}

void print_array(double** p, double** p1, double* s)// Печать матриц 
{
	system("cls");
	string part;
	fstream file(part, ios::out);
	if (g&&f)
	{	
		while (true)	 // проверка пути к файлу на коректный ввод данных
		{
			cout << "Введите путь к файлу:\n";
			cin >> part;
			file.open(part);
			if (!file.is_open())
			{
				cout << "Файл недоступен!\n"; // !!!!!!!!!!!!!!
				cin.sync();
				cin.clear();
				continue;
			}
			else
			{
				break;
			}
		}
		system("cls");
		if (f)
		{
			file << "Первоначальная матрица:\n";
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					file << setw(5) << p[i][j] << " ";
				}
				file << endl;
			}
			file << "\n\nОтсортированная матрица:\n";
			for (int i = 0; i < N; i++)
			{
				for (int j = 0;j < M;j++)
				{
					file << setw(6) << p1[i][j];
				}
				file << endl ;
			}
			for (int i = 0;i < (M / 2);i++)
			{
				file << setw(12) << s[i];
			}
			file << "\nХарактеристики столбцов:\n\n";
			cout << "Файл успешно заполнен!\n";
		}
		else
		{
			cout << "\nМатрица не отсортирована!\n\n";
		}
	}
	else
	{
		cout <<"Печать невозможна.Матрица не отсортирована!\n\n";
	}
	f = false;
	file.close();
}






