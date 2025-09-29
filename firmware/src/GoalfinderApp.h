/*
 * ===============================================================================
 * (c) HTL Leonding
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * Licensed under MIT License.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the license.
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * All trademarks used in this document are property of their respective owners.
 * ===============================================================================
 */

#pragma once

#include <Singleton.h>
#include <ToFSensor.h>
#include <VibrationSensor.h>
#include <BluetoothManager.h>
#include <web/WebServer.h>
#include <web/SNTP.h>
#include <FileSystem.h>
#include <AudioPlayer.h>
#include <LedController.h>

class GoalfinderApp : public Singleton<GoalfinderApp> {
	public:
		void SetIsSoundEnabled(bool value);
		bool IsSoundEnabled();

		bool GetIsClient();

		int GetDetectedHits();
		int GetDetectedMisses();

		void ResetDetectedHits();
		void ResetDetectedMisses();

		/** Destructor */
		virtual ~GoalfinderApp();

		/** Initializes the application. */
		void Init();

		/** Processes one single iteration step. */
		void Process();

	private:
		/** The enumeration of announcements */
		struct Announcement {
				typedef enum {
					/** no announcement to make */
					None,
					/** Shot with with unknown result */
					Shot,
					/** Hit to announce */
					Hit,
					/** Miss to announce. */
					Miss,
				} Enum;
		};

		friend class Singleton<GoalfinderApp>;
		/** Singleton constructor */
		GoalfinderApp();

		void InitAP();
		void TickMetronome();
		void DetectShot();
		void OnShotDetected() ;
		void AnnounceHit() ;
		void AnnounceMiss();
		void ProcessAnnouncement();
		void AnnounceEvent(const char* traceMsg, const char* sound);
		void PlaySound(const char* soundFileName);

		void UpdateSettings(bool force = false);

		static const int wifiTimeout;
		
		static const int pinTofSda;
		static const int pinTofScl;
		static const int pinI2sBclk;
		static const int pinI2sWclk;
		static const int pinI2sDataOut;
		static const int pinLedPwm;
		static const int pinRandomSeed;

		static const int ledPwmChannel;
		
		//static const int ballHitDetectionDistance;
		static const int shotVibrationThreshold;
		static const int maxShotDurationMs;

		static const char* waitingClip;
		static const char* hitClips[];
		static const int   hitClipsCnt;
		static const char* tickClips[];
		static const int   tickClipsCnt;
		static const char* missClips[];
		static const int   missClipsCnt;

		FileSystem fileSystem;
		WebServer webServer;
		SNTP sntp;
		AudioPlayer audioPlayer;
		ToFSensor tofSensor;
		VibrationSensor vibrationSensor;
		LedController ledController;

		int detectedHits = 0;
		int detectedMisses = 0;

		bool isSoundEnabled = false;
		bool isClient = false; // Is connected to GoalFinderHub?

		bool announcing;
		unsigned long lastMetronomeTickTime;
		unsigned long metronomeIntervalMs;
		unsigned long lastShockTime;
		Announcement::Enum announcement;
};