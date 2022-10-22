#pragma once
#include "RectTile.h"

class ExRectTile : public RectTile
{
protected:
	bool isClicked;

public:
	ExRectTile();
	virtual ~ExRectTile();

	virtual void Update(float dt) override;

	void SetClicked(bool isclicked) { isClicked = isclicked; }
	bool GetClicked() const { return isClicked; }

	function<void(const Texture*)> ClickOn;
	void ClickedOff() { tile->setOutlineColor({ 0, 0, 0, 255 }); }
};
