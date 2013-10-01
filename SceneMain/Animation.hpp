#ifndef ANIMATION_H
#define ANIMATION_H
#include "Commons.hpp"

struct AnimationFrame {
		vec4i rect;
		float time; //Seconds
};

struct AnimationTrack {
		short numOfLoops; //0 = Infinite
		std::string spritesheetFilename;
		std::vector<AnimationFrame> frames;
};

class Animation {
	public:
		std::vector<AnimationTrack> animations;
		std::map<std::string, int> animNames; //Name -> Vector pos

		bool Load(std::string filename);
		bool Save(const char* filename);

		std::set<std::string> getContentFilename();
		void getContentFilename(std::set<std::string>& contentFilename);

	private:
		bool ReadANIM (
				std::string& currentAnimName,
				AnimationTrack*& currentAnimTrack,
				std::string& line, int lineNum);

		bool ReadFRAME (
				AnimationTrack*& currentAnimTrack,
				std::string& line, int lineNum);
};

class AnimationPlayer
{
	public:
		AnimationPlayer();
		AnimationPlayer(Animation *data);

		virtual void Update(float GameTime);

		int getAnimID(std::string name);
		int getLoopsLeft() const;
		bool setAnimData(Animation* data);
		bool SelectAnim(std::string name);
		bool SelectAnim(int animID);

		vec4i getCurrentFrame() const;

	private:
		Animation* data;
		int animSelected;
		int loopsLeft;
		int frameSelected;
		float frameTimeLeft;

		void NextFrame();
};

#endif // ANIMATION_H

