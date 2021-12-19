# include <Siv3D.hpp> // OpenSiv3D v0.6.3

#define FIGHTER_TOP_Y	300

typedef struct _Charactor {
	Texture texture = Texture(U"img/bullet.png");
	Point position;
	double hp;

	void recover() {
		hp+=0.5;
	}

	void damage() {
		hp--;
	}
} Charactor;

struct Particle
{
	Vec2 start;

	Vec2 velocity;
};

struct Spark : IEffect
{
	Array<Particle> m_particles;

	Spark(const Vec2& start)
		: m_particles(20)
	{
		for (auto& particle : m_particles)
		{
			particle.start = start + RandomVec2(10.0);

			particle.velocity = RandomVec2(1.0) * Random(80.0);
		}
	}

	bool update(double t) override
	{
		for (const auto& particle : m_particles)
		{
			const Vec2 pos = particle.start
				+ particle.velocity * t + 0.5 * t * t * Vec2(0, 240);

			Triangle(pos, 16.0, pos.x * 5_deg).draw(ColorF(1.0, 1.0 - 0.6 * t, 1.0 - t, 1.0 - t * 1.5));
		}

		return t < 1.0;
	}
};

struct Bullet {
	struct BulletPosition {
		Point position;
		Vec2 direction;
	};

	Texture m_texture;
	Array<BulletPosition> m_position;
	double m_last_add_time;

	Bullet(String img_filepath) {
		m_texture = Texture(img_filepath);
		m_last_add_time = 0;
	}

	void add(Point fighter_position, Vec2 direction) {
		if (Scene::Time() < m_last_add_time + 0.1) {
			return;
		}
		m_last_add_time = Scene::Time();
		m_position << BulletPosition(fighter_position, direction);
	}

	void update() {
		for (int i = 0; i < m_position.size(); i++) {
			m_texture.draw(Arg::center(m_position[i].position));

			m_position[i].position.x += m_position[i].direction.x;
			m_position[i].position.y += m_position[i].direction.y;

			if (m_position[i].position.x < 0 || m_position[i].position.y < 0 ||
				m_position[i].position.y > Scene::Width() || m_position[i].position.y > Scene::Height()) {
				m_position.remove_at(i);
				i--;
			}
		}
	}

	bool isHit(Point pos, Size size) {
		for (int i = 0; i < m_position.size(); i++) {
			if (m_position[i].position.x >= pos.x && m_position[i].position.y >= pos.y &&
				m_position[i].position.x <= pos.x + size.x && m_position[i].position.y <= pos.y + size.y) {

				m_position.remove_at(i);
				i--;

				return true;
			}
		}
		return false;
	}
};

void game() {
	// キャラクター
	Charactor santa;
	Charactor fighter;

	// キャラ画像読み込み
	santa.texture = Texture(U"img/santa.png");
	fighter.texture = Texture(U"img/fighter.png");

	// キャラの位置
	santa.position = Point(Scene::Width() / 2, 150);
	fighter.position = Point(Scene::Width() / 2, 400);

	// キャラのHPの初期値
	santa.hp = 100;
	fighter.hp = 100;

	// 火花
	Effect effect;

	// 弾丸
	Bullet santa_bullets(U"img/bullet.png");
	Bullet fighter_bullets(U"img/bullet2.png");

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
		/*
		if (RandomBool()) {
			if (RandomBool()) {
				if (RandomBool()) {
					santa.position.x += 10;
				}
				else {
					santa.position.x -= 10;
				}
			}
			else {
				if (RandomBool()) {
					santa.position.y += 10;
				}
				else {
					santa.position.y -= 10;
				}
			}
		}*/

		// サンタによる弾丸の発射
		if (RandomBool()) {
			santa_bullets.add(Point(santa.position.x, santa.position.y + 90), Vec2(Random<int>(-10, 10), 10));
		}

		// プレイヤーによる弾丸の発射
		if (KeySpace.pressed()) {
			fighter_bullets.add(Point(fighter.position.x, fighter.position.y - 32), Vec2(0, -10));
		}

		santa_bullets.update();
		fighter_bullets.update();

		if (santa_bullets.isHit({ fighter.position.x - 20, fighter.position.y - 20 }, fighter.texture.size())) {
			fighter.damage();
		}
		if (fighter_bullets.isHit({ santa.position.x - 20, santa.position.y - 100 }, santa.texture.size())) {
			santa.damage();
		}
	}
}

void Main()
{
	game();

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

//
// = アドバイス =
// Debug ビルドではプログラムの最適化がオフになります。
// 実行速度が遅いと感じた場合は Release ビルドを試しましょう。
// アプリをリリースするときにも、Release ビルドにするのを忘れないように！
//
// 思ったように動作しない場合は「デバッグの開始」でプログラムを実行すると、
// 出力ウィンドウに詳細なログが表示されるので、エラーの原因を見つけやすくなります。
//
// = お役立ちリンク | Quick Links =
//
// Siv3D リファレンス
// https://zenn.dev/reputeless/books/siv3d-documentation
//
// Siv3D Reference
// https://zenn.dev/reputeless/books/siv3d-documentation-en
//
// Siv3D コミュニティへの参加
// Slack や Twitter, BBS で気軽に質問や情報交換ができます。
// https://zenn.dev/reputeless/books/siv3d-documentation/viewer/community
//
// Siv3D User Community
// https://zenn.dev/reputeless/books/siv3d-documentation-en/viewer/community
//
// 新機能の提案やバグの報告 | Feedback
// https://github.com/Siv3D/OpenSiv3D/issues
//
