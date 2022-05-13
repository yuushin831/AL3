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

	textureHandleStage_ = TextureManager::Load("stage.jpg");
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

	worldTransformStage_.translation_ = {0, -1.5f, 0};
	worldTransformStage_.scale_ = {4.5f, 1, 40};
	worldTransformStage_.Initialize();

	worldTransformBeam_.scale_ = {0.3f, 0.3f, 0.3f};
	worldTransformBeam_.Initialize();

	worldTransformEnemy_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformEnemy_.translation_ = {0, 0, 35};
	worldTransformEnemy_.Initialize();


	srand((unsigned int)time(NULL));

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
	BeamUpdate();
	EnemyUpdate();

	Collision();
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
	if (EnemyFlag) {

		modelEnemy_->Draw(worldTransformEnemy_, viewProjection_, textureHandleEnemy_);
	}
	if (BeamFlag==1) 
	{
		modelBeam_->Draw(worldTransformBeam_, viewProjection_, textureHandleBeam_);
	}

	char str[100];
	sprintf_s(str, "SCORE:%d", gamescore_);
	debugText_->Print(str, 200, 10, 2);

	char str2[100];
	sprintf_s(str2, "LIFE:%d", playerLife_);
	debugText_->Print(str2, 400, 10, 2);


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

void GameScene::BeamUpdate() 
{ 
	BeamBorn();
	BeamMove();
	worldTransformBeam_.UpdateMatrix();
	
	


}

void GameScene::BeamMove() 
{ 
	if (BeamFlag == 1) {

		worldTransformBeam_.translation_.z += 1;
		worldTransformBeam_.rotation_.x += 0.1f;
		
	
	}
	if (worldTransformBeam_.translation_.z >= 40) {
		BeamFlag = 0;
	}
}

void GameScene::BeamBorn() 
{ 
	if (BeamFlag == 0) 
	{

		if (input_->PushKey(DIK_SPACE)) {

			worldTransformBeam_.translation_.x = worldTransformplayer_.translation_.x;
			worldTransformBeam_.translation_.y = worldTransformplayer_.translation_.y;
			worldTransformBeam_.translation_.z = worldTransformplayer_.translation_.z;
			BeamFlag = 1;
		}
	}
	

}


void GameScene::EnemyUpdate() 
{ 
	EnemyMove();
	EnemyBorn(); 
	worldTransformEnemy_.UpdateMatrix();
	
}

void GameScene::EnemyMove() 
{ 
	if (EnemyFlag == 1) 
	{
		
		
			


		//worldTransformEnemy_.translation_.x += Enemyspeed;
		//if (worldTransformEnemy_.translation_.x >= 4) {
		//	// worldTransformEnemy_.translation_.x -=
		//	Enemyspeed -= 0.1f;
		//}
		//if (worldTransformEnemy_.translation_.x <= -4) {
		//	// worldTransformEnemy_.translation_.x -=
		//	Enemyspeed += 0.1f;
		//}
		worldTransformEnemy_.rotation_.x -= 0.1f;
		worldTransformEnemy_.translation_.z -= 0.1f;
		if (worldTransformEnemy_.translation_.z<-5)
		{
			EnemyFlag = 0;
		}
		

	}

}

void GameScene::EnemyBorn() 
{

	if (EnemyFlag==0) 
	{
		EnemyFlag = 1;
		worldTransformEnemy_.translation_.z = 40;


			int x = rand() % 80;
		float x2 = (float)x / 10 - 4;
		worldTransformEnemy_.translation_.x = x2;


	}


	





}

void GameScene::Collision() {

	Collisionplayerenemy();

}

void GameScene::Collisionplayerenemy() 
{

	if (EnemyFlag == 1) {

		float dx = abs(worldTransformplayer_.translation_.x - worldTransformEnemy_.translation_.x);
		float dz = abs(worldTransformplayer_.translation_.z - worldTransformEnemy_.translation_.z);
		
		if (dx < 1 && dz < 1) 
		{
			EnemyFlag = 0;
			playerLife_ -= 1;
		}
		
	}

	if (EnemyFlag==1&&BeamFlag==1) {
		float bx = abs(worldTransformBeam_.translation_.x - worldTransformEnemy_.translation_.x);
		float bz = abs(worldTransformBeam_.translation_.z - worldTransformEnemy_.translation_.z);

		if (bx<1&&bz<1) {
			EnemyFlag = 0;
			BeamFlag = 0;
			gamescore_ += 10;
		}
	}


}

