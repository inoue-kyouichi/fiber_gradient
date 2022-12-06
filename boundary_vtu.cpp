#include "fileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

const int numOfNode = 12541; //input yourself
const int numOfElm = 63914; //input yourself
const int numOfbd = 656;

void export_vtu_boundary(ARRAY2D<double> &x,const std::vector<ElementType> &element,
            const int &numOfNode,const int &numOfElm,
            ARRAY2D<int> &ibd,ARRAY2D<double> &bd,const string &file)
{
  FILE *fp;
  if ((fp = fopen(file.c_str(), "w")) == NULL) {
    cout << file << " open error" << endl;
    exit(1);
  }

  fprintf(fp,"<VTKFile type=\"UnstructuredGrid\" version=\"1.0\" byte_order=\"LittleEndian\" header_type=\"UInt64\">\n");
  fprintf(fp,"<UnstructuredGrid>\n");
  fprintf(fp,"<Piece NumberOfPoints= \"%d\" NumberOfCells= \"%d\" >\n",numOfNode,numOfElm);
  fprintf(fp,"<Points>\n");
  fprintf(fp,"<DataArray type=\"Float64\" Name=\"Points\" NumberOfComponents=\"3\" format=\"ascii\">\n");
  for(int i=0;i<numOfNode;i++){
    fprintf(fp,"%e %e %e\n",x(i,0),x(i,1),x(i,2));
  }
  fprintf(fp,"</DataArray>\n");
  fprintf(fp,"</Points>\n");
  fprintf(fp,"<Cells>\n");
  fprintf(fp,"<DataArray type=\"Int64\" Name=\"connectivity\" format=\"ascii\">\n");
  for(int i=0;i<numOfElm;i++){
    for(int j=0;j<element[i].node.size();j++) fprintf(fp,"%d ",element[i].node[j]);
    fprintf(fp,"\n");
  }
  fprintf(fp,"</DataArray>\n");
  fprintf(fp,"<DataArray type=\"Int64\" Name=\"offsets\" format=\"ascii\">\n");
  int num=0;
  for(int i=0;i<numOfElm;i++){
    num += element[i].node.size();
    fprintf(fp,"%d\n",num);
  }
  fprintf(fp,"</DataArray>\n");
  fprintf(fp,"<DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n");
  for(int i=0;i<numOfElm;i++) fprintf(fp,"%d\n",element[i].meshType);
  fprintf(fp,"</DataArray>\n");
  fprintf(fp,"</Cells>\n");

  fprintf(fp,"<PointData>\n");
  fprintf(fp,"<DataArray type=\"Float64\" Name=\"bd\" NumberOfComponents=\"3\" format=\"ascii\">\n");
  for(int i=0;i<numOfNode;i++){
    fprintf(fp,"%e %e %e\n",bd(i,0),bd(i,1),bd(i,2));
  }
  fprintf(fp,"</DataArray>\n");
  fprintf(fp,"<DataArray type=\"Int64\" Name=\"ibd\" NumberOfComponents=\"3\" format=\"ascii\">\n");
  for(int i=0;i<numOfNode;i++){
    fprintf(fp,"%d %d %d\n",ibd(i,0),ibd(i,1),ibd(i,2));
  }
  fprintf(fp,"</DataArray>\n");
  fprintf(fp,"</PointData>\n");
  fprintf(fp,"<CellData>\n");
  fprintf(fp,"</CellData>\n");

  fprintf(fp,"</Piece>");
  fprintf(fp,"</UnstructuredGrid>");
  fprintf(fp,"</VTKFile>");
  fclose(fp);
}

int main(){
    
   FILE *fp;
   
   char file_read_node[numOfNode] = "object_all_node.dat";
   char file_read_element[numOfElm] = "object_all_element.dat";
   char file_read_boundary[numOfbd] = "dirichlet1ofall_ve_bottom.dat";
   ARRAY2D<double> x;
 
   x.allocate(numOfNode,3);
 
   if ((fp = fopen(file_read_node, "r")) == NULL) {
     cout << "file open error" << endl;
     exit(1); 
   }
   for(int i=0;i<numOfNode;i++){
     fscanf(fp,"%lf %lf %lf\n",&x(i,0),&x(i,1),&x(i,2));
   }
   fclose(fp);

   vector<ElementType> element;
   if ((fp = fopen(file_read_element, "r")) == NULL) {
     cout << "file open error" << endl;
     exit(1); 
   }
   element.resize(numOfElm);
   for(int i=0;i<numOfElm;i++){
      element[i].node.resize(4);
      fscanf(fp,"%d %d %d %d\n",&element[i].node[0],&element[i].node[1],&element[i].node[2],&element[i].node[3]);
      element[i].meshType = VTK_TETRA ;
    }
    fclose(fp);

    ARRAY2D<int> ibd;
    ARRAY2D<double> bd;
    int n;
  ibd.allocate(numOfNode,3);
  bd.allocate(numOfNode,3);
  for(int i=0;i<numOfNode;i++){
    for(int j=0;j<3;j++){
      ibd(i,j)=1;
      bd(i,j)=0e0;
    }
  }
  if ((fp = fopen(file_read_boundary, "r")) == NULL) {
     cout << "file open error" << endl;
     exit(1); 
   }
  for(int i=0;i<numOfbd;i++){
     fscanf(fp,"%d\n",&n);
     ibd(n,0) = 0;
     ibd(n,0) = 0;
     ibd(n,0) = 0;
  }

  string output = "boundary.vtu";
  export_vtu_boundary(x,element,numOfNode,numOfElm,ibd,bd,output);
  


    return 0;
}