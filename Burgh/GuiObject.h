
#pragma once

#include "Utils.h"

//#define GuiObjFrame_ 0x001
//#define GuiObjButton_ 0x002
//#define GuiObjListItem_ 0x004

enum {GuiObj_Frame = 0xff,GuiObj_Undefined};
enum { GuiEvent_Capture = 0xffff, GuiEvent_None };
enum {GuiClientAlignLeft = 0x22,GuiClientAlignRight};
#include <memory>
#include <vector>
#include <algorithm>

template <typename T>
static void delete_ptr(T*  ptr)
{
	SAFE_DELETE( ptr );
}


class GuiObject
{
public:
	
protected:
	std::vector<GuiObject*>children;
	
	GuiObject* _parent = NULL;
protected:
	bool _enabled = true;
	bool _visible = true;
	UINT _type = GUIOBJECT_UNDEFINED;
	
public:
	GuiObject()
	{
	}
	virtual ~GuiObject()
	{
		std::for_each(children.begin(), children.end(), delete_ptr<GuiObject>);
	}
	
	virtual bool Enabled(){ return _enabled; }
	virtual void Enabled(bool v){_enabled = v;}
	virtual bool Visible(){ return _visible; }
	virtual void Visible(bool v){ _visible = v; }
	virtual UINT Type(){ return _type; }
	virtual void Type(UINT t){ _type = t; }
	GuiObject* Owner(){ return _parent; }
	void SetOwner(GuiObject* obj){ _parent = obj; }
	void AddChild(GuiObject* obj)
	{
		obj->SetOwner(this);
		children.push_back(obj);
	}
	GuiObject* GetChildType(UINT type)
	{
		for (UINT c = 0; c < children.size(); c++)
		{
			if (children[c]->Type() == type)
			{
				return children[c];
			}
		}
		return NULL;
	}
	GuiObject* GetChild(UINT index)
	{ 
		if (index < children.size())
		   return children[index];
	    
		return NULL;

	}
	GuiObject* GetLastChild()
	{ 
		if (children.size())
		    return children.back();

		return NULL;
	}
};