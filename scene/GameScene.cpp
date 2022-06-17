#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<time.h>
#include<stdlib.h>

using namespace DirectX;
//コンストラクタ
GameScene::GameScene() {}

//デストラクタ
GameScene::~GameScene() 
{ 
	delete spriteBG_;
	delete modelStage_;
	delete modelplayer_;
	delete modelBeam_;
	delete modelEnemy_;
	delete spriteTitle_;
	delete spriteEnter_;
	delete spriteOver_;
}
//初期化
void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandleBG_ = TextureManager::Load("bg.jpg");
	textureHandleBeam_ = TextureManager::Load("beam.png");
	textureHandleEnemy_ = TextureManager::Load("enemy.png");

	textureHandleStage_ = TextureManager::Load("stage2.jpg");
	textureHandleplayer_ = TextureManager::Load("player.png");
	spriteBG_ = Sprite::Create(textureHandleBG_, {0, 0});
	modelStage_ = Model::Create();
	modelplayer_ = Model::Create();
	modelBeam_ = Model::Create();
	modelEnemy_ = Model::Create();
	worldTransformplayer_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformplayer_.Initialize();
	  
	
	
	
	viewProjection_.eye = {0,1,-6};
	viewProjection_.target = {0, 1, 0};
	viewProjection_.Initialize();

	for (int k = 0; k < 20; k++) {

		worldTransformStage_[k].translation_ = {0, -1.5f, 2.0f * k - 5};
		worldTransformStage_[k].scale_ = {4.5f, 1, 1};
		worldTransformStage_[k].Initialize();
	}
	for (int j = 0; j < 10; j++) {

		worldTransformBeam_[j].scale_ = {0.3f, 0.3f, 0.3f};
		worldTransformBeam_[j].Initialize();
	}
	for (int i = 0; i < 10; i++) {

		worldTransformEnemy_[i].scale_ = {0.5f, 0.5f, 0.5f};
		worldTransformEnemy_[i].translation_ = {0, 0, 35};
		worldTransformEnemy_[i].Initialize();
	}
	textureHandleTitle_ = TextureManager::Load("title.png");
	spriteTitle_ = Sprite::Create(textureHandleTitle_, {0, 0});

	textureHandleEnter_ = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandleEnter_, {400, 500});

	textureHandleOver_ = TextureManager::Load("gameover.png");
	spriteOver_ = Sprite::Create(textureHandleOver_, {0, 0});
	srand((unsigned int)time(NULL));

	soundDetaHandleTitleBGM_ = audio_->LoadWave("Audio/Ring05.wav");
	soundDetaHandleGamePlayBGM_ = audio_->LoadWave("Audio/Ring08.wav");
	soundDetaHandleGameOverBGM_ = audio_->LoadWave("Audio/Ring09.wav");
	soundDetaHandleEnemyHitSE_ = audio_->LoadWave("Audio/chord.wav");
	soundDetaHandlePlayerHitSE_ = audio_->LoadWave("Audio/tada.wav");

	voiceHandleBGM_ = audio_->PlayWave(soundDetaHandleTitleBGM_, true);


	//soundDataHandle_ = audio_->LoadWave("se_sad03.wav");
	//audio_->PlayWave(soundDataHandle_);
	//voiceHandle_ = audio_->PlayWave(soundDataHandle_,true);

}
//更新
void GameScene::Update() 
{ 
	gameTimer_ += 1;
	switch (sceneMode_) 
	{
	case 0:
		GamePlayUpdate();
		break;
	case 1:
		TitleUpdate();
		break;
	case 2:
		OverUpdate();
		break;
	}
	

	


	
	
}
//表示
void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	switch (sceneMode_) 
	{
	case 0:
		GameplayDraw2DBack();
		break;
	case 2:
		GameplayDraw2DBack();

		break;
	}
	

	
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	switch (sceneMode_) {
	case 0:
		GemePlayDraw3D();
		break;
	case 2:
		GemePlayDraw3D();

		break;
	}
	

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	



	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);
	switch (sceneMode_) {
	case 0:
		GemePlayDraw2DNear();
		break;
	case 1:
		TitleDraw2DNear();
		break;
	case 2:
		GemePlayDraw2DNear();
		OverDraw2DNear();
		break;
	}
	
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

void GameScene::BeamUpdate() 
{ 
	BeamBorn();
	BeamMove();
	for (int j = 0; j < 10; j++) {
		worldTransformBeam_[j].UpdateMatrix();
	}
	


}

void GameScene::BeamMove() 
{ 
	for (int j = 0; j < 10; j++) {
		if (BeamFlag[j] == 1) {

			worldTransformBeam_[j].translation_.z += 1;
			worldTransformBeam_[j].rotation_.x += 0.1f;
		}
		if (worldTransformBeam_[j].translation_.z >= 40) {
			BeamFlag[j] = 0;
		}
	}
}

void GameScene::BeamBorn() 
{ 
	if (beamTimer_ == 0) 
	{

		for (int j = 0; j < 10; j++) 
		{
			if (BeamFlag[j] == 0) 
			{

				if (input_->PushKey(DIK_SPACE)) 
				{

					worldTransformBeam_[j].translation_.x = worldTransformplayer_.translation_.x;
					worldTransformBeam_[j].translation_.y = worldTransformplayer_.translation_.y;
					worldTransformBeam_[j].translation_.z = worldTransformplayer_.translation_.z;
					BeamFlag[j] = 1;
					beamTimer_=1;
					break;
				}
			}
		}
	} else {
		beamTimer_++;
		if (beamTimer_ > 10) {
			beamTimer_ = 0;
		}
	}

}


void GameScene::EnemyUpdate() 
{ 
	EnemyMove();
	EnemyBorn(); 
	EnemyJump();
	for (int i = 0; i < 10; i++) {

		worldTransformEnemy_[i].UpdateMatrix();
	}
}

void GameScene::EnemyMove() 
{ 
	for (int i = 0; i < 10; i++) 
	{
		if (EnemyFlag[i] == 1) {

			 worldTransformEnemy_[i].translation_.x += Enemyspeed[i];
			worldTransformEnemy_[i].rotation_.x -= 0.1f;
			
			worldTransformEnemy_[i].translation_.z -= gameTimer_ / 10000.0f; // 0.5f;
			
			if (worldTransformEnemy_[i].translation_.z < -5) {
				EnemyFlag[i] = 0;
			}

			if (worldTransformEnemy_[i].translation_.x<=-4) {
				Enemyspeed[i] = 0.2f;
			}
			if (worldTransformEnemy_[i].translation_.x >= 4) {
				Enemyspeed[i] = -0.2f;
			}
		}
	}
}

void GameScene::EnemyBorn() 
{
	if (rand() % 10 == 0) {

		for (int i = 0; i < 10; i++) {
			if (EnemyFlag[i] == 0) {
				EnemyFlag[i] = 1;
				worldTransformEnemy_[i].translation_.z = 40;

				int x = rand() % 80;
				float x2 = (float)x / 10 - 4;
				worldTransformEnemy_[i].translation_.x = x2;


				if (rand() % 2 == 0) {
					Enemyspeed[i] = 0.2f;
				} else {
					Enemyspeed[i] = -0.2f;
				}
				break;
			}
		}
	}
	
	





}

void GameScene::Collision() {

	Collisionplayerenemy();

}

void GameScene::Collisionplayerenemy() 
{
	for (int i = 0; i < 10; i++) {
		if (EnemyFlag[i] == 1) {

			float dx =
			  abs(worldTransformplayer_.translation_.x - worldTransformEnemy_[i].translation_.x);
			float dz =
			  abs(worldTransformplayer_.translation_.z - worldTransformEnemy_[i].translation_.z);

			if (dx < 1 && dz < 1) {
				EnemyFlag[i] = 0;
				playerLife_ -= 1;

				audio_->PlayWave(soundDetaHandlePlayerHitSE_);
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (EnemyFlag[i] == 1 && BeamFlag[j] == 1) {
				float bx = abs(
				  worldTransformBeam_[j].translation_.x - worldTransformEnemy_[i].translation_.x);
				float bz = abs(
				  worldTransformBeam_[j].translation_.z - worldTransformEnemy_[i].translation_.z);

				if (bx < 1 && bz < 1) {
					EnemyFlag[i] = 2;
					enemyJumpSpeed_[i] = 1;
					BeamFlag[j] = 0;
					gamescore_ += 10;
					audio_->PlayWave(soundDetaHandleEnemyHitSE_);
				}
			}
		}
	}


}

void GameScene::GamePlayUpdate() {
	playerUpdate();
	BeamUpdate();
	EnemyUpdate();
	StageUpdate();
	Collision();


	if (playerLife_ == 0) {
		sceneMode_ = 2;
		audio_->StopWave(voiceHandleBGM_);
		voiceHandleBGM_ = audio_->PlayWave(soundDetaHandleGameOverBGM_, true);
	}
}

void GameScene::GemePlayDraw3D() {
	for (int k = 0; k < 20; k++) {

		modelStage_->Draw(worldTransformStage_[k], viewProjection_, textureHandleStage_);
	}
	modelplayer_->Draw(worldTransformplayer_, viewProjection_, textureHandleplayer_);

	for (int j = 0; j < 10; j++) {
		if (BeamFlag[j] == 1) {
			modelBeam_->Draw(worldTransformBeam_[j], viewProjection_, textureHandleBeam_);
		}
	}

		for (int i = 0; i < 10; i++) {
			if (EnemyFlag[i]!=0) {

				modelEnemy_->Draw(worldTransformEnemy_[i], viewProjection_, textureHandleEnemy_);
			}
			
		}
	
}

void GameScene::GameplayDraw2DBack() {

	spriteBG_->Draw(); }

void GameScene::GemePlayDraw2DNear() {
	char str[100];
	sprintf_s(str, "SCORE:%d", gamescore_);
	debugText_->Print(str, 200, 10, 2);

	char str2[100];
	sprintf_s(str2, "LIFE:%d", playerLife_);
	debugText_->Print(str2, 400, 10, 2);
}

void GameScene::TitleUpdate() { 
	if (input_->TriggerKey(DIK_RETURN)) {
		sceneMode_ = 0;
		GamePlayStart();

		audio_->StopWave(voiceHandleBGM_);
		voiceHandleBGM_ = audio_->PlayWave(soundDetaHandleGamePlayBGM_, true);
	}
}

void GameScene::TitleDraw2DNear() { 
	spriteTitle_->Draw();
	if (gameTimer_%40>=20) 
	{
		spriteEnter_->Draw();
	}
	
}

void GameScene::OverDraw2DNear() 
{ 
	spriteOver_->Draw();
	if (gameTimer_ % 40 >= 20) 
	{
		spriteEnter_->Draw();
	}


}

void GameScene::OverUpdate() 
{ 
	
	if (input_->TriggerKey(DIK_RETURN)) {
		sceneMode_ = 1;
		audio_->StopWave(voiceHandleBGM_);
		voiceHandleBGM_ = audio_->PlayWave(soundDetaHandleTitleBGM_, true);
	}
}

void GameScene::GamePlayStart() 
{
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			EnemyFlag[i] = 0;
			gamescore_ = 0;
			playerLife_ = 3;
			BeamFlag[j] = 0;
			gameTimer_ = 0;
			// sceneMode_ = 1;
		}
	}
}

void GameScene::StageUpdate() 
{ 
	for (int k = 0; k < 20;k++) 
	{
		worldTransformStage_[k].translation_.z -= 0.1f;
		if (worldTransformStage_[k].translation_.z< -5) {
			worldTransformStage_[k].translation_.z += 40;
		}

		worldTransformStage_[k].UpdateMatrix();
	}
}

void GameScene::EnemyJump() 
{ 
	for (int i=0;i<10;i++) 
	{
		if (EnemyFlag[i]==2) 
		{
			worldTransformEnemy_[i].translation_.y += enemyJumpSpeed_[i];

			enemyJumpSpeed_[i] -= 0.1f;

			worldTransformEnemy_[i].translation_.x += Enemyspeed[i] * 2;

			if (worldTransformEnemy_[i].translation_.y<-3) {
				EnemyFlag[i] = 0;
				worldTransformEnemy_[1].translation_.y = 0;
			}

		}
	}




}

