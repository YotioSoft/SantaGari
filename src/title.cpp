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
	icon.draw(position.x - region.w / 2 - icon.width(), position.y - icon.height() / 2);

	// 文字の表示
	FontAsset(U"Medium")(text).draw(Arg::center(position.x + icon.width() / 2, position.y));

	return rr.leftClicked();
}
bool RoundRectButton(const String text, const Point position, const Size size) {
	// 背景図形の表示
	RoundRect rr(Arg::center(position.x, position.y), size, 5);
	if (rr.mouseOver()) {
		rr.drawFrame(0, 1, Palette::Deepskyblue);
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	else {
		rr.drawFrame(0, 1, Palette::Gray);
	}

	// 文字の表示
	FontAsset(U"Medium")(text).draw(Arg::center(position.x, position.y));

	return rr.leftClicked();
}

TitleReturn::Type title(const String current_path, bool& bgm) {
	// 背景色
	Scene::SetBackground(ColorF{ 0.1, 0.1, 0.4 });

	// ロゴの読み込み
	const Texture logo(U"{}/img/logo.png"_fmt(current_path));

	// アイコンの読み込み
	Texture icon_play{ 0xf11b_icon, 30 };
	Texture icon_howtoplay{ 0xf059_icon, 30 };

	while (System::Update()) {
		// ロゴ
		logo.draw(Arg::center(Scene::Width()/2, 100));

		// メニュー
		if (RoundRectButton(icon_play, U"Play", Point(Scene::Width() / 2, 400), Size(250, 40))) {
			return select_level(current_path, bgm);
		}
		if (RoundRectButton(icon_howtoplay, U"How to Play", Point(Scene::Width() / 2, 450), Size(250, 40))) {
			return TitleReturn::HowToPlay;
		}

		FontAsset(U"Small")(U"©YotioSoft 2021").draw(Arg::center(Scene::Width() / 2, Scene::Height()-30));
	}
	
	return TitleReturn::Exit;
}

TitleReturn::Type select_level(const String current_path, bool& bgm) {
	// 背景色
	Scene::SetBackground(ColorF{ 0.1, 0.1, 0.4 });

	// ロゴの読み込み
	const Texture logo(U"{}/img/logo.png"_fmt(current_path));

	// アイコンの読み込み
	Texture icon_bgm{ 0xf028_icon, 20 };
	Texture icon_nobgm{ 0xf6a9_icon, 20 };

	while (System::Update()) {
		// ロゴ
		logo.draw(Arg::center(Scene::Width() / 2, 100));

		// メニュー
		if (RoundRectButton(U"Level1", Point(Scene::Width() / 2, 350), Size(250, 40))) {
			return TitleReturn::StartGameLv1;
		}
		if (RoundRectButton(U"Level2", Point(Scene::Width() / 2, 400), Size(250, 40))) {
			return TitleReturn::StartGameLv2;
		}
		if (RoundRectButton(U"Level3", Point(Scene::Width() / 2, 450), Size(250, 40))) {
			return TitleReturn::StartGameLv3;
		}
		
		// BGMのON/OFF
		if (RoundRectButton(bgm ? icon_bgm : icon_nobgm, bgm ? U"BGM:  ON" : U"BGM: OFF", Point(Scene::Width() / 2, 250), Size(150, 30))) {
			bgm = !bgm;
		}

		FontAsset(U"Small")(U"©YotioSoft 2021").draw(Arg::center(Scene::Width() / 2, Scene::Height() - 30));
	}

	return TitleReturn::Exit;
}

void how_to_play() {
	// 背景色
	Scene::SetBackground(ColorF{ 0.1, 0.1, 0.4 });

	// アイコンの読み込み
	Texture icon_arrows{ 0xf0b2_icon, 20 };
	
	RectF rf1(10, 10, Scene::Width()-10, 100);

	while (System::Update()) {
		FontAsset(U"Medium")(U"ルール").draw(10, 10);
		FontAsset(U"Small")(U"サンタを狙撃する古典的なシューティングゲームです。戦闘機を操作し、迎撃を躱しつつサンタを狙い撃ちましょう。サンタはプレゼントを配りながら飛行します。プレゼントは獲得（横取り）するほどポイントが上がります。").draw(rf1);
	}
}
