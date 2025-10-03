import {defineStore} from "pinia";
import {ref} from "vue";

const API_URL = "/api"

export const useSettingsStore = defineStore("settings", () => {
    let isValid = false;
    const enableDarkMode = ref(false);
    const isSoundEnabled = ref(false);

    //General
    const deviceName = ref("");
    const devicePassword = ref("");

    //Devices
    const ledMode = ref(0);
    const isBluetoothEnabled = ref(false);
    const connectedBluetoothDevices = ref([]);
    const availableBluetoothDevices = ref([]);
    
    const vibrationSensorSensitivity = ref(0);

    const isWifiEnabled = ref(false);
    const connectedNetwork = ref("");
    const availableNetworks = ref([]);

    //Audio
    const volume = ref(0);
    const hitSound = ref(0);
    const missSound = ref(0);

    //System
    const macAddress = ref("");
    const version = ref("");

    const refreshAvailableNetworks = () => {

    }

    const refreshAvailableBluetoothDevices = () => {

    }

    async function getSettings(): Promise<void> {
        try {
            const response = await fetch(`${API_URL}/settings`, {method: "GET"});

            if(response.ok) {
                const json = await response.json();

                deviceName.value = json["deviceName"];
                devicePassword.value = json["devicePassword"];
                volume.value = json["volume"];
                ledMode.value = json["ledMode"];
                macAddress.value = json["macAddress"];
                isSoundEnabled.value = json["isSoundEnabled"];
                version.value = json["version"];
                hitSound.value = json["hitSound"];
                missSound.value = json["missSound"];
            }

        } catch (error) {
            console.error(error);
        }
    }

    async function saveSettings(): Promise<void> {
        try {
            await fetch(`${API_URL}/settings`, {
                method: "POST",
                body: JSON.stringify(useSettingsStore().$state),
            });
        } catch (error) {
            console.error(error);
        }
    }

    async function restartDevice() : Promise<void> {
        try {
            await fetch(`${API_URL}/restart`, {method: "POST"});
        } catch (error) {
            console.error(error);
        }
    }

    async function updateFirmware(firmwareFile: File): Promise<boolean> {
        const data = new FormData();
        data.append('file', firmwareFile);

        const response = await fetch(`${API_URL}/update`, { method: 'POST', body: data });

        return response.ok;
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
        isSoundEnabled,
        version,
        updateFirmware
    };
})