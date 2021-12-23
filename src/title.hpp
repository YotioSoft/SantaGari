//
//  title.hpp
//  SantaGari
//
//  Created by YotioSoft on 2021/12/23.
//

#ifndef title_hpp
#define title_hpp

#include "Header.hpp"

bool RoundRectButton(Texture& icon, const String text, const Point position, const Size size);
bool RoundRectButton(const String text, const Point position, const Size size);

TitleReturn::Type title(const String current_path, bool& bgm);
TitleReturn::Type select_level(const String current_path, bool& bgm);
void how_to_play();

#endif /* title_hpp */
