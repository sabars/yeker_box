/*
*********************************************************************************************************
*											        ePDK
*						            the Easy Portable/Player Develop Kits
*									           hello world sample
*
*						        (c) Copyright 2006-2007, Steven.ZGJ China
*											All	Rights Reserved
*
* File    : pfhead.h
* By      : Steven.ZGJ
* Version : V1.00
*********************************************************************************************************
*/

#include "epdk.h"


extern __s32 test_app(void *p_arg);
#pragma arm section rodata="MAGIC"
const __exec_mgsec_t exfinfo =
{
	{'e','P','D','K','.','e','x','f'},		//.magic
	0x01000000,								//.version
	0,										//.type
	/*���̶ѵĵ�ַ������С��32M�����ұ�֤�ѵķ��ò������32M�߽�            */
	0x1F00000,
	/* ���̶Ѵ�С����ֵ������������Ҫ���Զ����ӣ�������ܲ���32M�߽�      */
	0x400,
	/*��������ڵ�ַ                                                        */
	test_app,	
	/*������ջ��С                                                          */
	0x40000,				
	/* �������������ȼ�                                                     */
  KRNL_priolevel3		
};
#pragma arm section 