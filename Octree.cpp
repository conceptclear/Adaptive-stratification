#include "Octree/Octree.h"
using namespace std;

void Octree::MakeOctree(int height)
{
    if(max_height<height)
        max_height = height;
    if(max_height<1)
        cerr<<"error input"<<endl;
    else if(max_height==1)
    {
        return;
    }
    else
    {
        string rootnum = root->orderstr;
        string rootnum0,rootnum1,rootnum2,rootnum3,rootnum4,rootnum5,rootnum6,rootnum7;
        rootnum0 = rootnum1 = rootnum2 = rootnum3 = rootnum4 = rootnum5 = rootnum6 = rootnum7 = rootnum;
        rootnum0.insert(rootnum0.end(),'0');
        rootnum1.insert(rootnum1.end(),'1');
        rootnum2.insert(rootnum2.end(),'2');
        rootnum3.insert(rootnum3.end(),'3');
        rootnum4.insert(rootnum4.end(),'4');
        rootnum5.insert(rootnum5.end(),'5');
        rootnum6.insert(rootnum6.end(),'6');
        rootnum7.insert(rootnum7.end(),'7');
        Octree* back_left_bottom =new Octree(rootnum0);
        Octree* back_left_top =new Octree(rootnum1);
        Octree* back_right_bottom =new Octree(rootnum2);
        Octree* back_right_top =new Octree(rootnum3);
        Octree* front_left_bottom =new Octree(rootnum4);
        Octree* front_left_top =new Octree(rootnum5);
        Octree* front_right_bottom =new Octree(rootnum6);
        Octree* front_right_top =new Octree(rootnum7);
        root->Back_Left_Bottom = back_left_bottom->root;
        root->Back_Left_Top = back_left_top->root;
        root->Back_Right_Bottom = back_right_bottom->root;
        root->Back_Right_Top = back_right_top->root;
        root->Front_Left_Bottom = front_left_bottom->root;
        root->Front_Left_Top = front_left_top->root;
        root->Front_Right_Bottom = front_right_bottom->root;
        root->Front_Right_Top = front_right_top->root;
        back_left_bottom->MakeOctree(height-1);
        back_left_top->MakeOctree(height-1);
        back_right_bottom->MakeOctree(height-1);
        back_right_top->MakeOctree(height-1);
        front_left_bottom->MakeOctree(height-1);
        front_left_top->MakeOctree(height-1);
        front_right_bottom->MakeOctree(height-1);
        front_right_top->MakeOctree(height-1);
    }
}

void Octree::DeleteRoot(OctreeNode *pRoot)
{
    if(pRoot==NULL)
        return;
    OctreeNode* back_left_bottom = pRoot->Back_Left_Bottom;
    OctreeNode* back_left_top = pRoot->Back_Left_Top;
    OctreeNode* back_right_bottom = pRoot->Back_Right_Bottom;
    OctreeNode* back_right_top = pRoot->Back_Right_Top;
    OctreeNode* front_left_bottom = pRoot->Front_Left_Bottom;
    OctreeNode* front_left_top = pRoot->Front_Left_Top;
    OctreeNode* front_right_bottom = pRoot->Front_Right_Bottom;
    OctreeNode* front_right_top = pRoot->Front_Right_Top;

    //    cout<<pRoot->orderstr<<endl;

    delete pRoot;
    if(back_left_bottom!=NULL)DeleteRoot(back_left_bottom);
    if(back_left_top!=NULL)DeleteRoot(back_left_top);
    if(back_right_bottom!=NULL)DeleteRoot(back_right_bottom);
    if(back_right_top!=NULL)DeleteRoot(back_right_top);
    if(front_left_bottom!=NULL)DeleteRoot(front_left_bottom);
    if(front_left_top!=NULL)DeleteRoot(front_left_top);
    if(front_right_bottom!=NULL)DeleteRoot(front_right_bottom);
    if(front_right_top!=NULL)DeleteRoot(front_right_top);
    return;
}

void Octree::PointToOctree(vector<CVertex> VectorPoint,float xmax,float xmin,float ymax,float ymin,float zmax,float zmin)
{
    for(int i=0;i<int(VectorPoint.size());i++)
    {
        string binaryx = ChangeCoordinate(VectorPoint[i].m_Point[0],xmax,xmin);
        string binaryy = ChangeCoordinate(VectorPoint[i].m_Point[1],ymax,ymin);
        string binaryz = ChangeCoordinate(VectorPoint[i].m_Point[2],zmax,zmin);
        //        cout<<binaryx<<binaryy<<binaryz<<endl;
        ChangePoint(binaryx,binaryy,binaryz);
    }

}

void Octree::ChangePoint(string x,string y,string z)
{
    OctreeNode* node =root; 
    for(int j=0;j<max_height-1;j++)
    {
        int position=int(x[j]-48)*4+int(y[j]-48)*2+int(z[j]-48);
        //            cout<<position<<endl;
        switch(position)
        {
            case 0:
                node=node->Back_Left_Bottom;
                break;
            case 1:
                node=node->Back_Left_Top;
                break;
            case 2:
                node=node->Back_Right_Bottom;
                break;
            case 3:
                node=node->Back_Right_Top;
                break;
            case 4:
                node=node->Front_Left_Bottom;
                break;
            case 5:
                node=node->Front_Left_Top;
                break;
            case 6:
                node=node->Front_Right_Bottom;
                break;
            case 7:
                node=node->Front_Right_Top;
                break;
            default:
                cerr<<"error"<<endl;
                break;
        }
    }
    node->flag=0;
    //            cout<<node->orderstr<<endl;
}

string Octree::ChangeCoordinate(float coordinate,float max,float min)
{
    unsigned int data = (coordinate-min)*pow(2,max_height-1)/(max-min);
    //    cout<<data<<endl;
    string output;
    output=ChangeToBinary(data);
    return output;
}

string Octree::ChangeToBinary(unsigned int decimal)
{
    string output;
    output="";
    decimal = CheckDecimal(decimal);
    for(int count=max_height-1;count--;decimal=decimal/2)
    {
        output=output+(decimal%2?"1":"0");
    }
    reverse(output.begin(),output.end());
    //    cout<<output<<endl;
    return output;
}

unsigned int Octree::ChangeToDecimal(string binary)
{
    int output = 0;
    for(int i=0;i<int(binary.length());i++)
    {
        output=2*output+int(binary[i])-48;
    }
    return output;
}

float Octree::CheckDecimal(float num)
{
    if(num==pow(2,max_height-1))
        num--;
    return num;
}

void Octree::Traverse(void)
{
    PreOrder(root);
}

void Octree::PreOrder(OctreeNode *pRoot)
{
    if(pRoot!=NULL)
    {
        DisplayOctree(pRoot);
        PreOrder(pRoot->Back_Left_Bottom);
        PreOrder(pRoot->Back_Left_Top);
        PreOrder(pRoot->Back_Right_Bottom);
        PreOrder(pRoot->Back_Right_Top);
        PreOrder(pRoot->Front_Left_Bottom);
        PreOrder(pRoot->Front_Left_Top);
        PreOrder(pRoot->Front_Right_Bottom);
        PreOrder(pRoot->Front_Right_Top);
    }
}

void Octree::DisplayOctree(OctreeNode *pRoot)
{
    if(int(pRoot->orderstr.length())!=max_height)
        return;
    if(pRoot->flag!=0)
        return;
    else
    {
        string x="";
        string y="";
        string z="";
        for(int i=0;i<max_height;i++)
        {
            int data = int(pRoot->orderstr[i])-48;
            z+=(data%2?"1":"0");
            data=data/2;
            y+=(data%2?"1":"0");
            data=data/2;
            x+=(data%2?"1":"0");
        }
        //        cout<<x<<endl;
        //        cout<<y<<endl;
        //        cout<<z<<endl;
        //        cout<<pRoot->orderstr<<endl;
        DrawVoxel(x,y,z);
    }
}

void Octree::DrawVoxel(string x,string y,string z)
{
    unsigned int voxelx,voxely,voxelz;
    voxelx=voxely=voxelz=0;
    voxelx=ChangeToDecimal(x);
    voxely=ChangeToDecimal(y);
    voxelz=ChangeToDecimal(z);
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3i(voxelx,voxely,voxelz);
    glVertex3i(voxelx+1,voxely,voxelz);
    glVertex3i(voxelx+1,voxely+1,voxelz);
    glVertex3i(voxelx,voxely+1,voxelz);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3i(voxelx,voxely,voxelz+1);
    glVertex3i(voxelx+1,voxely,voxelz+1);
    glVertex3i(voxelx+1,voxely+1,voxelz+1);
    glVertex3i(voxelx,voxely+1,voxelz+1);
    glEnd();
    glBegin(GL_LINES);
    glVertex3i(voxelx,voxely,voxelz);
    glVertex3i(voxelx,voxely,voxelz+1);
    glEnd();
    glBegin(GL_LINES);
    glVertex3i(voxelx+1,voxely,voxelz);
    glVertex3i(voxelx+1,voxely,voxelz+1);
    glEnd();
    glBegin(GL_LINES);
    glVertex3i(voxelx+1,voxely+1,voxelz);
    glVertex3i(voxelx+1,voxely+1,voxelz+1);
    glEnd();
    glBegin(GL_LINES);
    glVertex3i(voxelx,voxely+1,voxelz);
    glVertex3i(voxelx,voxely+1,voxelz+1);
    glEnd();
    glColor3f(0.0f,1.0f,1.0f);
    glBegin(GL_POLYGON);
    glVertex3i(voxelx,voxely,voxelz);
    glVertex3i(voxelx+1,voxely,voxelz);
    glVertex3i(voxelx+1,voxely+1,voxelz);
    glVertex3i(voxelx,voxely+1,voxelz);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3i(voxelx,voxely,voxelz+1);
    glVertex3i(voxelx+1,voxely,voxelz+1);
    glVertex3i(voxelx+1,voxely+1,voxelz+1);
    glVertex3i(voxelx,voxely+1,voxelz+1);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3i(voxelx,voxely,voxelz);
    glVertex3i(voxelx,voxely,voxelz+1);
    glVertex3i(voxelx+1,voxely,voxelz+1);
    glVertex3i(voxelx+1,voxely,voxelz);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3i(voxelx+1,voxely+1,voxelz);
    glVertex3i(voxelx+1,voxely+1,voxelz+1);
    glVertex3i(voxelx,voxely+1,voxelz+1);
    glVertex3i(voxelx,voxely+1,voxelz);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3i(voxelx+1,voxely+1,voxelz);
    glVertex3i(voxelx+1,voxely+1,voxelz+1);
    glVertex3i(voxelx+1,voxely,voxelz+1);
    glVertex3i(voxelx+1,voxely,voxelz);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3i(voxelx,voxely+1,voxelz);
    glVertex3i(voxelx,voxely+1,voxelz+1);
    glVertex3i(voxelx,voxely,voxelz+1);
    glVertex3i(voxelx,voxely,voxelz);
    glEnd();
    //    cout<<voxelx<<":"<<voxely<<":"<<voxelz<<endl;
}

void Octree::EdgeToOctree(vector<CEdge> VectorEdge, vector<CVertex> VectorPoint,float xmax,float xmin,float ymax,float ymin,float zmax,float zmin)
{
    for(int i=0;i<int(VectorEdge.size());i++)
    {
        //change the coordinate system
        float flx1 = (VectorPoint[VectorEdge[i].PointIndex[0]].m_Point[0]-xmin)*pow(2,max_height-1)/(xmax-xmin);
        float flx2 = (VectorPoint[VectorEdge[i].PointIndex[1]].m_Point[0]-xmin)*pow(2,max_height-1)/(xmax-xmin);
        float fly1 = (VectorPoint[VectorEdge[i].PointIndex[0]].m_Point[1]-ymin)*pow(2,max_height-1)/(ymax-ymin);
        float fly2 = (VectorPoint[VectorEdge[i].PointIndex[1]].m_Point[1]-ymin)*pow(2,max_height-1)/(ymax-ymin);
        float flz1 = (VectorPoint[VectorEdge[i].PointIndex[0]].m_Point[2]-zmin)*pow(2,max_height-1)/(zmax-zmin);
        float flz2 = (VectorPoint[VectorEdge[i].PointIndex[1]].m_Point[2]-zmin)*pow(2,max_height-1)/(zmax-zmin);
        // to find the special Edge which is perpendicular to the coordinate surface
        OctreePoint point1(flx1,fly1,flz1);
        OctreePoint point2(flx2,fly2,flz2);
        EdgeChange(point1,point2);
    }
}

void Octree::EdgeChange(OctreePoint point1,OctreePoint point2)
{
    string strx1 = ChangeToBinary(point1.x);
    string strx2 = ChangeToBinary(point2.x);
    string stry1 = ChangeToBinary(point1.y);
    string stry2 = ChangeToBinary(point2.y);
    string strz1 = ChangeToBinary(point1.z);
    string strz2 = ChangeToBinary(point2.z);
    if((strx1==strx2)&&(stry1==stry2)&&(strz1==strz2))return;
    if((strx1==strx2)&&(stry1==stry2))
        PerpendicularToSurfaceEdge(point1,point2,3);
    else if((stry1==stry2)&&(strz1==strz2))
        PerpendicularToSurfaceEdge(point1,point2,1);
    else if((strx1==strx2)&&(strz1==strz2))
        PerpendicularToSurfaceEdge(point1,point2,2);
    else if(strx1==strx2)
        ParallelToSurfaceEdge(point1,point2,1);
    else if(stry1==stry2)
        ParallelToSurfaceEdge(point1,point2,2);
    else if(strz1==strz2)
        ParallelToSurfaceEdge(point1,point2,3);
    else
        GeneralLocationEdge(point1,point2);
}

void Octree::PerpendicularToSurfaceEdge(OctreePoint point1,OctreePoint point2, int serial)
{
    m_OctreeEdge.clear();
    float diffx=point1.x-point2.x;
    float diffy=point1.y-point2.y;
    float diffz=point1.z-point2.z;
    int sign_x = diffx>0?1:-1;
    int sign_y = diffy>0?1:-1;
    int sign_z = diffz>0?1:-1;
    string xi = ChangeToBinary(point2.x);
    string yi = ChangeToBinary(point2.y);
    string zi = ChangeToBinary(point2.z);
    OctreePoint opoint(point2);
    int nummax,nummin;
    switch(serial)
    {
        case 1:
            {
                nummax=diffx>0?point1.x:point2.x;
                nummin=diffx>0?point2.x:point1.x;
                nummax=CheckDecimal(nummax);
                for(int i = nummin+1;i<nummax;i++)
                {
                    xi = ChangeToBinary(i);
                    ChangePoint(xi,yi,zi);
                    opoint.x += sign_x;
                    opoint.y += sign_y*abs(diffy/diffx);
                    opoint.z += sign_z*abs(diffz/diffx);
                    m_OctreeEdge.push_back(opoint);
                }
            }
            break;
        case 2:
            {
                nummax=diffy>0?point1.y:point2.y;
                nummin=diffy>0?point2.y:point1.y;
                nummax=CheckDecimal(nummax);
                for(int i = nummin+1;i<nummax;i++)
                {
                    yi = ChangeToBinary(i);
                    ChangePoint(xi,yi,zi);
                    opoint.x += sign_x*abs(diffx/diffy);
                    opoint.y += sign_y;
                    opoint.z += sign_z*abs(diffz/diffy);
                    m_OctreeEdge.push_back(opoint);
                }
            }
            break;
        case 3:
            {
                nummax=diffz>0?point1.z:point2.z;
                nummin=diffz>0?point2.z:point1.z;
                nummax=CheckDecimal(nummax);
                for(int i = nummin+1;i<nummax;i++)
                {
                    zi = ChangeToBinary(i);
                    ChangePoint(xi,yi,zi);
                    opoint.x += sign_x*abs(diffx/diffz);
                    opoint.y += sign_y*abs(diffy/diffz);
                    opoint.z += sign_z;
                    m_OctreeEdge.push_back(opoint);
                }
            }
            break;
        default:
            cout<<"error in PerpendicularToSurfaceEdge"<<endl;
            break;
    }
}

void Octree::ParallelToSurfaceEdge(OctreePoint point1, OctreePoint point2, int serial)
{
    m_OctreeEdge.clear();
    float diffx = point1.x-point2.x;
    float diffy = point1.y-point2.y;
    float diffz = point1.z-point2.z;
    int sign_x = diffx>0?1:-1;
    int sign_y = diffy>0?1:-1;
    int sign_z = diffz>0?1:-1;
    string strx = ChangeToBinary(point2.x);
    string stry = ChangeToBinary(point2.y);
    string strz = ChangeToBinary(point2.z);
    OctreePoint opoint(point2);
    //choose 0.5 position to decide 
    switch(serial)
    {
        case 1:
            {
                if(abs(diffy)>=abs(diffz))
                {
                    opoint.y = CheckDecimal(opoint.y);
                    opoint.y = diffy>0?(floor(opoint.y)+1.5):(floor(opoint.y)-0.5);
                    opoint.z = diffz/diffy*(opoint.y-point2.y)+point2.z;
                    opoint.x = diffx/diffy*(opoint.y-point2.y)+point2.x;
                    while(opoint.y!=(floor(CheckDecimal(point1.y))+0.5))
                    {
                        m_OctreeEdge.push_back(opoint);
                        stry=ChangeToBinary(opoint.y);
                        strz=ChangeToBinary(opoint.z);
                        ChangePoint(strx,stry,strz);
                        opoint.y+=sign_y;
                        opoint.z+=sign_z*abs(diffz/diffy);
                        opoint.x+=sign_x*abs(diffx/diffy);
                    }
                }
                else
                {
                    opoint.z = CheckDecimal(opoint.z);
                    opoint.z = diffz>0?(floor(opoint.z)+1.5):(floor(opoint.z)-0.5);
                    opoint.y = diffy/diffz*(opoint.z-point2.z)+point2.y;
                    opoint.x = diffx/diffz*(opoint.z-point2.z)+point2.x;
                    while(opoint.z!=(floor(CheckDecimal(point1.z))+0.5))
                    {
                        m_OctreeEdge.push_back(opoint);
                        stry=ChangeToBinary(opoint.y);
                        strz=ChangeToBinary(opoint.z);
                        ChangePoint(strx,stry,strz);
                        opoint.y+=sign_y*abs(diffy/diffz);
                        opoint.z+=sign_z;
                        opoint.x+=sign_x*abs(diffx/diffz);
                    }
                }
            }
            break;
        case 2:
            {
                if(abs(diffx)>=abs(diffz))
                {
                    opoint.x = CheckDecimal(opoint.x);
                    opoint.x = diffx>0?(floor(opoint.x)+1.5):(floor(opoint.x)-0.5);
                    opoint.z = diffz/diffx*(opoint.x-point2.x)+point2.z;
                    opoint.y = diffy/diffx*(opoint.x-point2.x)+point2.y;
                    while(opoint.x!=(floor(CheckDecimal(point1.x))+0.5))
                    {
                        m_OctreeEdge.push_back(opoint);
                        strx=ChangeToBinary(opoint.x);
                        strz=ChangeToBinary(opoint.z);
                        ChangePoint(strx,stry,strz);
                        opoint.y+=sign_y*abs(diffy/diffx);
                        opoint.z+=sign_z*abs(diffz/diffx);
                        opoint.x+=sign_x;
                    }
                }
                else
                {
                    opoint.z = CheckDecimal(opoint.z);
                    opoint.z = diffz>0?(floor(opoint.z)+1.5):(floor(opoint.z)-0.5);
                    opoint.y = diffy/diffz*(opoint.z-point2.z)+point2.y;
                    opoint.x = diffx/diffz*(opoint.z-point2.z)+point2.x;
                    while(opoint.z!=(floor(CheckDecimal(point1.z))+0.5))
                    {
                        m_OctreeEdge.push_back(opoint);
                        strx=ChangeToBinary(opoint.x);
                        strz=ChangeToBinary(opoint.z);
                        ChangePoint(strx,stry,strz);
                        opoint.y+=sign_y*abs(diffy/diffz);
                        opoint.z+=sign_z;
                        opoint.x+=sign_x*abs(diffx/diffz);
                    }
                }
            }
            break;
        case 3:
            {
                if(abs(diffy)>=abs(diffx))
                {
                    opoint.y = CheckDecimal(opoint.y);
                    opoint.y = diffy>0?(floor(opoint.y)+1.5):(floor(opoint.y)-0.5);
                    opoint.z = diffz/diffy*(opoint.y-point2.y)+point2.z;
                    opoint.x = diffx/diffy*(opoint.y-point2.y)+point2.x;
                    while(opoint.y!=(floor(CheckDecimal(point1.y))+0.5))
                    {
                        m_OctreeEdge.push_back(opoint);
                        stry=ChangeToBinary(opoint.y);
                        strx=ChangeToBinary(opoint.x);
                        ChangePoint(strx,stry,strz);
                        opoint.y+=sign_y;
                        opoint.z+=sign_z*abs(diffz/diffy);
                        opoint.x+=sign_x*abs(diffx/diffy);
                    }
                }
                else
                {
                    opoint.x = CheckDecimal(opoint.x);
                    opoint.x = diffx>0?(floor(opoint.x)+1.5):(floor(opoint.x)-0.5);
                    opoint.z = diffz/diffx*(opoint.x-point2.x)+point2.z;
                    opoint.y = diffy/diffx*(opoint.x-point2.x)+point2.y;
                    while(opoint.x!=(floor(CheckDecimal(point1.x))+0.5))
                    {
                        m_OctreeEdge.push_back(opoint);
                        strx=ChangeToBinary(opoint.x);
                        stry=ChangeToBinary(opoint.y);
                        ChangePoint(strx,stry,strz);
                        opoint.y+=sign_y*abs(diffy/diffx);
                        opoint.z+=sign_z*abs(diffz/diffx);
                        opoint.x+=sign_x;
                    }
                }
            }
            break;
        default:
            cout<<"error occured in ParallelToSurfaceEdge"<<endl;
            break;
    }
}

void Octree::GeneralLocationEdge(OctreePoint point1, OctreePoint point2)
{
    m_OctreeEdge.clear();
    float diffx = point1.x-point2.x;
    float diffy = point1.y-point2.y;
    float diffz = point1.z-point2.z;
    int sign_x = diffx>0?1:-1;
    int sign_y = diffy>0?1:-1;
    int sign_z = diffz>0?1:-1;
    string strx = ChangeToBinary(point2.x);
    string stry = ChangeToBinary(point2.y);
    string strz = ChangeToBinary(point2.z);
    OctreePoint opoint(point2);
    float diffmax=max((abs(diffx),abs(diffy)),abs(diffz));
    if(diffmax==abs(diffx))
    {
        opoint.x = CheckDecimal(opoint.x);
        opoint.x = diffx>0?(floor(opoint.x)+1.5):(floor(opoint.x)-0.5);
        opoint.z = diffz/diffx*(opoint.x-point2.x)+point2.z;
        opoint.y = diffy/diffx*(opoint.x-point2.x)+point2.y;
        while(opoint.x!=(floor(CheckDecimal(point1.x))+0.5))
        {
            m_OctreeEdge.push_back(opoint);
            strx=ChangeToBinary(opoint.x);
            stry=ChangeToBinary(opoint.y);
            strz=ChangeToBinary(opoint.z);
            ChangePoint(strx,stry,strz);
            opoint.y+=sign_y*abs(diffy/diffx);
            opoint.z+=sign_z*abs(diffz/diffx);
            opoint.x+=sign_x;
        }
    }
    else if(diffmax==abs(diffy))
    {
        opoint.y = CheckDecimal(opoint.y);
        opoint.y = diffy>0?(floor(opoint.y)+1.5):(floor(opoint.y)-0.5);
        opoint.z = diffz/diffy*(opoint.y-point2.y)+point2.z;
        opoint.x = diffx/diffy*(opoint.y-point2.y)+point2.x;
        while(opoint.y!=(floor(CheckDecimal(point1.y))+0.5))
        {
            m_OctreeEdge.push_back(opoint);
            stry=ChangeToBinary(opoint.y);
            strx=ChangeToBinary(opoint.x);
            strz=ChangeToBinary(opoint.z);
            ChangePoint(strx,stry,strz);
            opoint.y+=sign_y;
            opoint.z+=sign_z*abs(diffz/diffy);
            opoint.x+=sign_x*abs(diffx/diffy);
        }
    }
    else
    {
        opoint.z = CheckDecimal(opoint.z);
        opoint.z = diffz>0?(floor(opoint.z)+1.5):(floor(opoint.z)-0.5);
        opoint.y = diffy/diffz*(opoint.z-point2.z)+point2.y;
        opoint.x = diffx/diffz*(opoint.z-point2.z)+point2.x;
        while(opoint.z!=(floor(CheckDecimal(point1.z))+0.5))
        {
            m_OctreeEdge.push_back(opoint);
            strx=ChangeToBinary(opoint.x);
            stry=ChangeToBinary(opoint.y);
            strz=ChangeToBinary(opoint.z);
            ChangePoint(strx,stry,strz);
            opoint.y+=sign_y*abs(diffy/diffz);
            opoint.z+=sign_z;
            opoint.x+=sign_x*abs(diffx/diffz);
        }
    }
}

void Octree::SuperCoverLine(OctreePoint point1, OctreePoint point2)
{
    string strx1 = ChangeToBinary(point1.x);
    string strx2 = ChangeToBinary(point2.x);
    string stry1 = ChangeToBinary(point1.y);
    string stry2 = ChangeToBinary(point2.y);
    string strz1 = ChangeToBinary(point1.z);
    string strz2 = ChangeToBinary(point2.z);
    if((strx1==strx2)&&(stry1==stry2)&&(strz1==strz2))return;
    if((strx1==strx2)&&(stry1==stry2))
        PerpendicularToSurfaceEdge(point1,point2,3);
    else if((stry1==stry2)&&(strz1==strz2))
        PerpendicularToSurfaceEdge(point1,point2,1);
    else if((strx1==strx2)&&(strz1==strz2))
        PerpendicularToSurfaceEdge(point1,point2,2);
    else if(strx1==strx2)
        ParallelToSurfaceEdgeSC(point1,point2,1);
    else if(stry1==stry2)
        ParallelToSurfaceEdgeSC(point1,point2,2);
    else if(strz1==strz2)
        ParallelToSurfaceEdgeSC(point1,point2,3);
}


void Octree::FacetToOctree(vector<CFacet> VectorFacet, vector <CVertex> VectorPoint,float xmax, float xmin, float ymax, float ymin, float zmax, float zmin)
{
    for(int i=0;i<int(VectorFacet.size());i++)
    {
        //change the coordinate system
        float flx1 = (VectorPoint[VectorFacet[i].PointIndex[0]].m_Point[0]-xmin)*pow(2,max_height-1)/(xmax-xmin);
        float flx2 = (VectorPoint[VectorFacet[i].PointIndex[1]].m_Point[0]-xmin)*pow(2,max_height-1)/(xmax-xmin);
        float flx3 = (VectorPoint[VectorFacet[i].PointIndex[2]].m_Point[0]-xmin)*pow(2,max_height-1)/(xmax-xmin);
        float fly1 = (VectorPoint[VectorFacet[i].PointIndex[0]].m_Point[1]-ymin)*pow(2,max_height-1)/(ymax-ymin);
        float fly2 = (VectorPoint[VectorFacet[i].PointIndex[1]].m_Point[1]-ymin)*pow(2,max_height-1)/(ymax-ymin);
        float fly3 = (VectorPoint[VectorFacet[i].PointIndex[2]].m_Point[1]-ymin)*pow(2,max_height-1)/(ymax-ymin);
        float flz1 = (VectorPoint[VectorFacet[i].PointIndex[0]].m_Point[2]-zmin)*pow(2,max_height-1)/(zmax-zmin);
        float flz2 = (VectorPoint[VectorFacet[i].PointIndex[1]].m_Point[2]-zmin)*pow(2,max_height-1)/(zmax-zmin);
        float flz3 = (VectorPoint[VectorFacet[i].PointIndex[2]].m_Point[2]-zmin)*pow(2,max_height-1)/(zmax-zmin);
        OctreePoint point1(flx1,fly1,flz1);
        OctreePoint point2(flx2,fly2,flz2);
        OctreePoint point3(flx3,fly3,flz3);
        //to voxelize one edge
        EdgeChange(point1,point2);
        vector<OctreePoint> OctreeEdge = m_OctreeEdge;
        //exist bug
        //here we need to use supercover line
        for(int j=0;j<int(OctreeEdge.size());j++)
        {
            OctreePoint opoint(OctreeEdge[j].x,OctreeEdge[j].y,OctreeEdge[j].z);
            SuperCoverLine(opoint,point3);
        }
        EdgeChange(point3,point2);
        EdgeChange(point1,point3);
    }
}

void Octree::ParallelToSurfaceEdgeSC(OctreePoint point1, OctreePoint point2, int serial)
{
    float diffx = point1.x-point2.x;
    float diffy = point1.y-point2.y;
    float diffz = point1.z-point2.z;
    int sign_x = diffx>0?1:-1;
    int sign_y = diffy>0?1:-1;
    int sign_z = diffz>0?1:-1;
    string strx = ChangeToBinary(point2.x);
    string stry = ChangeToBinary(point2.y);
    string strz = ChangeToBinary(point2.z);
    OctreePoint opoint(point2);
    //find the every intersection of the long side 
    switch(serial)
    {
        case 1:
            {
                if(abs(diffy)>=abs(diffz))
                {
                    opoint.y = CheckDecimal(opoint.y);
                    opoint.y = diffy>0?(floor(opoint.y)+1):(floor(opoint.y));
                    opoint.z = diffz/diffy*(opoint.y-point2.y)+point2.z;
                    float flag = diffy<=0?(floor(point1.y)+1):(floor(point1.y));
                    while(opoint.y!=flag)
                    {
                        stry=ChangeToBinary(opoint.y-1);
                        strz=ChangeToBinary(opoint.z);
                        ChangePoint(strx,stry,strz);
                        stry=ChangeToBinary(opoint.y);
                        ChangePoint(strx,stry,strz);
                        if(opoint.z-floor(opoint.z)==0)
                        {
                            strz=ChangeToBinary(opoint.z-1);
                            ChangePoint(strx,stry,strz);
                            stry=ChangeToBinary(opoint.y-1);
                            ChangePoint(strx,stry,strz);
                        }    
                        opoint.y+=sign_y;
                        opoint.z+=sign_z*abs(diffz/diffy);
                    }
                }
                else
                {
                    opoint.z = CheckDecimal(opoint.z);
                    opoint.z = diffz>0?(floor(opoint.z)+1):(floor(opoint.z));
                    opoint.y = diffy/diffz*(opoint.z-point2.z)+point2.y;
                    float flag = diffz<=0?(floor(point1.z)+1):(floor(point1.z));
                    while(opoint.z!=flag)
                    {
                        strz=ChangeToBinary(opoint.z-1);
                        stry=ChangeToBinary(opoint.y);
                        ChangePoint(strx,stry,strz);
                        strz=ChangeToBinary(opoint.z);
                        ChangePoint(strx,stry,strz);
                        if(opoint.y-floor(opoint.y)==0)
                        {
                            stry=ChangeToBinary(opoint.y-1);
                            ChangePoint(strx,stry,strz);
                            strz=ChangeToBinary(opoint.z-1);
                            ChangePoint(strx,stry,strz);
                        }    
                        opoint.z+=sign_z;
                        opoint.y+=sign_y*abs(diffy/diffz);
                    }
                }
            }
            break;
        case 2:
            {
                if(abs(diffx)>=abs(diffz))
                {
                    opoint.x = CheckDecimal(opoint.x);
                    opoint.x = diffx>0?(floor(opoint.x)+1):(floor(opoint.x));
                    opoint.z = diffz/diffx*(opoint.x-point2.x)+point2.z;
                    float flag = diffx<=0?(floor(point1.x)+1):(floor(point1.x));
                    while(opoint.x!=flag)
                    {
                        strx=ChangeToBinary(opoint.x-1);
                        strz=ChangeToBinary(opoint.z);
                        ChangePoint(strx,stry,strz);
                        strx=ChangeToBinary(opoint.x);
                        ChangePoint(strx,stry,strz);
                        if(opoint.z-floor(opoint.z)==0)
                        {
                            strz=ChangeToBinary(opoint.z-1);
                            ChangePoint(strx,stry,strz);
                            strx=ChangeToBinary(opoint.x-1);
                            ChangePoint(strx,stry,strz);
                        }    
                        opoint.x+=sign_x;
                        opoint.z+=sign_z*abs(diffz/diffx);
                    }
                }
                else
                {
                    opoint.z = CheckDecimal(opoint.z);
                    opoint.z = diffz>0?(floor(opoint.z)+1):(floor(opoint.z));
                    opoint.x = diffx/diffz*(opoint.z-point2.z)+point2.x;
                    float flag = diffz<=0?(floor(point1.z)+1):(floor(point1.z));
                    while(opoint.z!=flag)
                    {
                        strz=ChangeToBinary(opoint.z-1);
                        strx=ChangeToBinary(opoint.x);
                        ChangePoint(strx,stry,strz);
                        strz=ChangeToBinary(opoint.z);
                        ChangePoint(strx,stry,strz);
                        if(opoint.x-floor(opoint.x)==0)
                        {
                            strx=ChangeToBinary(opoint.x-1);
                            ChangePoint(strx,stry,strz);
                            strz=ChangeToBinary(opoint.z-1);
                            ChangePoint(strx,stry,strz);
                        }    
                        opoint.z+=sign_z;
                        opoint.x+=sign_x*abs(diffx/diffz);
                    }
                }
            }
            break;
        case 3:
            {
                if(abs(diffx)>=abs(diffy))
                {
                    opoint.x = CheckDecimal(opoint.x);
                    opoint.x = diffx>0?(floor(opoint.x)+1):(floor(opoint.x));
                    opoint.y = diffy/diffx*(opoint.x-point2.x)+point2.y;
                    float flag = diffx<=0?(floor(point1.x)+1):(floor(point1.x));
                    while(opoint.x!=flag)
                    {
                        strx=ChangeToBinary(opoint.x-1);
                        stry=ChangeToBinary(opoint.y);
                        ChangePoint(strx,stry,strz);
                        strx=ChangeToBinary(opoint.x);
                        ChangePoint(strx,stry,strz);
                        if(opoint.y-floor(opoint.y)==0)
                        {
                            stry=ChangeToBinary(opoint.y-1);
                            ChangePoint(strx,stry,strz);
                            strx=ChangeToBinary(opoint.x-1);
                            ChangePoint(strx,stry,strz);
                        }    
                        opoint.x+=sign_x;
                        opoint.y+=sign_y*abs(diffy/diffx);
                    }
                }
                else
                {
                    opoint.y = CheckDecimal(opoint.y);
                    opoint.y = diffy>0?(floor(opoint.y)+1):(floor(opoint.y));
                    opoint.x = diffx/diffy*(opoint.y-point2.y)+point2.x;
                    float flag = diffy<=0?(floor(point1.y)+1):(floor(point1.y));
                    while(opoint.y!=flag)
                    {
                        stry=ChangeToBinary(opoint.y-1);
                        strx=ChangeToBinary(opoint.x);
                        ChangePoint(strx,stry,strz);
                        stry=ChangeToBinary(opoint.y);
                        ChangePoint(strx,stry,strz);
                        if(opoint.x-floor(opoint.x)==0)
                        {
                            strx=ChangeToBinary(opoint.x-1);
                            ChangePoint(strx,stry,strz);
                            stry=ChangeToBinary(opoint.y-1);
                            ChangePoint(strx,stry,strz);
                        }    
                        opoint.y+=sign_y;
                        opoint.x+=sign_x*abs(diffx/diffy);
                    }
                }
            }
            break;
        default:
            cout<<"error occured in ParallelToSurfaceEdgeSC"<<endl;
            break;
    }
}
