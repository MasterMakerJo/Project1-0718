#include "SplitCard.h"

/*
*  
* ����޶��ߣ�������&&��С�� 2017.7.13
*/
SplitCard::SplitCard()
{
	iCards = NULL;//�ⲿ����

	//���صĽ��
	iResult[0] = iRocket;//���	
	iResult[1] = iBomb;	//ը��
	iResult[2] = iThree;//����
	iResult[3] = iLinkThree;//��˳
	iResult[4] = iLinkSingle;//��˳
	iResult[5] = iLinkDouble;//˫˳
	iResult[6] = iDouble;//����
	iResult[7] = iSingle;//����
}

SplitCard::~SplitCard()
{
}

SplitCard* SplitCard::Instance()
{
	static SplitCard instance;

	return &instance;
}

//��ʼ������
void SplitCard::initData()
{
	for (int k = 0; k < 4; k++)
	{
		iRocket[k] = 0;//���
	}
	for (int j = 0; j < 38; j++)
	{
		iMyCards[j] = 0;//�ڲ�����
		iWaitOrder[j] = 0;//�����Ƶ���
		iOrder[j] = 0;//�����Ƶ���
		iMinLinkIndex[j] = 0;//��С����������

		iSingleInRepeatIndex[j] = -1;//������ĵ��Ƶ�����
		iSingleInLinkIndex[j] = -1;//˳����ĵ��Ƶ�����
		iLinkIndex[j] = -1;//˳�ӵ�����

		iBomb[j] = 0;//ը��
		iSingle[j] = 0;//����
		iDouble[j] = 0;//����
		iThree[j] = 0;//����
		iLinkSingle[j] = 0;//��˳
		iLinkDouble[j] = 0;//˫˳
		iLinkThree[j] = 0;//��˳
	}
	for (int i = 0; i < 26; i++)
	{
		iRepeat[i] = i % 2;//����  0-25  0 1 0 1 0 1...
	}
}

//�������ͣ���׼�������ڲ������������ͬ���ϸ�
void SplitCard::transcode()
{
	for (int i = 0; i < 38; i++)
	{
		if (iCards[i] == -1)
		{
			iMyCards[i] = -1;
			break;
		}
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
			iMyCards[i] = 14;    //A
		if (iCards[i] / 4 == 12)
			iMyCards[i] = 22;    //2
		if (iCards[i] == 52)
			iMyCards[i] = 66;    //С��
		if (iCards[i] == 53)
			iMyCards[i] = 99;    //����
	}
}

//�ж����ƣ��ϸ�
void SplitCard::judgeRepeat()
{
	for (int i = 0, j = 0, k = 0; iMyCards[i] != -1; i++)
	{
		if (iMyCards[i] == iMyCards[i + 1])
		{
			iRepeat[j] = iMyCards[i + 1];
			iRepeat[j + 1]++;
		}
		else
		{
			j += 2;
			//�������ظ��ĵ���
			if (iMyCards[i] != iMyCards[i - 1] && iMyCards[i] != iMyCards[i + 1])
			{
				iSingleInRepeatIndex[k] = i;
				k++;
			}
		}
	}
}

//�ж����ƣ��ϸ�
void SplitCard::judgeOrder()
{
	int iLinkEnd = iWaitOrder[0];//�����е����һ����ֵ
	int iLinkEndIndex = 0;//һ�����ƵĿ�ʼ����
	int iEndIndex = -1;//��������-1��������
	bool bStartLock = true;//�Ƿ���һ�����Ƶı�־

	//��ʼ��������
	for (int i = 1, j = 1; iWaitOrder[i] != -1; i++, j++)
	{
		//һ�����ƵĿ�ʼ
		if (bStartLock)
		{
			//��ʼ����λ�Ƿ�����
			if (iWaitOrder[i] == iLinkEnd + 1)
			{
				iOrder[iLinkEndIndex] = iLinkEnd;
				iOrder[j] = iWaitOrder[i];
				iLinkEnd = iOrder[j];
			}
			//��ʼ����λ�Ƿ����
			else if (iLinkEnd == iWaitOrder[i])
			{
				iOrder[iLinkEndIndex] = 0;
				iOrder[j] = iWaitOrder[i];
			}
			//��ʼ����λ�Ƿ����
			else if (iLinkEnd + 1 < iWaitOrder[i])
			{
				iOrder[iLinkEndIndex] = 0;
				iOrder[j] = iWaitOrder[i];
				iLinkEnd = iOrder[j];
			}
			//��ʼ����λ�ĵڶ�λΪ0
			else
			{
				iOrder[j] = 0;
			}
			//����
			if (iWaitOrder[i] != 0)
			{
				bStartLock = false;
			}
		}
		else
		{
			//���һλ����
			if (iLinkEnd + 1 == iWaitOrder[i])
			{
				iOrder[j] = iWaitOrder[i];
				iLinkEnd = iOrder[j];
			}
			//���һλ�����һ�����ƽ���
			else if (iLinkEnd + 1 < iWaitOrder[i])
			{
				iLinkEndIndex = i;
				iLinkEnd = iWaitOrder[i];
				bStartLock = true;
			}
			//���һλ��ȣ����һλΪ0
			else
			{
				iOrder[j] = 0;
			}
		}
		iEndIndex = j + 1;
	}
	if (iEndIndex == -1)
	{
		iEndIndex = 0;
	}
	iOrder[iEndIndex] = -2;
	iEndIndex++;
	iOrder[iEndIndex] = -1;
}

//ѡȡ��С�������ƣ��ϸ�
void SplitCard::judgeMinLink(int iMinLink)
{
	int iLinkEnd = 0;//�����е����һ����ֵ
	int iFiveIndex[] = { -1, -1, -1, -1, -1 };//�����Ƶ�����
	int iIndex = 0;//��С�����Ƶı�������
	int iLinkNum = 0;//���Ƶ�����
	int iIsCircle = -1;//�Ƿ������С�����������ı�־

	//ѭ��������С������
	while (iIsCircle != iIndex)
	{
		//������WaitOrder����������
		judgeOrder();
		//���ϴ���С�����Ľ�����������
		iIsCircle = iIndex;
		//Order��ʼλ�����⴦��
		if (iOrder[0] != 0)
		{
			iLinkEnd = iOrder[0] - 1;
		}
		//�����Order��������С������
		for (int i = 0; iOrder[i] != -1; i++)
		{
			//�ҵ�����������������
			if (iLinkNum == iMinLink)
			{
				for (int k = 0; k < iMinLink; k++)
				{
					iMinLinkIndex[iIndex] = iFiveIndex[k];
					iWaitOrder[iFiveIndex[k]] = 0;
					iFiveIndex[k] = -1;
					iIndex++;
				}
				iMinLinkIndex[iIndex] = -2;
				iIndex++;
				iLinkNum = 0;
				iLinkEnd = 0;
				break;
			}
			//������������������������
			else
			{
				//����
				if (iOrder[i] != 0 && iLinkEnd + 1 == iOrder[i])
				{
					iFiveIndex[iLinkNum] = i;
					iLinkEnd = iOrder[i];
					iLinkNum++;
				}

				//һ�����ƽ�������С������
				else if (iLinkEnd + 1 < iOrder[i])
				{
					for (int k = iLinkNum; k >= 0; k--)
					{
						iFiveIndex[k] = -1;
					}
					iLinkNum = 0;
					iLinkEnd = iOrder[i];
					iFiveIndex[iLinkNum] = i;
					iLinkNum++;
				}
				//��һλΪ0�����һ��λ���
				else
				{
					//��һλΪ0�����ڶ�λ��Ϊ0
					if (iLinkEnd == 0)
					{
						iLinkEnd = iOrder[i + 1] - 1;
					}
				}
			}
		}
	}
	//������
	iMinLinkIndex[iIndex] = -1;
}

//�ж�˳�ӣ��ϸ�
void SplitCard::judgeLink(int iMinLink)
{
	int iLinkExtendIndex[12] = { 0 };//��չ�����ƣ���ÿ�������Ľ�������Ϊ��ʼ����-2Ϊ������
	int iWriteIndex = -1;
	int iReadIndex = 0;
	bool bIsExtendLink = false;
	int iLinkSingleIndex = 0;

	judgeMinLink(iMinLink);

	//����ʣ����ֵ
	for (int i = 0; iWaitOrder[i] != -1; i++)
	{
		if (iWaitOrder[i] != 0)
		{
			//�����Ƿ������չ
			//��չ�Ƿ�����������������MinLinkIndex��������������LinkExtendIndex�м�����չ
			if (!bIsExtendLink)
			{
				for (int j = iMinLink - 1; iMinLinkIndex[j] != -1; j = j + iMinLink + 1)
				{
					if (iMinLinkIndex[j] != 0 && iMyCards[iMinLinkIndex[j]] + 1 == iWaitOrder[i])
					{
						iWriteIndex++;
						iLinkExtendIndex[iWriteIndex] = iMinLinkIndex[j];
						iWriteIndex++;
						iLinkExtendIndex[iWriteIndex] = i;
						iWaitOrder[i] = 0;
						bIsExtendLink = true;
					}
				}
			}
			else
			{
				for (int j = i; iWaitOrder[j] != -1; j++)
				{
					if (iMyCards[iLinkExtendIndex[iWriteIndex]] + 1 == iWaitOrder[j])
					{
						iWriteIndex++;
						iLinkExtendIndex[iWriteIndex] = j;
						iWaitOrder[j] = 0;
						i = j;
					}
					else if (iMyCards[iLinkExtendIndex[iWriteIndex]] + 1 < iWaitOrder[j] || iWaitOrder[j + 1] == -1)
					{
						iWriteIndex++;
						iLinkExtendIndex[iWriteIndex] = -2;
						i = j - 1;
						bIsExtendLink = false;
						break;
					}
					else
					{
						continue;
					}
				}
			}
		}
		if (iWaitOrder[i + 1] == -1)
		{
			iWriteIndex++;
			iLinkExtendIndex[iWriteIndex] = -2;
		}
	}

	//�ϲ�����
	for (int j = 0; iMinLinkIndex[j] != -1; iLinkSingleIndex++, j++)
	{
		//��ȡ������
		if (iMinLinkIndex[j] != -2)
		{
			iLinkIndex[iLinkSingleIndex] = iMinLinkIndex[j];
		}
		//��ȡ��չ��
		else
		{
			//����չ
			if (iLinkExtendIndex[iReadIndex] != 0 && iLinkExtendIndex[iReadIndex] == iMinLinkIndex[j - 1])
			{
				iReadIndex++;
				iLinkIndex[iLinkSingleIndex] = iLinkExtendIndex[iReadIndex];
				iReadIndex++;
				iLinkSingleIndex++;
				while (iLinkExtendIndex[iReadIndex] != -2)
				{
					iLinkIndex[iLinkSingleIndex] = iLinkExtendIndex[iReadIndex];
					iReadIndex++;
					iLinkSingleIndex++;
				}
				iLinkIndex[iLinkSingleIndex] = -2;
				iReadIndex++;
			}
			//������չ
			else
			{
				iLinkIndex[iLinkSingleIndex] = -2;
			}
		}
	}
	//������
	iLinkIndex[iLinkSingleIndex] = -1;
	//�ж�����˳���Ƿ�����ٺϲ�
	for (int k = 0; iLinkIndex[k] != -1; k++)
	{
		if (iLinkIndex[k] == -2)
		{
			if (iMyCards[iLinkIndex[k - 1]] + 1 == iMyCards[iLinkIndex[k + 1]])
			{
				for (int l = k; iLinkIndex[l] != -1; l++)
				{
					iLinkIndex[l] = iLinkIndex[l + 1];
				}
			}
		}
	}
}

//�жϵ�˳���ϸ�
void SplitCard::judgeLinkSingle()
{
	int iEndIndex = -1;//��������-1��������

	//��ʼ��WaitOrder
	for (int l = 0; l < 38; l++)
	{
		iWaitOrder[l] = iMyCards[l];
	}

	judgeLink(5);

	//��˳��ɸѡ��ĵ���
	for (int i = 0, j = 0; iWaitOrder[i] != -1; i++)
	{
		if (iWaitOrder[i] > 0)
		{
			iSingleInLinkIndex[j] = i;
			j++;
			iWaitOrder[i] = 0;
		}
	}

	//�洢��˳�ⲿ����
	for (int k = 0; iLinkIndex[k] != -1; k++)
	{
		if (iLinkIndex[k] != -2)
		{
			iLinkSingle[k] = iCards[iLinkIndex[k]];
		}
		else
		{
			iLinkSingle[k] = iLinkIndex[k];
		}
		iEndIndex = k + 1;
	}
	//��ֹ�޵�˳ʱ����Խ��
	if (iEndIndex == -1)
	{
		iEndIndex++;
	}
	iLinkSingle[iEndIndex] = -1;
}

//�жϻ��(�ϸ�)
void SplitCard::judgeRocket()
{
	int j = 0;
	for (int i = 0; iMyCards[i] != -1; i++)
	{
		if (iMyCards[i] == 66 || iMyCards[i] == 99)
		{
			iRocket[j] = iCards[i];
			j++;
		}
	}
	iRocket[j] = -2;
	j++;
	iRocket[j] = -1;
	//ֻ��һ����
	if (iRocket[1] == -2)
	{
		iRocket[0] = -1;
		iRocket[1] = 0;
	}
}

//�ж�ը�����ϸ�
void SplitCard::judgeBomb()
{
	int iBombValue = 0;
	int iCount = 0;
	int iIndex = 0;

	for (int i = 1; i < 26; i += 2)
	{
		if (iRepeat[i] == 4)
		{
			iBombValue = iRepeat[i - 1];
			for (int j = 0; iMyCards[j] != -1; j++)
			{
				if (iBombValue == iMyCards[j])
				{
					iBomb[iIndex] = iCards[j];
					iCount++;
					iIndex++;
				}
				if (iCount == 4)
				{
					iBomb[iIndex] = -2;
					iIndex++;
					iCount = 0;
					break;
				}
			}
		}
	}
	iBomb[iIndex] = -1;
}

//�ж϶��ƣ��ϸ�
void SplitCard::judgeDouble()
{
	int iDoubleValue = 0;
	int iCount = 0;
	int iIndex = 0;

	for (int i = 1; i < 26; i += 2)
	{
		if (iRepeat[i] == 2)
		{
			iDoubleValue = iRepeat[i - 1];
			for (int j = 0; iMyCards[j] != -1; j++)
			{
				if (iDoubleValue == iMyCards[j])
				{
					iDouble[iIndex] = iCards[j];
					iCount++;
					iIndex++;
				}
				if (iCount == 2)
				{
					iDouble[iIndex] = -2;
					iIndex++;
					iCount = 0;
					break;
				}
			}
		}
	}
	iDouble[iIndex] = -1;
}

//�ж�˫˳���ϸ�
void SplitCard::judgeLinkDouble()
{
	int iIndex = 0;
	int iDoubleValue = 0;
	int iLastWaitOrderIndex = -1;

	//��ʼ��WaitOrder
	for (int k = 1; k < 26; k += 2)
	{
		if (iRepeat[k] >= 2)
		{
			iDoubleValue = iRepeat[k - 1];
			for (int l = 0; iMyCards[l] != -1; l++)
			{
				if (iDoubleValue == iMyCards[l])
				{
					iWaitOrder[l] = iMyCards[l];
					iLastWaitOrderIndex = l + 1;
					break;
				}
			}
		}
	}
	if (iLastWaitOrderIndex == -1)
	{
		iLastWaitOrderIndex = 1;
	}
	iWaitOrder[iLastWaitOrderIndex] = -1;

	judgeLink(3);

	for (int i = 0; iLinkIndex[i] != -1; i++)
	{
		if (iLinkIndex[i] != -2)
		{
			for (int j = 0; iMyCards[j] != -1; j++)
			{
				if (iMyCards[iLinkIndex[i]] == iMyCards[j])
				{
					iLinkDouble[iIndex] = iCards[j];
					iIndex++;
					iLinkDouble[iIndex] = iCards[j + 1];
					iIndex++;
					break;
				}
			}
		}
		else
		{
			iLinkDouble[iIndex] = -2;
			iIndex++;
		}
	}
	iLinkDouble[iIndex] = -1;
}

//�ж��������ϸ�
void SplitCard::judgeThree()
{
	int iThreeValue = 0;
	int iCount = 0;
	int iIndex = 0;

	for (int i = 1; i < 26; i += 2)
	{
		if (iRepeat[i] == 3)
		{
			iThreeValue = iRepeat[i - 1];
			for (int j = 0; iMyCards[j] != -1; j++)
			{
				if (iThreeValue == iMyCards[j])
				{
					iThree[iIndex] = iCards[j];
					iCount++;
					iIndex++;
					if (iCount == 1)
					{
						iWaitOrder[j] = iMyCards[j];
					}
				}
				if (iCount == 3)
				{
					iThree[iIndex] = -2;
					iIndex++;
					iCount = 0;
					break;
				}
			}
		}
	}
	iThree[iIndex] = -1;
}

//�ж���˳
void SplitCard::judgeLinkThree()
{
	judgeThree();//�Ƚ������Ž�iThree��
	int iIndex = 0;//iLinkThree���±�

	int iLinkIndex[8];//��¼�����������iLinkThree������±ꣻ
	int iLinkCount= 0;

	if (iThree[4] == -1||iThree[4]==0)//���ֻ��һ����������û�����������أ�
	{
		iLinkThree[0] = -1;
		return;
	}
	else 
	{
		for (int i = 0; i < 8; i++)//��ʼ������
		{
			iLinkIndex[i] = -1;
		}
		//012,3,456,7,8910,11,121314,15
		for (int i = 4; iThree[i]!=-1 ; i=i+4)//ÿ��������iThree�п�ʼ���±�Ϊ0��4��8��12...
		{
			if (iThree[i - 4] / 4 + 1 == iThree[i]/4)//�������������ʼ���±����1��������˳
			{
				if (iLinkCount == 0)			//�����û�м�¼����˳���±�
				{
					iLinkIndex[iLinkCount++] = i - 4;
					iLinkIndex[iLinkCount++] = i;
				}
				else
				{
					if (iLinkIndex[iLinkCount - 1] == i - 4)//�������������˳������3334444  444555�����������333444555
					{
						iLinkIndex[iLinkCount++] = i;
					}
					else
					{
						iLinkIndex[iLinkCount++] = -2;
						iLinkIndex[iLinkCount++] = i - 4;
						iLinkIndex[iLinkCount++] = i;
					}
				}
					
			}
		}
	}
	
	for (int i = 0; iLinkIndex[i]!=-1; i++) //�ü�¼���±��ȡiThree���Ƶı�����iLinkThree��
	{
		if (iLinkIndex[i] != -2)
		{
			iLinkThree[iIndex++] = iThree[iLinkIndex[i]];
			iLinkThree[iIndex++] = iThree[iLinkIndex[i]+1];
			iLinkThree[iIndex++] = iThree[iLinkIndex[i]+2];
		}
		else if (iLinkIndex[i] == -2)
		{
			iLinkThree[iIndex++] = -2;
		}
	}
	iLinkThree[iIndex] = -1;
}


void SplitCard::OptimizeLinkSingle() {

	judgeLinkSingle();

	int iLinkIndex[10];
	int j = 1, i = 0;
	iLinkIndex[0] = 0;
	//				0 1 2  3  4  5  6  7  8 9 10  11  12...
	//��¼��˳��β�±� 1 2 3  4  5  -2  6  7  8 9 10  -2  -1
	//	iLinkIndex	0 4 -2 6  10 -2  -1
	for (i; iLinkSingle[i] != -1; i++)
	{
		if (iLinkSingle[i] == -2)
		{
			iLinkIndex[j] = i - 1;
			iLinkIndex[j + 1] = -2;
			if (iLinkSingle[i + 1] != -1)
			{
				iLinkIndex[j + 2] = i + 1;
				j = j + 3;
			}
			else
			{
				j = j + 2;
				iLinkIndex[j] = -1;
			}

		}
	}

	//	iLinkIndex[j] = -1;
	judgeThree();
	//				0 1 2  3  4  5  6  7  8 9 10  11  12...
	//��¼��˳��β�±� 1 2 3  4  5  6  -2 7  8 9 10  11  12 -2  -1
	//	iLinkIndex	0 5 -2 7  12 -2  -1
	if (iLinkSingle[0] != -1)//�����һ��˳�Ӽ�����
	{
		for (int i = 0; iLinkIndex[i] != -1; i = i + 3)
		{
			for (int k = 0; iThree[k] != -1; k = k + 4)
			{
				if (iLinkSingle[iLinkIndex[i + 1]] / 4 - iLinkSingle[iLinkIndex[i]] / 4 >= 5)//��
				{
					if ( iLinkSingle[iLinkIndex[i]] / 4 == iThree[k] / 4)//�����˳�����ϵ���λ������������ɾ��
					{
						for (int j = iLinkIndex[i]; iLinkSingle[j] != -1; j++)
						{
							iLinkSingle[j] = iLinkSingle[j + 1];//ȥ���±�Ϊ iLinkIndex[i]���Ʊ���
						}
						iLinkIndex[i + 1]--;
					}
					else if ( iLinkSingle[iLinkIndex[i + 1]] / 4 == iThree[k] / 4)//β
					{
						
						for (int j = iLinkIndex[i + 1]; iLinkSingle[j] != -1; j++)
						{
							iLinkSingle[j] = iLinkSingle[j + 1];//ȥ���±�Ϊ iLinkIndex[i+1]���Ʊ���
						}
						iLinkIndex[i + 1]--;
					}
				}
				
			}
		}
	}

}

//�жϵ��ƣ��ϸ�
void SplitCard::judgeSingle()
{
	int iIndex = 0;

	//judgeLinkSingle();
	OptimizeLinkSingle();
	int iCopyCards[21];//����iCard;

	int i = 0;
	
	for (i; iCards[i]!=-1; i++)
	{
		iCopyCards[i] = iCards[i];
		//cout << iCards[i] << " ";
	}

	iCopyCards[i] = -1;
	for (int j = 0; iResult[4][j] != -1; j++)
	{
		for (int i = 0; iCopyCards[i]!=-1; i++)
		{
			//�����˳���е�����ȣ�ɾ��
			if (iResult[4][j] == iCopyCards[i])
			{
				//iCopyCards[i] = -1;
				for (int k = i; iCopyCards[k]!=-1; k++)
				{
					iCopyCards[k] = iCopyCards[k+1];
				}
				break;
			}
		}
	}
	if (iCopyCards[1] == -1&& iCopyCards[0]!=-1) {
		iSingle[iIndex++] = iCopyCards[0];
	}else {
		for (int i = 0; iCopyCards[i] != -1; i++)
		{
			if (iCopyCards[i] / 4 != iCopyCards[i + 1] / 4 && iCopyCards[i] / 4 != iCopyCards[i - 1] / 4)
			{
				iSingle[iIndex++] = iCopyCards[i];
				iSingle[iIndex++] = -2;
			}
		}
	}
	iSingle[iIndex] = -1;
}


//����ӿڣ��ϸ�
int** SplitCard::startSplitCard(int iInitCards[])
{
	iCards = iInitCards;
	//��ʼ������
	initData();
	//��ֹiInitCards����ֵ
	if (iCards[0] == -1)
	{
		iBomb[0] = -1;
		iSingle[0] = -1;
		iDouble[0] = -1;
		iThree[0] = -1;
		iLinkSingle[0] = -1;
		iLinkDouble[0] = -1;
		iLinkThree[0] = -1;

		return iResult;
	}

	transcode();//ת������

	judgeRepeat();//��������
	judgeRocket();//�жϻ��
	judgeBomb();//�ж�ը��
	//judgeLinkSingle();//�жϵ�˳
	OptimizeLinkSingle();
	judgeDouble();//�ж϶���
	judgeLinkDouble();//�ж�˫˳
	judgeThree();//�ж�����
	judgeLinkThree();//�ж���˳
	judgeSingle();//�жϵ���

	
	return iResult;
}

//����ӿڣ��ϸ�
int* SplitCard::startSplitCard(int iInitCards[], int type)
{
	iCards = iInitCards;
	//��ʼ������
	initData();
	//��ֹiInitCards����ֵ
	if (iCards[0] == -1)
	{
		return iCards;
	}

	transcode();//ת������
	judgeRepeat();//��������

	switch (type)
	{
	case 0:
		judgeRocket();//�жϻ��
		return iRocket;
	case 1:
		judgeBomb();//�ж�ը��
		return iBomb;
	case 2:
		judgeThree();//�ж�����
		return iThree;
	case 3:
		judgeLinkThree();//�ж���˳
		return iLinkThree;
	case 4:
		//judgeLinkSingle();//�жϵ�˳
		OptimizeLinkSingle();
		return iLinkSingle;
	case 5:
		judgeLinkDouble();//�ж�˫˳
		return iLinkDouble;
	case 6:
		judgeDouble();//�ж϶���
		return iDouble;
	case 7:
		judgeSingle();//�жϵ���
		return iSingle;
	default:
		return NULL;
	}
}
