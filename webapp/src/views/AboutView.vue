<script setup>
  import {useSettingsStore} from "@/stores/settings.js";

  const settings = useSettingsStore();
</script>

<template>
  <div class="container">
    <h1 class="mb-3">{{$t("header.about")}}</h1>
    <Card>
      <template #content>
        <img v-if="!settings.enableDarkMode" id="htl-logo" src="@/assets/htllogo_2022_black_v2.png" alt="logo"/>
        <img v-else id="htl-logo" src="@/assets/htllogo_2022_white_v2.png" alt="logo"/>
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
  #htl-logo {
    width: 40%;
  }
</style>