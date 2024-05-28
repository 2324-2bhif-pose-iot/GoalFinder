import { createApp } from 'vue';
import {createPinia} from "pinia";
import {createI18n} from "vue-i18n"
import App from './App.vue';
import router from './router';
import 'primevue/resources/themes/aura-light-green/theme.css'
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
                sessions_description: "Add and remove persons into a basketball shot tracker"
            },
            settings: {
                settings: "settings",
                general: "General",
                wifi: "WiFi",
                devices: "Devices",
                audio: "Audio",
                system: "System"
            },
            word : {
              save: "Save",
              open: "Open",
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
                sessions_description: "Add and remove persons into a basketball shot tracker"
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
                open: "Öffnen"
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

app.mount('#app');
