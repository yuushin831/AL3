#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>
#include<stdlib.h>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	uint32_t textureHandleBG_ = 0;
	uint32_t textureHandleBeam_ = 0;
	uint32_t textureHandleEnemy_ = 0;
	uint32_t textureHandleStage_ = 0;
	uint32_t textureHandleplayer_ = 0;
	Model* modelStage_ = nullptr;
	Model* modelBeam_ = nullptr;
	Model* modelEnemy_ = nullptr;
	Model* modelplayer_ = nullptr;
	Sprite* spriteBG_ = nullptr;
	WorldTransform worldTransformStage_;
	WorldTransform worldTransformBeam_;
	WorldTransform worldTransformEnemy_;
	WorldTransform worldTransformplayer_;
	ViewProjection viewProjection_;
	int BeamFlag = 0;
	//uint32_t soundDataHandle_ = 0;
	//uint32_t voiceHandle_ = 0;
	//uint32_t value_ = 0;
	void playerUpdate();
	void BeamUpdate();
	void BeamMove();
	void BeamBorn();
	void EnemyUpdate();
	void EnemyMove();
	void EnemyBorn();
	void Collision();
	void Collisionplayerenemy();
	float Enemyspeed = 0.1f;
	int EnemyFlag = 0;
	int gamescore_ = 0;
	int playerLife_ = 3;
};
