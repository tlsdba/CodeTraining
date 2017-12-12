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
	* \brief ����ѭ���ӵݹ����ʽ��idx1_origin��idx2_origin�ֱ��ʾ�����һ�����ݵ���������ѭ�����Ƶ����ڵ�ǰidx1�£�idx2һֱ������β��̽���Ĺ��̣��ݹ����ҵ���ǰ���ʵ�һ�����ݺ��������̽���������������ݶԡ�
	* ÿ���ݹ麯������������ݲ�ѯ����idx2_origin == constantTeamNumʱ��ɵ�ǰ����
	* �������ʱ�жϵ�ǰ�����Ƿ������ս׶Σ�Ҳ����idx_(��ɵ�ƥ�����ݸ���)�����ܵ�����������ʱ����checkState�鿴��ǰƥ��״̬�Ƿ�����������
	*/

	//
	for (; idx2_origin < constantTeamNum; idx2_origin++)
	{
		//�ж����ݶ��Ƿ�����ƥ������
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
			//����ƥ�������ƶ�idx1��idx2�����õݹ�������̽��
			f(idx1, idx2, num, data, label);
			//��ǰƥ��Ե�״̬������ɺ󣬽���״̬���ã�����idx1���䣬����ƶ�idx2����̽��
			label[idx1_origin] = 0;
			label[idx2_origin] = 0;
			idx_vec[--idx_] = -1;
			idx_vec[--idx_] = -1;

		}
		else
		{
			//ƥ�䲻���㣬���Ȳ鿴idx1�Ƿ��Ѿ���ƥ�䣬����ǣ�������ƶ�idx1
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
			// idx1���������£��鿴idx2�Ƿ��Ѿ���ƥ�䣬����ǣ����������ƶ�idx2(Ҳ����idx2_origin++)
			else if (label[idx2_origin] == 1)
			{
				continue;
			}

		}
	}
	//����������ݵ�ƥ��󣬼���������ݶ�״̬
	if (idx_ == constantTeamNum)
	{
		num += checkState(label);
		//����꣬�����󣬽���ǰ��ĩβ��ƥ������ã��������
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
		//label ��¼ÿ�����ݵ�ƥ��״̬���ڼ�������У��ᱻ��ͣ��ˢ��
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