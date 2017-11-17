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
    if (data==pow(2,max_height-1))data--;
//    cout<<data<<endl;
    string output;
    output=ChangeToBinary(data);
    return output;
}

string Octree::ChangeToBinary(unsigned int decimal)
{
    string output;
    output="";
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
//    cout<<voxelx<<":"<<voxely<<":"<<voxelz<<endl;
}

void Octree::EdgeToOctree(vector<CEdge> VectorEdge, vector<CVertex> VectorPoint,float xmax,float xmin,float ymax,float ymin,float zmax,float zmin)
{
    for(int i=0;i<int(VectorEdge.size());i++)
    {
        // it is not necessary to calculate the exact coordinate. The line between the voxel of the two point perpendicular can be special
        string strx1 = ChangeCoordinate(VectorPoint[VectorEdge[i].PointIndex[0]].m_Point[0],xmax,xmin);
        string strx2 = ChangeCoordinate(VectorPoint[VectorEdge[i].PointIndex[1]].m_Point[0],xmax,xmin);
        string stry1 = ChangeCoordinate(VectorPoint[VectorEdge[i].PointIndex[0]].m_Point[1],ymax,ymin);
        string stry2 = ChangeCoordinate(VectorPoint[VectorEdge[i].PointIndex[1]].m_Point[1],ymax,ymin);
        string strz1 = ChangeCoordinate(VectorPoint[VectorEdge[i].PointIndex[0]].m_Point[2],zmax,zmin);
        string strz2 = ChangeCoordinate(VectorPoint[VectorEdge[i].PointIndex[1]].m_Point[2],zmax,zmin);
        //change the coordinate system
        float flx1 = (VectorPoint[VectorEdge[i].PointIndex[0]].m_Point[0]-xmin)*pow(2,max_height-1)/(xmax-xmin);
        float flx2 = (VectorPoint[VectorEdge[i].PointIndex[1]].m_Point[0]-xmin)*pow(2,max_height-1)/(xmax-xmin);
        float fly1 = (VectorPoint[VectorEdge[i].PointIndex[0]].m_Point[1]-ymin)*pow(2,max_height-1)/(ymax-ymin);
        float fly2 = (VectorPoint[VectorEdge[i].PointIndex[1]].m_Point[1]-ymin)*pow(2,max_height-1)/(ymax-ymin);
        float flz1 = (VectorPoint[VectorEdge[i].PointIndex[0]].m_Point[2]-zmin)*pow(2,max_height-1)/(zmax-zmin);
        float flz2 = (VectorPoint[VectorEdge[i].PointIndex[1]].m_Point[2]-zmin)*pow(2,max_height-1)/(zmax-zmin);
        // to find the special Edge which is perpendicular to the coordinate surface
        EdgeChange(strx1,strx2,stry1,stry2,strz1,strz2,flx1,flx2,fly1,fly2,flz1,flz2);
    }
}

void Octree::EdgeChange(string strx1,string strx2
                ,string stry1,string stry2
                ,string strz1,string strz2,
                float flx1,float flx2,
                float fly1,float fly2,
                float flz1,float flz2)
{
        if((strx1==strx2)&&(stry1==stry2)&&(strz1==strz2))return;
        if((strx1==strx2)&&(stry1==stry2))
            PerpendicularToSurfaceEdge(strx1,stry1,strz1,strz2,3);
        else if((stry1==stry2)&&(strz1==strz2))
            PerpendicularToSurfaceEdge(strx1,stry1,strz1,strx2,1);
        else if((strx1==strx2)&&(strz1==strz2))
            PerpendicularToSurfaceEdge(strx1,stry1,strz1,stry2,2);
        else if(strx1==strx2)
            ParallelToSurfaceEdge(fly1,fly2,flz1,flz2,strx1,1);
        else if(stry1==stry2)
            ParallelToSurfaceEdge(flx1,flx2,flz1,flz2,stry1,2);
        else if(strz1==strz2)
            ParallelToSurfaceEdge(flx1,flx2,fly1,fly2,strz1,3);
        else
            GeneralLocationEdge(flx1,flx2,fly1,fly2,flz1,flz2);
}

void Octree::PerpendicularToSurfaceEdge(string x,string y,string z,string diff,int serial)
{
    m_OctreeEdge.clear();
    switch(serial)
    {
        case 1:
            unsigned int xmax,xmin;
            xmin = xmax = ChangeToDecimal(x);
            if(xmin>ChangeToDecimal(diff))
                xmin=ChangeToDecimal(diff);
            else
                xmax=ChangeToDecimal(diff);
            for(unsigned int i=xmin+1;i<xmax;i++)
            {
                string xi = ChangeToBinary(i);
                ChangePoint(xi,y,z);
                OctreePoint opoint;
                opoint.x=xi;
                opoint.y=y;
                opoint.z=z;
                m_OctreeEdge.push_back(opoint);
            }
            break;
        case 2:
            unsigned int ymax,ymin;
            ymin = ymax = ChangeToDecimal(y);
            if(ymin>ChangeToDecimal(diff))
                ymin=ChangeToDecimal(diff);
            else
                ymax=ChangeToDecimal(diff);
            for(unsigned int i=ymin+1;i<ymax;i++)
            {
                string yi = ChangeToBinary(i);
                ChangePoint(x,yi,z);
                OctreePoint opoint;
                opoint.x=x;
                opoint.y=yi;
                opoint.z=z;
                m_OctreeEdge.push_back(opoint);
            }
            break;
        case 3:
            unsigned int zmax,zmin;
            zmin = zmax = ChangeToDecimal(z);
            if(zmin>ChangeToDecimal(diff))
                zmin=ChangeToDecimal(diff);
            else
                zmax=ChangeToDecimal(diff);
            for(unsigned int i=zmin+1;i<zmax;i++)
            {
                string zi = ChangeToBinary(i);
                ChangePoint(x,y,zi);
                OctreePoint opoint;
                opoint.x=x;
                opoint.y=y;
                opoint.z=zi;
                m_OctreeEdge.push_back(opoint);
            }
            break;
        default:
            cout<<"error in PerpendicularToSurfaceEdge"<<endl;
            break;
    }
}

void Octree::ParallelToSurfaceEdge(float a1,float a2,float b1,float b2,string c,int serial)
{
    m_OctreeEdge.clear();
    float diffa = a1-a2;
    float diffb = b1-b2;
    //choose 0.5 position to decide 
    switch(serial)
    {
        case 1:
            if(abs(diffa)>=abs(diffb))
            {
                float k =diffb/diffa;
                int count=0;
                int ai=a1-diffa/abs(diffa);
                float bi = b1-diffb/abs(diffb)*abs(ai-a1+0.5)*abs(k);
                while(ai!=int(a2))
                {
                    string stra = ChangeToBinary(ai);
                    string strb = ChangeToBinary(bi+count*k);
                    ChangePoint(c,stra,strb);
                    OctreePoint opoint;
                    opoint.x=c;
                    opoint.y=stra;
                    opoint.z=strb;
                    m_OctreeEdge.push_back(opoint);
                    if(a1>a2)
                    {
                        ai--;
                        count--;
                    }
                    else
                    {
                        ai++;
                        count++;
                    }
                }
            }
            else
            {
                float k =diffa/diffb;
                int count=0;
                int bi=b1-diffb/abs(diffb);
                float ai = a1-diffa/abs(diffa)*abs(bi-b1+0.5)*abs(k);
                while(bi!=int(b2))
                {
                    string stra = ChangeToBinary(ai+count*k);
                    string strb = ChangeToBinary(bi);
                    ChangePoint(c,stra,strb);
                    OctreePoint opoint;
                    opoint.x=c;
                    opoint.y=stra;
                    opoint.z=strb;
                    m_OctreeEdge.push_back(opoint);
                    if(b1>b2)
                    {
                        bi--;
                        count--;
                    }
                    else
                    {
                        bi++;
                        count++;
                    }
                }
            }
            break;
        case 2:
            if(abs(diffa)>=abs(diffb))
            {
                float k =diffb/diffa;
                int count=0;
                int ai=a1-diffa/abs(diffa);
                float bi = b1-diffb/abs(diffb)*abs(ai-a1+0.5)*abs(k);
                while(ai!=int(a2))
                {
                    string stra = ChangeToBinary(ai);
                    string strb = ChangeToBinary(bi+count*k);
                    ChangePoint(stra,c,strb);
                    OctreePoint opoint;
                    opoint.x=stra;
                    opoint.y=c;
                    opoint.z=strb;
                    m_OctreeEdge.push_back(opoint);
                    if(a1>a2)
                    {
                        ai--;
                        count--;
                    }
                    else
                    {
                        ai++;
                        count++;
                    }
                }
            }
            else
            {
                float k =diffa/diffb;
                int count=0;
                int bi=b1-diffb/abs(diffb);
                float ai = a1-diffa/abs(diffa)*abs(bi-b1+0.5)*abs(k);
                while(bi!=int(b2))
                {
                    string stra = ChangeToBinary(ai+count*k);
                    string strb = ChangeToBinary(bi);
                    ChangePoint(stra,c,strb);
                    OctreePoint opoint;
                    opoint.x=stra;
                    opoint.y=c;
                    opoint.z=strb;
                    m_OctreeEdge.push_back(opoint);
                    if(b1>b2)
                    {
                        bi--;
                        count--;
                    }
                    else
                    {
                        bi++;
                        count++;
                    }
                }
            }
            break;
        case 3:
            if(abs(diffa)>=abs(diffb))
            {
                float k =diffb/diffa;
                int count=0;
                int ai=a1-diffa/abs(diffa);
                float bi = b1-diffb/abs(diffb)*abs(ai-a1+0.5)*abs(k);
                while(ai!=int(a2))
                {
                    string stra = ChangeToBinary(ai);
                    string strb = ChangeToBinary(bi+count*k);
                    ChangePoint(stra,strb,c);
                    OctreePoint opoint;
                    opoint.x=stra;
                    opoint.y=strb;
                    opoint.z=c;
                    m_OctreeEdge.push_back(opoint);
                    if(a1>a2)
                    {
                        ai--;
                        count--;
                    }
                    else
                    {
                        ai++;
                        count++;
                    }
                }
            }
            else
            {
                float k =diffa/diffb;
                int count=0;
                int bi=b1-diffb/abs(diffb);
                float ai = a1-diffa/abs(diffa)*abs(bi-b1+0.5)*abs(k);
                while(bi!=int(b2))
                {
                    string stra = ChangeToBinary(ai+count*k);
                    string strb = ChangeToBinary(bi);
                    ChangePoint(stra,strb,c);
                    OctreePoint opoint;
                    opoint.x=stra;
                    opoint.y=strb;
                    opoint.z=c;
                    m_OctreeEdge.push_back(opoint);
                    if(b1>b2)
                    {
                        bi--;
                        count--;
                    }
                    else
                    {
                        bi++;
                        count++;
                    }
                }
            }
            break;
        default:
            cout<<"error in ParallelToSurfaceEdge"<<endl;
            break;
    }
}

void Octree::GeneralLocationEdge(float x1,float x2,float y1,float y2,float z1,float z2)
{
    m_OctreeEdge.clear();
    float diffx=x1-x2;
    float diffy=y1-y2;
    float diffz=z1-z2;
    float diffmax = max(abs(diffx), max(abs(diffy),abs(diffz)));
    if(diffmax==abs(diffx))
    {
        float kyx = diffy/diffx;
        float kzx = diffz/diffx;
        int count=0;
        int xi=x1-diffx/abs(diffx);
        float yi = y1-diffy/abs(diffy)*abs(xi-x1+0.5)*abs(kyx);
        float zi = z1-diffz/abs(diffz)*abs(xi-x1+0.5)*abs(kzx);
        while(xi!=int(x2))
        {
            string strx = ChangeToBinary(xi);
            string stry = ChangeToBinary(yi+count*kyx);
            string strz = ChangeToBinary(zi+count*kzx);
            ChangePoint(strx,stry,strz);
            OctreePoint opoint;
            opoint.x=strx;
            opoint.y=stry;
            opoint.z=strz;
            m_OctreeEdge.push_back(opoint);
            if(x1>x2)
            {
                xi--;
                count--;
            }
            else
            {
                xi++;
                count++;
            }
        }
    }
    else if(diffmax==abs(diffy))
    {
        float kxy = diffx/diffy;
        float kzy = diffz/diffy;
        int count=0;
        int yi=y1-diffy/abs(diffy);
        float xi = x1-diffx/abs(diffx)*abs(yi-y1+0.5)*abs(kxy);
        float zi = z1-diffz/abs(diffz)*abs(yi-y1+0.5)*abs(kzy);
        while(yi!=int(y2))
        {
            string strx = ChangeToBinary(xi+count*kxy);
            string stry = ChangeToBinary(yi);
            string strz = ChangeToBinary(zi+count*kzy);
            ChangePoint(strx,stry,strz);
            OctreePoint opoint;
            opoint.x=strx;
            opoint.y=stry;
            opoint.z=strz;
            m_OctreeEdge.push_back(opoint);
            if(y1>y2)
            {
                yi--;
                count--;
            }
            else
            {
                yi++;
                count++;
            }
        }
    }
    else
    {
        float kxz = diffx/diffz;
        float kyz = diffy/diffz;
        int count=0;
        int zi=z1-diffz/abs(diffz);
        float xi = x1-diffx/abs(diffx)*abs(zi-z1+0.5)*abs(kxz);
        float yi = y1-diffy/abs(diffy)*abs(zi-z1+0.5)*abs(kyz);
        while(zi!=int(z2))
        {
            string strx = ChangeToBinary(xi+count*kxz);
            string stry = ChangeToBinary(yi+count*kyz);
            string strz = ChangeToBinary(zi);
            ChangePoint(strx,stry,strz);
            OctreePoint opoint;
            opoint.x=strx;
            opoint.y=stry;
            opoint.z=strz;
            m_OctreeEdge.push_back(opoint);
            if(z1>z2)
            {
                zi--;
                count--;
            }
            else
            {
                zi++;
                count++;
            }
        }
    }
}

void Octree::FacetToOctree(vector<CFacet> VectorFacet, vector <CVertex> VectorPoint,float xmax, float xmin, float ymax, float ymin, float zmax, float zmin)
{
    for(int i=0;i<int(VectorFacet.size());i++)
    {
        string strx1 = ChangeCoordinate(VectorPoint[VectorFacet[i].PointIndex[0]].m_Point[0],xmax,xmin);
        string strx2 = ChangeCoordinate(VectorPoint[VectorFacet[i].PointIndex[1]].m_Point[0],xmax,xmin);
        string strx3 = ChangeCoordinate(VectorPoint[VectorFacet[i].PointIndex[2]].m_Point[0],xmax,xmin);
        string stry1 = ChangeCoordinate(VectorPoint[VectorFacet[i].PointIndex[0]].m_Point[1],ymax,ymin);
        string stry2 = ChangeCoordinate(VectorPoint[VectorFacet[i].PointIndex[1]].m_Point[1],ymax,ymin);
        string stry3 = ChangeCoordinate(VectorPoint[VectorFacet[i].PointIndex[2]].m_Point[1],ymax,ymin);
        string strz1 = ChangeCoordinate(VectorPoint[VectorFacet[i].PointIndex[0]].m_Point[2],zmax,zmin);
        string strz2 = ChangeCoordinate(VectorPoint[VectorFacet[i].PointIndex[1]].m_Point[2],zmax,zmin);
        string strz3 = ChangeCoordinate(VectorPoint[VectorFacet[i].PointIndex[2]].m_Point[2],zmax,zmin);
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
        // to find the special facet that 2 vertex in one voxel
        if((strx1==strx2)&&(stry1==stry2)&&(strz1==strz2))continue;
        if((strx2==strx3)&&(stry2==stry3)&&(strz2==strz3))continue;
        if((strx1==strx3)&&(stry1==stry3)&&(strz1==strz3))continue;
        //to voxelize one edge
        EdgeChange(strx1,strx2,stry1,stry2,strz1,strz2,flx1,flx2,fly1,fly2,flz1,flz2);
        vector<OctreePoint> OctreeEdge = m_OctreeEdge;
        for(int j=1;j<int(OctreeEdge.size())-1;j++)
        {
            float fledgex = ChangeToDecimal(OctreeEdge[j].x)+0.5;
            float fledgey = ChangeToDecimal(OctreeEdge[j].y)+0.5;
            float fledgez = ChangeToDecimal(OctreeEdge[j].z)+0.5;
            EdgeChange(strx3,OctreeEdge[j].x,stry3,OctreeEdge[j].y,strz3,OctreeEdge[j].z,flx3,fledgex,fly3,fledgey,flz3,fledgez);
        }
        EdgeChange(strx1,strx3,stry1,stry3,strz1,strz3,flx1,flx3,fly1,fly3,flz1,flz3);
        EdgeChange(strx3,strx2,stry3,stry2,strz3,strz2,flx3,flx2,fly3,fly2,flz3,flz2);
    }
}

