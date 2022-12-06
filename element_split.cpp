#include <bits/stdc++.h>

using namespace std;

int main(){
   FILE *fp;
   char file_read_element[] = "object_all_element.dat";
   int E = 63914; //input yourself( number of element)
   int E1[E],E2[E],E3[E],E4[E];

   fp = fopen(file_read_element,"r");
    for (int i=0; i<E; i++){
        fscanf(fp, "%d %d %d %d\n", &E1[i], &E2[i], &E3[i], &E4[i]);
    }

    ofstream fout ("object3_element.dat");
    for(int i = 49365; i<63914; i++){ //input yourself( split element)
        fout << E1[i] << " " << E2[i] << " " << E3[i] << " " << E4[i] << endl;
    }

    return 0;
}