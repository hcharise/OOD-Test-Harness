#pragma once

// tested code elements

class iTest {
public:
	virtual bool test() = 0;
	virtual ~iTest() {};
};

// Checks if number is positive
class Pos_Num : public iTest {
private:
	int num;
public:
	Pos_Num(int n) : num(n) {}
	bool test() override {
		return num > 0;
	}
};

// Checks if parameters are equal numbers
class Equal_Num : public iTest {
private:
	int a, b;
public:
	Equal_Num(int x, int y) : a(x), b(y) {}
	bool test() override {
		return a == b;
	}
};

// Divides 10 by parameter; exception if 0 is parameter
class E_Divide_Ten : public iTest {
private:
	int a;
public:
	E_Divide_Ten(int x) : a(x) {}
	bool test() override {
		if (a == 0)
		{
			throw std::invalid_argument("Cannot divide by 0.");
		}
		return (10 / a);
	}
};