// #include "../../src/utils/uuid.h"
#include <iostream>
#include <array>
#include <list>
#include <vector>
#include <unordered_map>

struct Object
{
    Object(int a, int b): a {a}, b {b} {}
    int a, b;
};

int main() 
{
    std::vector<Object> v;
    v.emplace_back(3, 4);
    std::cout << v[0].a << " " << v[0].b << std::endl;
}