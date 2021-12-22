//
//  Header.hpp
//  SantaGari
//
//  Created by YotioSoft on 2021/12/20.
//

#ifndef Header_h
#define Header_h

#include <Siv3D.hpp>		// OpenSiv3D v0.6.3

#define FIGHTER_TOP_Y	300

typedef struct _Charactor {
	Texture texture = Texture(U"img/bullet.png");
	Point position;
	double hp;
	double m_t = 0.0;

	void recover() {
		if (hp >= 100) {
			hp = 100;
			return;
		}
		if (Scene::Time() < m_t + 1.0) {
			return;
		}
		hp += 0.25;
		m_t = Scene::Time();
	}

	void damage() {
		if (hp < 0) {
			hp = 0;
			return;
		}
		hp -= 0.5;
	}
} Charactor;

typedef struct Particle {
	Vec2 start;
	Vec2 velocity;
} Particle;

typedef struct Spark : IEffect {
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
				+ particle.velocity * t + t * t * Vec2(0, 240);

			Triangle(pos, 16.0, pos.x * 5_deg).draw(ColorF(1.0, 1.0 - 0.6 * t, 1.0 - t, 1.0 - t * 1.5));
		}

		return t < 1.0;
	}
} Spark;

typedef struct Bullet {
	typedef struct BulletPosition {
		Vec2 position;
		Vec2 direction;
		Texture* texture;
	} BulletPosition;

	Texture m_texture;
	Array<BulletPosition> m_position;
	double m_last_add_time;
	
	Bullet(){}
	Bullet(String img_filepath) {
		m_texture = Texture(img_filepath);
		m_last_add_time = 0;
	}

	void add(Vec2 fighter_position, Vec2 direction) {
		if (Scene::Time() < m_last_add_time + 0.1) {
			return;
		}
		m_last_add_time = Scene::Time();
		m_position << BulletPosition{fighter_position, direction};
	}

	void update() {
		for (unsigned long i = 0; i < m_position.size(); i++) {
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
		for (unsigned long i = 0; i < m_position.size(); i++) {
			if (m_position[i].position.x >= pos.x && m_position[i].position.y >= pos.y &&
				m_position[i].position.x <= pos.x + size.x && m_position[i].position.y <= pos.y + size.y) {

				m_position.remove_at(i);
				i--;

				return true;
			}
		}
		return false;
	}
} Bullet;

typedef struct Present : Bullet {
	Array<Texture> m_texture_templetes;
	
	Present(Array<String> img_filepaths) {
		for (auto img_filepath : img_filepaths) {
			m_texture_templetes << Texture(img_filepath);
		}
		m_last_add_time = 0;
	}
	
	void add(Vec2 fighter_position, Vec2 direction) {
		if (Scene::Time() < m_last_add_time + 0.1) {
			return;
		}
		m_last_add_time = Scene::Time();
		m_position << BulletPosition{fighter_position, direction, &m_texture_templetes[Random(m_texture_templetes.size()-1)]};
	}
	
	void update() {
		for (unsigned long i = 0; i < m_position.size(); i++) {
			m_position[i].texture->draw(Arg::center(m_position[i].position));
			
			m_position[i].position.x += m_position[i].direction.x;
			m_position[i].position.y += m_position[i].direction.y;

			if (m_position[i].position.x < 0 || m_position[i].position.y < 0 ||
				m_position[i].position.y > Scene::Width() || m_position[i].position.y > Scene::Height()) {
				m_position.remove_at(i);
				i--;
			}
		}
	}
} Present;

#endif /* Header_h */
