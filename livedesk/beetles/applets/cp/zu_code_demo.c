#include <apps.h>
#include "zu_code_demo.h"//开关键 、单按键、 矩阵建发码
#include "tongxin_demo.h"
#include "cp_i.h"
ButtonCode_handle * ButtonCodehandleNew(void)
{
	ButtonCode_handle * create;
	create = (ButtonCode_handle *)esMEMS_Malloc(0, sizeof(ButtonCode_handle));
	if (create) {
		eLIBs_memset(create, 0, sizeof(ButtonCode_handle));
		return create;
	} else {
		return NULL;
	}
}
///////////////////按键button code
void Buttonhandle_add(ButtonCode_handle*handle,gg_handler codeNode,int num,int num2)
{
	gg_handler toitecode;
	gg_char * item_code_datas;
	gg_char * item_code_baurate;
	gg_char * item_code_delay;
	gg_char * item_code_port;
	gg_char * up_down;
	ButtonCode_handle * buttoncode;
	//LogMI("num = %d num2 = %d",num,num2);
	if(num2 <= num){
		if(num2 == 1){
			toitecode = GG_DOMGetFirstChild(codeNode);
			if(GG_DOMGetBrotherElementByTagName(toitecode, "item_code_datas")){
			    item_code_datas = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(toitecode, "item_code_datas"));
			    item_code_baurate = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(toitecode, "item_code_baurate"));
			    item_code_delay = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(toitecode, "item_code_delay"));
			    item_code_port = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(toitecode, "item_code_port"));
				if(GG_DOMGetBrotherElementByTagName(toitecode, "released") || GG_DOMGetBrotherElementByTagName(toitecode, "dec")){
					up_down = "up";//弹起状态点击发按下状态的码
				}else{
					up_down = "down";
				}
			    handle->datas= item_code_datas;
			    handle->baurate = item_code_baurate;
			    handle->delay= item_code_delay;
			    handle->port= item_code_port;
				handle->up_down= up_down;
			    codeNode = GG_DOMGetNextBrother(codeNode);
			    Buttonhandle_add(handle, codeNode,num,num2 + 1);
			}
		} else {
		   toitecode = GG_DOMGetFirstChild(codeNode);
		   if(GG_DOMGetBrotherElementByTagName(toitecode, "item_code_datas")){
			   buttoncode = ButtonCodehandleNew();
			   item_code_datas = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(toitecode, "item_code_datas"));
			   item_code_baurate = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(toitecode, "item_code_baurate"));
			   item_code_delay = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(toitecode, "item_code_delay"));
			   item_code_port = GG_DOMGetNodeValue(GG_DOMGetBrotherElementByTagName(toitecode, "item_code_port"));
			   if(GG_DOMGetBrotherElementByTagName(toitecode, "released") || GG_DOMGetBrotherElementByTagName(toitecode, "dec")){
				   up_down = "up";
			   }else{
				   up_down = "down";
			   }
			   buttoncode->datas= item_code_datas;
			   buttoncode->baurate = item_code_baurate;
			   buttoncode->delay= item_code_delay;
			   buttoncode->port= item_code_port;
			   buttoncode->up_down= up_down;
			   handle->next = buttoncode;
			   codeNode = GG_DOMGetNextBrother(codeNode);
			   Buttonhandle_add(handle->next, codeNode,num,num2 + 1);
		   }
		}
	}
}

void Buttonhandle_Search_Up(ButtonCode_handle*handle)
{
   ButtonCode_handle * buttoncode; 
   buttoncode = handle;
   while(buttoncode){
	   //LogMI("Buttonhandle_Search buttoncode true");
	   if(buttoncode->datas){
	   	   if(SLIB_strcmp(buttoncode->up_down,"up") == 0){
			   Send_ButtonCode_Normal(buttoncode->port,buttoncode->baurate,buttoncode->datas,
						buttoncode->delay);
	   	   	}
	   }
	   buttoncode = buttoncode->next;
   }
}
void Buttonhandle_Search_Down(ButtonCode_handle*handle)
{
   ButtonCode_handle * buttoncode; 
   buttoncode = handle;
   while(buttoncode){
	   //LogMI("Buttonhandle_Search buttoncode true");
	   if(buttoncode->datas){
		   if(SLIB_strcmp(buttoncode->up_down,"down") == 0){
			   Send_ButtonCode_Normal(buttoncode->port,buttoncode->baurate,buttoncode->datas,
						buttoncode->delay);
			}
	   }
	   buttoncode = buttoncode->next;
   }
}

void Buttonhandle_Search_2(ButtonCode_handle*handle,char * array_in,char * array_out)
{
   ButtonCode_handle * buttoncode; 
   buttoncode = handle;
   while(buttoncode){
	   //LogMI("Buttonhandle_Search buttoncode true");
	   if(buttoncode->datas){
		   Send_ButtonCode_Matrix(buttoncode->port,buttoncode->baurate,buttoncode->datas,
					buttoncode->delay, array_in, array_out);
	   }
	   buttoncode = buttoncode->next;
   }
}



