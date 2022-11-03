#include <span>
#include "Program.hpp"
int main(int argc, char** argv) {
	return Program::Main(std::span<char*>(argv, argv + argc));
}