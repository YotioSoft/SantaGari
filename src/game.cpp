#include <game.hpp>

void start_game(const String current_path, const int level) {
	switch (level) {
	case 1:
		game(current_path, { 1.0, 0.1, 30, 3 });
		break;
	case 2:
		game(current_path, { 0.5, 0.5, 10, 5 });
		break;
	case 3:
		game(current_path, { 0.2, 0.8, 5, 10 });
		break;
	default:
		break;
	}
}

void game(const String current_path, const GameSetting game_setting) {
	Scene::SetBackground(ColorF{ 0.1, 0.1, 0.4 });

	// BGM
	AudioAsset::Register(U"GameBGM", U"{}/bgm/Mission_Rank_3.mp3"_fmt(current_path), Loop::Yes);

	// キャラクター
	Charactor santa;
	Charactor fighter;

	// キャラ画像読み込み
	santa.texture = Texture(U"{}/img/santa.png"_fmt(current_path));
	fighter.texture = Texture(U"{}/img/fighter.png"_fmt(current_path));

	// キャラの位置
	santa.position = Point(Scene::Width() / 2, 150);
	fighter.position = Point(Scene::Width() / 2, 400);

	// キャラのHPの初期値
	santa.hp = 100;
	fighter.hp = 100;

	// 火花
	Effect effect;

	// 弾丸
	Bullet santa_bullets(U"{}/img/bullet.png"_fmt(current_path));
	Bullet fighter_bullets(U"{}/img/bullet2.png"_fmt(current_path));
	
	// プレゼント
	Present presents({
		U"{}/img/present1.png"_fmt(current_path),
		U"{}/img/present2.png"_fmt(current_path),
		U"{}/img/present3.png"_fmt(current_path),
		U"{}/img/present4.png"_fmt(current_path),
	});
	Texture present_image(U"{}/img/present1.png"_fmt(current_path));
	
	// 盗んだプレゼント数
	int got_presents = 0;

	// サンタの移動
	double santa_moved_t = -10.0;
	Vec2 santa_move = { 0, 0 };

	// BGM再生
	AudioAsset(U"GameBGM").play();

	while (System::Update()) {
		// 火花の描画
		effect.add<Spark>(Point(fighter.position.x, fighter.position.y + fighter.texture.height() - 20));
		effect.update();

		// キャラクターの描画
		santa.texture.draw(Arg::center(santa.position));
		fighter.texture.draw(Arg::center(fighter.position));

		// キャラクターの移動
		if (KeyLeft.pressed() && fighter.position.x > 20) {
			fighter.position.x -= 10;
		}
		if (KeyRight.pressed() && fighter.position.x < Scene::Width() - 20) {
			fighter.position.x += 10;
		}
		if (KeyUp.pressed() && fighter.position.y > FIGHTER_TOP_Y) {
			fighter.position.y -= 10;
		}
		if (KeyDown.pressed() && fighter.position.y < Scene::Height() - 50) {
			fighter.position.y += 10;
		}

		// サンタの移動
		if (Scene::Time() > santa_moved_t + game_setting.santa_move_freq) {
			santa_move = { 0, 0 };

			if (RandomBool()) {
				if (RandomBool()) {
					if (RandomBool(0.5 - (santa.position.x - Scene::Width()/2)/Scene::Width())) {
						santa_move.x = 5;
					}
					else {
						santa_move.x = -5;
					}
				}
				else {
					if (RandomBool()) {
						santa_move.y = 5;
					}
					else {
						santa_move.y = -5;
					}
				}

				santa_moved_t = Scene::Time();
			}
		}
		if (santa.position.x < 40 || santa.position.x > Scene::Width() - 40) {
			santa.position.x -= santa_move.x;
			santa_move = { 0, 0 };
			santa_moved_t = Scene::Time();
		}
		if (santa.position.y < 20 || santa.position.y > 200) {
			santa.position.y -= santa_move.y;
			santa_move = { 0, 0 };
			santa_moved_t = Scene::Time();
		}
		santa.position.x += santa_move.x;
		santa.position.y += santa_move.y;

		// サンタによる弾丸の発射
		if (RandomBool(game_setting.santa_bullet_freq)) {
			double dist = sqrt(pow(fighter.position.x - santa.position.x + Random(-game_setting.santa_bullet_range, game_setting.santa_bullet_range), 2) 
				+ pow(fighter.position.y - santa.position.y + Random(-game_setting.santa_bullet_range, game_setting.santa_bullet_range), 2));
			santa_bullets.add(Point(santa.position.x, santa.position.y + 90),
				Vec2(game_setting.bullet_speed * (fighter.position.x - santa.position.x + Random(-game_setting.santa_bullet_range, game_setting.santa_bullet_range)) / dist,
					game_setting.bullet_speed * (fighter.position.y - santa.position.y + Random(-game_setting.santa_bullet_range, game_setting.santa_bullet_range) - 50) / dist));
		}

		// プレイヤーによる弾丸の発射
		//if (KeySpace.pressed()) {
			fighter_bullets.add(Point(fighter.position.x, fighter.position.y - 32), Vec2(0, -game_setting.bullet_speed));
		//}
		
		// プレゼントの投下
		if (RandomBool(0.1)) {
			presents.add(Point(santa.position.x, santa.position.y + 90),
						 Vec2(Random(-10, 10),
							  5));
		}

		// HPの表示
		FontAsset(U"Medium")(U"SANTA").draw(Scene::Width() / 2 - 100 * 2 - 80, 2);
		Rect(Scene::Width() / 2, 10, -santa.hp * 2, 10).draw(Palette::Red);			// サンタ
		FontAsset(U"Medium")(U"YOU").draw(Scene::Width() / 2 + 100 * 2 + 30, 2);
		Rect(Scene::Width() / 2, 10, fighter.hp * 2, 10).draw(Palette::Green);		// プレイヤー
		
		// 盗んだプレゼントの個数の表示
		present_image.draw(10, 10);
		FontAsset(U"Medium")(got_presents).drawAt(60, 25);
		
		// 当たり判定
		santa_bullets.update();
		fighter_bullets.update();
		presents.update();

		if (santa_bullets.isHit({ fighter.position.x - 20, fighter.position.y - 20 }, fighter.texture.size())) {
			fighter.damage();
		}
		else {
			fighter.recover();
		}
		if (fighter_bullets.isHit({ santa.position.x - 20, santa.position.y - 100 }, santa.texture.size())) {
			santa.damage();
		}
		else {
			santa.recover();
		}
		
		if (presents.isHit({ fighter.position.x - 20, fighter.position.y - 20 }, fighter.texture.size())) {
			got_presents++;
		}
	}
}
