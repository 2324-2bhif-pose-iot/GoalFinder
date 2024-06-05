import {defineStore} from "pinia";
import {ref} from "vue";

export const useSettingsStore = defineStore("settings", () => {
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

    const macAddress = "";
    const bluetoothAddress = "";

    const refreshAvailableNetworks = () => {

    }

    const refreshAvailableBluetoothDevices = () => {

    }

    const loadSettings = () => {
        //TODO
    }

    const saveSettings = () => {
        //TODO
    }

    return {
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
        bluetoothAddress,
        refreshAvailableNetworks,
        refreshAvailableBluetoothDevices,
        loadSettings,
        saveSettings
    };
})