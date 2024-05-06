import { createApp } from 'vue';
import {createPinia} from "pinia";
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

app.use(PrimeVue, { ripple: true });

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
