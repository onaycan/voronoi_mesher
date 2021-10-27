// voronoi_3.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <fstream> 
#include <stdio.h>
#include <search.h>
#include <malloc.h>
#include "VoronoiDiagramGenerator.h"
#include "my_functions.h"

int _tmain(int argc, _TCHAR* argv[])
{
    //	float xValues[4] = {-22, -17, 4,22};
//	float yValues[4] = {-9, 31,13,-5};
ifstream infile("inputs//Section_cloud.txt"); 
int numberofmodelnodes=1; 
float X_current[2]; 
float Xmin; 
float Xmax; 
float Ymin; 
float Ymax; 


infile>>Xmin; 
Xmax=Xmin; 
infile>>Ymin; 
Ymax=Ymin; 

while(infile>>X_current[0])
{
numberofmodelnodes++; 
if(X_current[0]<Xmin)
Xmin=X_current[0]; 
if(X_current[0]>Xmax)
Xmax=X_current[0];

infile>>X_current[1]; 
if(X_current[1]<Ymin)
Ymin=X_current[1]; 
if(X_current[1]>Ymax)
Ymax=X_current[1];


}
    
//cout<<numberofmodelnodes<<endl; 
ifstream infile2("inputs//Section_cloud.txt"); 

  float *xValues=new float[numberofmodelnodes];
  float *yValues=new float[numberofmodelnodes];

for(int i=0;i<numberofmodelnodes;i++)
{
infile2>>xValues[i];
infile2>>yValues[i];
}

ofstream voronoifile("outputs//GiD_voronoi.post.msh"); 
ofstream debugfile("outputs//debugfile.txt"); 	

/*
  

   for(int n=0;n<numberofmodelnodes;n++)
    {        
        xValues[n]=RandReal(-Lx,Lx);
        yValues[n]=RandReal(-Ly,Ly);       
    }
*/  
	long count = numberofmodelnodes;


	VoronoiDiagramGenerator vdg;
  vdg.setGenerateDelaunay(1); 
  vdg.generateVoronoi(xValues,yValues,count, Xmin,Xmax,Ymin,Ymax,0,1);

	vdg.resetIterator();
  vdg.resetDelaunayEdgesIterator(); 

	float x1,y1,x2,y2;
  int nodelabel=1; 
  int elementlabel=1; 


	printf("\n-------------------------------\n");

voronoifile<<"MESH voronoi dimension 3 ElemType Linear Nnode 2"<<endl; 
voronoifile<<"Coordinates"<<endl; 
  while(vdg.getNext(x1,y1,x2,y2))
	{
      
		//printf("GOT Line (%f,%f)->(%f,%f)\n",x1,y1,x2, y2);
      /*
      if(x1==Xmax || x1==Xmin)
      {
          x1=x2;
          y1=y2; 
      }

      else
      if(x2==Xmax || x2==Xmin)
      {
          x2=x1;
          y2=y1; 
      }

      else
      if(y1==Ymax || y1==Ymin)
      {      
          y1=y2; 
          x1=x2;   
      }

      else
      if(y2==Ymax || y2==Ymin)
      {
          y2=y1; 
          x2=x1; 
      }
        
      */ 
		voronoifile<<nodelabel<<'\t'<<x1<<'\t'<<y1<<endl; 
    voronoifile<<nodelabel+1<<'\t'<<x2<<'\t'<<y2<<endl;
    nodelabel=nodelabel+2;

      
	}
voronoifile<<"End Coordinates"<<endl;
voronoifile<<"Elements"<<endl; 

for(int i=0;i<nodelabel/2;i++)
{
voronoifile<<elementlabel<<'\t'<<elementlabel*2-1<<'\t'<<elementlabel*2<<endl;
elementlabel++; 
}
 
voronoifile<<"End Elements"<<endl; 
	return 0;
}

