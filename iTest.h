#ifndef ITEST_H
#define ITEST_H

#include <string>
#include <iostream>

class iTest {
	public:
		virtual bool test() = 0;
		virtual ~iTest() {};
};

class Pos_Num : public iTest {
	private:
		int num;

	public:
		Pos_Num(int n) : num(n) {}
		bool test() override {
			return num > 0;
		}
};

class Neg_Num : public iTest {
private:
	int num;

public:
	Neg_Num(int n) : num(n) {}

	bool test() override { 
		return num < 0;
	}
};

class Empty_Str : public iTest {
	private:
		std::string str;
	public:
		Empty_Str(const std::string& s) : str(s) {}
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

//Error: Unnecessary parameter in test()
class E_Pos_Num : public iTest {
	private:
		int num;

	public:
		E_Pos_Num(int n) : num(n) {}
		bool test(int n) {
			return num > 0;
		}
};

//Error: Adding cost
class E_Neg_Num : public iTest {
	private:
		int num;

	public:
		E_Neg_Num(int n) : num(n) {}

		bool test() override {
			return num < 0;
		}
};

//Error: Typo
class E_Empty_Str : public iTest {
	private:
		std::string str;
	public:
		E_Empty_Str(const std::string& s) : str(s) {}
		bool test() override {
			return !str.empty();
		}
};

//Error: Wrong return type
class E_Equal_Num : public iTest {
	private:
		int a, b;
	public:
		E_Equal_Num(int x, int y) : a(x), b(y) {}
		bool test() override {
			return a == b;
		}
};
#endif