#include <stdio.h>
#include <string.h>
#include <iostream>
#define kPlayerName "�ɻ���"
#define kPlaMax 500
#pragma once


using namespace std;

//�޸��ˣ�����ӱ
//�洢������Ϣ
//���ڣ�2017/7/13
//ȡ��iPlaCount��ģ������б�ʹ�øı���趨,iPlaArr��PASS����Ϊ-3
struct Ddz
{
	int  iStatus;			//����״̬-1����,0����,1��ʼ
	char sCommandIn[80];	//ͨ����������
	char sCommandOut[80];	//ͨ���������
	int iOnHand[21];		//�����ƣ�����ֵ��ʼ��Ϊ-1��
	int iOnTable[162][21];	//�ѳ������飨����ֵ��ʼ��Ϊ-2��ÿ����һ���ƣ���-1��β��Pass��Ϊ-1
	int iUpPlayerCards;		//�ϼ���������
	int iDownPlayerCards;	//�¼���������
	int iToTable[21];		//Ҫ������
	int iOnOtherHand[55];   //������������е���
	char sVer[80];			//Э��汾��
	char sName[80];			//����ѡ�ֳƺ�
	char cDir;				//��ҷ�λ���
	char cLandlord;			//������ҷ�λ���
	char cLastPlay;         //��ģ�����ʱ��λ������ҷ�λ���
	char cWinner;			//ʤ���߷�λ���
	int iBid[3];			//���ƹ���
	int iBmax;				//��ǰ��������ֵ��{0,1,2,3}
	int iOTmax;				//��ǰ��������
	int iRoundNow;			//��ǰ�ִ�
	int iRoundTotal;		//���ܾ���
	int iTurnNow;			//��ǰ�ִ�
	int iTurnTotal;			//������
	int iLevelUp;			//����ѡ����
	int iScoreMax;			//ת���÷ֽ���
	int iVoid;				//��Ͼ���м������
	int iLef[3];			//���ֵ���
	int iLastPassCount;		//��ǰ��������PASS����ֵ��[0,2],��ֵ2����������ȡ0��һ��PASSȡ1������PASSȡ2��
	int iLastTypeCount;		//��ǰ��������������ֵ��[0,1108],��ֵ0��iLastPassCount=0ʱ����ֵ��=1ʱ����ԭֵ��=2ʱֵΪ0��//���³���
	int iLastMainPoint;		//��ǰ�������Ƶ�����ֵ��[0,15],��ֵ-1��iLastPassCount=0ʱ����ֵ����=1ʱ����ԭֵ��=2ʱֵΪ-1��
};

