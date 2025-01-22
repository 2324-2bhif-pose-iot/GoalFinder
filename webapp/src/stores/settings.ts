import {defineStore} from "pinia";
import {ref} from "vue";

export const useSettingsStore = defineStore("settings", () => {
    let isValid = false;
    const enableDarkMode = ref(false);

    const deviceName = ref("");
    const devicePassword = ref("");

    const isBluetoothEnabled = ref(false);
    const connectedBluetoothDevices = ref([]);
    const availableBluetoothDevices = ref([]);
    
    const vibrationSensorSensitivity = ref(0);

    const isWifiEnabled = ref(false);
    const connectedNetwork = ref("");
    const availableNetworks = ref([]);

    const volume = ref(0);

    const macAddress = ref("");
    const ledMode = ref(0);

    const isMuted = ref(false);

    const refreshAvailableNetworks = () => {

    }

    const refreshAvailableBluetoothDevices = () => {

    }

    async function getSettings() {
        try {
            const response = await fetch("/loadsettings");

            if(response.ok) {
                const json = await response.json();

                deviceName.value = json["deviceName"];
                devicePassword.value = json["devicePassword"];
                volume.value = json["volume"];
                ledMode.value = json["ledMode"];
                macAddress.value = json["macAddress"];
            }

        } catch (error) {
            console.error(error);
        }
    }

    const loadSettings = () => {
        let xmlHttp = new XMLHttpRequest();
        xmlHttp.open( "GET", "/loadsettings", false); // false for synchronous request
        xmlHttp.send(null);

        try {
            const settings = JSON.parse(xmlHttp.responseText);

            deviceName.value = settings["deviceName"];
            devicePassword.value = settings["devicePassword"];
            volume.value = settings["volume"];
            ledMode.value = settings["ledMode"];
            macAddress.value = settings["macAddress"];
        } catch (error) {
            console.error(error);
        }
    }

    async function saveSettings() {
        /*let xmlHttp = new XMLHttpRequest();
        xmlHttp.open( "POST", "/savesettings", false);
        xmlHttp.send(JSON.stringify(useSettingsStore().$state));*/
        console.log("Saving settings");
        try {
            const response = await fetch("/savesettings", {
                method: "POST",
                body: JSON.stringify(useSettingsStore().$state),
            });
        } catch (error) {
            console.error(error);
        }
    }

    const restartDevice = () => {
        let xmlHttp = new XMLHttpRequest();
        xmlHttp.open( "POST", "/restart", false);
        xmlHttp.send(null);
    }

    return {
        enableDarkMode,
        deviceName,
        devicePassword,
        isBluetoothEnabled,
        connectedBluetoothDevices,
        availableBluetoothDevices,
        vibrationSensorSensitivity,
        isWifiEnabled,
        connectedNetwork,
        availableNetworks,
        volume,
        macAddress,
        refreshAvailableNetworks,
        refreshAvailableBluetoothDevices,
        getSettings,
        saveSettings,
        restartDevice,
        ledMode,
        isValid,
        isMuted
    };
})