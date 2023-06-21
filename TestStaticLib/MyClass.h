#pragma once
#include <windows.h>

class MyClass
{
public:
	MyClass()
		: a(0)
	{
		OutputDebugString(L"MyClass::MyClass\n");
	}
	~MyClass()
	{
		OutputDebugString(L"MyClass::~MyClass\n");
	}

public:
	int a;
};

