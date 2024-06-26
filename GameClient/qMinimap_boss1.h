#pragma once
#include "qUI.h"

class qTexture;

class qMinimap_boss1 : public qUI
{
public:
	CLONE(qMinimap_boss1);

	qMinimap_boss1();
	~qMinimap_boss1();

public:
	virtual void tick_ui() override;
	virtual void render_ui() override;


	void SetImage(qTexture* _Tex) { m_MinimapImg_boss1 = _Tex; }


private:
	qTexture* m_MinimapImg_boss1;
};

