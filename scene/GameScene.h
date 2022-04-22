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
	uint32_t textureHandleStage_ = 0;
	uint32_t textureHandleplayer_ = 0;
	Model* modelStage_ = nullptr;
	Model* modelplayer_ = nullptr;
	Sprite* spriteBG_ = nullptr;
	WorldTransform worldTransformStage_;
	WorldTransform worldTransformplayer_;
	ViewProjection viewProjection_;
	//uint32_t soundDataHandle_ = 0;
	//uint32_t voiceHandle_ = 0;
	//uint32_t value_ = 0;
	void playerUpdate();
};
