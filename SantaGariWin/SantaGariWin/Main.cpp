#include <Header.hpp>
#include <game.hpp>
#include <title.hpp>

#define CURRENT_DIR		U"."

void Main()
{
	// タイトル
	Window::SetTitle(U"サンタ狩りへGO!");

	// アセットの登録
	FontAsset::Register(U"Large", 22, Typeface::Medium);
	FontAsset::Register(U"Medium", 18, Typeface::Medium);
	FontAsset::Register(U"Small", 14, Typeface::Medium);

	// タイトル画面
	bool bgm = true;

	while (1) {
		TitleReturn::Type title_ret = title(CURRENT_DIR, bgm);

		bool exit = false;
		switch (title_ret) {
		case TitleReturn::StartGameLv1:
			exit = !start_game(CURRENT_DIR, 1, bgm);
			break;
		case TitleReturn::StartGameLv2:
			exit = !start_game(CURRENT_DIR, 2, bgm);
			break;
		case TitleReturn::StartGameLv3:
			exit = !start_game(CURRENT_DIR, 3, bgm);
			break;
		case TitleReturn::HowToPlay:
			how_to_play();
			break;
		case TitleReturn::Back:
			break;
		default:
			exit = true;
			break;
		}

		if (exit)
			break;
	}
}
