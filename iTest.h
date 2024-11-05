#ifndef ITEST_H
#define ITEST_H

#include <string>
#include <iostream>

class iTest {
public:
	virtual bool test() = 0;
	virtual ~iTest() {}
};

class PositiveNumber : public iTest {
private:
	int num;

public:
	PositiveNumber(int n) : num(n) {}
	bool test() override {
		return num > 0;
	}
};

class Empty_String : public iTest {
private:
	std::string str;
public:
	Empty_String(const std::string& s) : str(s) {}
	bool test() override {
		return !str.empty();
	}
};

class Equal_Num : public iTest {
private:
	int a, b;
public:
	Equal_Num(int x, int y) : a(x), b(y) {}
	bool test() override {
		return a == b;
	}
};
#endif