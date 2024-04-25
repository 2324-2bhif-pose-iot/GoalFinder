<script setup>
import { RouterLink, RouterView } from 'vue-router'
import SettingsIcon from "@/components/Icons/SettingsIcon.vue";
import HomeIcon from "@/components/Icons/HomeIcon.vue";
import GamesIcon from "@/components/Icons/GamesIcon.vue";
import InfoIcon from "@/components/Icons/InfoIcon.vue";

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
  <nav class="navbar navbar-expand-lg bg-body-tertiary mb-4">
    <div class="container-fluid">
      <label class="navbar-brand">Goal Finder</label>
      <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
      </button>
      <div class="collapse navbar-collapse" id="navbarSupportedContent">
        <ul class="navbar-nav me-auto mb-2 mb-lg-0">
          <li class="nav-item">
            <router-link to="/" class="nav-link">
              <HomeIcon/>
              Home
            </router-link>
          </li>
          <li class="nav-item">
            <router-link to="/games" class="nav-link">
              <GamesIcon/>
              Games
            </router-link>
          </li>
          <li class="nav-item">
            <router-link to="/settings" class="nav-link">
              <SettingsIcon/>
              Settings
            </router-link>
          </li>
        </ul>
        <router-link to="/about" class="nav-link">
          <InfoIcon/>
        </router-link>
      </div>
    </div>
  </nav>
  <router-view/>
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
