import { createApp } from 'vue';
import {createPinia} from "pinia";
import {createI18n} from "vue-i18n"
import App from './App.vue';
import router from './router';
import PrimeVue from 'primevue/config';
import 'bootstrap/dist/css/bootstrap-grid.css'
import './assets/main.css'
import Button from "primevue/button";
import Menubar from "primevue/menubar";
import Card from "primevue/card";
import Menu from "primevue/menu";
import Switch from "primevue/inputswitch"
import Listbox from "primevue/listbox";
import InputText from 'primevue/inputtext';
import Password from 'primevue/password';
import Panel from 'primevue/panel';
import Slider from 'primevue/slider';
import InputNumber from 'primevue/inputnumber';
import DataView from "primevue/dataview";
import Dropdown from 'primevue/dropdown';
import ToggleButton from "primevue/togglebutton";

const app= createApp(App);
app.use(router);

const pinia = createPinia();
app.use(pinia);

const i18n = createI18n({
    locale: "de",
    fallbackLocale: "en",
    messages: {
        en: {
            header: {
                dashboard: "Goal Finder Dashboard",
                home: "Home",
                games: "Games",
                sessions: "Sessions",
                settings: "Settings",
                about: "About",
                game_card: "Create new game",
                settings_card: "Configure device",
                sessions_card: "Create new session"
            },
            description: {
                settings_description: "Configure the device settings like sounds and devices.",
                sessions_description: "Add and remove persons into a basketball shot tracker",
                device_name_description: "Enter a name for the device.",
                device_password_description: "Enter a password for the device."
            },
            settings: {
                settings: "Settings",
                general: "General",
                wifi: "WiFi",
                devices: "Devices",
                audio: "Audio",
                system: "System",
                device_name: "Device name",
                device_password: "Device password"
            },
            word : {
                save: "Save",
                open: "Open",
                volume: "Volume",
                refresh: "Refresh",
                sensitivity: "Sensitivity",
                restart: "Restart",
                factory_settings_reset: "Reset to factory settings",
                search_for_update: "Search for update",
                light: "Light",
                dark: "Dark",
                add_person: "Add Person",
                basketball_shot_tracker: "Basketball Shot Tracker",
                hit: "Hit",
                miss: "Miss",
                remove: "Remove",
                person_list: "Person List",
                results: "Results",
                hits: "Hits",
                misses: "Misses",
                led_mode: "LED Mode",
                standard: "Standard",
                fade: "Fade",
                flash: "Flash",
                turbo: "Turbo",
                curr_mode: "Current Mode",
                curr_volume: "Current Volume",
                mac_address: "Mac address",
                bluetooth_address: "Bluetooth address",
                software_update: "Software Update",
                curr_version: "Current Version",
                finish: "Finish",
                leaderboard: "Leaderboard"
            }
        },
        de : {
            header: {
                dashboard: "Goal Finder Dashboard",
                home: "Startseite",
                games: "Spiele",
                sessions: "Sitzungen",
                settings: "Einstellungen",
                about: "Über uns",
                game_card: "Neues Spiel erstellen",
                settings_card: "Einstellungen",
                sessions_card: "Neue Sitzung erstellen"
            },
            description: {
                settings_description: "Einstellungen für das Gerät vornehmen",
                sessions_description: "Eine neue Sitzung erstellen",
                device_name_description: "Einen neuen Namen für dieses Gerät eingeben.",
                device_password_description: "Ein neues Passwort für dieses Gerät eingeben."
            },
            settings: {
                settings: "Einstellungen",
                general: "Allgemein",
                wifi: "WLAN",
                devices: "Geräte",
                audio: "Audio",
                system: "System"
            },
            word : {
                save: "Speichern",
                open: "Öffnen",
                volume: "Lautstärke",
                refresh: "Aktualisieren",
                sensitivity: "Empfindlichkeit",
                device_name: "Gerätename",
                device_password: "Passwort",
                restart: "Neustarten",
                factory_settings_reset: "Auf Werkseinstellungen zurücksetzen",
                search_for_update: "Auf Aktualisierungen prüfen",
                light: "Hell",
                dark: "Dunkel",
                add_person: "Person Hinzufügen",
                basketball_shot_tracker: "Basketball Schusszähler",
                hit: "Treffer",
                miss: "Fehlschuss",
                remove: "Entfernen",
                person_list: "Liste der Personen",
                results: "Ergebnisse",
                hits: "Treffer",
                misses: "Fehlschüsse",
                led_mode:"LED Modus",
                standard: "Standart",
                fade: "Verblassen",
                flash: "Blitzartig",
                turbo: "Turbo",
                curr_mode: "Ausgewählter Modus",
                curr_volume: "Derzeitige Lautstärke",
                mac_address: "Mac Adresse",
                bluetooth_address: "Bluetooth Adresse",
                software_update: "Software Aktualisierung",
                curr_version: "Derzeitige Version",
                finish: "Beenden",
                leaderboard: "Rangliste"
            }
        }
    }
});

app.use(PrimeVue, { ripple: true });
app.use(i18n);

export {i18n};

//PrimeVue components
app.component('Menubar', Menubar);
app.component('Button', Button);
app.component("Card", Card);
app.component("Menu", Menu);
app.component("InputSwitch", Switch);
app.component("Listbox", Listbox);
app.component("InputText", InputText);
app.component("Password", Password);
app.component("Panel", Panel);
app.component("Slider", Slider);
app.component("InputNumber", InputNumber);
app.component("DataView", DataView);
app.component("Dropdown", Dropdown);
app.component("ToggleButton", ToggleButton);

app.mount('#app');
