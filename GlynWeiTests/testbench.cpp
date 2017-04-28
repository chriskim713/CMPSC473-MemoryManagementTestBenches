/********************/
//Included for testing
#include <random>
#include <chrono>
#include <fstream>
#include <string>
/*******************/
typedef unsigned long long address;
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
	address addr;
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