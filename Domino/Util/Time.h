#ifndef __TIME_H__
#define __TIME_H__

namespace Domino {
	class Time {
	public:
		static const int STATISTICS_PERIOD_TIME = 1;
		static float deltaTime;
		static float time;
		static float fps;

		static void update(int thisTime) {
			static int lastTime = 0;
			static int lastStatTime = 0;
			deltaTime = (float)(thisTime - lastTime)/1000.0f;
			time = thisTime/1000.0f;
			lastTime = thisTime;

			if (thisTime - lastStatTime >= STATISTICS_PERIOD_TIME * 1000.0f) {
				caltStatInfo(thisTime - lastStatTime);
				lastStatTime = thisTime;
			}
			else {
				updateStatInfo();
			}
		}

	private:

		static void caltStatInfo(int timeDelta) {
			fps = fpsCounter * 1000.0f / timeDelta;
		}

		static void updateStatInfo() {
			fpsCounter++;
		}

		static int fpsCounter;
	};
}

#endif