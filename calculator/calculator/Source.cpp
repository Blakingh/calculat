#include <iostream>
#include <conio.h>
#include <windows.h>



using namespace std;





//Счёт целых элементов, разделённых пробелами
int count_whole_elements(char *str, const int size_str)
{
	int result = 0;
	for (int i = 0; i < size_str; i++)
	{
		if ((*(str + i) != ' ' && (*(str + i + 1) == ' ') || *(str + i + 1) == '\0'))
		{
			result++;
		}
	}
	return result;
}

//Считаем размер целого элемента
int size_element(char *str, const int size_str, int index)
{
	int result = 0;
	for (int i = index; *(str + i) != ' ' && *(str + i) != '\0'; i++)
	{
		result++;
	}
	return result;
}

//Распределение целых элементов по элементам двумерного массива
void distribution_elements(char **new_str, char *str, const int size_str)
{
	for (int i = 0,c = 0; i < size_str; i++)
	{
		if ((*(str + i) != ' ' && *(str + i - 1) == ' ') || (i == 0 && *(str + i) != ' '))
		{
			int sizeElements = size_element(str, size_str, i);
			*(new_str+c) = new char[sizeElements + 1];
			for (int j = i, v = 0; j < sizeElements + i; j++, v++)
			{
				new_str[c][v] = *(str + j);
			}
			new_str[c][sizeElements] = '\0';
			c++;
		}
	}
}

//Решаем выражение с помощью обратной польской записи
double obrat_polsca(char **new_str, const int size_new_str, char **arr_output)
{
	double result = 0;
	char operation = ' ';
	for (int i = 0, c = 0; c < size_new_str; i++)
	{
		if (c == size_new_str - 1)
		{
			*(arr_output + c) = new char[2];
			arr_output[c][0] = operation;
			arr_output[c][1] = '\0';
			c++;
		}
		else if ((int)new_str[i][0] >= 49 && (int)new_str[i][0] <= 57)
		{
			int size_output_element = strlen(*(new_str + i));
			*(arr_output + c) = new char[size_output_element + 1];
			for (int j = 0; j < size_output_element; j++)
			{
				arr_output[c][j] = new_str[i][j];
			}
			arr_output[c][size_output_element] = '\0';
			c++;
		}
		else if (new_str[i][0] == '+' || new_str[i][0] == '-')
		{
			if (operation == '*' || operation == '/' || operation == '+' || operation == '-')
			{
				*(arr_output + c) = new char[2];
				arr_output[c][0] = operation;
				arr_output[c][1] = '\0';
				c++;
				operation = new_str[i][0];
			}
			else
			{
				operation = new_str[i][0];
			}
		}
		else if (new_str[i][0] == '*' || new_str[i][0] == '/')
		{
			if (operation == '*' || operation == '/')
			{
				*(arr_output + c) = new char[2];
				arr_output[c][0] = operation;
				arr_output[c][1] = '\0';
				c++;
				operation = new_str[i][0];
			}
			else if (operation == '+' || operation == '-')
			{
				*(arr_output + c) = new char[2];
				arr_output[c][0] = new_str[i][0];
				arr_output[c][1] = '\0';
				c++;
				operation = new_str[i][0];
			}
			else
			{
				operation = new_str[i][0];
			}
		}
	}
















	return result;
}









void main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const int max_size_arr = 256;

	//СОЗДАНИЕ МАССИВА СИМВОЛОВ И ПОСЛЕ ВВОДА, СОЗДАНИЕ ОТДЕЛЬНО СТРОКИ
	cout << "Введите выражение: ";
	char arr[max_size_arr];
	gets_s(arr, max_size_arr);
	char *str = new char[strlen(arr)+1];
	strcpy_s(str, strlen(arr)+1, arr);
	//------------------------------------------------------------------

	char **new_str = new char*[count_whole_elements(str, strlen(str))];
	distribution_elements(new_str, str, strlen(str));
	for (int i = 0; i < count_whole_elements(str, strlen(str)); i++)
	{
		for (int j = 0; j < strlen(*(new_str+i)); j++)
		{
			cout << new_str[i][j];
		}
		cout << endl;
	}




	char **arr_output = new char*[count_whole_elements(str, strlen(str))];

	obrat_polsca(new_str, count_whole_elements(str, strlen(str)), arr_output);
	




	for (int i = 0; i < count_whole_elements(str, strlen(str)); i++)
	{
		for (int j = 0; j < strlen(*(arr_output)); j++)
		{
			cout << arr_output[i][j];
		}
		cout << " ";
	}







	for (int i = 0; i < count_whole_elements(str, strlen(str)); i++)
	{
		delete[] * (new_str + i);
	}
	delete[] str, new_str;
	_getch();
}
