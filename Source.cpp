#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <windows.h>
#include <ctime>
using namespace std;
//����� �����
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
	bool overlap(int x, int y) {
		return (this->x == x && this->y == y) ? true : false;
	}
	void Display() {
		cout << "(" << x << ", " << y << ")\n";
	}
	float Length(Point A) {
		return sqrt((A.get_X() - x)*(A.get_X() - x) + (A.get_Y() - y)*(A.get_Y() - y));
	}
};
//������� ������������
float TriangleSquare(Point A, Point B, Point C) {
	return fabs(0.5*((A.get_X() - C.get_X())*(B.get_Y() - C.get_Y()) - (A.get_Y() - C.get_Y())*(B.get_X() - C.get_X())));
}
//����� �������
class Square {
private:
	Point A, B, C, D;
public:

    Point get_A() {
		return this->A;
	}
    Point get_B() {
		return this->B;
	}
	Point get_C() {
		return this->C;
	}
	Point get_D() {
		return this->D;
	}

	float Sq() {
		return A.Length(B)*A.Length(B);
	}
	bool Init(Point A, Point B, Point C, Point D) {
		Point withA1, withA2, notWithA;
		float lenAB = A.Length(B);
		float lenAC = A.Length(C);
		float lenAD = A.Length(D);
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
			this->A = A;
			this->B = withA1;
			this->C = notWithA;
			this->D = withA2;
			return (A.Length(notWithA) == withA1.Length(withA2) && TriangleSquare(A, withA1, withA2)*2 != 0)? true : false;
		}
		return false;
	}

	void Display() {
		A.Display();
		B.Display();
		C.Display();
		D.Display();
	}

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
};
    //�������� �������� �� ����� � �������
	bool IntoSq(Square sq, Point K) {
		float SumSq = TriangleSquare(sq.get_A(), sq.get_B(), K) + TriangleSquare(sq.get_B(), sq.get_C(), K) + TriangleSquare(sq.get_C(), sq.get_D(), K) + TriangleSquare(sq.get_D(), sq.get_A(), K);
		return (fabs(sq.Sq() - SumSq) < 0.0000001) ? true : false;
	}
//�������� �� ����� � �������
	bool AllPointsIn(Square sq, vector<Point> Array, int N) {
		int c = 0;
		for (int i = 0; i < N; i++) {
			if (IntoSq(sq,Array[i])) {
				;
				c++;
			}
		}
		return (c == N) ? true : false;
	}

//�������� ����� �� ������ � �������
bool overlapPoints(vector<Point> &Array,int X,int Y, int &N) {
	for (int j = 0; j < N; j++) {
			if (Array[j].overlap(X,Y)){
				N--;
				return true;
			}
		}
	return false;
}

void FillFile(char Name[], int N){
    ofstream on(Name);
    for(int i = 0; i < N; i++){
        on << -100 + rand()%200;
        on << " ";
        on << -100 + rand()%200;
        on << " ";
    }
    on.close();
}

//�������� �������� �� ���������� ����� ������
bool CorrectSizeFile(char Name[], int N,int &size) {
	ifstream in(Name);
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
//������ �� �����
bool scanFile(vector<Point> &Array,char Name[],int &N) {
	ifstream in(Name);
	if (!in)
	{
		cout << "���� �� ����������!��������� ����� �� �� � ����� � ����������!" << endl;
		return false;
	}
	if (in.peek() == EOF) {
		cout << "���� ����!��������� ���� �������!" << endl;
		return false;
	}
	int sizeTrue;
	int size = N;
	while (CorrectSizeFile(Name, N,sizeTrue)) {
		cout << "�� ����� ���������� ����� ������ ��� ���� � �����!" << endl;
		cout << "������ ���������� ����� ������ ��� ��������� ���������� ����� �� �������?" << endl;

		int i = 0;
		while (i != 1 && i != 2) {
			cout << "<1/2>? ";
			cin >> i;
		}

		if (i == 1) {
			cout << "������� ���������� �����: ";
			cin >> N;
		}
		else {
			N = sizeTrue;
		}
	}

	int c = 0;
	int bufferX,bufferY;
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
		cout << "���������� ����� �������: " << c << endl;
		cout << "����� �����: " << N << endl;
	}
	in.close();
	return true;
}
//����� �����
void Display(vector<Point> &Array,int N) {
	for (int i = 0; i < N; i++) {
		Array[i].Display();
	}
}

int main() {
    srand(time(0));
  //  FillFile("First.txt",1000);
  //  FillFile("Second.txt",1000);
	setlocale(LC_ALL, "RUS");
	cout << "����� ������ ����������� �.�. �����11.\n";
	cout << "���� ��������� ����� �� ���������.������� ������ ��������� ����� ������� ��������� ���,\n����� ������� � ��������� � ���� ������ �������� ��� �����\n������� ��������� � ���� ���. �������.\n";
	cout << "N <= 100! ��� ����� � ������� ������ ������ � ����� � ����������!\n";

	while(true){
	int N;
	do {
		std::cout << "������� ���������� ����� ������� ���������:";
		cin >> N;
		if (N < 4) {
			cout << "������� ������ ����� ��� ������� 4 �����!" << endl;
		}
	} while (N < 4);
	std::vector<Point> FirstArray(N);
	if(!scanFile(FirstArray, "First.txt", N)) {
		return 0;
	}
	Display(FirstArray, N);
	int SecondPoints;
	do {
		cout << "������� ���������� ����� ������� ���������:";
		cin >> SecondPoints;
		if (SecondPoints < 1) {
			cout << "���������� ����� ������ ���� ����������� ������!" << endl;
		}
	} while (SecondPoints < 1);
	std::vector<Point> SecondArray(SecondPoints);
	if(!scanFile(SecondArray, "Second.txt", SecondPoints) || N < 4) {
		return 0;
	}
	Display(SecondArray, SecondPoints);
	Square check, right;
	float S = 0;
	float Smin = 999999;
	int t = 0;
	float t1 = clock();
	for (int i = 0; i < N - 3; i++) {
		for (int j = i + 1; j < N - 2; j++) {
			for (int k = j + 1; k < N - 1; k++) {
				for (int t = k + 1; t < N; t++) {
					if (check.Init(FirstArray[i], FirstArray[j], FirstArray[k], FirstArray[t]))
					{
						S = check.Sq();
						if (AllPointsIn(check, SecondArray, SecondPoints)) {
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
	float t2 = clock();
	if (S == 0) {
		cout << "�������� �� ����������!" << endl;
	}
	else if ( 999999 != Smin) {
		cout << "����� ������� ��������� ������ � �������!" << endl;
		cout << "����������� �������: " << Smin << endl;
		cout << "���������� ��������: " << endl;
		right.Display();
	}
	else {
		cout << "����� ������� ��������� �� ������ � �������!" << endl;
	}
	cout << "Time: " << (t2-t1)/1000 << endl;
}
	system("PAUSE");
	return 0;
}
