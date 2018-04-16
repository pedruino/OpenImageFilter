#pragma once
template<typename T>
T clamp(T Value, T Min, T Max)
{
	return (Value < Min) ? Min : (Value > Max) ? Max : Value;
}

template<class T>
const T& constrain(const T& x, const T& a, const T& b) {
	if (x < a) {
		return a;
	}
	else if (b < x) {
		return b;
	}
	else
		return x;
}