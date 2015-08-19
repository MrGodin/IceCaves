
#pragma once

#include "GuiListBox.h"


class GuiDisplayPanel : public GuiControl
{
public:
	struct GuiDisplayPanelDesc
	{
		GuiFrameDesc frmDesc;
		UINT  rows = 0;
		UINT  cols = 0;
		UINT  itemHeight = 16;
		UINT maxDisplayItems = 0;
		GuiDisplayPanelDesc(){}
		GuiDisplayPanelDesc(GuiFrameDesc desc,UINT r,UINT c,UINT itemH = 16)
			:
			frmDesc(desc),
			rows(r),
			cols(c),
			itemHeight(itemH)
		{
			maxDisplayItems = rows * cols;
		}

	};
protected:
	GuiDisplayPanelDesc Desc;
public:
	GuiDisplayPanel(GuiDisplayPanelDesc desc)
		:
		GuiControl(desc.frmDesc),
		Desc(desc)
	{

	}
	void SetDisplayText(TString str, UINT row, UINT col)
	{
		UINT index = row * Desc.cols + col;
		GuiListItem* item = GetItem(index);
		item->SetText(str.w_char());
	}
	GuiListItem* GetItem(UINT index){ return (GuiListItem*)children[index]; }
	UINT Rows(){ return Desc.rows; }
	UINT Columns(){ return Desc.cols; }
	UINT ItemCount(){ return Desc.rows * Desc.cols; }
	virtual void Create();
	virtual ~GuiDisplayPanel(){}
	virtual HRESULT Rasterize()override;
	virtual bool OnMouseMove(GuiEvent& Event)override;
	virtual bool OnMouseClick(GuiEvent& Event)override;

	
};