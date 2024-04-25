import { createRouter, createWebHistory } from 'vue-router'
import Login from "@/views/Login.vue";
import Home from "@/views/Home.vue";
import About from "@/views/About.vue";
import Configuration from "@/views/Settings/Settings.vue";
import NotFound from "@/views/NotFound.vue";
import ConfigGeneral from "@/views/Settings/GeneralSettings.vue";
import ConfigDevices from "@/views/Settings/DeviceSettings.vue";
import ConfigAudio from "@/views/Settings/AudioSettings.vue";
import ConfigSystem from "@/views/Settings/SystemSettings.vue";
import ConfigConnectivity from "@/views/Settings/ConnectivitySettings.vue";
import Games from "@/views/Games.vue";

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
    {
      name: "Games",
      component: Games,
      path: "/games"
    }
  ]
})

export default router
