#include<iostream>
#include<vector>
#include<functional>

// Basic method that executes functions from a vector.
void ExecuteFunction(std::vector<std::function<void(void)>> const& FunctionVector) {

	for (auto& Function : FunctionVector) {
		Function();
	}
}

void standard_void_function(void) {
	std::cout << "In normal void function\n";
}

void standard_int_function(int x) {
	std::cout << "In normal int function with x=" << x << "\n";
}

void standard_int_int_function(int x, int y) {
	std::cout << "In normal int int function with x=" << x << " and y=" << y << "\n";
}

class functor_class {
private:

	int x;

public:

	inline explicit functor_class(int y): x(y) {};

	// This operator overloading enables calling
	// operator function () on objects of functor,
	void operator()(void) {
		x += 1;
		std::cout << "In functor\n";
	}
};

int main() {

	std::vector < std::function<void(void)> > function_vector;

	auto lambda_function = [&]() {
		std::cout << "In lambda function\n";
	};

	functor_class functor(31);

	std::function<void(void)> bind_function_to_int = std::bind(standard_int_function, 42);
	std::function<void(int)> bind_function_to_int_with_placeholder = std::bind(standard_int_int_function, 1, std::placeholders::_1);

	function_vector.push_back(functor);
	function_vector.push_back(lambda_function);
	function_vector.push_back(standard_void_function);
	function_vector.push_back(bind_function_to_int);

	ExecuteFunction(function_vector);

	for (uint32_t functionindex = 0; functionindex < function_vector.size();  ++functionindex) {
		bind_function_to_int_with_placeholder(functionindex);
	}

	getchar();
	return 0;
}