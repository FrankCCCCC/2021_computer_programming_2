#include <string>
#include <iostream>

class Vector {
private:
    int v_size;
    int *v;
public:
    Vector() {
        v_size = 0;
        v = NULL;
    }
    Vector(int n) {
        v_size = n;
        v = new int[n];
    }
    ~Vector() {
        delete [] v;
    }
    void read() {
        for (int i = 0; i < v_size; i++) {
            std::cin >> v[i];
        }
    }
    void set(int index, int value) {
        if (index < 0 || index >= v_size) {
            std::cout << "OUT OF BOUND\n";
            return;
        }
        else v[index] = value;
    }
    const int size() const {
        return v_size;
    };

    // return the value of v[index]
    const int operator[](int index) const;

    // Dot product
    int operator*(const Vector& a);
};

const int Vector::operator[](int index) const
{
    return v[index];
}

int Vector::operator*(const Vector& a)
{
    int ans=0;
    for (int i=0; i<v_size; i++){
        ans += v[i] * a.v[i];
    }
    return ans;
}

// Print the Vector
std::ostream& operator<<(std::ostream& os, const Vector& v);

int main() {
    int m, size;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        std::string op;
        std::cin >> op >> size;
        Vector A(size);
        Vector B(size);
        A.read();
        B.read();
        if (op == "DOT")
            std::cout << A*B  << ' ' << '\n';
    }
    return 0;
}