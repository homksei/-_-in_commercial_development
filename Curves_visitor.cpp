//
//  Curves_v3.cpp
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
    virtual void accept(class Visitor &v) = 0;
    virtual ~Curve() {}
};

class Ellipse : public Curve {
public:
    double a;
    double b;
    void accept(Visitor &v);
    Ellipse(double _a = 0, double _b = 0) {
        a = _a;
        b = _b;
    }
    ~Ellipse() {}
};


class Circle: public Curve {
public:
    double r;
    void accept(Visitor &v);
    Circle(double _r = 0) {
        r = _r;
    }
    ~Circle() {}
};


class Visitor
{
public:
    virtual void visit(Ellipse *e) = 0;
    virtual void visit(Circle *e) = 0;
    virtual ~Visitor() {}
};

void Ellipse::accept(Visitor &v)
{
    v.visit(this);
}

void Circle::accept(Visitor &v)
{
    v.visit(this);
}

class VisitorArea: public Visitor
{
public:
    double area = 0;
    
    void visit(Ellipse *e)
    {
        area = M_PI * e->a * e->b;
    }
    void visit(Circle *e)
    {
        area = M_PI * e->r * e->r;
    }
    
};

class ThisIsVisitor: public Visitor
{
public:
    std::string instanceType = "";
    
    void visit(Ellipse *e)
    {
        instanceType="Ellipse";
    }
    void visit(Circle *e)
    {
        instanceType="Circle";
    }
    
};



int main(int argc, const char * argv[]) {
    if ( argc == 1 ) {
        std::cout << "Run with integer parameter:  " <<  std::endl;
        std::cout << "Examples:  Curves_v3.cpp 1000 " <<  std::endl;
        std::cout << "           Curves_v3.cpp 150" <<  std::endl;
        std::cout << "           Curves_v3.cpp 100 " <<  std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    double ammountOfArea = 0.0;
    int countOfInstance = atoi(argv[1]);
    int MY_MAX = countOfInstance/2;
    
    ThisIsVisitor curveInstancePrinter;
    VisitorArea curveAreaCalc;
    std::vector<Curve *> vec;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> d(0, MY_MAX);
    
    for (int n = 0; n < countOfInstance; ++n) {
        if (static_cast<int>(d(gen))%2 == 0) {
            vec.push_back(new Ellipse(d(gen), d(gen)));
        } else {
            vec.push_back(new Circle(d(gen)));
        }
    }
    
    std::sort(vec.begin(), vec.end(), [&curveAreaCalc](Curve* lhs, Curve* rhs) {
        double lhsArea = 0.0;
        double rhsArea = 0.0;
        lhs->accept(curveAreaCalc);
        lhsArea = curveAreaCalc.area;
        rhs->accept(curveAreaCalc);
        rhsArea = curveAreaCalc.area;
        return lhsArea < rhsArea;
    });
    
    std::cout << "Sorted Curves:  " << std::endl;
    for (auto* shape : vec) {
        shape->accept(curveInstancePrinter);
        if ( "Circle" == curveInstancePrinter.instanceType) {
            shape->accept(curveAreaCalc);
            std::cout << curveAreaCalc.area << std::endl;
            ammountOfArea+=curveAreaCalc.area;
        }
    }
    
    std::cout << "Total Area of Circles:  " << ammountOfArea << std::endl;
    
    for (auto p : vec) {
        delete p;
    }
    
    vec.clear();
    
    return 0;
}

