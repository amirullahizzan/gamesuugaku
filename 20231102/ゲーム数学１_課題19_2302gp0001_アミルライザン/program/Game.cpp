#include "Main.h"
#include "Game.h"
#include "Random.h"

//	ＮＰＣの数
#define	NPC_MAX	10

//	モデルデータを読み込んだ時にもらえる番号を入れる用の変数
int ground_model;	//	地面モデル
int player_model;	//	プレイヤーモデル
int npc_model;		//	ＮＰＣモデル

//	プレイヤー座標変数
float player_x;
float player_y;
float player_z;
int player_rota = 0;

//	ＮＰＣの座標変数
#define MAX_ENEMY 10
float npc_x[MAX_ENEMY];
float npc_y[MAX_ENEMY];
float npc_z[MAX_ENEMY];

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	モデルデータを読み込んで番号を取得
	ground_model = MV1LoadModel( "data/ground.mqoz" );	//	地面モデル
	player_model = MV1LoadModel( "data/player.mqoz" );	//	地面モデル
	npc_model = MV1LoadModel( "data/npc.mqoz" );	//	地面モデル

	//	プレイヤー初期座標の設定
	player_x = 0.0f;
	player_y = 0.0f;
	player_z = 0.0f;

	//	ＮＰＣの初期座標の設定（地面の四角１マス分奥）
	for (int i = 0 ;i < MAX_ENEMY;i++)
	{
	npc_x[i] = GetRandomF(-10.0f, 10.0f);
	npc_y[i] = 0.0f;
	npc_z[i] = GetRandomF(-10.0f, 10.0f);
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	十字キーでプレイヤーの座標移動
	//	右キーで右移動（カメラから見た右に移動）
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_x += 0.2f;
		player_rota = 90;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_x -= 0.2f;
		player_rota = -90;
	}
	//	上キーで移動（画面の奥に進ませたい）
	if( CheckHitKey( KEY_INPUT_UP ) ){
		player_z += 0.2f;
		player_rota = 0;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		player_z -= 0.2f;
		player_rota = -180;
	}

	for (int i = 0; i < MAX_ENEMY; i++)
	{
	npc_z[i] -= 0.1f;
	//	原点から１マス分手前に来たら
	if( npc_z[i] < -10.0f ){
		//	Ｘ座標を -10.0f ～ 10.0f のランダムな値に
		npc_x[i] = GetRandomF( -10.0f, 10.0f );
		//	Ｚ座標は原点から１マス分奥に
		npc_z[i] = GetRandomF(-10.0f, 10.0f);
	}
	}
	//	ＮＰＣの座標移動（画面手前に移動）

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	カメラの設定（カメラ座標（カメラをどこに置くか）と見る座標（そのカメラがどこを見るか）を渡して設定する）
	SetCameraPositionAndTarget_UpVecY( VGet( 0.0f, 10.0f, -20.0f ), VGet( 0.0f, 0.0f, 0.0f ) );

	//	モデルの描画一式
	//	モデルの座標設定
	MV1SetPosition( ground_model, VGet( 0.0f, 0.0f, 0.0f ) );
	//	モデルの向き設定
	MV1SetRotationXYZ( ground_model, VGet( TO_RADIAN( 0.0f ), TO_RADIAN( 0.0f ), TO_RADIAN( 0.0f ) ) );
	//	その設定された座標と向きでモデルの描画
	MV1DrawModel( ground_model );

	//	ＮＰＣモデルの描画
	for (int i = 0; i < MAX_ENEMY; i++)
	{
	MV1SetPosition( npc_model, VGet( npc_x[i], npc_y[i], npc_z[i]) );
	MV1SetRotationXYZ( npc_model, VGet( TO_RADIAN( 0.0f ), TO_RADIAN( 180.0f ), TO_RADIAN( 0.0f ) ) );
	MV1DrawModel( npc_model );
	}
	//	Ｙ軸に１８０度回転させて画面手前を向くようにします

	//	プレイヤーモデルの描画
	MV1SetPosition( player_model, VGet( player_x, player_y, player_z ) );
	MV1SetRotationXYZ( player_model, VGet( TO_RADIAN( 0.0f  ), TO_RADIAN( 0.0f + player_rota), TO_RADIAN( 0.0f ) ) );
	MV1DrawModel( player_model );

	DrawString( 16, 16, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "プレイヤー移動に合わせて向きも変更", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "ＮＰＣを複数に", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "→　初期座標：ＸＺ共に -10.0f ～ 10.0f", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	//	モデルデータの終了処理
	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
	MV1DeleteModel( npc_model );
}
