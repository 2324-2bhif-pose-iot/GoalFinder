<script setup>
  import {useSettingsStore} from "@/stores/settings.js";

  const settings = useSettingsStore();
</script>

<template>
  <div class="container">
    <h1 class="mb-3">{{$t("header.about")}}</h1>
    <Card>
      <template #content>
        <div class="row">
          <img src="@/assets/ssa_logo.svg" alt="Smart Sport Assistance" class="logo">
          <img src="@/assets/uni_wien_logo.png" alt="Uni Wien" class="logo">
        </div>
        <img v-if="!settings.enableDarkMode" src="@/assets/htllogo_black.png" alt="HTL Leonding" class="logo">
        <img v-else src="@/assets/htllogo_white.png" alt="HTL Leonding" class="logo">
        <p class="mt-5">
          Dieses Gerät wurde im Zuge des "Smart Sport Assistance" Projekt in Kooperation mit Universität Wien von Schülern der HTBLA Leonding, Klasse 2BHIF, Jahrgang 23/24 entwickelt.
        </p>
        <p class="mt-3">
          <strong>Entwickelt von:</strong>
        </p>
        <ul>
          <li>Omar Al-Desoky</li>
          <li>Rabbi Baysoy</li>
          <li>Alexander Coroi</li>
          <li>Edin Kurtic</li>
        </ul>
      </template>
    </Card>
  </div>
</template>

<style scoped>
  .logo {
    padding: 1rem;
    width: 20rem;
  }
</style>