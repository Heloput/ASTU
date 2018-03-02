#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
using namespace std;
//класс точка
class Point {
private:
	int x, y;
public:
	void Init(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int get_X() {
		return x;
	}

	int get_Y() {
		return y;
	}

	void add_X(int x) {
		this->x = x;
	}

	void add_Y(int y) {
		this->y = y;
	}
	//совпадение точек
	bool overlap(int x, int y) {
		return (this->x == x && this->y == y) ? true : false;
	}

	void Display() {
		cout << "(" << x << ", " << y << ")\n";
	}
	//длина вектора
	int Length(Point A) {
		return (A.get_X() - x)*(A.get_X() - x) + (A.get_Y() - y)*(A.get_Y() - y);
	}
};
//площадь треугольника
int TriangleSquare(Point A, Point B, Point C) {
	return abs(((A.get_X() - C.get_X())*(B.get_Y() - C.get_Y()) - (A.get_Y() - C.get_Y())*(B.get_X() - C.get_X())));
}
//класс квадрат
class Square {
private:
	Point A, B, C, D;
	Point withA1, withA2, notWithA;
public:
	//площадь квадрата
	int Sq() {
		return A.Length(withA2);
	}
	//проверка является ли квадратом
	bool IsSquare(Point A, Point B, Point C, Point D) {
		int lenAB = A.Length(B);
		int lenAC = A.Length(C);
		int lenAD = A.Length(D);
		if (lenAB == lenAC) {
			withA1 = B;
			withA2 = C;
			notWithA = D;
		}
		else if (lenAB == lenAD) {
			withA1 = B;
			withA2 = D;
			notWithA = C;
		}
		else if (lenAC == lenAD) {
			withA1 = C;
			withA2 = D;
			notWithA = B;
		}
		else
			return false;

		if (A.Length(withA1) == A.Length(withA2) && withA1.Length(notWithA) == A.Length(withA1) && notWithA.Length(withA2) == A.Length(withA2)) {
			return (TriangleSquare(A, withA1, withA2) != 0 && A.Length(notWithA) == withA1.Length(withA2)) ? true : false;
		}
		return false;
	}
	//инициализация с проверкой
	bool Init(Point A, Point B, Point C, Point D) {
		if (IsSquare(A, B, C, D)) {
			this->A = A;
			this->B = B;
			this->C = C;
			this->D = D;
			return true;
		}
		return false;
	}
	//вывод точек
	void Display() {
		A.Display();
		withA1.Display();
		notWithA.Display();
		withA2.Display();
	}
	//ввод точек
	void Enter() {
		int x, y;
		cin >> x >> y;
		A.Init(x, y);
		cin >> x >> y;
		B.Init(x, y);
		cin >> x >> y;
		C.Init(x, y);
		cin >> x >> y;
		D.Init(x, y);
	}
	//проверка попадает ли точка в квадрат
	bool IntoSq(Point K) {
		int SumSq = TriangleSquare(A, withA1, K) + TriangleSquare(withA1, notWithA, K) + TriangleSquare(notWithA, withA2, K) + TriangleSquare(withA2, A, K);
		return Sq() == SumSq/2 ? true : false;
	}
	//попадают ли точки в квадрат
	bool AllPointsIn(vector<Point> Array, int N) {
		int c = 0;
		for (int i = 0; i < N; i++) {
			if (IntoSq(Array[i])) {
				;
				c++;
			}
		}
		return (c == N) ? true : false;
	}
};
//проверка точки на повтор в векторе
bool overlapPoints(vector<Point> &Array, int X, int Y, int &N) {
	for (int j = 0; j < N; j++) {
		if (Array[j].overlap(X, Y)) {
			N--;
			return true;
		}
	}
	return false;
}
//проверка является ли количество точек верным
bool CorrectSizeFile(string Name, int N, int &size) {
	ifstream in(Name + ".txt");
	int k = 0;
	int i;
	while (in >> i)
	{
		++k;
	};
	size = k / 2;
	return size < N;
	in.close();
}
//чтение из файла
bool scanFile(vector<Point> &Array, string Name, int &N) {
	ifstream in(Name + ".txt");
	if (!in)
	{
		cout << "Файл не существует!Проверьте лежит ли он в папке с программой!" << endl;
		return false;
	}
	if (in.peek() == EOF) {
		cout << "Файл пуст!Заполните файл точками!" << endl;
		return false;
	}
	int sizeTrue;
	int size = N;
	while (CorrectSizeFile(Name, N, sizeTrue)) {
		cout << "Вы ввели количество точек больше чем есть в файле!" << endl;
		cout << "Ввести количество точек заново или уменьшить количество точек до предела?" << endl;

		int i = 0;
		while (i != 1 && i != 2) {
			cout << "<1/2>? ";
			cin >> i;
		}

		if (i == 1) {
			cout << "Введите количество точек: ";
			cin >> N;
		}
		else {
			N = sizeTrue;
		}
	}

	int c = 0;
	int bufferX, bufferY;
	for (int i = 0; i < N; i++) {
		in >> bufferX;
		in >> bufferY;
		if (!overlapPoints(Array, bufferX, bufferY, i)) {
			Array[i].add_X(bufferX);
			Array[i].add_Y(bufferY);

		}
		else {
			N--;
			c++;
		}
	}
	if (N != size) {
		cout << "Одинаковых точек удалено: " << c << endl;
		cout << "Всего точек: " << N << endl;
	}
	in.close();
	return true;
}
//вывод точек
void Display(vector<Point> &Array, int N) {
	for (int i = 0; i < N; i++) {
		Array[i].Display();
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	int N;
	//ввод количества точек первого множества
	do {
		std::cout << "Введите количество точек первого множества:";
		cin >> N;
		if (N < 4) {
			cout << "Квадрат должен иметь как минимум 4 точки!" << endl;
		}
	} while (N < 4);
	std::vector<Point> FirstArray(N);
	if (!scanFile(FirstArray, "First", N)) {
		return 0;
	}
	else if (N < 4) {
		cout << "Недостаточное количество точек для создания квадрата!" << endl;
		return 0;
	}
	else {
		Display(FirstArray, N);
	}
	int SecondPoints;
	//ввод количества точек второго множества
	do {
		cout << "Введите количество точек второго множества:";
		cin >> SecondPoints;
		if (SecondPoints < 1) {
			cout << "Количество точек должно быть натуральным числом!" << endl;
		}
	} while (SecondPoints < 1);
	std::vector<Point> SecondArray(SecondPoints);
	if (!scanFile(SecondArray, "Second", SecondPoints)) {
		return 0;
	}
	Display(SecondArray, SecondPoints);
	Square check, right;
	float S = 0;
	float Smin = 999999;
	//главный цикл перебора 4х точек нахождения квадрата с мин площадью,где все точки входят в него
	for (int i = 0; i < N - 3; i++) {
		for (int j = i + 1; j < N - 2; j++) {
			for (int k = j + 1; k < N - 1; k++) {
				for (int t = k + 1; t < N; t++) {
					if (check.Init(FirstArray[i], FirstArray[j], FirstArray[k], FirstArray[t]))
					{
						S = check.Sq();
						if (check.AllPointsIn(SecondArray, SecondPoints)) {
							if (Smin > S) {
								Smin = S;
								right.Init(FirstArray[i], FirstArray[j], FirstArray[k], FirstArray[t]);
							}
						}
					}
				}
			}
		}
	}
	//вывод результатов
	if (S == 0) {
		cout << "Квадрата не существует!" << endl;
	}
	else if (999999 != Smin) {
		cout << "Точки второго множества входят в квадрат!" << endl;
		cout << "Минимальная площадь: " << Smin << endl;
		cout << "Координаты квадрата: " << endl;
		right.Display();
	}
	else {
		cout << "Точки второго множества не входят в квадрат!" << endl;
	}
	system("PAUSE");
	return 0;
}

