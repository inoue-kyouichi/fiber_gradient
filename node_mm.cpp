#include <bits/stdc++.h>

using namespace std;

int main(){

    FILE *fp;
    char file_read_node[12541] = "object_all_node.dat";
    int N=12541;
    double x[N], y[N], z[N];

    fp = fopen(file_read_node,"r");
    for (int i=0; i<N; i++){
        fscanf(fp, "%lf %lf %lf\n", &x[i], &y[i], &z[i]);
    }
    fclose(fp);

    for(int i=0; i<N; i++){
        x[i] = x[i]*1e3;
        y[i] = y[i]*1e3;
        z[i] = z[i]*1e3;
    }

    ofstream fout("node_mm.dat");
    for(int i=0; i<N; i++){
        fout << x[i] << " " << y[i] << " " << z[i] << endl;
    }


    return 0;
}