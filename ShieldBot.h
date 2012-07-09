// ShieldBot.h: interface for the ShieldBot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHIELDBOT_H__9406A8E5_C15F_4C4D_8A80_409F4E364701__INCLUDED_)
#define AFX_SHIELDBOT_H__9406A8E5_C15F_4C4D_8A80_409F4E364701__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"


class ShieldBot  : public Moveable
{
public:
	ShieldBot();
	virtual ~ShieldBot();
	void move();
	void collide();

};

#endif // !defined(AFX_SHIELDBOT_H__9406A8E5_C15F_4C4D_8A80_409F4E364701__INCLUDED_)
