//
//  game.hpp
//  SantaGari
//
//  Created by YotioSoft on 2021/12/20.
//

#ifndef game_h
#define game_h

#include <Header.hpp>

typedef struct GameSetting {
	double santa_move_freq;
	double santa_bullet_freq;
	int santa_bullet_range;
	double bullet_speed;
} GameSetting;

void start_game(const String current_path, const int level, const bool bgm);
void game(const String current_path, const GameSetting game_setting, const bool bgm);

#endif /* game_h */
