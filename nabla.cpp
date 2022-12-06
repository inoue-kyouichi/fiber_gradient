#include <Eigen/Core>
#include <Eigen/LU>
#include <Eigen/Geometry>
#include <vector>
#include <Eigen/SparseCore>
#include <Eigen/SparseLU>
#include <bits/stdc++.h>

using namespace std;
using namespace Eigen;

typedef Triplet<double, int64_t> T;
typedef Matrix<double,3,4> Matrix3_4d;
typedef Matrix<double,4,3> Matrix4_3d;
typedef Matrix<double,7304,1> VectorNd; //input yourself (N)
typedef Matrix<double,34337,1> VectorEd; //input yourself (E)

int main(){
    FILE *fp;
    char file_read_node[7304] = "object1_node.dat";            //input yourself
    char file_read_element[34337] = "object1_element.dat";         //input yourself
    char file_read_dirichlet0[313] = "dirichlet0_ve_bottom.dat";    //input yourself
    char file_read_dirichlet1[69] = "dirichlet1_2_ve_bottom.dat";   //input yourself

    int N=7304, E=34337 , D0=313 , D1=69 ; //input yourself
    double x[N], y[N], z[N];
    int E1[E], E2[E], E3[E], E4[E], D_0[D0], D_1[D1];

    fp = fopen(file_read_node,"r");
    for (int i=0; i<N; i++){
        fscanf(fp, "%lf %lf %lf\n", &x[i], &y[i], &z[i]);
    }
    fclose(fp);

    fp = fopen(file_read_element,"r");
    for (int i=0; i<E; i++){
        fscanf(fp, "%d %d %d %d\n", &E1[i], &E2[i], &E3[i], &E4[i]);
    }
    fclose(fp);

    fp = fopen(file_read_dirichlet0,"r");
    for (int i=0; i<D0; i++){
        fscanf(fp, "%d\n", &D_0[i]);
    }
    fclose(fp);

    fp = fopen(file_read_dirichlet1,"r");
    for (int i=0; i<D1; i++){
        fscanf(fp, "%d\n", &D_1[i]);
    }
    fclose(fp);

    //creating K
    Matrix3_4d NS,Nxi;
    Matrix3d J;
    Matrix4d ke;
    Matrix4_3d xe;
    vector<vector<double>> Ka(N,vector<double>(N,0.0)); 
    SparseMatrix<double> K(N,N);
    int I[4] = {0};
    double detJ;
    NS << -1.0, 1.0, 0.0, 0.0,
          -1.0, 0.0, 1.0, 0.0,
          -1.0, 0.0, 0.0, 1.0;

    J = Matrix3d::Zero();

    for(int t = 0; t < E; t++){

        xe(0,0) = x[E1[t]]; xe(0,1) = y[E1[t]]; xe(0,2) = z[E1[t]];
        xe(1,0) = x[E2[t]]; xe(1,1) = y[E2[t]]; xe(1,2) = z[E2[t]];
        xe(2,0) = x[E3[t]]; xe(2,1) = y[E3[t]]; xe(2,2) = z[E3[t]];
        xe(3,0) = x[E4[t]]; xe(3,1) = y[E4[t]]; xe(3,2) = z[E4[t]];

        J = NS*xe;

        detJ = J.determinant();
        FullPivLU<Matrix3d> lu(J);
        Nxi = lu.solve(NS);

        I[0] = E1[t]; I[1] = E2[t]; I[2] = E3[t]; I[3] = E4[t];
        
        ke = Matrix4d::Zero();
        for(int p = 0; p<4; p++){
            for(int q = 0; q<4; q++){
                for(int k = 0; k<3; k++){
                        ke(p,q) += Nxi(k,p)*Nxi(k,q)*detJ/6.0;
                }
                //cout<< I[p] << " " << I[q] << endl;
                Ka.at(I[p]).at(I[q]) += ke(p,q);
            }
        }    
    }
    //vector<T> tripletVec_K;
    //for(int i=0; i<N; i++){
    //    tripletVec_K.push_back( T(i,i,1e0) );
    //}
    //K.setFromTriplets(tripletVec_K.begin(), tripletVec_K.end());

    //vector<T> tripletVec_K1;
    //for(int i = 0; i<3*N; i++){
    //    for(int j = 0; j<3*N; j++){
    //        if( Ka.at(i).at(j) != 0 ){
    //            tripletVec_K1.push_back( T(i,j,Ka.at(i).at(j)) );
    //        }
    //    }
    //}
    //K1.setFromTriplets(tripletVec_K1.begin(), tripletVec_K1.end());

    //boundary condition
   for(int i = 0; i< D0; i++){
       Ka.at(D_0[i]).at(D_0[i]) = 1.0;
       for(int j = 0; j<N; j++){
            if( D_0[i] == j){
            }
            else{
               Ka.at(D_0[i]).at(j) = 0.0;
            }
       }
   }
   for(int i = 0; i<D1; i++){
       Ka.at(D_1[i]).at(D_1[i]) = 1.0;
       for(int j = 0; j<N; j++){
            if( D_1[i] == j){
            }
            else{
               Ka.at(D_1[i]).at(j) = 0.0;
            }
       }
   }
   
   vector<T> tripletVec_K;
   for(int i = 0; i<N; i++){
       for(int j = 0; j<N; j++){
           if( Ka.at(i).at(j) != 0 ){
               tripletVec_K.push_back( T(i,j,Ka.at(i).at(j)) );
               //tripletVec_K.push_back( T(i+N,j+N,Ka.at(i).at(j)) );
               //tripletVec_K.push_back( T(i+2*N,j+2*N,Ka.at(i).at(j)) );
           }
       }
   }
   K.setFromTriplets(tripletVec_K.begin(), tripletVec_K.end());

    VectorNd u,F;
    //VectorXd u(12541),F(12541);
    u = VectorNd::Zero();
    F = VectorNd::Zero();

    for(int i = 0; i<D1; i++){
        F(D_1[i],0) = 1e0;
       // F(D_1[i]+N,0) = 1e0;
        //F(D_1[i]+2*N,0) = 1e0;
    }

    cout << "start simultaneous calculation" << endl;

    SparseLU<SparseMatrix<double>> solver;
    solver.compute(K);
    u = solver.solve(F);

    cout << "end simultaneous calculation" << endl;

    cout << "start nabla calculation" << endl;

    VectorEd Nux,Nuy,Nuz;
    Nux = VectorEd::Zero();
    Nuy = VectorEd::Zero();
    Nuz = VectorEd::Zero();
    for(int t = 0; t < E; t++){

        xe(0,0) = x[E1[t]]; xe(0,1) = y[E1[t]]; xe(0,2) = z[E1[t]];
        xe(1,0) = x[E2[t]]; xe(1,1) = y[E2[t]]; xe(1,2) = z[E2[t]];
        xe(2,0) = x[E3[t]]; xe(2,1) = y[E3[t]]; xe(2,2) = z[E3[t]];
        xe(3,0) = x[E4[t]]; xe(3,1) = y[E4[t]]; xe(3,2) = z[E4[t]];

        J = NS*xe;

        detJ = J.determinant();
        FullPivLU<Matrix3d> lu(J);
        Nxi = lu.solve(NS);

        
        Nux(t,0) = u(E1[t])*Nxi(0,0)+u(E2[t])*Nxi(0,1)+u(E3[t])*Nxi(0,2)+u(E4[t])*Nxi(0,3);
        Nuy(t,0) = u(E1[t])*Nxi(1,0)+u(E2[t])*Nxi(1,1)+u(E3[t])*Nxi(1,2)+u(E4[t])*Nxi(1,3);
        Nuz(t,0) = u(E1[t])*Nxi(2,0)+u(E2[t])*Nxi(2,1)+u(E3[t])*Nxi(2,2)+u(E4[t])*Nxi(2,3);
        
    }

    cout << "end nabla calculation" << endl;

    ofstream fout ("Nuz_1.dat"); //input yourself
    for(int i = 0; i<E; i++){
        fout << Nuz(i,0) << endl;   //input yourself(Nux or Nuy or Nuz)
    }
    

    return 0;
}
