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

class OctreePoint
{
    public:
        OctreePoint(float _x,float _y,float _z):x(_x),y(_y),z(_z){}
        OctreePoint(const OctreePoint& copy)
        {
            x=copy.x;
            y=copy.y;
            z=copy.z;
        }
        friend class Octree;
    private:
        float x;
        float y;
        float z;
};

class OctreeNode
{
    //declare the octree node class
    //define back as 0,front as 1,left as 0,right as 1,bottom as 0,top as 1
    //use right hand spiral rules
    //define x as back and front direction, y as left and front direciton, z as top and bottom direction
    //as an example, Front_Left_Top means 101,ChangeToDecimal is 5. So, the orderstr in this depth equals 5
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
        string orderstr; 
        //node coding which can define the location of this node in Octree
        int flag; 
        //use -1 to define the node out of the part
        //use 0 to define the node on the part
        //use 1 to define the node in the part
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
        //use iteration to delete the root
        void MakeOctree(int height);
        //set up an octree with all nodes out of the part
        void Traverse(void);
        //use perorder traversal
        void PreOrder(OctreeNode *pRoot); //traverse the octree
        void DisplayOctree(OctreeNode *pRoot); //draw
        void DrawVoxel(string x,string y,string z);
        int IsEmpty()
        {return root==NULL?1:0;}
        void PointToOctree(vector<CVertex> VectorPoint
                ,float xmax,float xmin
                ,float ymax,float ymin
                ,float zmax,float zmin);
        //find the Vertex on the part
        void EdgeToOctree(vector<CEdge> VectorEdge
                ,vector<CVertex> VectorPoint
                ,float xmax,float xmin
                ,float ymax,float ymin
                ,float zmax,float zmin);
        //Change a single edge into voxel
        void EdgeChange(OctreePoint point1, OctreePoint point2);
        //find the Edge on the part
        void PerpendicularToSurfaceEdge(OctreePoint point1,OctreePoint point2, int serial);
        //find the special edge that is perpendicular to surface
        void ParallelToSurfaceEdge(OctreePoint point1, OctreePoint point2, int serial);
        //a1,a2 b1,b2 mean different point coordinate,c means the same coordinate of two point
        void GeneralLocationEdge(OctreePoint point1, OctreePoint point2);
        //use supercoverline to fullfill the inner place
        void SuperCoverLine(OctreePoint point1, OctreePoint point2);
        //find the special edge that is perpendicular to surface by using SuperCoverLine
        void ParallelToSurfaceEdgeSC(OctreePoint point1, OctreePoint point2, int serial);
        //deal with the general edge
        void FacetToOctree(vector<CFacet> VectorFacet
                ,vector<CVertex> VectorPoint
                ,float xmax,float xmin
                ,float ymax,float ymin
                ,float zmax,float zmin);
        //find the facet on the part
        void ChangePoint(string x,string y,string z);
        //change this node flag to 0
        string ChangeCoordinate(float coordinate,float max,float min);
        //change the coordinate into binary
        unsigned int ChangeToDecimal(string binary);
        //change the binary into deciaml
        string ChangeToBinary(unsigned int decimal);
        //change the decimal into binary
        float CheckDecimal(float num);
        //due to the max num, if num == pow(2,max_height-1), when we use "int" to decide the voxel of this point, it will be false
    private:
        OctreeNode *root;
        int max_height;
        vector<OctreePoint> m_OctreeEdge;
};
