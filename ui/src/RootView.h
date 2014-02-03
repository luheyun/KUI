#pragma once

#include "View.h"

class Widget;

class RootView : public View
{
public:
    RootView();
    virtual ~RootView();

    void init(Widget* widget, int width, int height);

public:
    void OnDraw();

protected:
    // view
    virtual bool isUsedCanvas() override {return true;}
	virtual void schedulePaint(KRect* rect = nullptr) override;

private:
    Widget* _widget;
};
