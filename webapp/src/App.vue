<script setup>
import { RouterLink, RouterView } from 'vue-router'
import SettingsIcon from "@/components/Icons/SettingsIcon.vue";
import HomeIcon from "@/components/Icons/HomeIcon.vue";
import GamesIcon from "@/components/Icons/GamesIcon.vue";
import InfoIcon from "@/components/Icons/InfoIcon.vue";
import NavigationBar from "@/components/NavigationBar.vue";

function setTheme() {
  if (window.matchMedia) {
    // Check if the dark-mode Media-Query matches
    if (window.matchMedia("(prefers-color-scheme: dark)").matches) {
      document.documentElement.setAttribute("data-bs-theme", "dark");
    }
  }
}

function main() {
  setTheme();
}

main();
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
