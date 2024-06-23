<script setup>
import { RouterView } from 'vue-router'
import NavigationBar from "@/components/NavigationBar.vue";
import {onMounted, watch} from "vue";
import {useSettingsStore} from "@/stores/settings.js";
import { usePrimeVue } from 'primevue/config';

function setTheme() {
  if (window.matchMedia) {
    // Check if the dark-mode Media-Query matches
    if (window.matchMedia("(prefers-color-scheme: dark)").matches) {
      document.documentElement.setAttribute("data-bs-theme", "dark");
    }
  }
}

setTheme();

const settings = useSettingsStore();

const primeVue = usePrimeVue();

watch(() => settings.enableDarkMode, value => {
  if(value === true) {
    primeVue.changeTheme('aura-light-green', 'aura-dark-green', 'theme-link', () => {});
    localStorage.setItem("enable-dark-mode", "true");
  } else {
    primeVue.changeTheme('aura-dark-green', 'aura-light-green', 'theme-link', () => {});
    localStorage.setItem("enable-dark-mode", "false");
  }
});

onMounted(() => {
  settings.enableDarkMode = localStorage.getItem("enable-dark-mode") === "true";
  settings.loadSettings();
});

</script>

<template>
  <nav>
    <NavigationBar />
  </nav>
  <RouterView/>
</template>

<style scoped>
  .nav-link {
    display: flex;
    align-items: center;
    gap: 0.25rem;
  }

  .nav-link svg {
    width: 1rem;
    height: 1rem;
    margin-top: 0.15rem;
  }
</style>
