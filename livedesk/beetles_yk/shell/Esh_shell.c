/*
*********************************************************************************************************
*											        ePDK
*						            the Easy Portable/Player Develop Kits
*									          shell application
*
*						        (c) Copyright 2006-2007, Steven.ZGJ China
*											All	Rights Reserved
*
* File    : Esh_shell.c
* By      : sunny
* Version : V2.0                                                            2009.3.2
*********************************************************************************************************
*/

#include    "Esh_shell_private.h"
#include    "bmp_parser\\Parse_Picture.h"
#include    <mplayer.h>
__hdle logo_layer;
__bool pass_flag = EPDK_FALSE;
Picture_t * picture = NULL;

static void __Esh_Begin_Info(void)
{
    __inf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
    __inf("&                                                                                                                   &\n");
    __inf("&                                                      FFBBEE                                                       &\n");
    __inf("&                          I BBBBBBBBBBBB            I BBBB                            MMI         BBLL             &\n");
    __inf("&                    BBBBB@STEVEN@BMMBBBBBB          BBBBI                           BBBBFF      BBBBFF             &\n");
    __inf("&                  BBBBBBBBMMBBBBBBMMEEBBLL        BBBBBB                          BBBBBB::    BBBBBB..             &\n");
    __inf("&                BBBBBBBBBB        LLBB.         BBBBBB                          BBBB  BB    EEBB  BB               &\n");
    __inf("&                BBBB..          BB            I BBBB.                           BBI FFLL    BB..FFFF               &\n");
    __inf("&              I BBFF                          BBBBLL                          BBBB  BB    BBBB  BB                 &\n");
    __inf("&              ::BBBBBB                      BBBBBB    BB          BBBBBBBB    BBLLBB::    BBLLBB::                 &\n");
    __inf("&                LLBBBBBBBBBB              FFBBBB  . BBBBBB    . BBBB  BBFF  BBBBBBEE    BBBBBBBB                   &\n");
    __inf("&                      BBBBBBEEBB          BBBB  LLBBBBBB      BBBB  EEBB    BBBBBB      BBBBBB                     &\n");
    __inf("&                              BBBB::    BBBB. EEBBI BB      BBBB  BBEE    . BBBB      . BBBB                       &\n");
    __inf("&                                BBBB    MMBBLLBB  BBLL    ..BBBBBB        I BB::      BBBB.       ..               &\n");
    __inf("&                              BBBBBB    BBEEBB::LLBB    BBFFBBEE      LLBBEEBB::    BBBBBB..    BB                 &\n");
    __inf("&          BB::          BBBBBBBBBBFF    BBBBFF  BBBBBBBB  I BBBB    BBBB  I BBBB::BB::FFBBBB..BB..                 &\n");
    __inf("&        BBBBBBBBMMBBBBBBBBMMMMBBBB      BBBB    BBBBBB      BBBBBBBBBB      BBBBBBI     BBBBBBI                    &\n");
    __inf("&        BBBB@V1.0@BBMMBBBBBBBB                                BBBB            BB          BB                       &\n");
    __inf("&            ::BBBBMMBB                                                                                             &\n");
    __inf("&                                                                                                                   &\n");
    __inf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");

    __inf("-----Please input cmd after \"work_dir>:\"-----------------------------------------------------------------------------\n");
    __inf("-----Input \"help\" command for more information!----------------------------------------------------------------------\n");
    __inf("-----Give your requirement or sugguestion to sunny for improvement---------------------------------------------------\n");
    __inf("---------------------------------------------------------------------------------------------------------------------\n");
    __inf("\n");
}

static __s32 __show_logo(void)
{
	ES_FILE      * p_disp;
	__s32		width, height;
	__disp_layer_info_t layer_para;
    __u32 arg[3];
    __s32 ret;
    
	    
	//parse logo bmp	
	picture = (Picture_t *)eLIBs_malloc(sizeof(Picture_t));
	if(picture == NULL)
	{
		__wrn("malloc logo bmp buffer failed!\n");
		return EPDK_FAIL;
	}
    eLIBs_memset(picture, 0, sizeof(Picture_t));
	Parse_Pic_BMP_ByPath("d:\\res\\boot_ui\\logo.bmp", picture, NULL);
	
	
	/*open display driver handle*/
	p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
	if(!p_disp)
	{
		Esh_Wrn("open display device fail!\n");
		return EPDK_FAIL;
	}	

	width  = eLIBs_fioctrl(p_disp, DISP_CMD_SCN_GET_WIDTH, 0, 0);
	height = eLIBs_fioctrl(p_disp, DISP_CMD_SCN_GET_HEIGHT, 0, 0);

	__msg("width = %d, height = %d\n", width, height);
    arg[0] = DISP_LAYER_WORK_MODE_NORMAL;
    arg[1] = 0;
    arg[2] = 0;
    logo_layer = eLIBs_fioctrl(p_disp, DISP_CMD_LAYER_REQUEST, 0, (void*)arg);

    layer_para.mode = DISP_LAYER_WORK_MODE_NORMAL; 
    layer_para.fb.addr[0]       = (__u32)picture->Buffer; 
    layer_para.fb.size.width    =  picture->Width;
    layer_para.fb.size.height    = picture->Height;
    layer_para.fb.mode          = DISP_MOD_INTERLEAVED;
    layer_para.fb.format        = DISP_FORMAT_ARGB8888;
    layer_para.fb.br_swap       = 0;
    layer_para.fb.seq           = DISP_SEQ_ARGB;
    layer_para.ck_enable        = 0;
    layer_para.alpha_en         = 1; 
    layer_para.alpha_val        = 0xff;
    layer_para.pipe             = 0; 
    layer_para.src_win.x        = 0;
    layer_para.src_win.y        = 0;
    layer_para.src_win.width    = picture->Width;
    layer_para.src_win.height   = picture->Height;
    layer_para.scn_win.x        = (width-picture->Width)>>1;
    layer_para.scn_win.y        = (height-picture->Height)>>1;
    layer_para.scn_win.width    = picture->Width;
    layer_para.scn_win.height   = picture->Height;
	__msg("scn_win.x = %d, scn_win.y = %d\n", layer_para.scn_win.x, layer_para.scn_win.y);
    __msg("picture->Width = %d, picture->Height = %d\n", picture->Width, picture->Height);
    arg[0] = logo_layer;
    arg[1] = (__u32)&layer_para;
    arg[2] = 0;
    eLIBs_fioctrl(p_disp,DISP_CMD_LAYER_SET_PARA,0,(void*)arg);

    arg[0] = logo_layer;
    arg[1] = 0;
    arg[2] = 0;
    eLIBs_fioctrl(p_disp,DISP_CMD_LAYER_OPEN,0,(void*)arg);

	eLIBs_fioctrl(p_disp, DISP_CMD_LCD_ON, 0, 0);
	
	eLIBs_fclose(p_disp);

	return EPDK_OK;
}

static __s32 __key_graber(void *packet)
{		
	__u32 i;
	__input_event_packet_t *pPacket;
    __input_event_t        *pEventFrame;				
	
    if (packet == NULL)
    {
        __msg("invalid argument for call back\n");
        return EPDK_FAIL;
    }
    
    //dump packet events
    pPacket = (__input_event_packet_t *)packet;
    if (pPacket->event_cnt > INPUT_MAX_EVENT_NR)
    {
        __msg("invalid event count number\n");
        return EPDK_FAIL;
    }
	__msg("------------------------------------------------\n");
	for (i = 0; i < pPacket->event_cnt; i++)
	{
		pEventFrame = &(pPacket->events[i]);
		__msg("Event %d: type = %d, code = %d, value = %d\n", i + 1,
                                                                 pEventFrame->type,
                                                                 pEventFrame->code,
                                                                 pEventFrame->value
                                                                 );
		if(pEventFrame->type == EV_KEY) 
		{	  
			pass_flag = EPDK_TRUE;			
		}		
	}	
	__msg("------------------------------------------------\n");			
	
	return EPDK_OK;
}

static __s32 __close_logo(void)
{
	ES_FILE 	 * p_disp;	
	__u32 arg[3];

	/*open display driver handle*/
	p_disp = eLIBs_fopen("b:\\DISP\\DISPLAY", "r+");
	if(!p_disp)
	{
		Esh_Wrn("open display device fail!\n");
		return EPDK_FAIL;
	}	
	//close logo
	arg[0] = logo_layer;
	arg[1] = 0;
	arg[2] = 0;
	eLIBs_fioctrl(p_disp,DISP_CMD_LAYER_CLOSE,0,(void*)arg);

	eLIBs_fioctrl(p_disp,DISP_CMD_LAYER_RELEASE,0,(void*)arg);

	eLIBs_fclose(p_disp);
    __msg("close logo");
	return EPDK_OK;
}

__s32 shellmain(void *p_arg)
{

    __target_para_t target;
    ES_FILE *file = NULL;
    //__Esh_Begin_Info();
    esDEV_Plugin("\\drv\\display.drv", 0, 0, 1);
	__inf(".Display Device Installed!...........................................................................................\n");
	__show_logo();
    //media_player_main("f:\\liu.mp3");
    /* print shell begin information */
    
    esKRNL_TimeDly(100);
#if 0
   	Esh_printf(".....................................................................................................................\n");
   	Esh_printf(".Please press enter key(keypad or irkey) to continue!\n..............................................................\n");
   	Esh_printf(".....................................................................................................................\n");
#if (MW_PROJ_NAME == spider)
    Esh_printf("\nProject Name: spider\n");
#else
    Esh_printf("\nProject Name: null\n");
#endif
#if (MW_PROJ_MODEL == p35tp)
    Esh_printf("Project Model: p35tp\n");
#else
    Esh_printf("Project Model: null\n");
#endif
#if (MW_PROJ_MANUFACTURER == MaiWei)
    Esh_printf("Project Manufacturer: Mai Wei\n");
#else
    Esh_printf("Project Manufacturer: null\n");
#endif
#ifdef MW_PROJ_DEBUG
    Esh_printf("Project Debug: enable\n");
#else
    Esh_printf("Project Debug: disable\n");
#endif
#if (MW_PROJ_DEBUG == 0)
    Esh_printf("Project Debug: enable\n");
#else
    Esh_printf("Project Debug: disable\n");
#endif
#endif
#if 0
    esKSRV_GetTargetPara(&target);
    Esh_printf("Porject Platform Debug: %x\n\n", target.debugenable);
    if(target.debugenable == EPDK_TRUE)
    {
	    __hdle  		h_keyGraber;
		//esDEV_Plugin("\\drv\\ir.drv", 0, 0, 1);
        //enable device monitor
        {
            ES_FILE     *pHwsc;

            pHwsc = eLIBs_fopen("b:\\HWSC\\hwsc", "rb+");
            if(pHwsc)
            {
                eLIBs_fioctrl(pHwsc, DEV_IOC_USR_HWSC_ENABLE_MONITOR, 0, NULL);
                eLIBs_fclose(pHwsc);
                __inf(".start device monitor .......................................\n");
            }
            else
            {
                __err("try to open b:\\HWSC\\hwsc failed!\n");
            }
        }
#if (MW_PROJ_MODEL == p35tp)
    __inf("No keyboard\n");
#else
		{			
			h_keyGraber = esINPUT_LdevGrab(INPUT_LKEYBOARD_DEV_NAME, (__pCBK_t)__key_graber, 0, 0);
		    if (h_keyGraber == NULL)
		    {
		        eLIBs_printf("shell grab logical keyboard failed\n");		        
		    }
		}
		
        while(1)
        {            	
            if(pass_flag)
        	{
        		if (h_keyGraber)
        		{
        			esINPUT_LdevRelease(h_keyGraber);
        		}
//				esDEV_Plugout("\\drv\\ir.drv", 0 );
        		break;
        	}			
            esKRNL_TimeDly(10);
        }
#endif
    }
#endif

    /* Eshell initialize  */
    if ( ESH_FAILED == Esh_init() ) {
        Esh_Error("Eshell initialize failed\n");
        return ESH_FAILED;
    }
    /* execute setup first */
    Esh_StartUp();

	//if(target.debugenable == EPDK_TRUE)
	//{
		/* loop read commands, execute commands */
    	//Esh_ReaderLoop();
	//}

    /* Eshell exit */
    Esh_exit();

	/* kill shell self */
    esEXEC_PDel(EXEC_pidself);
	//eKNRL_TimeDly(10);
    __close_logo();
    /* del shell main thread */
    Esh_Msg("shell main thread: Bye Bye!\n");
    esKRNL_TDel(OS_PRIO_SELF);
    return ESH_SUCCEED;
}