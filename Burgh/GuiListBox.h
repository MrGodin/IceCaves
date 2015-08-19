

#pragma once

#include "GuiControl.h"
#include "GuiTextControl.h"
#include "GuiSlider.h"

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
	TString  GetText(){ return pText->Text(); }
	void SetText(WCHAR* txt){ pText->SetText(txt); }
	void SetSelected(bool val){ selected = false; }
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
	// Add string to listbox string list
	bool AddString(TString str)
	{ 
		if ( strList.size() >= (UINT)Desc.maxItemsInList)
			return false;

		strList.push_back(str);
		UpdateStrings( strList.size() - 1);
		return true;
	}
	TString GetString(UINT index){ return strList[index]; }
	// Set strings to display based on index
	void UpdateStrings(UINT index)
	{
		UINT count = strList.size();
		if (index >= count)
			return;

		UINT i = index;
		if (index > (UINT)(count - Desc.numbItemsToDisplay))
		{
			index = count - Desc.numbItemsToDisplay;
			i = index - 1;
		}
		else if (index < (UINT)Desc.numbItemsToDisplay)
		{
			i = index;
		}
		// i = (index - Desc.numbItemsToDisplay) + 1;

		if (count >= (UINT)Desc.numbItemsToDisplay)
		{
			GuiSlider* sl = (GuiSlider*)GetChild(0);
			GuiSliderKnob* knob = (GuiSliderKnob*)sl->GetChild(0);
			knob->Resize(count);
		}
		for (UINT c = 0; c < children.size(); c++)
		{


			GuiObject* obj = children[c];
			switch (obj->Type())
			{
			case GUIOBJECT_LISTBOX_ITEM:
			{
				GuiListItem* item = (GuiListItem*)obj;
				if (i < count)
				{
					TString str = strList[i];
					item->SetText(str.w_char());
					i++;
				}
				break;
			}
			default:
				break;
			}

		}
	}
	void Create()
	{
		
		frameDesc.height = Desc.numbItemsToDisplay * Desc.itemHeight + (Desc.numbItemsToDisplay);
		Init();
		
		GuiSliderKnob::GuiSliderKnobDesc knobDesc;
		GuiSlider* pSlider = NULL;
		GuiFrame::GuiFrameDesc sliderDesc;
		sliderDesc.width = 16;
		sliderDesc.height = frameDesc.height;
		sliderDesc.originX = (frameDesc.originX + frameDesc.width) - sliderDesc.width;
		sliderDesc.originY = frameDesc.originY;
		sliderDesc.baseColor = QVCDisabled;
		sliderDesc.outerBorderColor = QVCTransparent;
		sliderDesc.innerBorderColor = QVCDisabled;
		sliderDesc.type = GUIOBJECT_SLIDER;

		knobDesc.frmDesc = sliderDesc;
		knobDesc.frmDesc.width = 16;
		knobDesc.frmDesc.height = sliderDesc.height;
		knobDesc.frmDesc.baseColor = QVCGreen;
		knobDesc.itemDisplayCount = Desc.numbItemsToDisplay;
		knobDesc.maxItems = Desc.maxItemsInList;
		knobDesc.minHeight = 5;
		knobDesc.frmDesc.type = GUIOBJECT_KNOB;
		pSlider = new GuiSlider(sliderDesc);
		pSlider->SetFont(pFont);
		pSlider->CreateKnob(knobDesc);
		AddChild(pSlider);
		
		GuiFrameDesc itemDesc;
		itemDesc.height = Desc.itemHeight;
		itemDesc.width = frameDesc.width - (sliderDesc.width+ 2);
		itemDesc.originX = frameDesc.originX + 1;
		itemDesc.originY = frameDesc.originY + 1;
		itemDesc.type = GUIOBJECT_LISTBOX_ITEM;
		itemDesc.baseColor = itemDesc.innerBorderColor = itemDesc.outerBorderColor = itemDesc.hoverColor = QVCTransparent;
		long Y = frameDesc.originY + 1;


		for (UINT i = 0; i < (UINT)Desc.numbItemsToDisplay; i++)
		{
			itemDesc.originY = Y;
			AddChild(new GuiListItem(itemDesc));
			GuiListItem* item = (GuiListItem*)GetLastChild();
			item->SetFont(pFont);
			item->SetText(L"");
			
			Y += Desc.itemHeight;
		}

		
	}
};