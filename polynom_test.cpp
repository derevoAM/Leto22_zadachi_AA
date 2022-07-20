//
// Created by derev on 20.07.2022.
//

#include "polynom.h"

int main()
{
    Sparse_polynom<double> pol1 = {{1, 2}, {4, 3}, {6, 7}};
    Sparse_polynom<double> pol2 = {{4, -3}}; //{{0, 1}, {4, 7}, {8, 2}, {100, 4}};
    Sparse_polynom<double> pol3 = {{1, 2}, {3, 5}, {6, 2}};
    Sparse_polynom<double> pol4;
    Sparse_polynom<double> pol5 = pol3 + pol1;
    pol4 = pol1 + pol2;
    std::cout << pol4 << "\n";
    pol4 -= pol3;
    std::cout << pol4 << "\n";
    pol4 *= pol1;
    std::cout << pol4 << "\n";
    pol5 = pol4 / pol3;
    std::cout << pol5 << "\n";
    std::cout << pol4 << "\n";
    std::cout << "integral and derivative" << "\n";
    Sparse_polynom<double> integ = pol4.integral();
    Sparse_polynom<double> diff = pol4.derivative();
    std::cout << integ << "\n";
    std::cout << diff << "\n";
}
