<template>
  <div>
    <h4>Vibrationnssensor</h4>
    <div id="slider-control">
      <label>{{ $t("word.sensitivity") }}</label>
      <Slider id="slider" v-model="settings.volume"/>
    </div>
  </div>
</template>

<script setup>
  import {useSettingsStore} from "@/stores/settings.js";

  const settings = useSettingsStore();
</script>

<style scoped>
  #slider-control {
    display: flex;
    align-items: center;
    flex-wrap: wrap;
  }

  #slider {
    margin-left: auto;
    width: 80%;
  }
</style>
