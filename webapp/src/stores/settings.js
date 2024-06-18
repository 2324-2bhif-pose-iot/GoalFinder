import {defineStore} from "pinia";
import {ref} from "vue";

export const useSettingsStore = defineStore("settings", () => {
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

    const macAddress = "";
    const bluetoothAddress = "";

    const refreshAvailableNetworks = () => {

    }

    const refreshAvailableBluetoothDevices = () => {

    }

    const loadSettings = () => {
        var xmlHttp = new XMLHttpRequest();
        xmlHttp.open( "GET", "/loadsettings", false ); // false for synchronous request
        xmlHttp.send( null );
        console.log("Sended");
        console.log(xmlHttp.responseText);
    }

    const saveSettings = () => {
        //TODO
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
        bluetoothAddress,
        refreshAvailableNetworks,
        refreshAvailableBluetoothDevices,
        loadSettings,
        saveSettings
    };
})