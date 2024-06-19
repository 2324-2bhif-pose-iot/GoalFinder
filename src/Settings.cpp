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
const int Settings::defaultVolume = 100;

const char* Settings::keyDeviceName = "deviceName";
const String Settings::defaultDeviceName = "Goalfinder";

const char* Settings::keyDevicePassword = "devicePassword";
const String Settings::defaultDevicePassword = emptyString;

const char* Settings::keyVibrationSensorSensitivity = "vibrationSensorSensitivity";
const int Settings::defaultVibrationSensorSensitivity = 100;
	
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
	return store.GetString(keyDeviceName, defaultDeviceName);
};

void Settings::SetDeviceName(String deviceName)
{
	if(deviceName.isEmpty())
	{
		deviceName = defaultDeviceName;
		store.Remove(keyDeviceName);
	}
	
	store.PutString(keyDeviceName, deviceName);
	SetModified(); 
};

String Settings::GetDevicePassword()
{
	return store.GetString(keyDevicePassword, defaultDevicePassword);
};

void Settings::SetDevicePassword(String devicePassword)
{
	if(devicePassword.isEmpty())
	{
		devicePassword = emptyString;
		store.Remove(keyDevicePassword);
	}

	store.PutString(keyDevicePassword, devicePassword);
	SetModified();
};

int Settings::GetVibrationSensorSensitivity()
{
	return store.GetInt(keyVibrationSensorSensitivity, defaultVibrationSensorSensitivity);
}

void Settings::SetVibrationSensorSensitivity(int vibrationSensorSensitivity)
{
	vibrationSensorSensitivity = max(min(vibrationSensorSensitivity, 100), 0);
	store.PutInt(keyVibrationSensorSensitivity, vibrationSensorSensitivity);
	SetModified();
};