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

#include "Settings.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "WiFi.h"
#include <math.h>

const char* Settings::keyVolume = "volume";
const int Settings::defaultVolume = 50;
    const String Settings::deviceName = "Goalfinder";
    const String Settings::devicePassword = "ESP3232";
    const int Settings::vibrationSensorSensitivity = 100;
    const int Settings::volume = 100;
    const String Settings::macAddress = "00-1D-60-4A-8C-CB";
	
Settings::Settings() :
    Singleton<Settings>(),
	store(),
	modified(false)
{
    store.Begin("app_prefs");
}

 Settings::~Settings() {
 }

String Settings::GetMacAddress() {
	return String(WiFi.macAddress());
}

int Settings::GetVolume() {
	return store.GetInt(keyVolume, defaultVolume);
}

void Settings::SetVolume(int volume) {
	volume = max(min(volume, 100), 0);
	store.PutInt(keyVolume, volume);
	SetModified();
}

bool Settings::IsModified() const {
	return modified;
}

void Settings::SetModified() {
	modified = true;
}

void Settings::ClearModifiedState() {
	modified = false;
}


String Settings::GetDeviceName()
{

};

void Settings::SetDeviceName(String deviceName)
{

};

String GetDevicePassword()
{

};

void SetDevicePassword(String devicePassword)
{

};

int GetVibrationSensorSensitivity()
{

};

void SetVibrationSensorSensitivity(int vibrationSensorSensitivity)
{

};