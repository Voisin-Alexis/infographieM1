#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

using namespace std;

Model::Model(const char *filename) : verts_(), faces_() {
    ifstream in;
    in.open (filename, fstream::in);
	if (in){
    string ligne;
    while (!in.eof()) {
        getline(in, ligne);
		char caractere;
        istringstream iss(ligne.c_str());
        char trash;
        if (!ligne.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v.raw[i];
            verts_.push_back(v);
        } else if (!ligne.compare(0, 2, "f ")) {
            vector<int> f;
            int itrash, idx;
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                idx--; 
                f.push_back(idx);
            }
            faces_.push_back(f);
        }
    }
	}
    cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

std::vector<int> Model::face(int idx) {
    return faces_[idx];
}

Vec3f Model::vert(int i) {
    return verts_[i];
}

