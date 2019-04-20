// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include "Math.h"
class Actor
{
public:
	//アクターの状態管理用
	enum State
	{
		EActive,
		EPaused,
		EDead
	};
	//コンストラクターとデストラクター
	Actor(class Game* game);
	virtual ~Actor();
	//ゲームから呼び出される更新関数（オーバライド不可）
	void UpdateComponents(float deltaTime);
	//アクター独自の更新処理（オーバライド可能）
	virtual void UpdateActor(float deltaTime);

	//ゲッター/セッター
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }
	//コンポーネントの追加/削除
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	//アクターの状態
	State mState;
	//座標変換
	Vector2 mPosition; //アクターの中心位置
	float mScale; //アクターのスケール（1.0fが100%）
	float mRotation; //回転の角度（ラジアン）

	//アクターが持つコンポーネント
	std::vector<class Component*> mComponents;
	class Game* mGame;
/*public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// Getters/setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }


	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	// Actor's state
	State mState;

	// Transform
	Vector2 mPosition;
	float mScale;
	float mRotation;

	std::vector<class Component*> mComponents;
	class Game* mGame;
	*/
};
