#include <Novice.h>
#include <math.h>
#include "Enemy.h"
#include "object.h"

const char kWindowTitle[] = "学籍番号";

Object Player;
Object Bullet[10];

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Enemy* enemyA = new Enemy(100, 200, 8);
	Enemy* enemyB = new Enemy(100, 400, 6);

	Player.posX_ = 500;
	Player.posY_ = 500;
	Player.radius_ = 30;
	Player.speed_ = 5;
	Player.isAlive_ = true;

	for (int i = 0; i < 10; i++) {
		Bullet[i].posX_ = 500;
		Bullet[i].posY_ = 500;
		Bullet[i].radius_ = 10;
		Bullet[i].speed_ = 10;
		Bullet[i].isAlive_ = false;
	}

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		Novice::ScreenPrintf(0, 0, "%d", Enemy::enemyCount);
		enemyA->Update();
		enemyB->Update();
		if (Enemy::enemyCount == 1) {
			Enemy::enemyCount = 0;
			enemyA->isAlive_ = false;
			enemyB->isAlive_ = false;
		}
		if (!preKeys[DIK_R] && keys[DIK_R]) {
			if (enemyA) { delete enemyA; enemyA = nullptr; }
			enemyA = new Enemy(100, 200, 8);
			if (enemyB) { delete enemyB; enemyB = nullptr; }
			enemyB = new Enemy(100, 400, 6);
			Enemy::enemyCount = 2;
			for (int i = 0; i < 10; i++) {
				if (Bullet[i].isAlive_) {
					Bullet[i].isAlive_ = false;
				}
			}
		}

		if (keys[DIK_A]) {
			Player.posX_ -= Player.speed_;
		}
		if (keys[DIK_D]) {
			Player.posX_ += Player.speed_;
		}
		if (keys[DIK_W]) {
			Player.posY_ -= Player.speed_;
		}
		if (keys[DIK_S]) {
			Player.posY_ += Player.speed_;
		}
		if (!preKeys[DIK_SPACE] && keys[DIK_SPACE]) {
			for (int i = 0; i < 10; i++) {
				if (!Bullet[i].isAlive_) {
					Bullet[i].isAlive_ = true;
					Bullet[i].posX_ = Player.posX_;
					Bullet[i].posY_ = Player.posY_;
					break;
				}
			}
		}
		for (int i = 0; i < 10; i++) {
			if (Bullet[i].isAlive_) {
				Bullet[i].posY_ -= Bullet[i].speed_;
				if (Bullet[i].posY_ < -Bullet[i].radius_ * 2) {
					Bullet[i].isAlive_ = false;
				}
			}
		}
		for (int i = 0; i < 10; i++) {
			if (Bullet[i].isAlive_) {
				int distAX = enemyA->posX_ - Bullet[i].posX_;
				int distAY = enemyA->posY_ - Bullet[i].posY_;
				int distBX = enemyB->posX_ - Bullet[i].posX_;
				int distBY = enemyB->posY_ - Bullet[i].posY_;
				int distA = (distAX * distAX) + (distAY * distAY);
				int distB = (distBX * distBX) + (distBY * distBY);
				int radiusA = enemyA->radius_ + Bullet[i].radius_;
				int radiusB = enemyB->radius_ + Bullet[i].radius_;
				if (distA <= radiusA * radiusA) {
					if (enemyA->isAlive_) {
						enemyA->isAlive_ = false;
						Bullet[i].isAlive_ = false;
						Enemy::enemyCount--;
					}
				}
				if (distB <= radiusB * radiusB) {
					if (enemyB->isAlive_) {
						enemyB->isAlive_ = false;
						Bullet[i].isAlive_ = false;
						Enemy::enemyCount--;
					}
				}
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		enemyA->Draw();
		enemyB->Draw();

		for (int i = 0; i < 10; i++) {
			if (Bullet[i].isAlive_) {
				Novice::DrawEllipse(Bullet[i].posX_, Bullet[i].posY_, Bullet[i].radius_, Bullet[i].radius_, 0.0f, BLUE, kFillModeSolid);
			}
		}
		Novice::DrawEllipse(Player.posX_, Player.posY_, Player.radius_, Player.radius_, 0.0f, WHITE, kFillModeSolid);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			delete enemyA;
			delete enemyB;
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
