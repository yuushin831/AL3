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
	WorldTransform worldTransformStage_[20];
	WorldTransform worldTransformBeam_[10];
	WorldTransform worldTransformEnemy_[10];
	WorldTransform worldTransformplayer_;
	ViewProjection viewProjection_;
	int BeamFlag[10] = {};
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
	float Enemyspeed[10] = {};
	int EnemyFlag[10] = {};
	int gamescore_ = 0;
	int playerLife_ = 3;

	void GamePlayUpdate();

	void GemePlayDraw3D();

	void GameplayDraw2DBack();

	void GemePlayDraw2DNear();

	int sceneMode_ = 1;

	void TitleUpdate();

	void TitleDraw2DNear();

	void OverDraw2DNear();
	void OverUpdate();

	void GamePlayStart();

	void StageUpdate();

	int gameTimer_ = 0;
	int beamTimer_ = 0;

	uint32_t textureHandleTitle_ = 0;
	Sprite* spriteTitle_ = nullptr;
	uint32_t textureHandleEnter_ = 0;
	Sprite* spriteEnter_ = nullptr;
	uint32_t textureHandleOver_ = 0;
	Sprite* spriteOver_ = nullptr;

	uint32_t soundDetaHandleTitleBGM_ = 0;
	uint32_t soundDetaHandleGamePlayBGM_ = 0;
	uint32_t soundDetaHandleGameOverBGM_ = 0;
	uint32_t soundDetaHandleEnemyHitSE_ = 0;
	uint32_t soundDetaHandlePlayerHitSE_ = 0;
	uint32_t voiceHandleBGM_ = 0;

	float enemyJumpSpeed_[10] = {};
	void EnemyJump();

	void DrawScore();
	uint32_t texttureHandleNumber_ = 0;
	Sprite* spriteNumber_[5] = {};

	uint32_t texttureHandleScore_ = 0;
	Sprite* spriteScore_ = 0;

	Sprite* spriteNumberPlayer1_ = 0;
	Sprite* spriteNumberPlayer2_ = 0;
	Sprite* spriteNumberPlayer3_ = 0;

	int playerTimer_ = 0;
};
