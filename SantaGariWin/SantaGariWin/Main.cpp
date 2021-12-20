#include <Header.hpp>
#include <game.hpp>

void Main()
{
	game(U"./");

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
}
