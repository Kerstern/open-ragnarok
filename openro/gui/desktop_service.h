#ifndef __DESKTOP_SERVICE_H
#define __DESKTOP_SERVICE_H

// Forward declaration
class DesktopService;

#include "ro_desktop.h"
#include "roengine/gui/list.h"

class DesktopService : public RODesktop {
protected:
	GUI::List* slist;
	virtual void afterDraw(unsigned int delay);
public:
	DesktopService(OpenRO*);

	bool HandleKeyDown(SDL_Event *sdlEvent, int mod);

	bool handleBtnOk(GUI::Event&);
	bool handleBtnCancel(GUI::Event&);

	void clear();
	void add(const std::string&);
	int getSelected() const;
};

#endif /* __DESKTOP_SERVICe_H */
