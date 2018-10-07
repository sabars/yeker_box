/*
************************************************************************************************************************
*                                            repeat mode in register table
*
*                                  Copyright(C), 2006-2010, AllWinner Technology Co., Ltd.
*											       All Rights Reserved
*
* File Name   : reg_sort_mode.h
*
* Author      : Gary.Wang
*
* Version     : 1.0
*
* Date        : 2010.08.31
*
* Description :
* 
* Others      : None at present.
*
*
* History     :
*
*  <Author>        <time>       <version>      <description>
*
* Gary.Wang      2010.08.31        1.0         build the file
*
************************************************************************************************************************
*/
#ifndef  __REG_EXP_SORT_H__
#define  __REG_EXP_SORT_H__

#ifdef __cplusplus
extern "C" {
#endif



/*
****************************************************************************************************
*Name        : lion_reg_sort_mode_get
*Prototype   : cat_sort_type_t lion_reg_sort_mode_get( void )
*Arguments   : void
*Return      : the current repeat in register table.
*Description : get the current repeat in register table.
*Other       :
****************************************************************************************************
*/
extern cat_sort_type_t  lion_reg_sort_mode_get( void );

/*
****************************************************************************************************
*Name        : lion_reg_sort_mode_set
*Prototype   : __s32 lion_reg_sort_mode_set( cat_sort_type_t repeat )
*Arguments   : repeat  input. repeat.
*Return      : EPDK_OK    succeed
*              EPDK_FAIL  fail
*Description : set the current repeat in register table.
*Other       :
****************************************************************************************************
*/
extern __s32 lion_reg_sort_mode_set( cat_sort_type_t repeat );

/*
****************************************************************************************************
*Name        : lion_reg_sort_mode_get_default
*Prototype   : cat_sort_type_t lion_reg_sort_mode_get_default( void )
*Arguments   : void
*Return      : the default repeat in register table.
*Description : get the default repeat in register table.
*Other       :
****************************************************************************************************
*/
extern cat_sort_type_t  lion_reg_sort_mode_get_default( void );

/*
****************************************************************************************************
*Name        : lion_reg_sort_mode_restore
*Prototype   : __s32 lion_reg_sort_mode_restore( void )
*Arguments   : void
*Return      : EPDK_OK    succeed
*              EPDK_FAIL  fail
*Description : restore the default value of repeat in register table.
*Other       :
****************************************************************************************************
*/
extern __s32 lion_reg_sort_mode_restore( void );



#ifdef __cplusplus
}
#endif

#endif     //  ifndef __REG_EXP_SORT_H__

/* end of reg_sort_mode.h */