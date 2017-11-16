#pragma once

#include <iostream>
#include <string>
#include "../stl/CEdge.h"
#include "../stl/CFacet.h"
#include "../stl/CVertex.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <GL/glut.h>
using namespace std;

class OctreeNode
{
    friend class Octree;
    public:
        OctreeNode():
            Back_Left_Bottom(NULL),Back_Left_Top(NULL),
            Back_Right_Bottom(NULL),Back_Right_Top(NULL),
            Front_Left_Bottom(NULL),Front_Left_Top(NULL),
            Front_Right_Bottom(NULL),Front_Right_Top(NULL){}
        OctreeNode
            (string str="-1", int nodeflag=1,
             OctreeNode *back_left_bottom =NULL,
             OctreeNode *back_left_top =NULL,
             OctreeNode *back_right_bottom =NULL,
             OctreeNode *back_right_top =NULL,
             OctreeNode *front_left_bottom =NULL,
             OctreeNode *front_left_top =NULL,
             OctreeNode *front_right_bottom =NULL,
             OctreeNode *front_right_top =NULL):
                orderstr(str),flag(nodeflag),
                Back_Left_Bottom(back_left_bottom),
                Back_Left_Top(back_left_top),
                Back_Right_Bottom(back_right_bottom),
                Back_Right_Top(back_right_top),
                Front_Left_Bottom(front_left_bottom),
                Front_Left_Top(front_left_top),
                Front_Right_Bottom(front_right_bottom),
                Front_Right_Top(front_right_top){}
        ~OctreeNode(){}
    private:
        string orderstr; //node coding
        int flag; //flag
        OctreeNode *Back_Left_Bottom;
        OctreeNode *Back_Left_Top;
        OctreeNode *Back_Right_Bottom;
        OctreeNode *Back_Right_Top;
        OctreeNode *Front_Left_Bottom;
        OctreeNode *Front_Left_Top;
        OctreeNode *Front_Right_Bottom;
        OctreeNode *Front_Right_Top;
}; 

class Octree
{
    public:
        Octree():root(NULL),max_height(0){}
        Octree(string str)
        {
            root = new OctreeNode(str,1);
            max_height = 1;
        }
        ~Octree()
        {
            DeleteRoot(root);
        }
        void DeleteRoot(OctreeNode *pRoot);
        void MakeOctree(int height);
        void PointToOctree(vector<CVertex> VectorPoint,float xmax,float xmin,float ymax,float ymin,float zmax,float zmin);
        void EdgeToOctree(vector<CVertex> VectorPoint,vector<CEdge> VectorEdge,float xmax,float xmin,float ymax,float ymin,float zmax,float zmin);
        void PerpendicularToSurfaceEdge(string x,string y,string z,string diff, int serial);
        void ParallelToSurfaceEdge(float a1,float a2,float b1,float b2,string c, int serial);//a1,a2 b1,b2 mean different point coordinate,c means the same coordinate of two point
        void GeneralLocationEdge(float x1,float x2,float y1,float y2,float z1,float z2);
        void ChangePoint(string x,string y,string z);
        string ChangeCoordinate(float coordinate,float max,float min);
        unsigned int ChangeToDecimal(string binary);
        string ChangeToBinary(unsigned int decimal);
        void Traverse(void);
        void PreOrder(OctreeNode *pRoot); //traverse the octree
        void DisplayOctree(OctreeNode *pRoot); //draw
        void DrawVoxel(string x,string y,string z);
        int IsEmpty()
        {return root==NULL?1:0;}
    private:
        OctreeNode *root;
        int max_height;
};

