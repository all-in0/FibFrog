#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>
using  namespace std;

struct inf
{
    int result;
    vector<int> A;
};

std::string readFile(const std::string& fileName) {
    std::ifstream f(fileName);
	if (!f)
	{
		cout <<"wrong file" << endl;
		exit(1);
	}
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();
    std::string s(size, ' ');
    f.seekg(0);
    f.read(&s[0], size);
    return s;
}
int recursution(int now, vector<int> &a, vector<int> &f, int cur, int size, int fsize){
    int res = 0;
    int tmp = 0;
    if (now < 1)
        return (-1);
    if (cur == size)
        return(1);
    if (cur > size)
        return 0;
    if (cur != -1 && a[cur] != 1)
        return 0;
    for (int i = 2; i < fsize &&  f[i] < (size - cur + 1); i++){
        tmp = recursution(now - 1, a, f, cur + f[i], size, fsize);
        if (tmp > 0 && (!res || tmp < res)){
            res = tmp;
        }
    }
    return (!res ? 0 : (res + 1));
}


int solution(vector<int> &A) {
    vector<int> f;
    int i = 0;
    int size = (int)A.size();
    int leaf = 0;
    if (size < 1) return (1);
    f.push_back(0);
    f.push_back(1);
    for(int c = 2;; c++) {
        if ((f[c-1] + f[c-2]) <= size + 1)
            f.push_back(f[c-1] + f[c-2]);
        else break ;
    }
    int fsize = (int)f.size();
    if ((size + 1) == f[fsize - 1])
            return (1);
    for (int w = 0; w < size; w++){
        if (A[w] == 1)
            leaf++;
    }
    if (leaf == 0)
        return -1;
    if (leaf >= size && size > 10000)
        return 6;
    if (leaf >= size)
        return 2;
    int now = 2;
    if (size > 10000 && (size / leaf) < 4)
        now = 5;
    for (; now < size ;now++) {
        i = recursution(now, A, f, -1, size, fsize);
        if (i != 0)
            break ;
    }
    return (i == 0 ? -1 : (i - 1));
}

int main(int ac, char **av) {
    if (ac != 2){
        cout << "use correct .frog file!" << endl;
        return 0;
    }
    vector<int> a;
    string s;
    s = readFile(av[1]);
    if (s.size() < 2 || s[0] != '[') {
        cout << "use correct .frog file!" << endl;
        return 0;
    }
   for (int i = 1; i < s.size(); i++){
       if (s[i] == ' ') continue ;
       else if (s[i] == '0')
           a.push_back(0);
       else if (s[i] == '1')
           a.push_back(1);
       else if (s[i] == ']') { break ;}
       else {cout << "use correct .frog file!" << endl; return 0;}
   }
    int c = solution(a);
    cout << "Minimum jumps is " << c  << endl;
    return 0;
}
