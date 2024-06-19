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
#include <Settings.h>
#include <system/Settings.h>

class GoalfinderApp : public Singleton<GoalfinderApp> {
	public:
		/** Destructor */
		virtual ~GoalfinderApp();

		/** Initializes the application. */
		void Init();

		/** Processes one single iteration step. */
		void Process();

		void OnSettingsUpdated();
	private:
		friend class Singleton<GoalfinderApp> ;
		/** Singleton constructor */
		GoalfinderApp();
		
		static const int pinTofSda;
		static const int pinTofScl;
		static const int pinI2sBclk;
		static const int pinI2sWclk;
		static const int pinI2sDataOut;
		static const int pinLedPwm;

		static const int ledPwmFrequency;
		static const int ledPwmChannel;
		static const int ledPwmResolution;

		static const char* defaultSsid;
		static const char* defaultWifiPw; // no PW
		static const int defaultAudioVolume;

		Settings settings;
		System::Settings settingStore;
		FileSystem fileSystem;
		WebServer webServer;
		SNTP sntp;
		AudioPlayer* audioPlayer;
		ToFSensor tofSensor;
		VibrationSensor vibrationSensor;
		LedController ledController;
};