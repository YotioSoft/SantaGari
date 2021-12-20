#include <game.hpp>

void game(String current_path) {
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

	// サンタの移動
	double santa_moved_t = -10.0;
	Vec2 santa_move = { 0, 0 };

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
		if (Scene::Time() > santa_moved_t + 1.0) {
			santa_move = { 0, 0 };

			if (RandomBool()) {
				if (RandomBool()) {
					if (RandomBool()) {
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
		if (santa.position.x < 20 || santa.position.x > Scene::Width() - 20) {
			santa.position.x -= santa_move.x;
			santa_move = { 0, 0 };
		}
		if (santa.position.y < 20 || santa.position.y > 200) {
			santa.position.y -= santa_move.y;
			santa_move = { 0, 0 };
		}
		santa.position.x += santa_move.x;
		santa.position.y += santa_move.y;

		// サンタによる弾丸の発射
		if (RandomBool(0.2)) {
			double dist = sqrt(pow(fighter.position.x - santa.position.x, 2) + pow(fighter.position.y - santa.position.y, 2));
			santa_bullets.add(Point(santa.position.x, santa.position.y + 90),
				Vec2(5 * (fighter.position.x - santa.position.x) / dist,
					5 * (fighter.position.y - santa.position.y - 50) / dist));
		}

		// プレイヤーによる弾丸の発射
		if (KeySpace.pressed()) {
			fighter_bullets.add(Point(fighter.position.x, fighter.position.y - 32), Vec2(0, -5));
		}

		// HPの表示
		Rect(Scene::Width() / 2, 10, -santa.hp * 2, 10).draw(Palette::Red);			// サンタ
		Rect(Scene::Width() / 2, 10, fighter.hp * 2, 10).draw(Palette::Green);		// プレイヤー

		// 当たり判定
		santa_bullets.update();
		fighter_bullets.update();

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
	}
}