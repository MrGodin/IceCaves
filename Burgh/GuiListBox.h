

#pragma once

#include "GuiControl.h"
#include "GuiTextControl.h"

class GuiListItem : public GuiControl
{
private:
	bool selected = false;
	GuiText* pText = NULL;
	
public:
	GuiListItem(GuiFrameDesc desc)
		:
		GuiControl(desc)
	{
		GuiFrameDesc txtDesc;
		txtDesc = desc;
		pText = new GuiText(txtDesc, L"", TEXTALIGN_LEFT);
	}
	virtual ~GuiListItem()
	{
		SAFE_DELETE(pText);
	}
	
	void SetText(WCHAR* txt){ pText->SetText(txt); }
	virtual void SetFont(ID3DXFont* f)override
	{
		pFont = f;
		pText->SetFont(pFont);
		pText->AlignText();
	}
	virtual bool OnMouseMove(GuiEvent& Event);
	virtual bool OnMouseClick(GuiEvent& Event);
	virtual HRESULT Rasterize();
};

/////////////////////////////////////////////////

class GuiListBox : public GuiControl
{
private:
	//std::vector<GuiListItem*>DisplayItems;
	GuiListItem* pSelectedItem = NULL;
	std::vector<TString>strList;
	void Create()
	{

	}
	void UpdateStrings( UINT index)
	{
		UINT count = strList.size();
		if (index > count)
			return;

		UINT i;
		index < Desc.numbItemsToDisplay ? i = 0 : i = index;
		int topmost = (int)count - (int)Desc.numbItemsToDisplay;
		if (topmost >= 0 && i > topmost)
			i = topmost;

		for (UINT c = i,cd = 0; cd < Desc.numbItemsToDisplay ; c++,cd++)
		{
			
			TString str = strList[c];
			GuiListItem* item = (GuiListItem*)children[cd];
			item->SetText(str.w_char());
		}
	}
public:
	struct GuiListBoxDesc
	{
		long numbItemsToDisplay = 0;
		long maxItemsInList = 0;
		long itemHeight = 0;
		TString name;
		GuiFrameDesc frmDesc;

	};
	GuiListItem* SelectedItem(){ return pSelectedItem; }
private:
	GuiListBoxDesc Desc;
public:
	GuiListBox(GuiListBoxDesc desc)
		:
		GuiControl(desc.frmDesc),
		Desc(desc)
	{
		
	}
	virtual ~GuiListBox()
	{
		//std::for_each(DisplayItems.begin(), DisplayItems.end(), delete_ptr<GuiListItem>);
	}
	virtual bool OnMouseMove(GuiEvent& Event);
	virtual bool OnMouseClick(GuiEvent& Event);
	virtual HRESULT Rasterize();
	UINT StringCount(){ return strList.size(); }
	UINT AvaliableStringCount(){ return Desc.maxItemsInList - strList.size(); }
	TString Name(){ return Desc.name; }
	bool AddString(TString str)
	{ 
		if (Desc.maxItemsInList >= strList.size())
			return false;
		strList.push_back(str);
		UpdateStrings(strList.size() - 1);
		return true;
	}
	TString GetString(UINT index){ return strList[index]; }
};