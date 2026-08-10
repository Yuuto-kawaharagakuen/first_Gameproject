#include "stdafx.h"
#include "PopupText.h"
PopupText::PopupText(){}
PopupText::~PopupText(){}
void PopupText::Init(const wchar_t* text)
{
	fontRender.SetText(text);
	fontRender.SetScale(1.5f);
	fontRender.SetPivot(0.5f, 0.5f);

	pos = Vector3(-50.0f,200.0f, 0.0f); 
	fontRender.SetPosition(pos);
	fontRender.SetColor(g_vec4Cyan);
	lifeTimer = LifeTime;
	fontRender.SetFontType(enFontType::Bold);
}

void PopupText::Update() {
	lifeTimer -= 1.0f / 60.0f;
	if (lifeTimer <= 0.0f) {
		DeleteGO(this);
		return;
	}

	pos.y += MoveSpeed * (1.0f / 60.0f);
	fontRender.SetPosition(pos);

	float alpha = lifeTimer / LifeTime;
	fontRender.SetColor(g_vec4Cyan);
}

void PopupText::Render(RenderContext& rc) {
	fontRender.Draw(rc);
}