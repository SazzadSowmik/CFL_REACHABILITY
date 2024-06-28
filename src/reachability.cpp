#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"

#include "reachability.h"
#define MAX 100

string gram[MAX][MAX];  //to store entered grammar
int np;	

//concatenates unique non-terminals
string concat(string a, string b) {
	string r = a;
	for (int i = 0; i < b.length(); i++)
		if (r.find(b[i]) > r.length())
			r += b[i];
	return r;
}

//All the combinations BA * AB = {BA, BB, AA, BB}
string gen_comb(string a, string b) {
	string pri, re = "";
	for (int i = 0; i < a.length(); i++)
		for (int j = 0; j < b.length(); j++) {
			pri = "";
			pri = pri + a[i] + b[j];

			//searches if the generated productions p can be created by variables
			for (int j = 0; j < np; j++)
			{
				for (int k = 1; gram[j][k] != ""; k++)
				{
					if (gram[j][k] == pri)
					{
						re = concat(re, gram[j][0]);
					}
				}
			}
		}
	return re;
}


bool is_member(const string& sa) {
    int i, pt, j, l, k;
    string a, str, r, pr, start = "S";
    char buff[100];
    np = 0;
	bool prod_found=false;

    ifstream ifile("../data/cnf_input.txt");
    while (ifile.getline(buff, 99))
	{
		a = buff;
		if (a.find("PRODUCTIONS:") < a.length())
		{	
			prod_found=true;
			break;
		}
	}

    if(!prod_found)
	{
		cout<<"Unable to read production rules! Terminating the program\n";
		ifile.close();
		system("pause");
		return 1;
	}

    while (ifile.getline(buff, 99)) {
		a = buff;
		a.erase(remove_if(a.begin(), a.end(), ::isspace), a.end());
		a.erase(remove(a.begin(), a.end(), ';'), a.end());
		pt = a.find("->");

		//left side of production
		gram[np][0] = a.substr(0, pt);
		a = a.substr(pt + 2, a.length());
		//right side of production
		for (j = 0; a.length()!=0; j++)
		{
			int i = a.find("|");
			if (i > a.length())
			{
				gram[np][j + 1] = a;
				a = "";
			}
			else
			{
				gram[np][j + 1] = a.substr(0, i);
				a = a.substr(i + 1, a.length());
			}
		}

		np++;
	}
    ifile.close();

    string table[MAX][MAX], st;
	set<string> strings;

    strings.insert(sa);

    //For each string read from strings file
	for (set<string>::iterator it = strings.begin(); it != strings.end(); ++it) {
		str = *it;

		//Assigns values to principal diagonal of matrix
		for (i = 0; i < str.length(); i++)
		{
			r = "";
			st = "";
			st += str[i];

			for (j = 0; j < np; j++)
			{
				for (k = 1; gram[j][k] != ""; k++)
				{
					if (gram[j][k] == st)
					{
						r = concat(r, gram[j][0]);
					}
				}
			}
			table[i][i] = r;
		}

		//Assigns values to upper half of the matrix
		for (k = 1; k < str.length(); k++)
		{
			for (j = k; j < str.length(); j++)
			{
				r = "";
				for (l = j - k; l < j; l++)
				{
					pr = gen_comb(table[j - k][l], table[l + 1][j]);
					r = concat(r, pr);
				}
				table[j - k][j] = r;
			}
		}

		/*
		//Prints the matrix
		for (i = 0; i < str.length(); i++)
		{
			k = 0;
			l = str.length() - i - 1;
			for (j=l; j<str.length(); j++)
			{
				cout << "     " << table[k++][j] << " ";
			}
			cout << endl;
		}
		*/

		//Checks if last element of first row contains a Start variable
		if (table[0][str.length() - 1].find(start) <= table[0][str.length() - 1].length()){
            return true;
        }
	}
    return false;
}

vector<pair<int, int>> reachabilityAnalysis(const Graph &graph)
{
    vector<pair<int, int>> result;
    unordered_map<int, vector<pair<char, int>>> edges = graph.getEdges();

    vector<pair<pair<int, int>, string>> all_strings;

    // Helper function for DFS traversal
    function<void(int, int, string)> dfs = [&](int from, int current, string path)
    {
        // Add the current path to the result
        if (from != current)
        {
            all_strings.push_back({{from, current}, path});
        }

        // Explore neighbors
        if (edges.find(current) != edges.end())
        {
            for (const auto &edge : edges.at(current))
            {
                char label = edge.first;
                int to = edge.second;
                dfs(from, to, path + label);
            }
        }
    };

    // Start DFS from each node
    for (const auto &entry : edges)
    {
        int from = entry.first;
        dfs(from, from, "");
    }

    for (const auto &entry : all_strings)
    {
        if (is_member(entry.second)) {
            result.push_back({entry.first.first, entry.first.second});
            // cout << entry.second << " - is a Part of language\n";
        } else {
            // cout << entry.second << " - is Not a Part of language\n";
        }
    }

    return result;
}
