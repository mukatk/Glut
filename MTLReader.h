#include <vector>
#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Material.h";

using namespace std;

static string const Ka = "Ka";
static string const Kd = "Kd";
static string const Ks = "Ks";
static string const Ns = "Ns";
static string const map_Kd = "map_Kd";
static string const newmtl = "newmtl";

class MTLReader
{
public:
	MTLReader() {}
	~MTLReader() {}

	void read(string path, vector<Material*> &m) {
		Material* aux = new Material();

		ifstream MTL_FILE(path);

		if (!MTL_FILE) {
			cerr << "Arquivo MTL nao encontrado.";
			return;
		}

		string line;
		char word[100];

		for (int lineNumber = 0; getline(MTL_FILE, line); lineNumber++) {
			if (m.size() > 0)
				aux = m.at(m.size() - 1);

			if (line.empty() || line[0] == '#') continue;

			stringstream ss(line);

			for (int wordNumber = 1; ss >> word; wordNumber++) {

				if (word == Ka) {
					ss >> word;
					float r = atof(word);
					ss >> word;
					float g = atof(word);
					ss >> word;
					float b = atof(word);

					aux->Ka[0] = r;
					aux->Ka[1] = g;
					aux->Ka[2] = b;
				}
				else if (word == Kd) {
					ss >> word;
					float r = atof(word);
					ss >> word;
					float g = atof(word);
					ss >> word;
					float b = atof(word);

					aux->Kd[0] = r;
					aux->Kd[1] = g;
					aux->Kd[2] = b;
				}
				else if (word == Ks) {
					ss >> word;
					float r = atof(word);
					ss >> word;
					float g = atof(word);
					ss >> word;
					float b = atof(word);

					aux->Ks[0] = r;
					aux->Ks[1] = g;
					aux->Ks[2] = b;
				}
				else if (word == Ns) {
					ss >> word;
					float n = atof(word);
					aux->Ns = n;
				}
				else if (word == map_Kd) {
					ss >> word;
					aux->map_Kd = word;
					aux->loadImg();
				}
				else if (word == newmtl) {
					ss >> word;
					aux = new Material();
					aux->name = word;
					m.push_back(aux);
				}
				else {
					continue;
				}
			}
		}

		cout << "Leitura MTL finalizado.";


	}
};