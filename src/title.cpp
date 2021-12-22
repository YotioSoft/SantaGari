//
//  title.cpp
//  SantaGari
//
//  Created by YotioSoft on 2021/12/23.
//

#include "title.hpp"

bool RoundRectButton(Texture& icon, const String text, const Point position, const Size size) {
	// 背景図形の表示
	RoundRect rr(Arg::center(position.x, position.y), size, 5);
	if (rr.mouseOver()) {
		rr.drawFrame(0, 1, Palette::Deepskyblue);
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	else {
		rr.drawFrame(0, 1, Palette::Gray);
	}

	// ロゴの表示
	RectF region = FontAsset(U"Medium")(text).region(Arg::center(position.x, position.y));
	icon.draw(position.x - region.w / 2 - icon.width(), position.y - icon.height() / 2, Palette::Gray);

	// 文字の表示
	FontAsset(U"Medium")(text).draw(Arg::center(position.x + icon.width() / 2, position.y), Palette::Black);

	return rr.leftClicked();
}

int title(const String current_path) {
	// タイトル
	Window::SetTitle(U"サンタ狩りへGO!");

	// アセットの登録
	FontAsset::Register(U"Medium", 18, Typeface::Medium);
	FontAsset::Register(U"Small", 14, Typeface::Medium);

	//game(U"./");

	// 背景色
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// ロゴの読み込み
	const Texture logo(U"{}/img/logo.png"_fmt(current_path));

	// アイコンの読み込み
	Texture icon_play{ 0xf11b_icon, 30 };
	Texture icon_howtoplay{ 0xf059_icon, 30 };

	while (System::Update()) {
		// ロゴ
		logo.draw(Arg::center(Scene::Width()/2, 100));

		// メニュー
		if (RoundRectButton(icon_play, U"Play", Point(Scene::Width() / 2, 300), Size(250, 50))) {
			return 1;
		}
		RoundRectButton(icon_howtoplay, U"How to Play", Point(Scene::Width() / 2, 400), Size(250, 50));

		FontAsset(U"Small")(U"©YotioSoft 2021").draw(Arg::center(Scene::Width() / 2, Scene::Height()-30), Palette::Black);
	}
	
	return 0;
}
