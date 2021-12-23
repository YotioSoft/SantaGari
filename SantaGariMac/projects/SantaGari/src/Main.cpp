#include <Header.hpp>
#include <title.hpp>
#include <game.hpp>

#define CURRENT_DIR		U"SantaGari.app/Contents/Resources"

void Main()
{
	// タイトル
	Window::SetTitle(U"サンタ狩りへGO!");

	// アセットの登録
	FontAsset::Register(U"Medium", 18, Typeface::Medium);
	FontAsset::Register(U"Small", 14, Typeface::Medium);

	// タイトル画面
	bool bgm = true;
	TitleReturn::Type title_ret = title(CURRENT_DIR, bgm);

	switch (title_ret) {
	case TitleReturn::StartGameLv1:
		start_game(CURRENT_DIR, 1, bgm);
		break;
	case TitleReturn::StartGameLv2:
		start_game(CURRENT_DIR, 2, bgm);
		break;
	case TitleReturn::StartGameLv3:
		start_game(CURRENT_DIR, 3, bgm);
		break;
	case TitleReturn::HowToPlay:
		how_to_play();
		break;
	default:
		break;
	}
}
