#pragma once
#include <concepts>

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

template<typename T>
	requires arithmetic<T>
struct Vec4
{
public:
	T x;
	T y;
	T z;
	T w;
};
