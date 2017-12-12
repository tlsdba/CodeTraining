#include<iostream>
#include<string>
#include<vector>
using namespace std;

int constantTeamNum = 16;
vector<int> idx_vec(constantTeamNum, -1);
int idx_ = 0;

int checkState(vector<int>& label)
{
	int s = 0;
	for (int i = 0; i < constantTeamNum; i++)
	{
		s += label[i];
	}
	if (s == constantTeamNum)
		return 1;
	else
		return 0;
}
bool check(int idx1, int idx2, vector<vector<string>>& data, vector<int>& label)
{
	if (data[idx1][1] == data[idx2][1])
		return false;
	if (label[idx1] == 1 || label[idx2] == 1)
		return false;
	if (data[idx1][0][0] == data[idx2][0][0])
		return false;
	if (data[idx1][0][1] == data[idx2][0][1])
		return false;
	if (idx1 == (constantTeamNum - 1))
		return false;
	return true;

}


void f(int idx1_origin, int idx2_origin, int& num, vector<vector<string>>& data, vector<int>& label)
{
	/**
	* \brief 采用循环加递归的形式，idx1_origin，idx2_origin分别表示需检测的一对数据的两个数，循环控制的是在当前idx1下，idx2一直往数据尾部探索的过程；递归是找到当前合适的一对数据后，往后继续探索满足条件的数据对。
	* 每个递归函数完成向后的数据查询，即idx2_origin == constantTeamNum时完成当前任务
	* 完成任务时判断当前任务是否是最终阶段，也就是idx_(完成的匹配数据个数)等于总的数据数，这时调用checkState查看当前匹配状态是否满足条件。
	*/

	//
	for (; idx2_origin < constantTeamNum; idx2_origin++)
	{
		//判断数据对是否满足匹配条件
		if (check(idx1_origin, idx2_origin, data, label))
		{
			label[idx1_origin] = 1;
			label[idx2_origin] = 1;
			idx_vec[idx_++] = idx1_origin;
			idx_vec[idx_++] = idx2_origin;

			int idx1 = idx1_origin;
			int idx2 = idx2_origin;

			while (label[idx1] == 1)
			{
				if (idx1 == (constantTeamNum - 1))
					break;
				idx1++;

			}
			if (idx1 == (constantTeamNum - 1))
				break;

			idx2 = idx1 + 1;
			while (label[idx2] == 1)
			{
				if (idx2 == (constantTeamNum - 1))
					break;
				idx2++;
			}
			//可以匹配后，向后移动idx1和idx2，调用递归继续向后探索
			f(idx1, idx2, num, data, label);
			//当前匹配对的状态遍历完成后，将该状态重置，保持idx1不变，向后移动idx2继续探索
			label[idx1_origin] = 0;
			label[idx2_origin] = 0;
			idx_vec[--idx_] = -1;
			idx_vec[--idx_] = -1;

		}
		else
		{
			//匹配不满足，首先查看idx1是否已经被匹配，如果是，则向后移动idx1
			if (label[idx1_origin] == 1)
			{
				int idx1 = idx1_origin;
				while (label[idx1] == 1)
				{
					if (idx1 == (constantTeamNum - 1))
						break;
					idx1++;

				}
				f(idx1, idx1 + 1, num, data, label);
				break;
			}
			// idx1满足的情况下，查看idx2是否已经被匹配，如果是，则继续向后移动idx2(也就是idx2_origin++)
			else if (label[idx2_origin] == 1)
			{
				continue;
			}

		}
	}
	//完成所有数据的匹配后，检测所以数据对状态
	if (idx_ == constantTeamNum)
	{
		num += checkState(label);
		//检测完，计数后，将当前最末尾的匹配对重置，往后回退
		label[idx1_origin] = 0;
		label[idx2_origin] = 0;
		idx_vec[--idx_] = -1;
		idx_vec[--idx_] = -1;
	}
}

void main()
{
	int totalNum = -1;
	cin >> totalNum;

	while (totalNum-- > 0)
	{
		vector<vector<string>> data;
		//label 记录每个数据的匹配状态，在计算过程中，会被不停的刷新
		vector<int> label(constantTeamNum, 0); 
		string teamStr, areaStr;

		for (int teamNum = 0; teamNum < constantTeamNum; teamNum++)
		{
			vector<string> tmp_vec;
			cin >> teamStr >> areaStr;
			tmp_vec.push_back(teamStr);
			tmp_vec.push_back(areaStr);
			data.push_back(tmp_vec);
		}

		int num = 0;
		//
		f(0, 1, num, data, label);
		cout << num << endl;

	}

	return;
}