#include <Header.hpp>
#include <game.hpp>

void Main()
{
	// アセットの登録
	FontAsset::Register(U"Medium", 18, Typeface::Medium);

	game(U"./");

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
}
