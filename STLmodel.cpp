#include "STLmodel.h"
bool STLmodel::ReadASCII(const char *cfilename)
{
	int i = 0, j = 0, cnt = 0, pCnt = 4;
	int p_point = 0; //点的索引号
	int p_edge = 0; //边的索引号
	int p_facet = 0; //面的索引号
	int flag = 0;//寻找第一个点
	char a[100];
	char str[100];
	double x = 0, y = 0, z = 0;


	ifstream in;
	in.open(cfilename, ios::in);
	if (!in)
		return false;
	do
	{
		i = 0;
		cnt = 0;
		in.getline(a, 100, '\n');
		while (a[i] != '\0')
		{
			if (!islower((int)a[i]) && !isupper((int)a[i]) && a[i] != ' ')
				break;
			cnt++;
			i++;
		}

		while (a[cnt] != '\0')
		{
			str[j] = a[cnt];
			cnt++;
			j++;
		}
		str[j] = '\0';
		j = 0;

		if (sscanf(str, "%lf%lf%lf", &x, &y, &z) == 3)
		{
			flag++;
			if (flag % 4 == 1)
			{
				//将面片法向量存入m_Facet
				m_Facet.m_Normal[0] = x;
				m_Facet.m_Normal[1] = y;
				m_Facet.m_Normal[2] = z;
			}
			else
			{
				int f_remainder = flag % 4 - 2; //三角面片内部点顺序
				if (f_remainder < 0)
					f_remainder = f_remainder + 4;
				CVertex a;
				a.m_Point[0] = x;
				a.m_Point[1] = y;
				a.m_Point[2] = z;
				set<CVertex>::iterator iter;
				iter = m_SetPoint.find(a); //查找相同点
				if (iter != m_SetPoint.end())  //找到
				{
					m_Facet.PointIndex[f_remainder] = (*iter).m_PointIndex; //找到将该点索引号存入m_Facet.PointIndex
				}
				else            //未找到
				{
					a.m_PointIndex = p_point;
					m_Facet.PointIndex[f_remainder] = p_point;
					p_point++;
					m_SetPoint.insert(a);
				}
			}
			if (flag % 4 == 0 && flag != 0)
			{
				CEdge edge1, edge2, edge3;

				if (m_Facet.PointIndex[0] > m_Facet.PointIndex[1])
				{
					edge1.PointIndex[0] = m_Facet.PointIndex[0];
					edge1.PointIndex[1] = m_Facet.PointIndex[1];
				}
				else
				{
					edge1.PointIndex[0] = m_Facet.PointIndex[1];
					edge1.PointIndex[1] = m_Facet.PointIndex[0];
				}

				if (m_Facet.PointIndex[0] > m_Facet.PointIndex[2])
				{
					edge2.PointIndex[0] = m_Facet.PointIndex[0];
					edge2.PointIndex[1] = m_Facet.PointIndex[2];
				}
				else
				{
					edge2.PointIndex[0] = m_Facet.PointIndex[2];
					edge2.PointIndex[1] = m_Facet.PointIndex[0];
				}

				if (m_Facet.PointIndex[1] > m_Facet.PointIndex[2])
				{
					edge3.PointIndex[0] = m_Facet.PointIndex[1];
					edge3.PointIndex[1] = m_Facet.PointIndex[2];
				}
				else
				{
					edge3.PointIndex[0] = m_Facet.PointIndex[2];
					edge3.PointIndex[1] = m_Facet.PointIndex[1];
				}

				set<CEdge>::iterator iter1; //第一条边遍历
				set<CEdge>::iterator iter2; //第二条边遍历
				set<CEdge>::iterator iter3; //第三条边遍历

				iter1 = m_SetEdge.find(edge1); //查找相同边
				if (iter1 != m_SetEdge.end())  //找到
				{
					edge1.FacetIndex[0] = (*iter1).FacetIndex[0];
					edge1.FacetIndex[1] = p_facet;  //若已存在则把当前面的索引号存入FacetIndex[1]
					edge1.m_EdgeIndex = (*iter1).m_EdgeIndex; //索引值复制
					m_SetEdge.erase(iter1); //删除原结点
					m_SetEdge.insert(edge1); //插入新的节点
				}
				else            //未找到
				{
					edge1.FacetIndex[0] = p_facet;  //若不存在则把当前面的索引号存入FacetIndex[0]
					edge1.m_EdgeIndex = p_edge; //定义索引号
					m_SetEdge.insert(edge1); //插入当前边
					p_edge++;
				}

				iter2 = m_SetEdge.find(edge2); //查找相同边
				if (iter2 != m_SetEdge.end())  //找到
				{
					edge2.FacetIndex[0] = (*iter2).FacetIndex[0];
					edge2.FacetIndex[1] = p_facet;  //若已存在则把当前面的索引号存入FacetIndex[1]
					edge2.m_EdgeIndex = (*iter2).m_EdgeIndex; //索引值复制
					m_SetEdge.erase(iter2); //删除原结点
					m_SetEdge.insert(edge2); //插入新的节点
				}
				else            //未找到
				{
					edge2.FacetIndex[0] = p_facet;  //若不存在则把当前面的索引号存入FacetIndex[0]
					edge2.m_EdgeIndex = p_edge; //定义索引号
					m_SetEdge.insert(edge2); //插入当前边
					p_edge++;
				}

				iter3 = m_SetEdge.find(edge3); //查找相同边
				if (iter3 != m_SetEdge.end())  //找到
				{
					edge3.FacetIndex[0] = (*iter3).FacetIndex[0];
					edge3.FacetIndex[1] = p_facet;  //若已存在则把当前面的索引号存入FacetIndex[1]
					edge3.m_EdgeIndex = (*iter3).m_EdgeIndex; //索引值复制
					m_SetEdge.erase(iter3); //删除原结点
					m_SetEdge.insert(edge3); //插入新的节点
				}
				else            //未找到
				{
					edge3.FacetIndex[0] = p_facet;  //若不存在则把当前面的索引号存入FacetIndex[0]
					edge3.m_EdgeIndex = p_edge; //定义索引号
					m_SetEdge.insert(edge3); //插入当前边
					p_edge++;
				}
				m_Facet.EdgeIndex[0] = edge1.m_EdgeIndex;
				m_Facet.EdgeIndex[1] = edge2.m_EdgeIndex;
				m_Facet.EdgeIndex[2] = edge3.m_EdgeIndex;
				m_Facet.m_FacetIndex = p_facet;
				m_VectorFacet.push_back(m_Facet);
				p_facet++;
			}
		}
		pCnt++;
	} while (!in.eof());

	//  cout << "******  ACSII FILES　******" << endl;  
	//  for (int i = 0; i < coorX.size();i++)  
	//  {  
	//      cout << coorX[i] << " : " << coorY[i] << " : " << coorZ[i] << endl;  
	//  }  

	std::copy(m_SetPoint.begin(), m_SetPoint.end(), std::back_inserter(m_VectorPoint));
	std::copy(m_SetEdge.begin(), m_SetEdge.end(), std::back_inserter(m_VectorEdge));
	std::sort(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointIndex());
	std::sort(m_VectorEdge.begin(), m_VectorEdge.end(), LessEdgeIndex());

	x_max = (*max_element(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointx())).m_Point[0];
	x_min = (*min_element(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointx())).m_Point[0];
	y_max = (*max_element(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointy())).m_Point[1];
	y_min = (*min_element(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointy())).m_Point[1];
	z_max = (*max_element(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointz())).m_Point[2];
	z_min = (*min_element(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointz())).m_Point[2];

	vector<CFacet>::iterator iterfacet;
	for (iterfacet = m_VectorFacet.begin(); iterfacet != m_VectorFacet.end(); iterfacet++)
	{
		for (int i = 0; i <= 2; i++)
		{
			if (m_VectorEdge[(*iterfacet).EdgeIndex[i]].FacetIndex[0] == (*iterfacet).m_FacetIndex)
				(*iterfacet).FacetIndex[i] = m_VectorEdge[(*iterfacet).EdgeIndex[i]].FacetIndex[1];
			else
				(*iterfacet).FacetIndex[i] = m_VectorEdge[(*iterfacet).EdgeIndex[i]].FacetIndex[0];
		}
	}

	cout << flag / 4 << " triangles." << endl;
	return true;
}

bool STLmodel::ReadBinary(const char *cfilename)
{
	char str[80];
	ifstream in;
	int p_point = 0; //点的索引号
	int p_edge = 0; //边的索引号
	int p_facet = 0; //面的索引号

	in.open(cfilename, ios::in | ios::binary);

	if (!in)
		return false;

	in.read(str, 80);

	//number of triangles  
	int unTriangles;
	in.read((char*)&unTriangles, sizeof(int));

	if (unTriangles == 0)
		return false;

	for (int i = 0; i < unTriangles; i++)
	{
		float coorXYZ[12];
		in.read((char*)coorXYZ, 12 * sizeof(float));
		m_Facet.m_Normal[0] = coorXYZ[0];
		m_Facet.m_Normal[1] = coorXYZ[1];
		m_Facet.m_Normal[2] = coorXYZ[2];

		for (int j = 1; j < 4; j++)
		{

			int f_remainder = j - 1; //三角面片内部点顺序
			CVertex a;
			a.m_Point[0] = coorXYZ[j * 3];
			a.m_Point[1] = coorXYZ[j * 3 + 1];
			a.m_Point[2] = coorXYZ[j * 3 + 2];
			set<CVertex>::iterator iter;
			iter = m_SetPoint.find(a); //查找相同点
			if (iter != m_SetPoint.end())  //找到
			{
				m_Facet.PointIndex[f_remainder] = (*iter).m_PointIndex; //找到将该点索引号存入m_Facet.PointIndex
			}
			else            //未找到
			{
				a.m_PointIndex = p_point;
				m_Facet.PointIndex[f_remainder] = p_point;
				p_point++;
				m_SetPoint.insert(a);
			}
		}

		in.read((char*)coorXYZ, 2);

		CEdge edge1, edge2, edge3;

		if (m_Facet.PointIndex[0] > m_Facet.PointIndex[1])
		{
			edge1.PointIndex[0] = m_Facet.PointIndex[0];
			edge1.PointIndex[1] = m_Facet.PointIndex[1];
		}
		else
		{
			edge1.PointIndex[0] = m_Facet.PointIndex[1];
			edge1.PointIndex[1] = m_Facet.PointIndex[0];
		}

		if (m_Facet.PointIndex[0] > m_Facet.PointIndex[2])
		{
			edge2.PointIndex[0] = m_Facet.PointIndex[0];
			edge2.PointIndex[1] = m_Facet.PointIndex[2];
		}
		else
		{
			edge2.PointIndex[0] = m_Facet.PointIndex[2];
			edge2.PointIndex[1] = m_Facet.PointIndex[0];
		}

		if (m_Facet.PointIndex[1] > m_Facet.PointIndex[2])
		{
			edge3.PointIndex[0] = m_Facet.PointIndex[1];
			edge3.PointIndex[1] = m_Facet.PointIndex[2];
		}
		else
		{
			edge3.PointIndex[0] = m_Facet.PointIndex[2];
			edge3.PointIndex[1] = m_Facet.PointIndex[1];
		}

		set<CEdge>::iterator iter1; //第一条边遍历
		set<CEdge>::iterator iter2; //第二条边遍历
		set<CEdge>::iterator iter3; //第三条边遍历

		iter1 = m_SetEdge.find(edge1); //查找相同边
		if (iter1 != m_SetEdge.end())  //找到
		{
			edge1.FacetIndex[0] = (*iter1).FacetIndex[0];
			edge1.FacetIndex[1] = p_facet;  //若已存在则把当前面的索引号存入FacetIndex[1]
			edge1.m_EdgeIndex = (*iter1).m_EdgeIndex; //索引值复制
			m_SetEdge.erase(iter1); //删除原结点
			m_SetEdge.insert(edge1); //插入新的节点
		}
		else            //未找到
		{
			edge1.FacetIndex[0] = p_facet;  //若不存在则把当前面的索引号存入FacetIndex[0]
			edge1.m_EdgeIndex = p_edge; //定义索引号
			m_SetEdge.insert(edge1); //插入当前边
			p_edge++;
		}

		iter2 = m_SetEdge.find(edge2); //查找相同边
		if (iter2 != m_SetEdge.end())  //找到
		{
			edge2.FacetIndex[0] = (*iter2).FacetIndex[0];
			edge2.FacetIndex[1] = p_facet;  //若已存在则把当前面的索引号存入FacetIndex[1]
			edge2.m_EdgeIndex = (*iter2).m_EdgeIndex; //索引值复制
			m_SetEdge.erase(iter2); //删除原结点
			m_SetEdge.insert(edge2); //插入新的节点
		}
		else            //未找到
		{
			edge2.FacetIndex[0] = p_facet;  //若不存在则把当前面的索引号存入FacetIndex[0]
			edge2.m_EdgeIndex = p_edge; //定义索引号
			m_SetEdge.insert(edge2); //插入当前边
			p_edge++;
		}

		iter3 = m_SetEdge.find(edge3); //查找相同边
		if (iter3 != m_SetEdge.end())  //找到
		{
			edge3.FacetIndex[0] = (*iter3).FacetIndex[0];
			edge3.FacetIndex[1] = p_facet;  //若已存在则把当前面的索引号存入FacetIndex[1]
			edge3.m_EdgeIndex = (*iter3).m_EdgeIndex; //索引值复制
			m_SetEdge.erase(iter3); //删除原结点
			m_SetEdge.insert(edge3); //插入新的节点
		}
		else            //未找到
		{
			edge3.FacetIndex[0] = p_facet;  //若不存在则把当前面的索引号存入FacetIndex[0]
			edge3.m_EdgeIndex = p_edge; //定义索引号
			m_SetEdge.insert(edge3); //插入当前边
			p_edge++;
		}
		m_Facet.EdgeIndex[0] = edge1.m_EdgeIndex;
		m_Facet.EdgeIndex[1] = edge2.m_EdgeIndex;
		m_Facet.EdgeIndex[2] = edge3.m_EdgeIndex;
		m_Facet.m_FacetIndex = p_facet;
		m_VectorFacet.push_back(m_Facet);
		p_facet++;

	}

	in.close();

	std::copy(m_SetPoint.begin(), m_SetPoint.end(), std::back_inserter(m_VectorPoint));
	std::copy(m_SetEdge.begin(), m_SetEdge.end(), std::back_inserter(m_VectorEdge));
	std::sort(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointIndex());
	std::sort(m_VectorEdge.begin(), m_VectorEdge.end(), LessEdgeIndex());

	x_max = (*max_element(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointx())).m_Point[0];
	x_min = (*min_element(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointx())).m_Point[0];
	y_max = (*max_element(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointy())).m_Point[1];
	y_min = (*min_element(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointy())).m_Point[1];
	z_max = (*max_element(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointz())).m_Point[2];
	z_min = (*min_element(m_VectorPoint.begin(), m_VectorPoint.end(), LessPointz())).m_Point[2];

	vector<CFacet>::iterator iterfacet;
	for (iterfacet = m_VectorFacet.begin(); iterfacet != m_VectorFacet.end(); iterfacet++)
	{
		for (int i = 0; i <= 2; i++)
		{
			if (m_VectorEdge[(*iterfacet).EdgeIndex[i]].FacetIndex[0] == (*iterfacet).m_FacetIndex)
				(*iterfacet).FacetIndex[i] = m_VectorEdge[(*iterfacet).EdgeIndex[i]].FacetIndex[1];
			else
				(*iterfacet).FacetIndex[i] = m_VectorEdge[(*iterfacet).EdgeIndex[i]].FacetIndex[0];
		}
	}

	cout << m_VectorFacet.size() << " triangles." << endl;
	return true;
}


bool STLmodel::ReadSTLFile(const char *cfilename)
{
	if (cfilename == NULL)
		return false;

	ifstream in(cfilename, ios::in);
	if (!in)
		return false;

	string headStr;
	string SecondStr;
	getline(in, headStr);
	getline(in, SecondStr);
	in.close();

	if (headStr.empty())
		return false;

    int noempty=0;
    while(SecondStr[noempty]==' ')
        noempty++;
    if ((headStr[0] == 's') && (SecondStr[noempty] == 'f'))
	{
		cout << "ASCII File." << endl;
		ReadASCII(cfilename);
	}
	else
	{
		cout << "Binary File." << endl;
		ReadBinary(cfilename);
	}
	return true;
}

void STLmodel::drawSTL(void)
{
	glColor3f(0.0, 0.4, 0.2);
	for (int i = 0; i < m_VectorFacet.size(); i++)
	{
		glBegin(GL_LINE_LOOP);
		glVertex3f(m_VectorPoint[m_VectorFacet[i].PointIndex[0]].m_Point[0], m_VectorPoint[m_VectorFacet[i].PointIndex[0]].m_Point[1], m_VectorPoint[m_VectorFacet[i].PointIndex[0]].m_Point[2]);
		glVertex3f(m_VectorPoint[m_VectorFacet[i].PointIndex[1]].m_Point[0], m_VectorPoint[m_VectorFacet[i].PointIndex[1]].m_Point[1], m_VectorPoint[m_VectorFacet[i].PointIndex[1]].m_Point[2]);
		glVertex3f(m_VectorPoint[m_VectorFacet[i].PointIndex[2]].m_Point[0], m_VectorPoint[m_VectorFacet[i].PointIndex[2]].m_Point[1], m_VectorPoint[m_VectorFacet[i].PointIndex[2]].m_Point[2]);
		glEnd();
	}
}

bool STLmodel::slice(float z)
{
	if (z > z_max || z < z_min)
		return false;
	int edgesize = m_VectorEdge.size();
	vector<bool> bSlice(edgesize, false); //定义和边数量长度一致的数组，并全部赋值为false
	for (int edgenumber = 0; edgenumber != edgesize - 1; edgenumber++)
	{
		if (bSlice[edgenumber] == false)
		{
			//寻找其中为false的边（未切）
			vector<point> outline; //定义轮廓链
			if ((m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[0]].m_Point[2] == m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[2]) &&(m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[2]==z))
				continue;//如果这个边在切平面上，按照平移算法这条边是不能算作true的，这样会形成死循环
			if ((m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[0]].m_Point[2] - z)*(m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[2] - z) <= 0)
			{
				float zadd = z;//定义移动后的z平面
				int iNextedge;
				float x, y;
				int lastfacet;
				int nextfacet;
				if ((m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[0]].m_Point[2] - z)*(m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[2] - z) == 0)
				{
				     /*
					可以考虑将z向上移动一个微小距离，算出切边，再通过原z值计算交点
					*/
					if (m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[0]].m_Point[2] == z)
					{
						x = m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[0]].m_Point[0];
						y = m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[0]].m_Point[1];
					}
					else
					{
						x = m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[0];
						y = m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[1];
					}
					bSlice[edgenumber] = true;
					point pt(x, y, edgenumber);
					outline.push_back(pt);
					if ((m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[0]].m_Point[2] - z - 0.000001)*(m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[2] - z - 0.000001) < 0)
						zadd = z + 0.000001;
					else
						zadd = z - 0.000001;
					
					if ((m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[0] != edgenumber) && ((m_VectorPoint[m_VectorEdge[m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[0]].PointIndex[0]].m_Point[2] - zadd)*(m_VectorPoint[m_VectorEdge[m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[0]].PointIndex[1]].m_Point[2] - zadd) <= 0))
					{
						iNextedge = m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[0];
					}
					else if ((m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[1] != edgenumber) && ((m_VectorPoint[m_VectorEdge[m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[1]].PointIndex[0]].m_Point[2] - zadd)*(m_VectorPoint[m_VectorEdge[m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[1]].PointIndex[1]].m_Point[2] - zadd) <= 0))
					{
						iNextedge = m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[1];
					}
					else
						iNextedge = m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[2];
					lastfacet = m_VectorEdge[edgenumber].FacetIndex[0];
					if (m_VectorEdge[edgenumber].FacetIndex[0] == m_VectorEdge[iNextedge].FacetIndex[0])
						nextfacet = m_VectorEdge[iNextedge].FacetIndex[1];
					else
						nextfacet = m_VectorEdge[iNextedge].FacetIndex[0];
				}
				else
				{
					/*
					对于两个点(x1,y1,z1)和(x2,y2,z2)中间与z平面的交点(x,y,z)
					(x,y,z)=(x1-x2,y1-y2,z1-z2)*(z-z2)/(z1-z2)+(x2,y2,z2)
					*/
					x = m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[0] + (z - m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[2]) / (m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[0]].m_Point[2] - m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[2])*(m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[0]].m_Point[0] - m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[0]);
					y = m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[1] + (z - m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[2]) / (m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[0]].m_Point[2] - m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[2])*(m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[0]].m_Point[1] - m_VectorPoint[m_VectorEdge[edgenumber].PointIndex[1]].m_Point[1]);
					point pt(x, y, edgenumber);
					bSlice[edgenumber] = true;
					outline.push_back(pt);
					if ((m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[0] != edgenumber) && ((m_VectorPoint[m_VectorEdge[m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[0]].PointIndex[0]].m_Point[2] - z)*(m_VectorPoint[m_VectorEdge[m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[0]].PointIndex[1]].m_Point[2] - z) <= 0))
					{
						iNextedge = m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[0];
					}
					else if ((m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[1] != edgenumber) && ((m_VectorPoint[m_VectorEdge[m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[1]].PointIndex[0]].m_Point[2] - z)*(m_VectorPoint[m_VectorEdge[m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[1]].PointIndex[1]].m_Point[2] - z) <= 0))
					{
						iNextedge = m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[1];
					}
					else
						iNextedge = m_VectorFacet[m_VectorEdge[edgenumber].FacetIndex[0]].EdgeIndex[2];
					lastfacet = m_VectorEdge[edgenumber].FacetIndex[0];
					if (m_VectorEdge[edgenumber].FacetIndex[0] == m_VectorEdge[iNextedge].FacetIndex[0])
						nextfacet = m_VectorEdge[iNextedge].FacetIndex[1];
					else
						nextfacet = m_VectorEdge[iNextedge].FacetIndex[0];
					
				}
				while (iNextedge != edgenumber)
				{
					float zadd1 = z;
					if ((m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[0]].m_Point[2] - z)*(m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[1]].m_Point[2] - z) == 0)
					{
						/*
						可以考虑将z向上移动一个微小距离，算出切边，再通过原z值计算交点
						*/
						if (m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[0]].m_Point[2] == z)
						{
							x = m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[0]].m_Point[0];
							y = m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[0]].m_Point[1];
						}
						else
						{
							x = m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[1]].m_Point[0];
							y = m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[1]].m_Point[1];
						}
						if (zadd == z)
						{
							if ((m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[0]].m_Point[2] - z - 0.000001)*(m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[1]].m_Point[2] - z - 0.000001) < 0)
								zadd = z + 0.000001;
							else
								zadd = z - 0.000001;
						}
						zadd1 = zadd;
					}
					else
					{
						x = m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[1]].m_Point[0] + (z - m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[1]].m_Point[2]) / (m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[0]].m_Point[2] - m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[1]].m_Point[2])*(m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[0]].m_Point[0] - m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[1]].m_Point[0]);
						y = m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[1]].m_Point[1] + (z - m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[1]].m_Point[2]) / (m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[0]].m_Point[2] - m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[1]].m_Point[2])*(m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[0]].m_Point[1] - m_VectorPoint[m_VectorEdge[iNextedge].PointIndex[1]].m_Point[1]);
					}
					point pt1(x, y, iNextedge);
					bSlice[iNextedge] = true;
					outline.push_back(pt1);
					int iNextedge1;
					if ((m_VectorFacet[nextfacet].EdgeIndex[0] != iNextedge) && ((m_VectorPoint[m_VectorEdge[m_VectorFacet[nextfacet].EdgeIndex[0]].PointIndex[0]].m_Point[2] - zadd1)*(m_VectorPoint[m_VectorEdge[m_VectorFacet[nextfacet].EdgeIndex[0]].PointIndex[1]].m_Point[2] - zadd1) <= 0))
					{
						iNextedge1 = m_VectorFacet[nextfacet].EdgeIndex[0];
					}
					else if ((m_VectorFacet[nextfacet].EdgeIndex[1] != iNextedge) && ((m_VectorPoint[m_VectorEdge[m_VectorFacet[nextfacet].EdgeIndex[1]].PointIndex[0]].m_Point[2] - zadd1)*(m_VectorPoint[m_VectorEdge[m_VectorFacet[nextfacet].EdgeIndex[1]].PointIndex[1]].m_Point[2] - zadd1) <= 0))
					{
						iNextedge1 = m_VectorFacet[nextfacet].EdgeIndex[1];
					}
					else
						iNextedge1 = m_VectorFacet[nextfacet].EdgeIndex[2];
					lastfacet = nextfacet;
					if (lastfacet == m_VectorEdge[iNextedge1].FacetIndex[0])
						nextfacet = m_VectorEdge[iNextedge1].FacetIndex[1];
					else
						nextfacet = m_VectorEdge[iNextedge1].FacetIndex[0];
					iNextedge = iNextedge1;
				}
				z_point.push_back(outline);
			}
		}
	}
	return true;
}

void STLmodel::drawslice(float z)
{
	glColor3f(0.0, 1.0, 0.2);
	for (int i = 0; i < z_point.size(); i++)
	{
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < z_point[i].size(); j++)
		{
			glVertex3f(z_point[i][j].x, z_point[i][j].y, z);
		}
		glEnd();
	}
}

void STLmodel::setperspective(double eyex,double eyey,double eyez,double centrex,double centrey,double centrez,double upx,double upy,double upz)
{
	gluLookAt(0.5*(x_max + x_min) + 2 * eyex * max(max((x_max - x_min), (y_max - y_min)), (z_max - z_min)),  0.5*(y_max + y_min) + 2 * eyey * max(max((x_max - x_min), (y_max - y_min)), (z_max - z_min)), 0.5*(z_max + z_min) + eyez * max(max((x_max - x_min), (y_max - y_min)), (z_max - z_min)), 0.5*(x_max + x_min) + centrex, 0.5*(y_max + y_min) + centrey, 0.5*(z_max + z_min) + centrez, upx, upy, upz);
}

bool STLmodel::sliceequalllayers(int layernumber)
{
	if (layernumber <= 1)
	{
		cout << "层数应该大于1" << endl;
		return false;
	}
	else
	{
        float layerthickness = (z_max - z_min) / (layernumber - 1);
		for (float i = z_min; i <= z_max; i = i + layerthickness)
		{
			slice(i);
			slicingdata.push_back(z_point);
			z_point.clear();
		}
		return true;
	}
}

void STLmodel::drawsliceequalllayers(int layernumber)
{
	glColor3f(0.0, 1.0, 0.2);
	if (layernumber <= 1)
	{
		cout << "层数应该大于1" << endl;
	}
	else
	{
		float layerthickness = (z_max - z_min) / (layernumber - 1);
		for (int i = 0; i < slicingdata.size(); i++)
		{
			for (int j = 0; j < slicingdata[i].size(); j++)
			{
				glBegin(GL_LINE_LOOP);
				for (int k = 0; k < slicingdata[i][j].size(); k++)
				{
					glVertex3f(slicingdata[i][j][k].x, slicingdata[i][j][k].y, z_min + i*layerthickness);
				}
				glEnd();
			}
		}
	}
	
}

bool STLmodel::slicefacet(int layernumber)
{
	if (layernumber > slicingdata.size() || layernumber <= 0)
	{
		cout << "选择正确的层数" << endl;
		return false;
	}
	else
	{
		for (int i = 0; i < slicingdata[layernumber].size(); i++)
		{
			set<int> facetnumber;
			for (int j = 0; j < slicingdata[layernumber][i].size(); j++)
			{
				facetnumber.insert(m_VectorEdge[slicingdata[layernumber][i][j].edgenumber].FacetIndex[0]);
				facetnumber.insert(m_VectorEdge[slicingdata[layernumber][i][j].edgenumber].FacetIndex[1]);
			}
			slicefacetnumber.push_back(facetnumber);
		}
		return true;
	}
}

void STLmodel::drawslicefacet(void)
{
	for (int i = 0; i < slicefacetnumber.size(); i++)
	{
		set<int>::iterator it;
		for (it = slicefacetnumber[i].begin(); it != slicefacetnumber[i].end(); it++)
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(m_VectorPoint[m_VectorFacet[*it].PointIndex[0]].m_Point[0], m_VectorPoint[m_VectorFacet[*it].PointIndex[0]].m_Point[1], m_VectorPoint[m_VectorFacet[*it].PointIndex[0]].m_Point[2]);
			glVertex3f(m_VectorPoint[m_VectorFacet[*it].PointIndex[1]].m_Point[0], m_VectorPoint[m_VectorFacet[*it].PointIndex[1]].m_Point[1], m_VectorPoint[m_VectorFacet[*it].PointIndex[1]].m_Point[2]);
			glVertex3f(m_VectorPoint[m_VectorFacet[*it].PointIndex[2]].m_Point[0], m_VectorPoint[m_VectorFacet[*it].PointIndex[2]].m_Point[1], m_VectorPoint[m_VectorFacet[*it].PointIndex[2]].m_Point[2]);
			glEnd();
		}
	}
}

void STLmodel::drawAABB(void)
{
    glColor3f(0.0, 1.0, 0.2);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x_min,y_min,z_min);
    glVertex3f(x_min,y_max,z_min);
    glVertex3f(x_max,y_max,z_min);
    glVertex3f(x_max,y_min,z_min);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(x_min,y_min,z_max);
    glVertex3f(x_min,y_max,z_max);
    glVertex3f(x_max,y_max,z_max);
    glVertex3f(x_max,y_min,z_max);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(x_min,y_min,z_min);
    glVertex3f(x_min,y_min,z_max);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(x_max,y_min,z_min);
    glVertex3f(x_max,y_min,z_max);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(x_max,y_max,z_min);
    glVertex3f(x_max,y_max,z_max);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(x_min,y_max,z_min);
    glVertex3f(x_min,y_max,z_max);
    glEnd();
}

void STLmodel::VoxelizePoint(void)
{

}

float STLmodel::xmax(void)
{
    return x_max;
}

float STLmodel::ymax(void)
{
    return y_max;
}

float STLmodel::zmax(void)
{
    return z_max;
}

float STLmodel::xmin(void)
{
    return x_min;
}

float STLmodel::ymin(void)
{
    return y_min;
}

float STLmodel::zmin(void)
{
    return z_min;
}
