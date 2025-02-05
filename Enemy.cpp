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
}

Enemy::~Enemy()
{
	enemyCount--;
}

void Enemy::Update() {

	posX_ += speed_;

	if (posX_ - radius_ <= 0 || posX_ + radius_ >= 1280) {
		speed_ *= -1;
	}
}

void Enemy::Draw() {
	Novice::DrawEllipse(posX_, posY_, radius_, radius_, 0.0f, RED, kFillModeSolid);
}
