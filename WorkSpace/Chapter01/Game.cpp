// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include <iostream>
#include <windows.h>

const int thickness = 15;
const float paddleH = 100.0f;
std::random_device rnd;
std::mt19937 mt(rnd());
const int maxBallNum = 5;

Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
{
	for (int i = 0; i < 2; i++) mPaddleDir[i] = 0;
}

bool Game::Initialize()
{
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	//// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	for (int i = 0; i < 2; i++) {
		mPaddlePos[i].x = (i == 0) ? 10.0f : 1024.0f - 20.0f;
		mPaddlePos[i].y = 768.0f / 2.0f;
	}
	mBall.emplace_back();
	mBall[0].pos.x = 1024.0f / 2.0f;
	mBall[0].pos.y = 768.0f / 2.0f;
	mBall[0].vel.x = -2.0f;
	mBall[0].vel.y = 2.0f;
	mBallInitialPos = mBall[0].pos;
	mBallInitialVel = mBall[0].vel;
	NumBall = 1;

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE])
		{
			mIsRunning = false;
		}
		mPaddleDir[0] = 0;
		if (state[SDL_SCANCODE_W])
		{
			mPaddleDir[0] -= 1;

		}
		if (state[SDL_SCANCODE_S])
		{
			mPaddleDir[0] += 1;
		}
		mPaddleDir[1] = 0;
		if (state[SDL_SCANCODE_I])
		{
			mPaddleDir[1] -= 1;
		}
		if (state[SDL_SCANCODE_K])
		{
			mPaddleDir[1] += 1;
		}


	}
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	//時刻を更新
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();
	for (int i = 0; i < 2; i++)
	{
		if (mPaddleDir[i] != 0)
		{
			mPaddlePos[i].y += mPaddleDir[i] * 600.0f * deltaTime;

			if (mPaddlePos[i].y < (paddleH / 2.0f + thickness))
			{
				mPaddlePos[i].y = paddleH / 2.0f + thickness;
			}
			else if (mPaddlePos[i].y > 768.0f - paddleH / 2.0f - thickness)
			{
				mPaddlePos[i].y = 768.0f - paddleH / 2.0f - thickness;
			}
		}
	}

	int count = 0;
	for (Ball& b : mBall) {
		b.pos.x += b.vel.x * 100 * deltaTime;
		b.pos.y += b.vel.y * 100 * deltaTime;
		if (b.pos.y <= thickness && b.vel.y < 0.0f)
		{
			b.vel.y *= -1;
		}
		else if (b.pos.y >= (768.0f - thickness) && b.vel.y > 0.0f)
		{
			b.vel.y *= -1;
		}
		float diff[2];
		if (b.vel.x < 0)
		{
			int i = 0;
			diff[i] = b.pos.y - mPaddlePos[i].y;
			diff[i] = (diff[i] > 0.0f) ? diff[i] : -diff[i];
			if (diff[i] <= paddleH / 2.0f &&
				b.pos.x <= 25.0f && b.pos.x >= 20.0f &&
				b.vel.x < 0.0f)
			{
				b.vel.x *= -1.0f;
				if (NumBall <= maxBallNum) {
					Ball IniBall = {
					b.pos,
					{b.vel.x * GetRandom(0.7f, 1.5f), GetRandom(1.0f, 5.0f)}
					};
					mBall.push_back(IniBall);
					GenerateBall(mBall[mBall.size() - 1], IniBall.pos, IniBall.vel);
					NumBall++;
					b.pos = IniBall.pos; //push_backしたら座標がバグるのでそれを強制的に戻す
				}
				//mBall[0].vel.x *= 1.2;
				//mBall[0].vel.y *= 1.2;
			}
		}
		else
		{
			int i = 1;
			diff[i] = b.pos.y - mPaddlePos[i].y;
			diff[i] = (diff[i] > 0.0f) ? diff[i] : -diff[i];
			if (diff[i] <= paddleH / 2.0f &&
				b.pos.x <= 1024.0f - 20.0f && b.pos.x >= 1024.0f - 25.0f &&
				b.vel.x > 0.0f)
			{
				b.vel.x *= -1.0f;
				if (NumBall <= maxBallNum) {
					Ball IniBall = {
					b.pos,
					{b.vel.x * GetRandom(0.7f, 1.5f), GetRandom(1.0f, 5.0f)}
					};
					mBall.push_back(IniBall);
					GenerateBall(mBall[mBall.size() - 1], IniBall.pos, IniBall.vel);
					NumBall++;
					b.pos = IniBall.pos; //push_backしたら座標がバグるのでそれを強制的に戻す
				}
				//mBall.emplace_back();
				//GenerateBall(mBall[mBall.size() - 1], b.pos, { b.vel.x, 4.0f});
				//NumBall++;
				//mBall[0].vel.x *= 1.2; //パドルに当たった時ボールが早くなる（未実装）
				//mBall[0].vel.y *= 1.2;
			}
		}
		//ボールが範囲外にいったときポイント加算
		if (b.pos.x < 0.0f)
		{
			Score[1]++;
			std::cout << Score[0] << "VS" << Score[1] << std::endl;
			NumBall--;
			if (mBall.size() > 0) /*vectorのメモリ領域を超えてしまわないように*/ {
				mBall.erase(mBall.begin() + count);
			}

			//Sleep(1 * 1000);
			//b.pos = mBallInitialPos;
			//b.vel = mBallInitialVel;
			/*SDL_DestroyRenderer(mRenderer);
			mRenderer = SDL_CreateRenderer(
				mWindow, // Window to create renderer for
				-1,		 // Usually -1
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
			);
			GenerateOutput();*/
		}
		//ボールが範囲外にいったときポイント加算
		else if (b.pos.x > 1024.0f)
		{
			Score[0]++;
			std::cout << Score[0] << "VS" << Score[1] << std::endl;
			NumBall--;
			if (mBall.size() > 0)/*vectorのメモリ領域を超えてしまわないように*/ {
				mBall.erase(mBall.begin() + count);
			}
		}

		if (NumBall <= 0) break;
		count++;
	}

	//ボールがなくなったら初期化
	if (NumBall <= 0)
	{
		//Result確認
		std::cout << std::endl << "Result:" << Score[0] << "VS" << Score[1] << std::endl;
		if (Score[0] > Score[1])
		{
			std::cout << "Player0 Win : Player1 Lose" << std::endl;
		}
		else if (Score[0] < Score[1])
		{
			std::cout << "Player0 Lose : Player1 Win" << std::endl;
		}
		else
		{
			std::cout << "Draw" << std::endl;
		}
		Sleep(2 * 1000);
		SDL_DestroyRenderer(mRenderer);
		mBall.emplace_back();
		mBall[0].pos = mBallInitialPos;
		mBall[0].vel = mBallInitialVel;
		NumBall = 1;
		for (int i = 0; i < 2; i++) Score[i] = 0;
		mRenderer = SDL_CreateRenderer(
			mWindow, // Window to create renderer for
			-1,		 // Usually -1
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		);
		GenerateOutput();
	}

}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_Rect wall{
		0,			//左上隅のx
		0,			//左上隅のy
		1024,		//幅
		thickness	//高さ
	};
	SDL_RenderFillRect(mRenderer, &wall);

	for (int i = 0; i < 2; i++) {
		SDL_Rect paddle{
			static_cast<int>(mPaddlePos[i].x),
			static_cast<int>(mPaddlePos[i].y - paddleH / 2),
			thickness,
			static_cast<int>(paddleH)
		};
		SDL_RenderFillRect(mRenderer, &paddle);
	}


	/*SDL_Rect ball{
	static_cast<int>(mBall[0].pos.x - thickness / 2),	//static_cast<int>はfloatからint整数に変換する
	static_cast<int>(mBall[0].pos.y - thickness / 2),
	thickness,
	thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);
	*/
	for (Ball& b : mBall)
	{
		GenerateBall(b, b.pos, b.vel);
	}
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::GenerateBall(Ball b, Vector2 pos, Vector2 vel)
{
	//b.pos = pos;
	//b.vel = vel;
	SDL_Rect ball{
		static_cast<int>(b.pos.x - thickness / 2),	//static_cast<int>はfloatからint整数に変換する
		static_cast<int>(b.pos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);
}

float Game::GetRandom(float min, float max)
{
	std::uniform_real_distribution<float> random(min, max);
	return random(mt);
}

