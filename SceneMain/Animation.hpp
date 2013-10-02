#ifndef ANIMATION_HPP
#define ANIMATION_HPP
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

		Animation();
		Animation(std::string filename);

		bool loadFromFile(std::string filename);
		bool saveToFile(std::string filename);

		std::set<std::string> getContentFilename();
		void getContentFilename(std::set<std::string>& contentFilename);

	private:
		bool readAnim (
				std::string& currentAnimName,
				AnimationTrack*& currentAnimTrack,
				std::string& line, int lineNum);

		bool readFrame (AnimationTrack*& currentAnimTrack,
				std::string& line);
};

class AnimationPlayer
{
	public:
		AnimationPlayer();
		AnimationPlayer(Animation *data);

		virtual void update(float deltaTime);

		int getAnimID(std::string name);
		int getLoopsLeft() const;
		bool setAnimData(Animation* data);
		bool selectAnim(std::string name);
		bool selectAnim(int animID);

		vec4i getCurrentFrame() const;

	private:
		Animation* data;
		int animSelected;
		int loopsLeft;
		int frameSelected;
		float frameTimeLeft;

		void nextFrame();
};

#endif // ANIMATION_HPP

