#include <iostream>
#include <vector>
#include <random>
#include <sstream>

using namespace std;

double random(int a, int b)
{
    static mt19937 gen(random_device{}());
    uniform_real_distribution<double> dis(a, b);
    return dis(gen);
}

class Matrix 
{
public:
    vector <vector<double>> data;
    int rows, cols;

    Matrix()
    {
        rows = 0;
        cols = 0;
    }

    Matrix(int rows, int cols) 
    {
        this->rows = rows;
        this->cols = cols;
        data.resize(rows, vector<double>(cols, 0));
    }

    Matrix(vector <vector<double>> data)
    {
        this->data = data;
        rows = data.size();
        cols = data[0].size();
    }

    vector<double> operator[](const int& b)
    {
        return this->data[b];
    }

    Matrix operator*(const Matrix& b)
    {
        Matrix result(this->rows, b.cols);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < b.cols; j++)
            {
                for (int k = 0; k < this->cols; k++)
                {
                    result.data[i][j] += this->data[i][k] * b.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator*(const double& b)
    {
        Matrix result(this->data);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                result.data[i][j] *= b;
            }
        }
        return result;
    }

    Matrix operator+(const Matrix& b) 
    {
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++) 
        {
            for (int j = 0; j < this->cols; j++) 
            {
                result.data[i][j] = this->data[i][j] + b.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& b) 
    {
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++) 
        {
            for (int j = 0; j < this->cols; j++) 
            {
                result.data[i][j] = this->data[i][j] - b.data[i][j];
            }
        }
        return result;
    }

    void print() 
    {
        for (int i = 0; i < this->rows; i++) 
        {
            for (int j = 0; j < this->cols; j++) 
            {
                cout << this->data[i][j] << " ";
            }
            cout << endl;
        }
    }

    Matrix t() 
    {
        Matrix result(this->cols, this->rows);
        for (int i = 0; i < this->rows; i++) 
        {
            for (int j = 0; j < this->cols; j++) 
            {
                result.data[j][i] = this->data[i][j];
            }
        }
        return result;
    }

    Matrix randomMatrix() 
    {
        for (int i = 0; i < this->rows; i++) 
        {
            for (int j = 0; j < this->cols; j++) 
            {
                this->data[i][j] = random(-1,1);
            }
        }
        return *this;
    }
};

class NeuralNetwork
{
private:
    Matrix inputs;
    Matrix outputs;
    Matrix weights_0_1;
    Matrix weights_1_2;
    Matrix weights_2_3;

public:
    NeuralNetwork()
    {
        inputs = Matrix({ {0, 0},
                          {0, 1},
                          {1, 0} });

        outputs = Matrix({ {0},
                           {1},
                           {1} });

        weights_0_1 = Matrix(2, 10).randomMatrix();
        weights_1_2 = Matrix(10, 10).randomMatrix();
        weights_2_3 = Matrix(10, 1).randomMatrix();
    }

    void train(int epochs)
    {

        for (int i = 0; i < epochs; i++)
        {
            Matrix layer_0 = inputs;
            Matrix layer_1 = layer_0 * weights_0_1;
            Matrix layer_2 = layer_1 * weights_1_2;
            Matrix layer_3 = layer_2 * weights_2_3;

            Matrix layer_3_error = outputs - layer_3;
            Matrix layer_2_error = layer_3_error * weights_2_3.t();
            Matrix layer_1_error = layer_2_error * weights_1_2.t();

            weights_2_3 = weights_2_3 + layer_2.t() * layer_3_error * 0.01;
            weights_1_2 = weights_1_2 + layer_1.t() * layer_2_error * 0.01;
            weights_0_1 = weights_0_1 + layer_0.t() * layer_1_error * 0.01;
        }

        cout << "Learning completed" << endl;
    }

    double predict(double x, double y) // predict() = x + y
    {
        Matrix starting_array({ {x, y} });
        Matrix layer_1 = starting_array * weights_0_1;
        Matrix layer_2 = layer_1 * weights_1_2;
        Matrix layer_3 = layer_2 * weights_2_3;
        return layer_3[0][0];
    }
};

void neuralNetworkTesting(NeuralNetwork nn)
{
    while (true)
    {
        double num1, num2;
        string input;
        cout << "Enter the first number: ";
        getline(cin, input);
        stringstream(input) >> num1;
        cout << "Enter the second number: ";
        getline(cin, input);
        stringstream(input) >> num2;
        vector <double> numbers;
        numbers.push_back(num1);
        numbers.push_back(num2);
        cout << numbers[0] << " + " << numbers[1] << " = " << nn.predict(numbers[0], numbers[1]) << endl;
    }
}

int main() 
{
    NeuralNetwork perceptron;
    perceptron.train(2000);
    neuralNetworkTesting(perceptron);
}