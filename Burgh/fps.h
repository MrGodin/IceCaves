
#pragma once

class Fps
{
protected:
	float numFrames = 0.0f;
	float timeElapsed = 0.0f;
	float mfps = 0.0f;
	float mMilliSecPerFrame = 0.0f;
public:
	Fps(){}
	float Update(float dt)
	{


		numFrames += 1.0f;


		timeElapsed += dt;


		if (timeElapsed >= 1.0f)
		{

			mfps = numFrames;
			mMilliSecPerFrame = 1000.0f / mfps;
			timeElapsed = 0.0f;
			numFrames = 0.0f;
		}
		return mfps;
	}
};