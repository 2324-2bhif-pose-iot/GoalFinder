import { createRouter, createWebHistory } from 'vue-router'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      component: () => import('../views/HomeView.vue')
    },
    {
      path: '/games',
      name: 'games',
      component: () => import('../views/Games/GamesView.vue'),
    },
    {
      path: "/games/shot-challenge",
      name: "shot-challenge",
      component: () => import('../views/Games/ShotChallengeView.vue')
    },
    {
      path: "/games/timed-shots-challenge",
      name: "timed_shots-challenge",
      component: () => import('../views/Games/TimedShotsChallengeView.vue')
    },
    {
      path: '/settings',
      name: 'settings',
      redirect: '/settings/general',
      component: () => import('../views/Settings/SettingsView.vue'),
      children: [
        {
          path: "general",
          name: "general",
          component: () => import('../views/Settings/GeneralSettingsView.vue')
        },
        {
          path: "devices",
          name: "devices",
          component: () => import('../views/Settings/DevicesSettingsView.vue')
        },
        {
          path: "audio",
          name: "audio",
          component: () => import('../views/Settings/AudioSettingsView.vue')
        },
        {
          path: "system",
          name: "system",
          component: () => import('../views/Settings/SystemSettingsView.vue')
        },
      ]
    },
    {
      path: '/about',
      name: 'about',
      component: () => import('../views/AboutView.vue')
    },
      //404 not found
    {
      path: '/:pathMatch(.*)*',
      name: 'not-found',
      component: () => import('../views/NotFoundView.vue')
    }
    /*{
      path: '/about',
      name: 'about',
      // route level code-splitting
      // this generates a separate chunk (About.[hash].js) for this route
      // which is lazy-loaded when the route is visited.
      //component: () => import('../views/AboutView.vue')
    }*/
  ]
})

export default router
