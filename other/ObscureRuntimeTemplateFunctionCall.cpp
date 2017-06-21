#include <iostream>
#include <memory>
#include <map>
#include <functional>

template <typename T>
using functionType = std::function<void(T, void*)>;

template<typename T>
void PrintMe(T parameter)
{
	if (std::is_same<T, int>::value)
	{
		printf("int %d ", parameter);
	}
	else if (std::is_same<T, const char*>::value)
	{
		printf("string \'%s\' ",  parameter);
	}
	else if (std::is_same<T, float>::value)
	{
		printf("float %f ", parameter);
	}
}


template <typename T>
void ObscureFunction(T par1, void * par2, const std::string & stringedType)
{
	static bool initialized = 0;
	static std::map<std::string, functionType<T>> theMap;
	if ( !initialized )
	{
		theMap.emplace("int", [](T lhs, void* rhs){ PrintMe<T> (lhs); printf("int %d\n", *((int*) rhs)); return; });
		theMap.emplace("string", [](T lhs, void* rhs){ PrintMe<T> (lhs); printf("string \'%s\'\n", (*((std::string *) rhs)).c_str()); return; });
		initialized = true;		
	}

	theMap[ stringedType ](par1, par2);
}


int main()
{


	int a = 1;
	int b = 2;
	std::string klops("klops");
	ObscureFunction <int> (a, (void*) &b, "int");
	ObscureFunction <int> (a, (void*) &klops, "string");

	ObscureFunction <const char*> ("hue hue", (void*) &b, "int");

	return 0;
}