/*
Definition And Used
----------------------------------------------------------
A decision tree is a supervised learning algorithm used for classification and regression tasks.
It works by splitting the dataset into smaller subsets based on feature values, forming a tree 
structure with decision nodes and leaf nodes.
Each internal node represents a feature-based decision, and each leaf node represents an output class or value.
----------------------------------------------------------
This Model Will Support Only string values and gives the rootnode and child node
----------------------------------------------------------
*/


#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<iomanip>
#include<cmath>

using namespace std;

void gotoxy(int,int);
int main()
{
	int c,r,s;
	cout << "Enter Count Of Column :- ";
	cin >> s;
	cout << "Enter Count Of Rows :- ";
	cin >> r;
	string svalue[s][r];
	vector<double> v;
	vector<string> v2;
	vector<vector<string>>svalue2;
	vector<int> cls;
	vector<vector<int>>cls3;
	double entire = 0.0;
	int clss[r];
	double y = 0.0,n = 0.0;
	for (int i = 0; i < s; ++i)
	{
		for (int j = 0; j < r; ++j)
		{
			cout << "Enter " << i + 1 << " Text Column " << j + 1 << " Row Value :- ";
			cin >> svalue[i][j];
			v2.push_back(svalue[i][j]);
		}
		svalue2.push_back(v2);
		v2.clear();
	}
	for (int i = 0; i < r; ++i)
	{
		cout << "Enter " << i + 1 << " Class Value :- ";
		cin >> clss[i];
		if (clss[i]==1)
		{
			++y;
		}
		else if (clss[i]==0)
		{
			++n;
		}
	}
	int ct = 0,cct = 0,f = 0;
	if(s!=0)
	{
		for (int i = 0; i < s ; ++i)
		{
			sort(svalue2[i].begin(),svalue2[i].end());
		}
		cct = 0;
		ct = 0;
		f = 0;
		cls.clear();
		for (int j = 0; j < r && cct!=s; ++j)
		{
			cout << endl;
			for (int i = 0; i < r; ++i)
			{
				if (svalue[cct][i]==svalue2[cct][ct])
				{
					cls.push_back(clss[i]);
					++ct;
					if(ct==r)
					{
						cls3.push_back(cls);
						cls.clear();
						ct = 0;
						++cct;
						if (cct==s)
						{
							break;
						}
					}
				}
				++f;
			}
			if (cct==s)
			{
				break;
			}
		}
	}	
	vector<double> ans;
	vector<double> ans2;
	vector<double> entropy2;
	double sumation;
	vector<double> sum;
	vector<string> stri;
	double e;
	double e1;
	double y1 = 0.0, n1 = 0.0,entropy = 0.0;
	ct = 0;
	cct = 0;
	if(s!=0)	{
		string str = svalue2[0][0];
		for(int j = 0 ; j < r ; ++j)
		{
			for (int i = 0; i < r; ++i)
			{
				if (svalue2[cct][i]==str)
				{
					++ct;
					if (cls3[cct][i]==1)
					{
						++y1;
					}
					else if (cls3[cct][i]==0)
					{
						++n1;
					}
				}
				else if (svalue2[cct][i]!=str)
				{
					if (y1==0||n1==0)
					{
						entropy2.push_back(0);
						y1 = 0.0;
						n1 = 0.0;
						str = svalue2[cct][i];
						--i;
					}
					else
					{
						entropy2.push_back(((y1+n1) / r) * ((-(y1/(y1+n1)) * log2((y1/(y1+n1)))) + (-(n1/(y1+n1)) * log2((n1/(y1+n1))))));
						y1 = 0.0;
						n1 = 0.0;
						str = svalue2[cct][i];
						--i;
					}
				}
			}
			if (ct==r)
			{
				if (y1==0||n1==0)
				{
					entropy2.push_back(0);
				}
				else
				{
					entropy2.push_back(((y1+n1) / r) * ((-(y1/(y1+n1)) * log2((y1/(y1+n1)))) + (-(n1/(y1+n1)) * log2((n1/(y1+n1))))));
				}
				for (int i = 0; i < entropy2.size(); ++i)
				{
					entropy += (+entropy2[i]);
				}
				e = y / r;
				e1 = n / r;
				entire = ((-e * log2(e)) + (-e1 * log2(e1)));
				ans.push_back(entire - entropy);
				ans2.push_back(entire - entropy);
				++cct;
				if (cct != s)
				{
					entropy2.clear();
					entropy = 0;
					y1 = 0.0;
					n1 = 0.0;
					ct = 0;
					str = svalue2[cct][0];			
				}
			}
			if (cct==s)
			{
				break;
			}
		}
	}
	int l;
	sort(ans.begin(),ans.end());
	for (int i = 0; i < ans2.size(); ++i)
	{
		if (ans2[i]==ans.back())
		{
			l = i;
		}
	}
	if (l!=0)
	{
		for (int i = 0; i < r; ++i)
		{
			svalue2[0].push_back(svalue2[l][i]);
			svalue2[l].push_back(svalue2[0][i]);
		}
	}
	vector<string> svalue3;
	vector<string> svalue4;
	f = l + 1;
	string str = svalue2[l][0];
	stri.push_back(str);
	for (int j = 0; j < r; ++j)
	{
		if (str!=svalue2[l][j])
		{
			str = svalue2[l][j];
			stri.push_back(svalue2[l][j]);
		}			
	}
	vector<double> ans3;
	entire = 0;
	e = 0;
	e1 = 0;
	ans.clear();
	ans2.clear();
	entropy2.clear();
	entropy = 0;
	ans.clear();
	ans2.clear();
	entropy2.clear();
	ct = 0;
	y1 = 0;
	n1 = 0;
	cct = 0;
	y = 0;
	n = 0;
	vector<int> cls4;
	vector<int> cls5;
	for (int k = 0; k < stri.size(); ++k)
	{
		for (int i = 1; i < s; ++i)
		{
			for (int j = 0; j < r; ++j)
			{
				if (stri[k]==svalue[l][j])
				{
					svalue3.push_back(svalue[i][j]);
					svalue4.push_back(svalue[i][j]);
					cls4.push_back(clss[j]);
					if (clss[j]==1)
					{
						++y;
					}
					else if (clss[j]==0)
					{
						++n;
					}
				}
			}
			sort(svalue4.begin(),svalue4.end());
			for (int i = 0; i < svalue3.size(); ++i)
			{	
				for (int j = 0; j < svalue3.size(); ++j)
				{
					if (svalue4[ct]==svalue3[j])
					{
						cls5.push_back(cls4[j]);
					}
				}
			}
			string str = svalue4.front();
			for (int i = 0; i < svalue4.size(); ++i)
			{
				if (str==svalue4[i])
				{
					++ct;
					if (cls5[i]==1)
					{
						++y1;
					}
					else if (cls5[i]==0)
					{				
						++n1;
					}
				}
				else
				{
					if (y1==0||n1==0)
					{
						entropy2.push_back(0);
						str = svalue4[i];
						--i;
						y1 = 0;
						n1 = 0;
						ct = 0;
					}
					else
					{
						
						entropy2.push_back(((y1+n1) / ct) * ((-(y1/(y1+n1)) * log2((y1/(y1+n1)))) + (-(n1/(y1+n1)) * log2((n1/(y1+n1))))));
						str = svalue4[i];
						--i;
						y1 = 0;
						n1 = 0;
						ct = 0;
					}				
				}
			}
			if (y1==0||n1==0)
			{
				entropy2.push_back(0);
			}
			else
			{
				entropy2.push_back(((y1+n1) / ct) * ((-(y1/(y1+n1)) * log2((y1/(y1+n1)))) + (-(n1/(y1+n1)) * log2((n1/(y1+n1))))));
			}				
			for (int i = 0; i < entropy2.size(); ++i)
			{
				if (entropy2[i]==1)
				{	
					entropy2[i] = 0;
				}
			}
			for (int i = 0; i < entropy2.size(); ++i)
			{
				entropy += (+entropy2[i]);
			}
			e = y / (y + n);
			e1 = n / (y + n);
			entire = ((-e * log2(e)) + (-e1 * log2(e1)));
			ans.push_back(entire - entropy);
			ans2.push_back(entire - entropy);		
			y = 0;
			n = 0;
			e = 0;
			e1 = 0;
			y1 = 0;
			n1 = 0;
			ct = 0;
			entropy = 0;
			entire = 0;
			entropy2.clear();
			svalue3.clear();
			svalue4.clear();
			cls4.clear();
			cls5.clear();
		}
		for (int i = 0; i < ans.size() && ans2.size(); ++i)
		{
			if (isnan(ans[i]) && isnan(ans2[i]))
			{
				ans[i] = 0;
				ans2[i] = 0;
			}
		}
		sort(ans.begin(),ans.end());
		int fg = 0;
		if (ans.back()==0)
		{
			ans3.push_back(0.9123);
		}
		else
		{
			for (int i = 1; i < ans2.size() && ans.size(); ++i)
			{
				if (ans2[i]==ans.back())
				{
					ans3.push_back(i + 1);
					break;
				}
			}
		}
		y = 0;
		n = 0;
		e = 0;
		e1 = 0;
		y1 = 0;
		n1 = 0;
		ct = 0;
		entropy = 0;
		entire = 0;
		entropy2.clear();
		svalue3.clear();
		svalue4.clear();
		cls4.clear();
		cls5.clear();
		ans.clear();
		ans2.clear();
	}
	y = 0;
	n = 0;
	e = 0;
	e1 = 0;
	y1 = 0;
	n1 = 0;
	ct = 0;
	cct = 0;
	cls4.clear();
	vector<string> stri2;
	vector<string> stri3;
	vector<string> stri4;
	vector<string> stri5;
	vector<string> stri6;
	for (int i = 0; i < stri.size(); ++i)
	{
		if (ans3[cct]!=0.9123)
		{
			for (int j = 0; j < r; ++j)
			{
				if (stri[i]==svalue[l][j])
				{
					int m = ans3[cct];
					stri2.push_back(svalue[m][j]);
					stri3.push_back(svalue[m][j]);
					cls4.push_back(clss[j]);
				}
			}
			sort(stri2.begin(),stri2.end());
			string str = stri2.front();
			stri4.push_back(stri2.front());
			stri6.push_back(stri2.front());
			for (int i = 0; i < stri2.size(); ++i)
			{
				if (str!=stri2[i])
				{
					stri4.push_back(stri2[i]);
					stri6.push_back(stri2[i]);
					str = stri2[i];
				}
			}
	
			for (int i = 0; i < stri4.size(); ++i)
			{
				for (int j = 0; j < stri3.size(); ++j)
				{
					if (stri4[i]==stri3[j])
					{
						if (cls4[j]==1)
						{
							++y;
						}
						else if (cls4[j]==0)
						{
							++n;
						}
					}
				}
				if (y > n)
				{
					stri5.push_back("Yes");
				}
				else if (y < n)
				{
					stri5.push_back("No");
				}
				else if (y==n)
				{
					stri5.push_back("Yes");
				}
				y = 0;
				n = 0;
			}
			++cct;
			y = 0;
			n = 0;
			cls4.clear();
			stri2.clear();
			stri3.clear();
			stri4.clear();
		}
		else
		{
			++cct;
			y = 0;
			n = 0;
			cls4.clear();
			stri2.clear();
			stri3.clear();
			stri4.clear();
		}
	}
	cout << "--------------------------";
	cout << "Root Node" << endl;
	cout << "--------------------------";
	cout << endl;
	for (int i = 0; i < stri.size(); ++i)
	{
		if (ans3[i]==0.9123)
		{
			cout << stri[i] << " For Yes " << endl;	
		}
		else
		{
			cout << stri[i] << " For " << (ans3[i] + 1) << " Column" << endl;	
		}
	}
	cout << endl;
	cout << endl;
	cout << "--------------------------";
	cout << "Child Node" << endl;
	cout << "--------------------------";
	cout << endl;
	for (int i = 0; i < stri5.size(); ++i)
	{
		cout << stri6[i] << " For " << stri5[i] << endl;
	}
	return 0;
}
