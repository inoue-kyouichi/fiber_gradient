#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;

int main(){
    FILE *fp;
    char file_read_Nux1[34337] = "Nux_1.dat";
    char file_read_Nuy1[34337] = "Nuy_1.dat";
    char file_read_Nuz1[34337] = "Nuz_1.dat";
    char file_read_Nux2[15028] = "Nux_2.dat";
    char file_read_Nuy2[15028] = "Nuy_2.dat";
    char file_read_Nuz2[15028] = "Nuz_2.dat";
    char file_read_Nux3[14549] = "Nux_3.dat";
    char file_read_Nuy3[14549] = "Nuy_3.dat";
    char file_read_Nuz3[14549] = "Nuz_3.dat";

    int E=63914, E1=34337, E2=15028, E3=14549;
    //double Nx2[E2], Ny2[E2], Nz2[E2]; //Nx3[E3], Ny3[E3], Nz[E3];
    //vector<double> Nx2(E2),Ny2(E2),Nz2(E2);
    double *Nx1, *Ny1, *Nz1,*Nx2, *Ny2, *Nz2,*Nx3, *Ny3, *Nz3;

    Nx1 = (double *)malloc(E1*sizeof(double));
    Ny1 = (double *)malloc(E1*sizeof(double));
    Nz1 = (double *)malloc(E1*sizeof(double));
    Nx2 = (double *)malloc(E2*sizeof(double));
    Ny2 = (double *)malloc(E2*sizeof(double));
    Nz2 = (double *)malloc(E2*sizeof(double));
    Nx3 = (double *)malloc(E3*sizeof(double));
    Ny3 = (double *)malloc(E3*sizeof(double));
    Nz3 = (double *)malloc(E3*sizeof(double));

    fp = fopen(file_read_Nux1,"r");
    for (int i=0; i<E1; i++){
        double tmp;
        fscanf(fp, "%lf\n", &tmp);
        Nx1[i] = tmp;
    }
    fclose(fp);
    fp = fopen(file_read_Nuy1,"r");
    for (int i=0; i<E1; i++){
        double tmp;
        fscanf(fp, "%lf\n", &tmp);
        Ny1[i] = tmp;
    }
    fclose(fp);
    fp = fopen(file_read_Nuz1,"r");
    for (int i=0; i<E1; i++){
        double tmp;
        fscanf(fp, "%lf\n", &tmp);
        Nz1[i] = tmp;
    }
    fclose(fp);
    fp = fopen(file_read_Nux2,"r");
    for (int i=0; i<E2; i++){
        double tmp;
        fscanf(fp, "%lf\n", &tmp);
        Nx2[i] = tmp;
    }
    fclose(fp);
    fp = fopen(file_read_Nuy2,"r");
    for (int i=0; i<E2; i++){
        double tmp;
        fscanf(fp, "%lf\n", &tmp);
        Ny2[i] = tmp;
    }
    fclose(fp);
    fp = fopen(file_read_Nuz2,"r");
    for (int i=0; i<E2; i++){
        double tmp;
        fscanf(fp, "%lf\n", &tmp);
        Nz2[i] = tmp;
    }
    fclose(fp);
    fp = fopen(file_read_Nux3,"r");
    for (int i=0; i<E3; i++){
        double tmp;
        fscanf(fp, "%lf\n", &tmp);
        Nx3[i] = tmp;
    }
    fclose(fp);
    fp = fopen(file_read_Nuy3,"r");
    for (int i=0; i<E3; i++){
        double tmp;
        fscanf(fp, "%lf\n", &tmp);
        Ny3[i] = tmp;
    }
    fclose(fp);
    fp = fopen(file_read_Nuz3,"r");
    for (int i=0; i<E3; i++){
        double tmp;
        fscanf(fp, "%lf\n", &tmp);
        Nz3[i] = tmp;
    }
    fclose(fp);

    ofstream fout ("fiber_model123_3.cal"); 

    fout << E << " " << 10 << " " << 10 << endl;
    
    //number of fibers
    for(int i = 0; i<E1; i++){
        fout << 1 << endl;   
    }
    for(int i = 0; i<E2; i++){
        fout << 1 << endl;
    }
    for(int i = 0; i<E3; i++){
        fout << 1 << endl;
    }

    //fiber No
    for(int i = 0; i<E1; i++){
        fout << 1 << endl;
    }
    for(int i = 0; i<E2; i++){
        fout << 2 << endl;
    }
    for(int i = 0; i<E3; i++){
        fout << 3 << endl;
    }

    // create unit vector
    double lambda;
    for(int i = 0; i<E1; i++){
        lambda = sqrt(Nx1[i]*Nx1[i]+Ny1[i]*Ny1[i]+Nz1[i]*Nz1[i]);
        Nx1[i] = -Nx1[i]/lambda;
        Ny1[i] = -Ny1[i]/lambda;
        Nz1[i] = -Nz1[i]/lambda;
    }
    for(int i = 0; i<E2; i++){
        lambda = sqrt(Nx2[i]*Nx2[i]+Ny2[i]*Ny2[i]+Nz2[i]*Nz2[i]);
        Nx2[i] = Nx2[i]/lambda;
        Ny2[i] = Ny2[i]/lambda;
        Nz2[i] = Nz2[i]/lambda;
    }
    for(int i = 0; i<E3; i++){
        lambda = sqrt(Nx3[i]*Nx3[i]+Ny3[i]*Ny3[i]+Nz3[i]*Nz3[i]);
        Nx3[i] = Nx3[i]/lambda;
        Ny3[i] = Ny3[i]/lambda;
        Nz3[i] = Nz3[i]/lambda;
    }


    //x vector
    for(int i = 0; i<E1;  i++){
        fout << Nx1[i] << endl;
    }
    for(int i = 0; i<E2;  i++){
        fout << Nx2[i] << endl;
    }
    for(int i = 0; i<E3;  i++){
        fout << Nx3[i] << endl;
    }

    //y vector
    for(int i = 0; i<E1;  i++){
        fout << Ny1[i] << endl;
    }
    for(int i = 0; i<E2;  i++){
        fout << Ny2[i] << endl;
    }
    for(int i = 0; i<E3;  i++){
        fout << Ny3[i] << endl;
    }

    //z vector
    for(int i = 0; i<E1;  i++){
        fout << Nz1[i] << endl;
    }
    for(int i = 0; i<E2;  i++){
        fout << Nz2[i] << endl;
    }
    for(int i = 0; i<E3;  i++){
        fout << Nz3[i] << endl;
    }
    
    free(Nx1);
    free(Ny1);
    free(Nz1);
    free(Nx2);
    free(Ny2);
    free(Nz2);
    free(Nx3);
    free(Ny3);
    free(Nz3);

    return 0;
}