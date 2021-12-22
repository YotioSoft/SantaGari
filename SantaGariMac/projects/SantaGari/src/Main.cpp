#include <Header.hpp>
#include <title.hpp>
#include <game.hpp>

#define CURRENT_DIR		U"SantaGari.app/Contents/Resources"

void Main()
{
	// タイトル画面
	int title_ret = title(CURRENT_DIR);
	
	if (title_ret == 1) {
		// ゲーム開始
		game(CURRENT_DIR);
	}
}
