// Нелдер-мид.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Функция, которую будем минимизировать
double f(vector<double> x) {
    double result = (x[0]*x[0])+(x[0]*x[1])+(x[1]*x[1])-(6*x[0])-(9*x[1]);
    return result;
}

// Реализация метода Нелдера-Мида
double nelder_mead(vector<double> start, double alpha, double beta, double gamma, double epsilon) {
    int n = start.size();
    vector<vector<double>> simplex(n + 1, vector<double>(n));
    for (int i = 0; i < n + 1; i++) {
        if (i == 0) {
            simplex[i] = start;
        }
        else {
            for (int j = 0; j < n; j++) {
                if (j == i - 1) {
                    simplex[i][j] = start[j] + epsilon;
                }
                else {
                    simplex[i][j] = start[j];
                }
            }
        }
    }

    while (true) {
        int worst = 0, second_worst = 0, best = 0;
        for (int i = 0; i < n + 1; i++) {
            if (f(simplex[i]) > f(simplex[worst])) {
                second_worst = worst;
                worst = i;
            }
            else if (f(simplex[i]) > f(simplex[second_worst]) && i != worst) {
                second_worst = i;
            }
            if (f(simplex[i]) < f(simplex[best])) {
                best = i;
            }
        }

        vector<double> centroid(n);
        for (int i = 0; i < n + 1; i++) {
            if (i != worst) {
                for (int j = 0; j < n; j++) {
                    centroid[j] += simplex[i][j];
                }
            }
        }
        for (int i = 0; i < n; i++) {
            centroid[i] /= n;
        }

        vector<double> reflection(n);
        for (int i = 0; i < n; i++) {
            reflection[i] = centroid[i] + alpha * (centroid[i] - simplex[worst][i]);
        }
        if (f(reflection) < f(simplex[second_worst]) && f(reflection) >= f(simplex[best])) {
            simplex[worst] = reflection;
        }
        else if (f(reflection) < f(simplex[best])) {
            vector<double> expansion(n);
            for (int i = 0; i < n; i++) {
                expansion[i] = centroid[i] + gamma * (reflection[i] - centroid[i]);
            }
            if (f(expansion) < f(reflection)) {
                simplex[worst] = expansion;
            }
            else {
                simplex[worst] = reflection;
            }
        }
        else {
            vector<double> contraction(n);
            for (int i = 0; i < n; i++) {
                contraction[i] = centroid[i] + beta * (simplex[worst][i] - centroid[i]);
            }
            if (f(contraction) < f(simplex[worst])) {
                simplex[worst] = contraction;
            }
            else {
                for (int i = 0; i < n + 1; i++) {
                    if (i != best) {
                        for (int j = 0; j < n; j++) {
                            simplex[i][j] = simplex[best][j] + 0.5 * (simplex[i][j] - simplex[best][j]);
                        }
                    }
                }
            }
            double diff = 0;
            for (int i = 0; i < n; i++) {
                diff += pow(simplex[best][i] - simplex[second_worst][i], 2);
            }
            diff = sqrt(diff);
            if (diff < epsilon) {
                return f(simplex[best]);
            }
        }
    }
}
    int main() {
        vector<double> start = { 0, 0 };
        double alpha = 1, beta = 0.5, gamma = 2, epsilon = 0.0001;
        double result = nelder_mead(start, alpha, beta, gamma, epsilon);
        cout << "Minimum value found: " << result << endl;
        return 0;
    }

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
