#pragma once
#include "object.h"
class Enemy : public Object
{
public:	// メンバ関数
	static int enemyCount;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="posX">X座標</param>
	/// <param name="posY">Y座標</param>
	/// <param name="speed">移動速度</param>
	Enemy(int posX, int posY, int speed);
	~Enemy();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

};

