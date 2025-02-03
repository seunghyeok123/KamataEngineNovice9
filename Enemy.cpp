#include "Enemy.h"
#include "Novice.h"

int Enemy::enemyCount = 0;

Enemy::Enemy(int posX, int posY, int speed)
{
	enemyCount++;
	posX_ = posX;
	posY_ = posY;
	speed_ = speed;
	radius_ = 16;
	isAlive_ = true;
}

void Enemy::Update() {
	if (isAlive_) {
		posX_ += speed_;

		if (posX_ - radius_ <= 0 || posX_ + radius_ >= 1280) {
			speed_ *= -1;
		}
	}
}

void Enemy::Draw() {
	if (isAlive_) {
		Novice::DrawEllipse(posX_, posY_, radius_, radius_, 0.0f, RED, kFillModeSolid);
	}
}
