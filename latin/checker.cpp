#include <bits/stdc++.h>

using namespace std;

float score = 0;

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

long long manacher(const std::string &s) {
    string v="^";
    for(const auto &c:s) {
        v.push_back('#');
        v.push_back(c);
    }
    v.push_back('#');
    v.push_back('$');

    int n=(int)v.size();
    long long ans=0;
    vector<int> p(n,0);
    int c=0,r=0;

    for(int i=1; i<n-1; i++) {
        int j=2*c-i;
        if(r>i) {
            p[i]=min(r-i,p[j]);
        }

        while(v[i+1+p[i]]==v[i-1-p[i]]) {
            p[i]++;
        }

        if(i+p[i]>r) {
            c=i;
            r=i+p[i];
        }

        ans+=1LL*(p[i]+1)/2LL;
    }

    return ans;
}

ifstream out, ok, in;

int main(int argc, char* argv[]) {
	in.open(argv[1]); // test input; assumed to be valid
	ok.open(argv[2]); // correct output
	out.open(argv[3]); // user output

    int n,k;
    in >> n >> k;

    string res;
    Assert(!!(out >> res), "Bad string format");
    Assert((int)res.size()==n, "Bad string format");

    string in_plus;
    if(out >> in_plus) {
        Assert(false, "Bad string format");
    }

    for(const auto &c:res) {
        if('a'<=c && c<=((char)('a'+k-1))) {
            continue;
        }
        Assert(false, "Bad string format");
    }

    string ref;
    ok >> ref;

    long long ans=manacher(res);
    long long target=manacher(ref);
    Assert(ans==target, "Wrong answer");
    Success(1.0, "Correct!");

    return 0;
}
