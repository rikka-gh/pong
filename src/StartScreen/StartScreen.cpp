#include "StartScreen.h"
#include "Game/game.h"
#include "CourtScene/CourtScene.h"

#include "SDL.h"

StartScreen::StartScreen(Game& game) : mGame(game), mTopicTexture(nullptr), mVeryMotivationalText(nullptr), mLeftPlayerKeybinds(nullptr), mVeryMotivationalTextLine2(nullptr), mVeryMotivationalTextLine3(nullptr), mVeryMotivationalTextLine4(nullptr), mContinueInstructions(nullptr)
{
	mTopicTexture = mGame.createLargeText("PONG");
	mLeftPlayerKeybinds = mGame.createText("Use W and S to control your Paddle (Left)");
	mContinueInstructions = mGame.createText("Press space to start");

}

StartScreen::~StartScreen()
{
	SDL_DestroyTexture(mTopicTexture);
	SDL_DestroyTexture(mLeftPlayerKeybinds);
	SDL_DestroyTexture(mContinueInstructions);

}

void StartScreen::onDraw(SDL_Renderer& renderer)
{
	SDL_Rect rect{ 0, 100, 0, 0 };
	SDL_QueryTexture(mTopicTexture, nullptr, nullptr, &rect.w, &rect.h);
	rect.x = (500 - (rect.w / 2));
	SDL_RenderCopy(&renderer, mTopicTexture, nullptr, &rect);

	SDL_QueryTexture(mLeftPlayerKeybinds, nullptr, nullptr, &rect.w, &rect.h);
	rect.x = (500 - (rect.w / 2));
	rect.y = 200;
	SDL_RenderCopy(&renderer, mLeftPlayerKeybinds, nullptr, &rect);

	SDL_QueryTexture(mContinueInstructions, nullptr, nullptr, &rect.w, &rect.h);
	rect.x = (500 - (rect.w / 2));
	rect.y = 400;
	SDL_RenderCopy(&renderer, mContinueInstructions, nullptr, &rect);

	
}

void StartScreen::onUpdate() {

}
void StartScreen::onEnter() {

}
void StartScreen::onExit() {

}
void StartScreen::onKeyDown(SDL_KeyboardEvent& event) {

}


void StartScreen::onKeyUp(SDL_KeyboardEvent& event)
{
	switch (event.keysym.sym)
	{
	case SDLK_SPACE:
		mGame.setScene(std::make_shared<CourtScene>(mGame));
		break;
	}
}
