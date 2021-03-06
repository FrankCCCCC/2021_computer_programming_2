#include <iostream>
using namespace std;

class Matrix {
 private:
  int size_row, size_col;
  int **arr;

 public:
  Matrix(int row, int col) {
    size_row = row;
    size_col = col;
    arr = new int *[row];
    for (int i = 0; i < row; i++) {
      arr[i] = new int[col];
    }
    init_Matrix();
  };
  void init_Matrix() {
    for (int i = 0; i < size_row; i++) {
      for (int j = 0; j < size_col; j++) {
        if (i == j)
          arr[i][j] = 1;
        else
          arr[i][j] = 0;
      }
    }
  }
  int *get_col(int col_id) const {
    int *tmparr = new int[size_row];
    for (int i = 0; i < size_row; i++) {
      tmparr[i] = arr[i][col_id];
    }
    return tmparr;
  }
  int *get_row(int row_id) const {
    int *tmparr = new int[size_col];
    for (int i = 0; i < size_col; i++) {
      tmparr[i] = arr[row_id][i];
    }
    return tmparr;
  }
  int get_value(int i, int j) const { return arr[i][j]; }
  void set_value(int i, int j, int val) { arr[i][j] = val; }
  const int get_size_row() const { return size_row; }
  const int get_size_col() const { return size_col; }
  Matrix operator*(const Matrix &a) const;  //[TODO]
  Matrix operator=(const Matrix &a);        //[TODO]
};

Matrix Matrix::operator*(const Matrix &a) const
{
    Matrix m(size_row, a.size_col);

    for (int i=0; i<size_row; i++) {
        for (int j=0; j<a.size_col; j++) {
            m.arr[i][j] = 0;
            for (int k=0; k<size_col; k++) {
                m.arr[i][j] = m.arr[i][j] + (arr[i][k] * a.arr[k][j]);
            }
        }
    }
    return m;
}

Matrix Matrix::operator=(const Matrix &a)
{
    size_row = a.size_row;
    size_col = a.size_col;
    for (int i=0; i<a.size_row; i++) {
        for (int j=0; j<a.size_col; j++) {
            arr[i][j] = a.arr[i][j];
        }
    }

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m);

class MatrixChain {
 private:
  int num;

 public:
  Matrix *arr[100];

  MatrixChain(int matrixNum) { num = matrixNum; }
  Matrix calc(int l, int r) const;
  Matrix *setMatrix(int x, int row, int col) {
    arr[x] = new Matrix(row, col);
    return arr[x];
  }
};

Matrix MatrixChain::calc(int l, int r) const
{
    Matrix m = *arr[l];

    for (int i=l+1; i<r; i++) {
        m = m * (*arr[i]);
    }
    return m;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
  int r = m.get_size_row();
  int c = m.get_size_col();
  for (int i = 0; i < r; i++) {
    int* tmp = m.get_row(i);
    for (int j = 0; j < c; j++) {
      os << tmp[j] << " ";
    }
    os << "\n";
  }
  return os;
}

int main() {
  int Mat_num, row, col, val;
  cin >> Mat_num;
  MatrixChain MCChen(Mat_num);
  for (int i = 0; i < Mat_num; i++) {
    cin >> row >> col;
    Matrix* now = MCChen.setMatrix(i, row, col);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        cin >> val;
        now->set_value(i, j, val);
      }
    }
  }
  int l, r;
  cin >> l >> r;
  Matrix m(MCChen.arr[l]->get_size_row(), MCChen.arr[r - 1]->get_size_col());
  m = MCChen.calc(l, r);
  cout << m;
}
