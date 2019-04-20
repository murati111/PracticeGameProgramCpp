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
	//�A�N�^�[�̏�ԊǗ��p
	enum State
	{
		EActive,
		EPaused,
		EDead
	};
	//�R���X�g���N�^�[�ƃf�X�g���N�^�[
	Actor(class Game* game);
	virtual ~Actor();
	//�Q�[������Ăяo�����X�V�֐��i�I�[�o���C�h�s�j
	void UpdateComponents(float deltaTime);
	//�A�N�^�[�Ǝ��̍X�V�����i�I�[�o���C�h�\�j
	virtual void UpdateActor(float deltaTime);

	//�Q�b�^�[/�Z�b�^�[
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }
	//�R���|�[�l���g�̒ǉ�/�폜
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	//�A�N�^�[�̏��
	State mState;
	//���W�ϊ�
	Vector2 mPosition; //�A�N�^�[�̒��S�ʒu
	float mScale; //�A�N�^�[�̃X�P�[���i1.0f��100%�j
	float mRotation; //��]�̊p�x�i���W�A���j

	//�A�N�^�[�����R���|�[�l���g
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
