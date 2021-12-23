//
//  game.hpp
//  SantaGari
//
//  Created by YotioSoft on 2021/12/20.
//

#ifndef game_h
#define game_h

#include <Header.hpp>
#include <title.hpp>

typedef struct GameSetting {
	int level;
	double santa_move_freq;
	double santa_bullet_freq;
	int santa_bullet_range;
	double bullet_speed;
} GameSetting;

bool start_game(const String current_path, const int level, const bool bgm);
bool game(const String current_path, const GameSetting game_setting, const bool bgm);

bool result_win(const Charactor santa, const Charactor fighter, const int got_presents, const int level);
bool result_lose(const Charactor santa, const Charactor fighter, const int got_presents);

#endif /* game_h */
