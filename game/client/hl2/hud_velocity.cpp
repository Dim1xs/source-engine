//Credits to Valve Corporation for CHud base element.
//Velocity hud counter by Dim1xs. (21.10.2023)
// 
// implementation of CHudVelocity class
//
#include "cbase.h"
#include "hud.h"
#include "hudelement.h"
#include "hud_macros.h"
#include "hud_numericdisplay.h"
#include "iclientmode.h"

#include "vgui_controls/AnimationController.h"
#include "vgui/ILocalize.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Purpose: Displays suit power (armor) on hud
//-----------------------------------------------------------------------------
class CHudVelocity : public CHudNumericDisplay, public CHudElement
{
	DECLARE_CLASS_SIMPLE(CHudVelocity, CHudNumericDisplay);

public:
	CHudVelocity(const char* pElementName);
	void Init(void);
	void Reset(void);
	void VidInit(void);
	void OnThink(void);
	bool ShouldDraw();

private:
	int		m_iVel;
};

DECLARE_HUDELEMENT(CHudVelocity);

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CHudVelocity::CHudVelocity(const char* pElementName) : BaseClass(NULL, "HudVelocity"), CHudElement(pElementName)
{
	SetHiddenBits(HIDEHUD_HEALTH | HIDEHUD_PLAYERDEAD | HIDEHUD_NEEDSUIT);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudVelocity::Init(void)
{
	Reset();
	m_iVel = 0;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHudVelocity::Reset(void)
{
	SetLabelText(L"UPS:");
	SetDisplayValue(m_iVel);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHudVelocity::VidInit(void)
{
	Reset();
}

//-----------------------------------------------------------------------------
// Purpose: Save CPU cycles by letting the HUD system early cull
// costly traversal.  Called per frame, return true if thinking and 
// painting need to occur.
//-----------------------------------------------------------------------------
bool CHudVelocity::ShouldDraw(void)
{
	return true;
}

//-----------------------------------------------------------------------------
// Purpose: Get PlayerVelocity and update Counter.
//-----------------------------------------------------------------------------
void CHudVelocity::OnThink(void)
{
	C_BasePlayer* pClient = C_BasePlayer::GetLocalPlayer();
	if (pClient)
	{
		if (pClient->IsAlive())
		{
			m_iVel = pClient->GetAbsVelocity().Length();
		}
	}

	SetDisplayValue(m_iVel);
}

