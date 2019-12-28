//
//  Curves.cpp
//
//
//  Copyright © 2019 Alexey Khomenko. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>


class Curve {
 public:
    double a;
    double b;

    explicit Curve(double _a = 0, double _b = 0):a(_a), b(_b) {
    }
    virtual ~Curve() {
    }
    virtual double Area() const = 0;
};

class Ellipse : public Curve {
 public:
    double a;
    double b;

    explicit Ellipse(double _a = 0, double _b = 0):Curve(_a, _b) {
        a = _a;
        b = _b;
    }
    double Area() const {
        return M_PI*a*b;
    }
};


class Circle: public Curve {
 public:
    double r;

    explicit Circle(double _r = 0):Curve(_r, _r) {
        r = _r;
    }
    double Area() const {
        return M_PI*r*r;
    }
};


int main(int argc, const char * argv[]) {
    if ( argc == 1 ) {
        std::cout << "Run with integer parameter:  " <<  std::endl;
        std::cout << "Examples:  Curves.cpp 1000 " <<  std::endl;
        std::cout << "           Curves.cpp 150" <<  std::endl;
        std::cout << "           Curves.cpp 100 " <<  std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::vector<Curve *> vec;
    double SummArea = 0.0;
    int CountOfInstance = atoi(argv[1]);
    int MY_MAX = CountOfInstance/2;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> d(0, MY_MAX);

    for (int n = 0; n < CountOfInstance; ++n) {
        if (static_cast<int>(d(gen))%2 == 0) {
            vec.push_back(new Ellipse(d(gen), d(gen)));

        } else {
            vec.push_back(new Circle(d(gen)));
        }
    }

    std::sort(vec.begin(), vec.end(), [ ](const Curve* lhs, const Curve* rhs) {
        return lhs->Area() < rhs->Area();
    });

    std::cout << "Sorted Circles:  " << std::endl;
    for (int i=0; i < CountOfInstance; ++i) {
       if (dynamic_cast<Circle*>(vec[i])) {
            std::cout << vec[i]->Area() << std::endl;
            SummArea+=vec[i]->Area();
        }
    }

    std::cout << "Total Area of Circles:  " << SummArea << std::endl;

    for (auto p : vec) {
        delete p;
    }
    vec.clear();

    return 0;
}
