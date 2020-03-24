#pragma once

#include <string>

#include "lua/lapi.h"
#include "lua/lauxlib.h"
#include "lua/lua.h"

#include "sol/sol.hpp"
#include "TGUI/Gui.hpp"

template <typename T>
class GUIBuilder
{
private:
	T& mState;
	tgui::Gui& mGUI;
	sol::state mSource;
public:
	GUIBuilder(T& state, tgui::Gui& gui);

	void build(const std::string file);
private:
	void buildButton();
	void buildLabel();
	void buildComboBox();
	void buildEditBox();
};

template<typename T>
inline GUIBuilder<T>::GUIBuilder(T& state, tgui::Gui& gui)
	:	mState(state)
	,	mGUI(gui)
{
}

template<typename T>
inline void GUIBuilder<T>::build(const std::string file)
{
	mSource.load_file(file);
}
