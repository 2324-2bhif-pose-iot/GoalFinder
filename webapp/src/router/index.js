import { createRouter, createWebHistory } from 'vue-router'
import Login from "@/views/LoginView.vue";
import Home from "@/views/HomeView.vue";
import About from "@/views/AboutView.vue";
import Configuration from "@/views/Settings/SettingsView.vue";
import NotFound from "@/views/NotFoundView.vue";
import ConfigGeneral from "@/views/Settings/GeneralSettingsView.vue";
import ConfigDevices from "@/views/Settings/DeviceSettingsView.vue";
import ConfigAudio from "@/views/Settings/AudioSettingsView.vue";
import ConfigSystem from "@/views/Settings/SystemSettingsView.vue";
import ConfigConnectivity from "@/views/Settings/ConnectivitySettingsView.vue";
import Games from "@/views/GamesView.vue";
import ListView from "@/views/ListView.vue";

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      name: "Home",
      component: Home,
      path: "/"
    },
    {
      name: "Settings",
      component: Configuration,
      path: "/settings",
      redirect: "/settings/general",
      children: [
        {
          component: ConfigGeneral,
          path: "general"
        },
        {
          component: ConfigConnectivity,
          path: "connectivity"
        },
        {
          component: ConfigDevices,
          path: "devices"
        },
        {
          component: ConfigAudio,
          path: "audio"
        },
        {
          component: ConfigSystem,
          path: "system"
        },
      ]
    },
    {
      name: "Login",
      component: Login,
      path: "/login"
    },
    {
      name: "About",
      component: About,
      path: "/about"
    },
    // catchall 404
    {
      name: "NotFound",
      component: NotFound,
      path: "/:catchAll(.*)"
    },
    /*{
      name: "Games",
      component: Games,
      path: "/games"
    },*/
    {
      name: "List",
      component: ListView,
      path: "/list"
    }
  ]
})

export default router
