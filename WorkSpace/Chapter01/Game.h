// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"
#include <vector>
#include <random>

// Vector2 struct just stores x/y coordinates
// (for now)
struct Vector2
{
	float x;
	float y;
};

struct Ball
{
	Vector2 pos;
	Vector2 vel;
};

// Game class
class Game
{
public:
	Game();
	// Initialize the game
	bool Initialize();
	// Runs the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();
private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void GenerateBall(Ball b, Vector2 pos, Vector2 vel);
	float GetRandom(float min, float max);

	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer;
	// Number of ticks since start of game
	Uint32 mTicksCount;
	// Game should continue to run
	bool mIsRunning;

	// Pong specific
	// Direction of paddle
	int mPaddleDir[2];
	// Position of paddle
	Vector2 mPaddlePos[2];
	// Position of ball
	Vector2 mBallPos;
	Vector2 mBallInitialPos;
	// Velocity of ball
	Vector2 mBallVel;
	Vector2 mBallInitialVel;
	std::vector < Ball > mBall;
	int Score[2];
	int NumBall;
};
