<script setup lang="ts">

import Button from "@/components/Button.vue";
</script>

<template>
  <div>
    <div id="nav-bar">
      <RouterLink to="/"><h1>Goalfinder</h1></RouterLink>
      <div id="links-container">
        <RouterLink to="/games"><Button class="link">{{ $t("header.games") }}</Button></RouterLink>
        <RouterLink to="/settings"><Button class="link">{{ $t("header.settings") }}</Button></RouterLink>
        <RouterLink to="/about"><Button class="link">{{ $t("header.about") }}</Button></RouterLink>
      </div>
    </div>
  </div>
</template>

<style scoped>
  #nav-bar {
    z-index: 1;
    position: sticky;
    top: 0;
    display: flex;
    justify-content: center;
    align-items: center;
    backdrop-filter: blur(30px) saturate(120%);
    -webkit-backdrop-filter: blur(30px) saturate(120%);
    padding: 0.3rem 0 0.3rem 0;
    border-bottom: 2px solid var(--border-color);
  }

  h1 {
    margin: 0.5rem;
    color: cornflowerblue;
    display: none;
  }

  @media (min-width: 768px) {
    h1 {
      display: block;
    }
  }

  #links-container {
    margin-left: 1rem;
    display: flex;
    gap: 0.5rem;
  }

  .link {
    min-width: 6rem;
    font-weight: bold;
  }

  .router-link-active > Button {
    border-color: cornflowerblue;
  }
</style>