#include <Header.hpp>
#include <game.hpp>
#include <title.hpp>

#define CURRENT_DIR		U"."

void Main()
{
	// タイトル
	Window::SetTitle(U"サンタ狩りへGO!");

	// アセットの登録
	FontAsset::Register(U"Medium", 18, Typeface::Medium);
	FontAsset::Register(U"Small", 14, Typeface::Medium);

	// タイトル画面
	TitleReturn::Type title_ret = title(CURRENT_DIR);

	switch (title_ret) {
	case TitleReturn::StartGameLv1:
		start_game(CURRENT_DIR, 1);
		break;
	case TitleReturn::StartGameLv2:
		start_game(CURRENT_DIR, 2);
		break;
	case TitleReturn::StartGameLv3:
		start_game(CURRENT_DIR, 3);
		break;
	case TitleReturn::HowToPlay:
		start_game(CURRENT_DIR, 1);
		break;
	default:
		break;
	}
}
