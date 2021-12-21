#include <Header.hpp>
#include <game.hpp>

void Main()
{
	// アセットの登録
	FontAsset::Register(U"Medium", 18, Typeface::Medium);
	
	game(U"SantaGari.app/Contents/Resources");

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// 通常のフォントを作成 | Create a new font
	const Font font{ 60 };

	// 絵文字用フォントを作成 | Create a new emoji font
	const Font emojiFont{ 60, Typeface::ColorEmoji };

	// `font` が絵文字用フォントも使えるようにする | Set emojiFont as a fallback
	font.addFallback(emojiFont);

	// 画像ファイルからテクスチャを作成 | Create a texture from an image file
	const Texture texture{ U"example/windmill.png" };

	// 絵文字からテクスチャを作成 | Create a texture from an emoji
	const Texture emoji{ U" "_emoji };

	// 絵文字を描画する座標 | Coordinates of the emoji
	Vec2 emojiPos{ 300, 150 };

	// テキストを画面にデバッグ出力 | Print a text
	Print << U"Push [A] key";

	while (System::Update())
	{
		// テクスチャを描く | Draw a texture
		texture.draw(200, 200);

		// テキストを画面の中心に描く | Put a text in the middle of the screen
		font(U"Hello, Siv3D! ").drawAt(Scene::Center(), Palette::Black);

		// サイズをアニメーションさせて絵文字を描く | Draw a texture with animated size
		emoji.resized(100 + Periodic::Sine0_1(1s) * 20).drawAt(emojiPos);

		// マウスカーソルに追随する半透明な円を描く | Draw a red transparent circle that follows the mouse cursor
		Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 1, 0, 0, 0.5 });

		// もし [A] キーが押されたら | When [A] key is down
		if (KeyA.down())
		{
			// 選択肢からランダムに選ばれたメッセージをデバッグ表示 | Print a randomly selected text
			Print << Sample({ U"Hello!", U"こんにちは", U"?好", U"??????" });
		}

		// もし [Button] が押されたら | When [Button] is pushed
		if (SimpleGUI::Button(U"Button", Vec2{ 640, 40 }))
		{
			// 画面内のランダムな場所に座標を移動
			// Move the coordinates to a random position in the screen
			emojiPos = RandomVec2(Scene::Rect());
		}
	}
}
