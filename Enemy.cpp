#include "Enemy.h"
#include "Novice.h"

bool Enemy::isAlive = true;

Enemy::Enemy(int posX, int posY, int speed)
{
	posX_ = posX;
	posY_ = posY;
	speed_ = speed;
	radius_ = 16;
}

Enemy::~Enemy()
{
}

void Enemy::Update() {
	if (isAlive) {
		posX_ += speed_;

		if (posX_ - radius_ <= 0 || posX_ + radius_ >= 1280) {
			speed_ *= -1;
		}
	}
}

void Enemy::Draw() {
	if (isAlive) {
		Novice::DrawEllipse(posX_, posY_, radius_, radius_, 0.0f, RED, kFillModeSolid);
	}
}
