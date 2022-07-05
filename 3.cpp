#include <array>
#include <vector>
#include <initializer_list>
#include <cmath>
#include <iostream>

template <typename Type, int N>
class Vector {
    static_assert(N >= 0);
    std::array<Type, N> data_;

public:
    constexpr Vector()
    {
        for(int i = 0; i < N; i ++) data_[i] = 0;
    }
    constexpr Vector(const Vector<Type, N>& other)
    {
        for(int i = 0; i < N; i ++) data_[i] = other.data_[i];
    }
    constexpr Vector(std::initializer_list<Type> in_list)
    {
        int i = 0;
        for(auto it: in_list)
        {
            data_[i] = it;
            i ++;
        }
    }

    const Type& operator[](unsigned int i) const
    {
        return data_[i];
    }

    Type& operator[](unsigned int i)
    {
        return data_[i];
    }

    Type norm() const
    {
        Type norm = 0;
        for(int i = 0; i < N; i ++) norm += data_[i] * data_[i];
        return std::sqrt(norm);
    }

    Vector<Type, N> operator*=(Type num)
    {
        for(int i = 0; i < N; i ++) data_[i] *= num;
        return *this;
    }

    Vector<Type, N> operator/=(Type num)
    {
        for(int i = 0; i < N; i ++) data_[i] /= num;
        return *this;
    }

    Vector<Type, N> operator+=(const Vector<Type, N>& other)
    {
        for(int i = 0; i < N; i ++) data_[i] += other.data_[i];
        return *this;
    }

    Vector<Type, N> operator-=(const Vector<Type, N>& other)
    {
        for(int i = 0; i < N; i ++) data_[i] -= other.data_[i];
        return *this;
    }

    Vector<Type, N> operator*(Type num) const
    {
        Vector<Type, N> result;
        for(int i = 0; i < N; i ++) result.data_[i] = data_[i] * num;
        return result;
    }

    Vector<Type, N> operator/(Type num) const
    {
        Vector<Type, N> result;
        for(int i = 0; i < N; i ++) result.data_[i] = data_[i] / num;
        return result;
    }
    Vector<Type, N> operator+(const Vector<Type, N>& other) const
    {
        Vector<Type, N> result;
        for(int i = 0; i < N; i ++) result.data_[i] = data_[i] + other.data_[i];
        return result;
    }

    Vector<Type, N> operator-(const Vector<Type, N>& other) const
    {
        Vector<Type, N> result;
        for(int i = 0; i < N; i ++) result.data_[i] = data_[i] - other.data_[i];
        return result;
    }

    friend Vector<Type, N> operator*(Type num, const Vector<Type, N>& vec)
    {
        Vector<Type, N> result;
        for(int i = 0; i < N; i ++) result.data_[i] = vec.data_[i] * num;
        return result;
    }

    friend std::ostream& operator<<(std::ostream& out,  const Vector<Type, N>& vec)
    {
        for(int i = 0; i < N; i ++) out << vec.data_[i] << " ";
        return out;
    }
};

constexpr int Dynamic = -1;

template <typename Type>
class Vector<Type, Dynamic> {
    std::vector<Type> data_;
    int size_;

public:
    constexpr Vector()
    {
        size_ = 0;
    }
    constexpr Vector(const Vector<Type, Dynamic>& other)
    {
        for(int i = 0; i < other.size_; i ++) data_.push_back(other.data_[i]);
        size_ = other.size_;
    }
    constexpr Vector(std::initializer_list<Type> in_list)
    {
        for(auto it: in_list) data_.push_back(it);
        size_ = in_list.size();
    }

    const Type& operator[](unsigned int i) const
    {
        return data_[i];
    }

    Type& operator[](unsigned int i)
    {
        if(i < size_) return data_[i];
        else
        {
            while(size_ <= i)
            {
                data_.push_back(0);
                size_ ++;
            }
            return data_[i];
        }

    }

    Type norm() const
    {
        Type norm = 0;
        for(int i = 0; i < size_; i ++) norm += data_[i] * data_[i];
        return std::sqrt(norm);
    }

    Vector<Type, Dynamic> operator*=(Type num)
    {
        for(int i = 0; i < size_; i ++) data_[i] *= num;
        return *this;
    }

    Vector<Type, Dynamic> operator/=(Type num)
    {
        for(int i = 0; i < size_; i ++) data_[i] /= num;
        return *this;
    }

    Vector<Type, Dynamic> operator+=(const Vector<Type, Dynamic>& other)
    {
        for(int i = 0; i < size_; i ++) data_[i] += other.data_[i];
        return *this;
    }

    Vector<Type, Dynamic> operator-=(const Vector<Type, Dynamic>& other)
    {
        for(int i = 0; i < size_; i ++) data_[i] -= other.data_[i];
        return *this;
    }

    Vector<Type, Dynamic> operator*(Type num) const
    {
        Vector<Type, Dynamic> result;
        for(int i = 0; i < size_; i ++) result.data_.push_back(data_[i] * num);
        result.size_ = size_;
        return result;
    }

    Vector<Type, Dynamic> operator/(Type num) const
    {
        Vector<Type, Dynamic> result;
        for(int i = 0; i < size_; i ++) result.data_.push_back(data_[i] / num);
        result.size_ = size_;
        return result;
    }

    Vector<Type, Dynamic> operator+(const Vector<Type, Dynamic>& other) const
    {
        Vector<Type, Dynamic> result;
        for(int i = 0; i < size_; i ++) result.data_.push_back(data_[i] + other.data_[i]);
        result.size_ = size_;
        return result;
    }

    Vector<Type, Dynamic> operator-(const Vector<Type, Dynamic>& other) const
    {
        Vector<Type, Dynamic> result;
        for(int i = 0; i < size_; i ++) result.data_.push_back(data_[i] - other.data_[i]);
        result.size_ = size_;
        return result;
    }

    friend Vector<Type, Dynamic> operator*(Type num, const Vector<Type, Dynamic>& vec)
    {
        Vector<Type, Dynamic> result;
        for(int i = 0; i < vec.size_; i ++) result.data_.push_back(vec.data_[i] * num);
        result.size_ = vec.size_;
        return result;
    }

    friend std::ostream& operator<<(std::ostream& out,  const Vector<Type, Dynamic>& vec)
    {
        for(int i = 0; i < vec.size_; i ++) out << vec.data_[i] << " ";
        return out;
    }
};

int main()
{
    // static vector
/*
    Vector<int, 5> vec1; // default initialization
    for(int i = 0; i < 5; i ++) vec1[i] = i;
    std::cout << vec1 << "\n";

    Vector<int, 5> vec2 = vec1; // initialization via equalization
    std::cout << vec2 << "\n";

    Vector<int, 5> vec3 = {5, 2, 4, 8, 6}; // initialization via initializer list
    std::cout << vec3 << "\n";

    vec1 /= 2;
    std::cout << "/=: " << vec1  << "\n";

    vec2 *= 2;
    std::cout << "*=: " << vec2 << "\n";

    vec2 = vec3 + vec1;
    std::cout << "+: " << vec2 << "\n";

    vec3 = vec1 * 2;
    vec3 = 2 * vec1;
    std::cout << "*: " << vec3 << "\n";

    vec1[0] = vec2[1];
    std::cout << "[]: " << vec1 << "\n";

    std::cout << "norm: " << vec1.norm() << "\n";
*/


    // dynamic vector
    Vector<int, -1> vec1; // default initialization
    for(int i = 0; i < 5; i ++) vec1[i] = i;
    std::cout << vec1 << "\n";

    Vector<int, -1> vec2 = vec1; // initialization via equalization
    std::cout << vec2 << "\n";

    Vector<int, -1> vec3 = {5, 2, 4, 8, 6}; // initialization via initializer list
    std::cout << vec3 << "\n";

    vec1 /= 2;
    std::cout << "/=: " << vec1  << "\n";

    vec2 *= 2;
    std::cout << "*=: " << vec2 << "\n";

    vec3 = vec1 + vec2;
    std::cout << "+: " << vec3 << "\n";

    vec3 = vec1 * 2;
    vec3 = vec1 * 2;
    std::cout << "*: " << vec3 << "\n";

    vec1[0] = vec2[1];
    std::cout << "[]: " << vec1 << "\n";

    std::cout << "norm: " << vec1.norm() << "\n";

    vec3[7] = 19;
    std::cout << vec3 << "\n";

}