#include "CallNum.h"

CallNum::CallNum()
{
	CInfo = CardsInfo::Instance();
	pSplitCards = new SplitCard();
}

CallNum::~CallNum()
{
}

CallNum* CallNum::Instance()
{
	static CallNum instance;

	return &instance;
}



//�����жϺ���

int CallNum::CardForce(int iCards[])
{

	
	int iMyCards[18] = { 0 };//��������

	//ż��Ϊ�ƵĴ�С������Ϊ���Ƶ�����
	int iRepeat[27] = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };//���Ƽ�����
	
	int iOrder[18] = { 0 };//���� 

	int iBomb[5] = { 0 };//ը��
	int iPair[9] = { 0 };//����
	int iThree[6] = { 0 };//����һ

	int iStraight[9] = { 0 };//˳��

	int iSingle = 0;//���ţ����ƣ�

	int iEntry = 0;//������  ///A 2 ��С��

	int iForce = 0;//����

	bool bLock = true;//������


	int*single = pSplitCards->startSplitCard(iCards, 7);

	for (int i = 0; single[i] != -1; i++)
	{
		if (single[i] != -2&&single[i]<44)
		{
			iSingle++;
		}
	}



	//�������ͣ�ת��Ϊʵ�ʵ�����������������
	for (int i = 0; i < 17; i++)
	{
	
		if (iCards[i] / 4 == 0)
			iMyCards[i] = 3;    //3
		if (iCards[i] / 4 == 1)
			iMyCards[i] = 4;    //4
		if (iCards[i] / 4 == 2)
			iMyCards[i] = 5;    //5
		if (iCards[i] / 4 == 3)
			iMyCards[i] = 6;    //6
		if (iCards[i] / 4 == 4)
			iMyCards[i] = 7;    //7
		if (iCards[i] / 4 == 5)
			iMyCards[i] = 8;    //8
		if (iCards[i] / 4 == 6)
			iMyCards[i] = 9;    //9
		if (iCards[i] / 4 == 7)
			iMyCards[i] = 10;    //10
		if (iCards[i] / 4 == 8)
			iMyCards[i] = 11;    //J
		if (iCards[i] / 4 == 9)
			iMyCards[i] = 12;    //Q
		if (iCards[i] / 4 == 10)
			iMyCards[i] = 13;    //K
		if (iCards[i] / 4 == 11)
		{
			iMyCards[i] = 14;    //A
			iEntry++;
		}
		if (iCards[i] / 4 == 12)
		{
			iMyCards[i] = 22;    //2
			iEntry++;
		}
		if (iCards[i] == 52)
		{
			iMyCards[i] = 66;    //С��
			iEntry++;
		}
		if (iCards[i] == 53)
		{
			iMyCards[i] = 99;    //����
			iEntry++;
		}
	}

	//���ӡ�����һ��ը���ĵ�һ��ɸѡ
	for (int i = 0, j = 0; i < 17; i++)
	{
		if (iMyCards[i] == iMyCards[i + 1])
		{
			iRepeat[j] = iMyCards[i + 1];
			iRepeat[j + 1]++;
		}
		else
		{
			j += 2;
		}
	}


	//�ڶ���ɸѡ
	for (int i = 1, j = 0, k = 0, l = 0; i < 26; i += 2)
	{	//ը������j ���Ӽ���k������һ����l
		//ը���ļ���
		if (iRepeat[i] == 4)
		{
			iBomb[j] = iRepeat[i - 1];
			j++;
		}
		//���ӵļ���
		if (iRepeat[i] == 2)
		{
			iPair[k] = iRepeat[i - 1];
			k++;
		}
		//����һ�ļ���
		if (iRepeat[i] == 3)
		{
			iThree[l] = iRepeat[i - 1];
			l++;
		}
	}


	//˳�ӵĵ�һ��ɸѡ
	for (int i = 0, j = 0; i < 17; i++)
	{	
		if (iMyCards[i ] + 1 == iMyCards[i + 1])
		{	
			iOrder[j] = iMyCards[i];    ///����������ڵ��Ƶ���������ֻ��¼��ǰһ��
			j++;
		}
		///�������ڵ��� ���ߴ���ǰ��2�㼰���� ����Ϊ���һ����
		else if (iMyCards[i] + 1 < iMyCards[i + 1]|| i == 16)
		{
			///
			if (iOrder[j - 1] + 1 == iMyCards[i])
			{
				iOrder[j] = iMyCards[i];
				j += 2;
			}
		}
		else
		{
			continue;
		}
	}

	//˳�ӵĵڶ���ɸѡ
	for (int i = 0, j = 0; i < 17; i++)
	{
		if (iOrder[i] != 0)
		{
			if (bLock)
			{
				iStraight[j] = iOrder[i];
				j++;
				bLock = false;	
			}
		}
		else
		{
			if (iOrder[i - 1] == 0 && iOrder[i + 1] == 0)
			{
				break;
			}
			else
			{
				if (iOrder[i - 1] - iStraight[j - 1] >= 4)
				{
					iStraight[j] = iOrder[i - 1];
					j++;
					iStraight[j] = 0;
					j++;
					bLock = true;
				}
				else
				{
					iStraight[j - 1] = 0;
					j--;
					bLock = true;
				}
			}
		}
	}



/*	����е����⣬���ǵ���splitcard��İɡ���
//���Ƶļ��� (˳���еĵ��Ʋ��㣬���ڵ���A�ĵ��Ʋ���) 
	for (int i = 0; i < 17; i++)
	{
		if (iMyCards[i] != iMyCards[i - 1] && iMyCards[i] != iMyCards[i + 1] && iMyCards[i] < 14)
		{
			iSingle++;
			//��˳�ӣ���鵥���Ƿ���˳����

			for (int j = 0; j < 9; j = j + 3)//iStraight����ĸ�ʽΪ ˳����㣬˳�ӽ�㣬0��˳����㣬˳�ӽ�㣬0
			{
				if (iStraight[j] != 0)
				{
					if (iMyCards[i] >= iStraight[j] && iMyCards[i] <= iStraight[j + 1])//���������˳���� ����--
					{
						iSingle--;
					}
				}
			}
		}
	}

	for (int j = 0; j < 9; j = j + 3)//iStraight����ĸ�ʽΪ ˳����㣬˳�ӽ�㣬0��˳����㣬˳�ӽ�㣬0
	{
		if (iStraight[j] != 0)
		{
				for (int k = 0; k < 9; k++)
				{
					if (iPair[k] != 0 && iPair[k] >= iStraight[j] && iPair[k] <= iStraight[j + 1])//���������˳���У�����++
					{
						iSingle++;
					}
				}
		}
	}*/
	

	//�����ļ���
	for (int i = 0; i < 17; i++)
	{
		//ը����4��������������м��ƣ���Ҫ��1����Ϊ��ʱ���ò����ը��ȥ��˳�ӡ�
		if (i < 4 && iBomb[i] != 0)
		{
			iForce += 4;
			if (iBomb[i] < 11 && iBomb[i] > 6)
			{
				iForce -= 1;
			}
		}

		//QQ,KK,AA����ֵ��1
		if (i < 9 && iPair[i] >=12&&iPair[i]!=22)
		{
			iForce += 1;
		}

		//3��J�����ϼ�1������
		if (i < 6 && iThree[i] > 10&& iThree[i]!=22)
		{
			iForce += 1;
		}

		//˳�Ӽ�1��2������
		if (i < 9 && iStraight[i + 1] != 0 && iStraight[i] != 0)
		{
			if (iStraight[i + 1] - iStraight[i] > 8 || iStraight[i + 1] > 12)
			{
				iForce += 2;
			}
			else
			{
				iForce += 1;
			}
		}

	}

	//������С�ڵ���,���Ų��ױ�����
	if (iEntry < iSingle)
	{
		int iTemp = iSingle - iEntry;
		iForce -= iTemp;
	}

	//���������С��3����������ֵ
	if (iSingle < 3)
	{
		iForce +=3 - iSingle;
	}
	cout << " SingleNumber " << iSingle << endl;
	return iForce;
}




//�жϽ��Ƶ���
int CallNum::CallCardAnalyze(Ddz* pDdz)
{
	int iInHand = 0;//������
	int iPip = 0;//�Ƶ�
	int iCallPoint = -1;//���ս�����
	int iHeadCallPointSecond;//�ϼҽ����ܵ���
	int iHeadCallPointFirst;//���ϼҽ��Ƶ���

	//��ȡ�ϼҽ�����
	if (pDdz->iBid[0] == -1)
	{
		iHeadCallPointFirst = -1;//���ϼҽ��Ƶ���
		iHeadCallPointSecond = -1;//�ϼҽ��Ƶ���
	}
	else if (pDdz->iBid[1] == -1)
	{
		iHeadCallPointFirst = -1;//���ϼҽ��Ƶ���
		iHeadCallPointSecond = pDdz->iBid[0];//�ϼҽ��Ƶ���
	}
	else if (pDdz->iBid[2] == -1)
	{
		iHeadCallPointFirst = pDdz->iBid[0];//���ϼҽ��Ƶ���
		iHeadCallPointSecond = pDdz->iBid[1];//�ϼҽ��Ƶ���
	}

	int bomb=0;
	int one=0;
	//�Ƶ��ж�
	for (int i = 0; i<17; i++)
	{
		iInHand = pDdz->iOnHand[i];
		if (iInHand >= 53)		//����
			//iPip += 3;
			bomb += 2;
		else if (iInHand >= 52)	//С��
			bomb += 1;
		else if (iInHand >= 48)	//2
			iPip++;
		else if (iInHand >= 44)
			one++;
	} 

	if (bomb == 3)
		iPip += 7;
	if (bomb == 1)
		iPip += 2;
	if (bomb == 2)
		iPip += 3;
	if (one >= 2)
		iPip++;

	//���Ʒ���
	//���ƵĻ�������������4���Ƶ�
	if (iPip >=4)
	{
		int iPipNum = CardForce(pDdz->iOnHand) + iPip;
		//Test
		cout << "Card Force: " << iPipNum-iPip << " �Ƶ�ֵ�� " << iPip << " iPipNum " << iPipNum << endl;
		if (iHeadCallPointFirst == -1 && iHeadCallPointSecond == -1)
		{
			if (iPipNum > 11)
			{
				iCallPoint = 3;
			}
			else if (iPipNum > 9)
			{
				iCallPoint = 2;
			}
			else if (iPipNum > 7)
			{
				iCallPoint = 1;
			}
			else
			{
				iCallPoint = 0;
			}
		}
		if (iHeadCallPointFirst == -1 && iHeadCallPointSecond != -1)
		{
			if (iPipNum > 11 && iHeadCallPointSecond != 3)
			{
				iCallPoint = 3;
			}
			else if (iPipNum > 9)
			{
				if (iHeadCallPointSecond <= 2)
				{
					iCallPoint = 3;
				}
				else
				{
					iCallPoint = 0;
				}
			}
			else if (iPipNum > 7)
			{
				if (iHeadCallPointSecond <= 1)
				{
					iCallPoint = 2;
				}
				else
				{
					iCallPoint = 0;
				}
			}
			else
			{
				if (iHeadCallPointSecond == 0)
				{
					iCallPoint = 1;
				}
				else
				{
					iCallPoint = 0;
				}
			}
		}
		if (iHeadCallPointFirst != -1 && iHeadCallPointSecond != -1)
		{
			if (iPipNum > 11 && iHeadCallPointFirst != 3 && iHeadCallPointSecond != 3)
			{
				iCallPoint = 3;
			}
			else if (iPipNum > 9)
			{
				if (iHeadCallPointSecond <= 2 && iHeadCallPointFirst <= 2)
				{
					iCallPoint = 3;
				}
				else
				{
					iCallPoint = 0;
				}
			}
			else if (iPipNum > 7)
			{
				if (iHeadCallPointSecond <= 1 && iHeadCallPointFirst <= 1)
				{
					iCallPoint = 2;
				}
				else
				{
					iCallPoint = 0;
				}
			}
			else
			{
				if (iHeadCallPointSecond == 0 && iHeadCallPointFirst == 0)
				{
					iCallPoint = 1;
				}
				else
				{
					iCallPoint = 0;
				}
			}
		}
	}
	else
	{
		int iPipNum = CardForce(pDdz->iOnHand) + iPip;
		//Test
		cout << "Card Force: " << iPipNum - iPip << " �Ƶ�ֵ�� " << iPip << " iPipNum " << iPipNum << endl;
		iCallPoint = 0;
	}
		


	//�ж��Ƿ���2�����������ֵ�ǰ�ᣬ����Ҫ��1������2���� ����������һ����
	int j = 0,k=0;
	if (iCallPoint == 3)
	{
		for (int i = 0; i < 17; i++)
		{
			if (pDdz->iOnHand[i]/4==12) 
			{
				j++;//2
			}
			else if (pDdz->iOnHand[i] / 4 == 13)
			{
				k++;//��
			}
		}
		if (j < 2 || k < 1) {
			iCallPoint = 2;
		}
		if (j >= 1 && k == 2)
		{
			iCallPoint = 3;
		}
	}

	//���ؽ��Ƶ���
	return iCallPoint;
}
