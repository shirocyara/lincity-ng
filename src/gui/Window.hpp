/*
Copyright (C) 2005 Matthias Braun <matze@braunis.de>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef WINDOW_HPP
#define WINDOW_HPP

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

#include "Component.hpp"

class XmlReader;
class Button;

/**
 * @class Window
 * @brief Implement the main game window.
 * @file Window.hpp
 * @author Matthias Braun
 */

class Window : public Component
{
public:
    Window();
    virtual ~Window();

    void parse(XmlReader& reader);

    void draw(Painter& painter);
    void event(const Event& event);

private:
    void closeButtonClicked(Button* button);

    float border;
    float titlesize;
    bool dragging;
    Vector2 dragOffset;

    Child& background()
    { return childs[0]; }
    Child& title_background()
    { return childs[1]; }        
    Child& title()
    { return childs[2]; }
    Child& closeButton()
    { return childs[3]; }
    Child& contents()
    { return childs[4]; }
};

#endif

