/********************/
//Included for testing
#include <random>
#include <chrono>
#include <fstream>
#include <string>
/*******************/
typedef unsigned long long _address;
void run_test(string in, string out) {
	ifstream in_stream(in);
	ofstream out_stream(out);
	unsigned p;
	unsigned page_size;
	unsigned no_frames;
	unsigned address_size;
	in_stream >> p;
	in_stream >> page_size;
	in_stream >> no_frames;
	in_stream >> address_size;
	memoryManager manager(static_cast<ReplacementPolicy>(p), page_size, no_frames, address_size);
	_address addr;
	auto start = chrono::high_resolution_clock::now();
	while (in_stream >> addr) {
		out_stream << manager.memoryAccess(addr) <<endl;
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> time = end - start;
	cout << "Finished running test.\nTime elapsed:" << time.count() << "\nNumber of swaps: " << manager.numberPageSwaps() << endl;
	in_stream.close();
	out_stream.close();
}
void generate_tests(ReplacementPolicy p, unsigned page_size, unsigned no_frames, unsigned address_size, string in, string out, long memory_accesses) {
	ofstream in_stream(in);
	ofstream out_stream(out);
	auto max = pow(2, address_size);
	in_stream << p << endl << page_size << endl << no_frames << endl << address_size << endl;
	memoryManager manager(p, page_size, no_frames, address_size);
	default_random_engine generator;
	uniform_real_distribution<double> distr(0, max);
	auto start = chrono::high_resolution_clock::now();
	for (long i = 0; i < memory_accesses; i++) {
		_address adr = static_cast<_address>(distr(generator));
		in_stream << adr << endl;
		out_stream << manager.memoryAccess(adr) << endl;
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> time = end - start;
	cout << "Generating tests done.\nTime elapsed:" << time.count() << "\nNumber of swaps: " << manager.numberPageSwaps() << endl;
	in_stream.close();
	out_stream.close();
}
