#include <charconv>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void result(const char* msg, float pts) {
    //"{score}" to stdout
    //"{message}" to stderr
    // score is a float between 0 and 1
	printf("%f", pts);
    fprintf(stderr, "%s", msg);
	exit(0);
}

void Assert(bool cond, string str) {
	if (!cond)
		result(str.c_str(), 0);
}
void Success(float pts, string str) {
	result(str.c_str(), pts);
}

ifstream out, ok, in;

// Reads one integer in [low, high] from the user output; anything else is a wrong answer.
long long read(long long low, long long high, string what) {
	string token;
	Assert(bool(out >> token), "expected an integer for " + what);
	long long value;
	auto [end, error] = from_chars(token.data(), token.data() + token.size(), value);
	Assert(error == errc{} && end == token.data() + token.size(), "expected an integer for " + what);
	Assert(low <= value && value <= high,
	       what + " = " + to_string(value) + " is outside [" + to_string(low) + ", " + to_string(high) + "]");
	return value;
}

int main(int argc, char* argv[]) {
	in.open(argv[1]); // test input; assumed to be valid
	ok.open(argv[2]); // correct output
	out.open(argv[3]); // user output
	int n; in >> n;
	vector<int> p(n + 1);
	for (int i = 1; i <= n; ++i) in >> p[i];
	long long best; ok >> best;

	long long k = read(0, n, "k");
	Assert(k == best, "k = " + to_string(k) + ", but the minimum is " + to_string(best));

	// lastUsed[i] == s marks position i as already swapped during second s.
	vector<long long> lastUsed(n + 1, 0);
	for (long long s = 1; s <= k; ++s) {
		string second = "second " + to_string(s);
		long long m = read(0, n / 2, "m in " + second);
		for (long long t = 0; t < m; ++t) {
			long long i = read(1, n, "a position in " + second);
			long long j = read(1, n, "a position in " + second);
			Assert(i != j, "swap (" + to_string(i) + ", " + to_string(j) + ") in " + second);
			for (long long x : {i, j}) {
				Assert(lastUsed[x] != s, "position " + to_string(x) + " is used twice in " + second);
				lastUsed[x] = s;
			}
			swap(p[i], p[j]);
		}
	}

	string extra;
	Assert(!(out >> extra), "extra output after the last swap");
	for (int i = 1; i <= n; ++i)
		Assert(p[i] == i, "position " + to_string(i) + " holds " + to_string(p[i]) + " at the end");
	Success(1, "translate:success");
}
