﻿#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;
//コンストラクタ
GameScene::GameScene() {}

//デストラクタ
GameScene::~GameScene() 
{ 
	delete spriteBG_;
	delete modelStage_;
	delete modelplayer_;
}
//初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandleBG_ = TextureManager::Load("bg.jpg");
	textureHandleStage_ = TextureManager::Load("stage.jpg");
	textureHandleplayer_ = TextureManager::Load("player.png");
	spriteBG_ = Sprite::Create(textureHandleBG_, {0, 0});
	modelStage_ = Model::Create();
	modelplayer_ = Model::Create();
	worldTransformplayer_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformplayer_.Initialize();
	  
	
	
	
	viewProjection_.eye = {0,1,-6};
	viewProjection_.target = {0, 1, 0};
	viewProjection_.Initialize();
	worldTransformStage_.translation_ = {0, -1.5f, 0};
	worldTransformStage_.scale_ = {4.5f, 1, 40};
	
	worldTransformStage_.Initialize();
	//soundDataHandle_ = audio_->LoadWave("se_sad03.wav");
	//audio_->PlayWave(soundDataHandle_);
	//voiceHandle_ = audio_->PlayWave(soundDataHandle_,true);

}
//更新
void GameScene::Update() 
{ 
	//XMFLOAT2 position = sprite_->GetPosition();

	//position.x += 2.0f;
	//position.y += 1.0f;
	playerUpdate();
	//sprite_->SetPosition(position);

	if(input_->TriggerKey(DIK_SPACE)) 
	{
		//audio_->StopWave(voiceHandle_);
	}
	//debugText_->Print("kaizokuou ni orw ha naru", 50, 50, 1.0f);
	debugText_->SetPos(50, 70);
	//debugText_->Printf("year:%d", value_);
	//value_++;

	//std::string strDebug = std::string("value!!");
	//std::to_string(value_);
	//debugText_->Print(strDebug, 50, 50, 1.0f);
}
//表示
void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	spriteBG_->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	modelStage_->Draw(worldTransformStage_, viewProjection_, textureHandleStage_);
	modelplayer_->Draw(worldTransformplayer_, viewProjection_, textureHandleplayer_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//sprite_->Draw();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();
	
	
#pragma endregion
}

void GameScene::playerUpdate() 
{ 
	if (input_->PushKey(DIK_RIGHT)) 
	{
		worldTransformplayer_.translation_.x += 0.1f;
	}

	if (input_->PushKey(DIK_LEFT)) {
	
		worldTransformplayer_.translation_.x -= 0.1f;
	}
	worldTransformplayer_.UpdateMatrix();
	
	if (worldTransformplayer_.translation_.x>=4) {
		worldTransformplayer_.translation_.x =4;
	}

	if (worldTransformplayer_.translation_.x <= -4) {
		worldTransformplayer_.translation_.x = -4;
	}




}

